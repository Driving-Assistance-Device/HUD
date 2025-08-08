# HUD

</div>

## Environemnt
### HW
- Waveshare ESP32-S3 2.41inch AMOLED Touch Display
  - MCU : ESP32-S3
  - Driver IC : RM690B0
  - Touch IC : FT6336

### SW
- **Squareline Studio* : 1.5.3
- **LVGL** : 8.3.11 

</div>

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
