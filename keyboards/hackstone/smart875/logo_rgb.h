
#pragma once

#include "quantum.h"
#include "color.h"

#define BOX_LED_FIRST 48
#define BOX_LED_NUM   3

#define BOX_LED_MAX_V 200
#define BOX_LED_VAL_STEP 50

#define BOX_LED_MAX_S 40
#define BOX_LED_SPEED_STEP 10

#define BOX_LED_MAX_COLOR 255
#define BOX_LED_COLOR_STEP 32

#define BOX_LED_MAX_EFFECT 4

void logo_rgb_matrix_task(void);

void rgb_box_mode_step(bool back);
void rgb_box_mode_set(uint8_t mode);
uint8_t rgb_box_mode_get(void);

void rgb_box_val_step(bool back);
void rgb_box_val_set(uint8_t percent);
uint8_t rgb_box_val_get(void);

void rgb_box_speed_step(bool back);
void rgb_box_speed_set(uint8_t percent);
uint8_t rgb_box_speed_get(void);

void rgb_box_color_step(bool back);
void rgb_box_color_set(RGB rgb);
RGB rgb_box_color_get(void);

void rgb_box_colored_set(bool enable);
uint8_t rgb_box_colored_get(void);

