RGB_MATRIX_EFFECT(my_cool_effect)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t car_ef_h_1 = 128;
uint8_t car_ef_h_2 = 85;
uint8_t car_ef_h_3 = 128;
uint8_t car_ef_h_4 = 85;

static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV front_hsv = rgb_matrix_config.hsv;

  for (size_t i = 0; i < 4; i++)
  {
    front_hsv.h = g_rgb_timer/(20+i*40) % 256;
    RGB rgb = hsv_to_rgb(front_hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }


  uint8_t center = (g_rgb_timer/100) % 10 + 4;
  HSV hsv = {HSV_GREEN};
  hsv.v = 0;
  if (center == 13) {
    car_ef_h_1 = ((g_rgb_timer/60)+120) % 255;
  }
  hsv.h = car_ef_h_1;
  for (uint8_t i = 4; i < 14; i++) {
    if (i > center ||  center > i + 4) {
        hsv.v = 0;
    } else {
        hsv.v = rgb_matrix_config.hsv.v - rgb_matrix_config.hsv.v * (center-i)*0.2;
    }
    hsv.v = MIN(hsv.v, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  center = (g_rgb_timer/150) % 6 + 14;
  hsv.v = 0;
  if (center == 19) {
    car_ef_h_2 = (g_rgb_timer/60) % 255;
  }
  hsv.h = car_ef_h_2;
  for (uint8_t i = 14; i < 20; i++) {
    if (i > center ||  center > i + 3) {
        hsv.v = 0;
    } else {
        hsv.v = rgb_matrix_config.hsv.v - rgb_matrix_config.hsv.v * (center-i)*0.25;
    }
    hsv.v = MIN(hsv.v, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  center = (g_rgb_timer/150) % 6 + 20;
  hsv.v = 0;
  if (center == 25) {
    car_ef_h_3 = (g_rgb_timer/60) % 255;
  }
  hsv.h = car_ef_h_3;
  for (uint8_t i = 20; i < 26; i++) {
    if (i > center ||  center > i + 3) {
        hsv.v = 0;
    } else {
        hsv.v = rgb_matrix_config.hsv.v - rgb_matrix_config.hsv.v * (center-i)*0.25;
    }
    hsv.v = MIN(hsv.v, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  center = (g_rgb_timer/100) % 10 + 26;
  hsv.v = 0;
  if (center == 35) {
    car_ef_h_4 = ((g_rgb_timer/60)+120) % 255;
  }
  hsv.h = car_ef_h_4;
  for (uint8_t i = 26; i < 36; i++) {
    if (i > center ||  center > i + 4) {
        hsv.v = 0;
    } else {
        hsv.v = rgb_matrix_config.hsv.v - rgb_matrix_config.hsv.v * (center-i)*0.2;
    }
    hsv.v = MIN(hsv.v, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }

  return rgb_matrix_check_finished_leds(led_max);
}

#endif
