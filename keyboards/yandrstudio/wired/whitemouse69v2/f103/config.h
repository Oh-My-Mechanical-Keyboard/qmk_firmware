#pragma once
#include "config_common.h"

/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN B15
#    define RGBLED_NUM 69
#    define DRIVER_LED_TOTAL RGBLED_NUM

#   define WS2812_SPI SPID2 // default: SPID1
#   define WS2812_SPI_MOSI_PAL_MODE 5
#   define WS2812_SPI_USE_CIRCULAR_BUFFER

#endif


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B15
#    define RGBLED_NUM 69
#    define DRIVER_LED_TOTAL RGBLED_NUM

#   define WS2812_SPI SPID2 // default: SPID1
#   define WS2812_SPI_MOSI_PAL_MODE 5
#   define WS2812_SPI_USE_CIRCULAR_BUFFER

#endif



