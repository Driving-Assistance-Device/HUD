# HUD
<br>

This project receives **lane deviation** and **inter-vehicle distance** data from a Raspberry Pi, displays the information on an ESP32-based display module, and implements a **HUD** (Head-Up Display) using a combiner method.

<br>

### Key Features
- Real-time visualization of lane deviation and following distance  
- Display output using ESP32 and LVGL  
- HUD implementation via combiner reflection  
- Touch-based UI with calibration functionality

<br>

## HW
- Waveshare ESP32-S3 2.41inch AMOLED Touch Display
  - MCU : ESP32-S3
  - Driver IC : RM690B0
  - Touch IC : FT6336

## SW
- **Squareline Studio** : 1.5.3
- **LVGL** : 8.3.11
- **IDE** : PlatformIO

<br>

## System Overview
<p align="center">
  <img width="1000" height="430" alt="Image" src="https://github.com/user-attachments/assets/f3e229a8-6b9c-4136-841c-ce285a8fbed9" />
</p>
<br>

## HUD usage example

<p align="center">
  <img src="https://github.com/user-attachments/assets/2d93b3bb-a523-4cbf-9893-10645ae0ac8a" width="550"/>
</p>

<br>

<table align="center">
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/b2dacc19-2f68-4626-9bfa-b7ea40e03f93" alt="Offset calibration" width="250"/><br>
      <strong>Offset calibration mode</strong><br>
      <strong>&nbsp;</strong>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/2a4f5e9c-7cb1-4764-a614-49db047172ba" alt="Left deviation" width="250"/><br>
      <strong>Normal driving</strong><br>
      <strong>Safe distance</strong>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/b22a9c84-4e58-432c-bb89-f36f919f3275" alt="Right deviation" width="250"/><br>
      <strong>Right deviation</strong><br>
      <strong>Dangerous distance</strong>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/822964e1-8c0f-4c0b-8650-e53816e4f46b" alt="Normal driving" width="250"/><br>
      <strong>Left deviation</strong><br>
      <strong>Warning distance</strong>
    </td>
  </tr>
</table>

<br>


## Project structure

```markdown
HUD
┣ HUD
┃ ┗ lib
┃ ┃ ┗ UI
┃ ┃   ┗ ...
┃ ┗ src
┃ ┃ ┣ esp_lcd_sh8601.c
┃ ┃ ┣ esp_lcd_sh8601.h
┃ ┃ ┣ esp_lcd_touch.c
┃ ┃ ┣ esp_lcd_touch.h
┃ ┃ ┣ esp_lcd_touch_ft5x06.c
┃ ┃ ┣ esp_lcd_touch_ft5x06.h
┃ ┃ ┣ hudCtrl.cpp
┃ ┃ ┣ hudCtrl.h
┃ ┃ ┗ main.cpp
┃ ┗ platformio.ini
┃
┣ libraries
┃ ┗ ESP32-audioI2S-master
┃ ┗ lvgl
┃ ┗ lv_conf.h
┃
┣ HUD_amoled_v1
┃ ┗ ...
┃
┗ README.md
```
