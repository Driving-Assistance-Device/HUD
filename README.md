# HUD
<br>

This project receives **lane deviation** and **inter-vehicle distance** data from a Raspberry Pi, displays the information on an ESP32-based display module, and implements a **HUD** (Head-Up Display) using a combiner method.

<div style="display: flex; justify-content: center; gap: 20px;">
  <img src="https://github.com/user-attachments/assets/2d93b3bb-a523-4cbf-9893-10645ae0ac8a" width="550">
  <img src="https://github.com/user-attachments/assets/a217981c-fa00-4a64-a355-d3e4d62f6005" width="410">
</div>

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

<br>

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
      <img src="https://github.com/user-attachments/assets/f685b994-e12f-44f0-b47d-d916f0575975" alt="Normal driving" width="250"/><br>
      <strong>Left deviation</strong><br>
      <strong>Warning distance</strong>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/6051b6ee-5995-4cbf-81b5-cb8293f42285" alt="Normal driving" width="250"/><br>
      <strong>Right deviation</strong><br>
      <strong>Dangerous distance</strong>
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
