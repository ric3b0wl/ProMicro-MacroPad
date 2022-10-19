# De-MacroPad
This is a Pro-Micro ATmega32U4 Macro-Pad project.

>There is possibility of changing MCU in the future

Version 2.0

Version 2.1

## PlateformIO & libraries
- chris--a/Keypad@^3.1.1
- paulstoffregen/Encoder@^1.4.2
- thomasfredericks/Bounce2@^2.71
- nicohood/HID-Project@^2.8.4
- adafruit/Adafruit SSD1306@^2.5.7
- adafruit/Adafruit GFX Library@^1.11.3

## CAD
[CAD](https://github.com/ric3b0wl/ProMirco-MacroPad_v2.1/tree/main/CAD) dir contains 3D model for the enclosure.

## Issues
Could not make Rotary Encoder to work since currently using Pin **2** and **3** on the **ATmega32U4** for I$^{2}$C connection for the OLED display

There two option:
- [ ] Switching MCU with available pins
- [ ] Find a polling method for the rotary encoder

>This project was heavily inspired by project from **tinyboatproductions** from [instructables](https://www.instructables.com/Programmable-Macropad-V2/).
