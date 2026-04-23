#include <Arduino_GFX_Library.h>
#include <SPI.h>

// =====================================================
// STACKSWORTHmini
// Waveshare ESP32-C6-LCD-1.47 base sketch
// ST7789 + Arduino_GFX
// Portrait layout with placeholder values
// =====================================================

// -------- Waveshare ESP32-C6-LCD-1.47 pins --------
#define TFT_MOSI 6
#define TFT_SCLK 7
#define TFT_CS   14
#define TFT_DC   15
#define TFT_RST  21
#define TFT_BL   22
#define RGB_CTRL 8

// -------- Display size --------
#define SCREEN_WIDTH  172
#define SCREEN_HEIGHT 320

// -------- Colors (RGB565) --------
#define SW_BLACK      0x0000
#define SW_WHITE      0xFFFF
#define SW_ORANGE     0xFD20
#define SW_CYAN       0x07FF
#define SW_GREEN      0x07E0
#define SW_RED        0xF800
#define SW_GREY       0x8410
#define SW_DARKGREY   0x4208

// -------- Display driver --------
// ST7789, 172x320, no MISO used
Arduino_DataBus *bus = new Arduino_SWSPI(
  GFX_NOT_DEFINED, // DC handled by display object
  TFT_CS,
  TFT_SCLK,
  GFX_NOT_DEFINED, // MISO not used
  TFT_MOSI
);

Arduino_GFX *gfx = new Arduino_ST7789(
  bus,
  TFT_RST,
  0,     // rotation handled later
  true,  // IPS
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  34,    // col offset
  0,     // row offset
  34,    // col offset 2
  0      // row offset 2
);

// -------- Placeholder values --------
String displayPrice = "$143,221";
String displayBlock = "893245";
String displayTime  = "8:42 PM";
String footerText   = "BOOT SCREEN";

// -------- Timing --------
unsigned long lastBlink = 0;
bool ledState = false;

// =====================================================
// Helpers
// =====================================================
void setStatusLED(bool on)
{
  digitalWrite(RGB_CTRL, on ? HIGH : LOW);
}

void pulseLED()
{
  if (millis() - lastBlink > 700)
  {
    lastBlink = millis();
    ledState = !ledState;
    setStatusLED(ledState);
  }
}

void drawCenteredText(const String &text, int y, uint16_t color, uint8_t size)
{
  int16_t x1, y1;
  uint16_t w, h;
  gfx->setTextSize(size);
  gfx->getTextBounds(text, 0, y, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  gfx->setCursor(x, y);
  gfx->setTextColor(color);
  gfx->print(text);
}

void drawHeader()
{
  gfx->drawRoundRect(8, 10, 156, 38, 8, SW_ORANGE);

  gfx->setTextColor(SW_WHITE);
  gfx->setTextSize(1);
  gfx->setCursor(22, 16);
  gfx->print("STACKSWORTH");

  gfx->setTextColor(SW_CYAN);
  gfx->setTextSize(2);
  gfx->setCursor(48, 28);
  gfx->print("mini");
}

void drawMetricCard(int x, int y, int w, int h, const char *label, const String &value, uint16_t borderColor)
{
  gfx->drawRoundRect(x, y, w, h, 10, borderColor);
  gfx->drawRoundRect(x + 1, y + 1, w - 2, h - 2, 10, SW_DARKGREY);

  gfx->setTextColor(borderColor);
  gfx->setTextSize(1);
  gfx->setCursor(x + 10, y + 8);
  gfx->print(label);

  gfx->setTextColor(SW_WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(x + 10, y + 30);
  gfx->print(value);
}

void drawFooter(const String &text)
{
  gfx->drawFastHLine(12, 292, 148, SW_DARKGREY);
  gfx->setTextColor(SW_GREY);
  gfx->setTextSize(1);
  gfx->setCursor(26, 302);
  gfx->print(text);
}

void drawBootScreen()
{
  gfx->fillScreen(SW_BLACK);
  gfx->drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SW_DARKGREY);

  drawCenteredText("STACKSWORTH", 60, SW_ORANGE, 2);
  drawCenteredText("mini",        95, SW_CYAN,   3);
  drawCenteredText("Starting...", 150, SW_WHITE, 2);

  drawFooter("Bitcoin's Pulse");
}

void drawMainScreen()
{
  gfx->fillScreen(SW_BLACK);

  drawHeader();
  drawMetricCard(12, 58, 148, 64, "PRICE", displayPrice, SW_ORANGE);
  drawMetricCard(12, 132, 148, 64, "BLOCK", displayBlock, SW_CYAN);
  drawMetricCard(12, 206, 148, 64, "TIME",  displayTime, SW_WHITE);
  drawFooter(footerText);
}

// =====================================================
// Setup
// =====================================================
void setup()
{
  Serial.begin(115200);
  delay(200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  pinMode(RGB_CTRL, OUTPUT);
  digitalWrite(RGB_CTRL, LOW);

  if (!gfx->begin())
  {
    Serial.println("Display begin failed!");
    while (1)
    {
      pulseLED();
      delay(10);
    }
  }

  // Portrait
  gfx->setRotation(0);

  drawBootScreen();
  delay(1200);

  footerText = "STACKSWORTHmini";
  drawMainScreen();

  // base indicator
  digitalWrite(RGB_CTRL, HIGH);
}

// =====================================================
// Loop
// =====================================================
void loop()
{
  pulseLED();

  // Later:
  // - fetch price from SatoNak
  // - fetch block from SatoNak
  // - fetch NTP time
  // - green/red price change logic
  // - blue flash on new block
}
