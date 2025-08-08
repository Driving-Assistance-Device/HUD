#ifndef __HUDCTRL_H__
#define __HUDCTRL_H__

#pragma once
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif



//--------------------------------------------------------------------------------
// Data struct
//--------------------------------------------------------------------------------

typedef struct {
    int32_t left;
    int32_t right;
} laneLimit;

extern laneLimit g_laneLimit;


//--------------------------------------------------------------------------------
// 
//--------------------------------------------------------------------------------

// NVS
void save_lane_limit_to_nvs(laneLimit *limit);

void load_lane_limit_from_nvs(laneLimit *limit);


/// HUD run
void HUD_run(float x_offset, float tSigST);


// Distance warning
void dist_warn(float dist);


// Calibration
void start_calibration();

void stop_calibration();

void update_calibration_ui();

void set_lane_left();

void set_lane_right();

void save_calibration();



#ifdef __cplusplus
}
#endif

#endif
