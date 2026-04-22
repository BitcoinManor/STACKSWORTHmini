# STACKSWORTHmini

A compact Bitcoin display built on the Waveshare ESP32-C6 1.47" board, designed to show live Bitcoin price, block height, time, and simple status visuals in the STACKSWORTH style.

## Overview

STACKSWORTHmini is a small and affordable Bitcoin display created as part of the broader STACKSWORTH product lineup.

The goal of this project is to build a cute, desk-friendly Bitcoin companion that delivers essential information at a glance, while staying simple enough to be fast to build, easy to flash, and affordable to bring to market.

The first version is focused on a clean portrait layout showing:

- Bitcoin Price
- Block Height
- Time

Future improvements may include:

- Live data from the SatoNak API
- RGB LED status feedback
- Green/red price movement indication
- Blue flash on new block detection
- Refined screen themes and animations
- Market-ready enclosure and branding

## Hardware

This project is being developed for the:

- Waveshare ESP32-C6 1.47" Display Development Board
- Resolution: 172 × 320
- Display orientation: Portrait
- Display driver: ST7789
- Connectivity: Wi-Fi / BLE
- Onboard RGB LED

## Software Direction

STACKSWORTHmini is being built using:

- Arduino IDE
- TFT_eSPI
- ESP32 board support
- SatoNak API integration for Bitcoin data

## Project Status

This repository is in early development.

The current focus is:

1. Confirm screen initialization and orientation
2. Build the first clean STACKSWORTHmini main screen
3. Add placeholder values for layout testing
4. Integrate live Bitcoin data afterward

## Product Vision

STACKSWORTHmini is intended to become a small impulse-buy Bitcoin display that complements the larger STACKSWORTH lineup such as Matrix and Spark.

It is designed to be:

- Simple
- Cute
- Affordable
- Fast to build
- Instantly recognizable as a STACKSWORTH product

## Author

Built by [BitcoinManor.com](https://bitcoinmanor.com)

Part of the STACKSWORTH lineup.
