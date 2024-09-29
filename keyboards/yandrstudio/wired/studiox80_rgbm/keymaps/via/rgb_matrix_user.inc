RGB_MATRIX_EFFECT(my_cool_effect)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  static uint32_t center_timer = 0;
  static uint8_t center = 0;
  HSV hsv = {HSV_GREEN};
  hsv.v = 0;
  if (timer_elapsed32(center_timer) > 100) {
    center += 1;
    center %= 255;
    center_timer = timer_read32();
  }
  dprintf("gtime: %ld, time %d\n", g_rgb_timer, time);
  for (uint8_t i = 0; i < 4; i++) {
    if (center%4 == i) {
        hsv.v = rgb_matrix_config.hsv.v;
    } else {
        hsv.v = 0;
    }
    hsv.v = MIN(hsv.v, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif
