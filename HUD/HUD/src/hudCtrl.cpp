#include "hudCtrl.h"
#include <ui.h>
#include "nvs_flash.h"
#include "nvs.h"



//--------------------------------------------------------------------------------
// Define
//--------------------------------------------------------------------------------

#define OFFSET_LIMIT 120   // input offset limit
#define SENSE_RANGE 50


laneLimit g_laneLimit = { -130, 130 };   // Default

typedef struct {
    bool active;
    float current_offset;
    int temp_setL, temp_setR;
    bool has_setL, has_setR;
} calibration_t;


static calibration_t cal = {0};


static lv_style_t laneL_style, laneR_style, dist_style;
static bool styles_initialized = false;
static bool dist_style_initialized = false;


//--------------------------------------------------------------------------------
// NVS
//--------------------------------------------------------------------------------

void save_lane_limit_to_nvs(laneLimit *limit)
{
    nvs_handle_t nvs_handle;
    nvs_open("storage", NVS_READWRITE, &nvs_handle);
    nvs_set_blob(nvs_handle, "lane_limit", limit, sizeof(laneLimit));
    nvs_commit(nvs_handle);
    nvs_close(nvs_handle);
}


void load_lane_limit_from_nvs(laneLimit *limit)
{
    nvs_handle_t nvs_handle;
    size_t required_size = sizeof(laneLimit);
    
    if (nvs_open("storage", NVS_READONLY, &nvs_handle) == ESP_OK)
    {
        if (nvs_get_blob(nvs_handle, "lane_limit", limit, &required_size) != ESP_OK)
        {
            limit->left = -130;
            limit->right = 130;
        }
        nvs_close(nvs_handle);
    }
}


//--------------------------------------------------------------------------------
// HUD run
//--------------------------------------------------------------------------------

void HUD_run(float x_offset, float tSigST)
{
  int center = (g_laneLimit.left + g_laneLimit.right) / 2;

  lv_color_t green = lv_color_make(0, 255, 0);
  lv_color_t black = lv_color_make(0, 0, 0);
  lv_color_t red_l, red_r;

  // While calibration
  if (cal.active)
  {
    cal.current_offset = x_offset;
    update_calibration_ui();
    return;
  }

  // Move car
  float move_offset = x_offset - center;
  if (move_offset > OFFSET_LIMIT) move_offset = OFFSET_LIMIT;
  if (move_offset < -OFFSET_LIMIT) move_offset = -OFFSET_LIMIT;

  lv_obj_set_x(ui_vehicle, move_offset);
  lv_obj_set_x(ui_dist, move_offset);

  // Init LVGL style
  if (!styles_initialized)
  {
    lv_style_init(&laneL_style);
    lv_style_set_img_recolor_opa(&laneL_style, LV_OPA_COVER);
    lv_obj_add_style(ui_laneL, &laneL_style, LV_PART_MAIN);

    lv_style_init(&laneR_style);
    lv_style_set_img_recolor_opa(&laneR_style, LV_OPA_COVER);
    lv_obj_add_style(ui_laneR, &laneR_style, LV_PART_MAIN);

    styles_initialized = true;
  }

  // Turn signal
  if (tSigST == -1.0f)
  {
    red_l = green;
    red_r = black;
  }
  else if (tSigST == 1.0f)
  {
    red_l = black;
    red_r = green;
  }
  else
  {
    if (move_offset < 0)
    {
      float ratio = (float)LV_ABS(move_offset) / SENSE_RANGE;
      if (ratio > 1.0f) ratio = 1.0f;
      int red_val = 255 * ratio * ratio;
      int green_val = 255 - red_val;
      red_l = lv_color_make(red_val, green_val, 0);
      red_r = green;
    }
    else if (move_offset > 0)
    {
      float ratio = (float)LV_ABS(move_offset) / SENSE_RANGE;
      if (ratio > 1.0f) ratio = 1.0f;
      int red_val = 255 * ratio * ratio;
      int green_val = 255 - red_val;
      red_r = lv_color_make(red_val, green_val, 0);
      red_l = green;
    }
    else {
      red_l = green;
      red_r = green;
    }
  }

  // Update UI
  lv_style_set_img_recolor(&laneL_style, red_l);
  lv_style_set_img_recolor(&laneR_style, red_r);
  lv_obj_refresh_style(ui_laneL, LV_PART_MAIN, LV_STYLE_IMG_RECOLOR);
  lv_obj_refresh_style(ui_laneR, LV_PART_MAIN, LV_STYLE_IMG_RECOLOR);
}


//--------------------------------------------------------------------------------
// Distance warning
//--------------------------------------------------------------------------------

void dist_warn(float dist)
{

  lv_color_t color;


  if ( dist == 2 ) {
    color = lv_color_make(255, 0, 0);  //red
  }
  else if ( dist == 1 ) {
    color = lv_color_make(255, 165, 0);  // orange
  }
  else {
    color = lv_color_make(0, 255, 0);  // green
  }


  if (!dist_style_initialized) {
    lv_style_init(&dist_style);
    lv_style_set_img_recolor_opa(&dist_style, LV_OPA_COVER);
    lv_obj_add_style(ui_dist, &dist_style, LV_PART_MAIN);
    dist_style_initialized = true;
  }

  lv_style_set_img_recolor(&dist_style, color);
  lv_obj_refresh_style(ui_dist, LV_PART_MAIN, LV_STYLE_IMG_RECOLOR);
}


//--------------------------------------------------------------------------------
// Calibration
//--------------------------------------------------------------------------------

void start_calibration()
{
    cal.active = true;
    cal.has_setL = false;
    cal.has_setR = false;
    
    // Cur limit
    lv_label_set_text_fmt(ui_LabelCurL, "%d", g_laneLimit.left);
    lv_label_set_text_fmt(ui_LabelCurR, "%d", g_laneLimit.right);
    
    // Init setting data
    lv_label_set_text(ui_LabelSetL, "---");
    lv_label_set_text(ui_LabelSetR, "---");
}


void stop_calibration()
{
    cal.active = false;
}


void update_calibration_ui()
{
    if (!cal.active) return;
    
    // Print cur offset
    lv_label_set_text_fmt(ui_LabelOffset, "%d", (int)cal.current_offset);
}


void set_lane_left()
{
    if (!cal.active) return;
    
    cal.temp_setL = (int)cal.current_offset;
    cal.has_setL = true;
    lv_label_set_text_fmt(ui_LabelSetL, "%d", cal.temp_setL);
}


void set_lane_right()
{
    if (!cal.active) return;
    
    cal.temp_setR = (int)cal.current_offset;
    cal.has_setR = true;
    lv_label_set_text_fmt(ui_LabelSetR, "%d", cal.temp_setR);
}


void save_calibration()
{
    if (!cal.active || !cal.has_setL || !cal.has_setR) return;
    
    g_laneLimit.left = cal.temp_setL;
    g_laneLimit.right = cal.temp_setR;
    
    save_lane_limit_to_nvs(&g_laneLimit);
    
    // Update UI
    lv_label_set_text_fmt(ui_LabelCurL, "%d", g_laneLimit.left);
    lv_label_set_text_fmt(ui_LabelCurR, "%d", g_laneLimit.right);
}
