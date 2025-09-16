/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAAB2
#define DEVICE_VER 0x0001
#define MANUFACTURER "ZHOU_Y&R"
#define PRODUCT "zhou68ble"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                         0      1       2       3       4       5       6       7       8       9       10      11      12      13      14   15
#define MATRIX_COL_PINS { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, C14, C13 }
#define MATRIX_ROW_PINS { A4, A5, A3, B12, B10 }

#define USE_BOTH_595_AND_GPIO
#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                           c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14   c15
#define MATRIX_OF_74HC595 {{ 0x40, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00 }}


#define SPI_SCK_PIN_OF_595 A8
#define SPI_MOSI_PIN_OF_595 B14
#define SPI_74HC595_CS B15

// enable the nkro when using the VIA.
#define FORCE_NKRO

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define WS2812_DI_PIN B13
#    define RGB_MATRIX_LED_COUNT 68

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#    define RGB_MATRIX_STARTUP_VAL 200
#    define RGBLIGHT_VAL_STEP 8
#    define RGB_MATRIX_CENTER { 112, 32 }

#    define RGB_MATRIX_KEYPRESSES
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define ENABLE_RGB_MATRIX_SPLASH
#    define ENABLE_RGB_MATRIX_MULTISPLASH
#    define ENABLE_RGB_MATRIX_SOLID_SPLASH
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    define ENABLE_RGB_MATRIX_DIGITAL_RAIN

#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_VAL
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL

#    define ENABLE_RGB_MATRIX_DUAL_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define ENABLE_RGB_MATRIX_RAINDROPS

#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN
/*蓝牙下存在问题*/
// #    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL

#    define RGB_MATRIX_LAYERS
#    define RGB_MATRIX_LAYER_BLINK
#    define RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
#    define RGB_MATRIX_LAYERS_RETAIN_VAL
#    define RGB_MATRIX_MAX_LAYERS 21

#endif

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B13
#    define RGBLED_NUM 68
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_ANIMATIONS

#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL+4)

#endif

#ifdef WS2812_DRIVER_PWM

#    define WS2812_PWM_DRIVER PWMD1  // default: PWMD2
#    define WS2812_PWM_CHANNEL 1  // default: 2
#    define WS2812_PWM_PAL_MODE 1  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM STM32_DMA2_STREAM5  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 6  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_PWM_COMPLEMENTARY_OUTPUT
#    define WS2812_PWM_TARGET_PERIOD 800000

#endif

#define TAP_HOLD_CAPS_DELAY 200

// for ble
#define USE_MUILT_THREAD_FOR_BLE
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52WKPin A1
#define BIUNRF52ResetPin A2
// disable rgb when using ble
#define RGB_BLE_SW A6
#define RGB_EN_STATE 1

// enable ble indicator
#define BleGetChannleEnable

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN A7

// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN B1
#define USE_BAT_MAP_V1

/* W25QXX */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B6
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SECTOR_SIZE (4 * 1024)
#define EXTERNAL_FLASH_BLOCK_SIZE (64 * 1024)
#define EXTERNAL_FLASH_ADDRESS_SIZE 3
/* w25q32*/
#define EXTERNAL_FLASH_SIZE (4 * 1024 * 1024)
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 1

#define EXTERNAL_FLASH_SPI_TIMEOUT 50

// Wear-leveling driver configuration
// #define WEAR_LEVELING_LOGICAL_SIZE 1024
// #define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)

/* ST7735 TFT*/
// reset
#define ST7735_RES_PIN B8
// display/command rs pin
#define ST7735_DC_PIN B9
// chip select
#define ST7735_CS_PIN A15
// LED Anode
#define ST7735_BLK_PIN B7
// Byte Order
#define TFT_COLOR_BYTE_ORDER TFT_COLOR_BYTE_ORDER_BGR
// #define TFT_COLOR_BYTE_ORDER TFT_COLOR_BYTE_ORDER_RGB

#define ST7735S_NO_AUTOMATIC_VIEWPORT_OFFSETS

/* SPI For Flash and TFT*/
#define SPI_DRIVER SPID3
#define SPI_SCK_PIN B3
#define SPI_SCK_PAL_MODE 6
#define SPI_MOSI_PIN B5
#define SPI_MOSI_PAL_MODE 6
#define SPI_MISO_PIN B4
#define SPI_MISO_PAL_MODE 6


#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0

#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_CONCURRENT_ANIMATIONS 1
#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 2048
#define QUANTUM_PAINTER_DEBUG
// #define DEBUG_FLASH_SPI_OUTPUT

#define QP_STREAM_HAS_SPI_FLASH_IO
#define QP_USE_MULTI_THREAD

#define GPIO_INPUT_PIN_DELAY 4
#define MATRIX_IO_DELAY 2
