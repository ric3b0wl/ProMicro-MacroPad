# De-MacroPad
This is a Pro-Micro ATmega32U4 Macro-Pad project.

>There is possibility of changing MCU in the future

## Version
### V2.0
<img src="https://github.com/ric3b0wl/De-MacroPad/blob/main/IMG/2-0_0.jpg" width=30% height=30%>
<img src="https://github.com/ric3b0wl/De-MacroPad/blob/main/IMG/2-0_1.jpg" width=30% height=30%>

### V2.1
<img src="https://github.com/ric3b0wl/De-MacroPad/blob/main/IMG/2-1_0.jpg" width=30% height=30%>
<img src="https://github.com/ric3b0wl/De-MacroPad/blob/main/IMG/2-1_1.jpg" width=30% height=30%>

## PlateformIO & libraries
- chris--a/Keypad@^3.1.1
- paulstoffregen/Encoder@^1.4.2
- thomasfredericks/Bounce2@^2.71
- nicohood/HID-Project@^2.8.4
- adafruit/Adafruit SSD1306@^2.5.7
- adafruit/Adafruit GFX Library@^1.11.3

## CAD
[CAD](https://github.com/ric3b0wl/ProMirco-MacroPad_v2.1/tree/main/CAD) dir contains Version2.1 STL files for 3D printable enclosure.

## Issues
Could not make Rotary Encoder to work since currently using Pin **2** and **3** on the **ATmega32U4** for I$^{2}$C connection for the OLED display

There two option:
- [ ] Switching MCU with available pins
  - [ ] Will need to creat a custom PCB board design to replace [no-solder-pcb](https://github.com/ric3b0wl/ProMirco-MacroPad_v2.1/tree/main/CAD/no-solder-pcb.stl)
- [ ] Find a polling method for the rotary encoder

>This project was heavily inspired by project from **tinyboatproductions** from [instructables](https://www.instructables.com/Programmable-Macropad-V2/).
