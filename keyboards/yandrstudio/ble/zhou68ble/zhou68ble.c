/* Copyright 2022 JasonRen(biu)
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
#include "zhou68ble.h"

#define YR_DEBUG_DIS_QP TRUE

#if (YR_DEBUG_DIS_QP == TRUE)
#    include "qp.h"
#    include "color.h"
#    include "print.h"
#    include <string.h>
#    include "xiongmaotou_st7735s.qgf.h"
#    include "raw_hid.h"
#    include "flash_spi.h"
#    include "spi_master.h"
#endif

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#    include "rgb_matrix_layer.h"

led_config_t g_led_config = {{{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}, {44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, NO_LED, NO_LED, NO_LED}, {45, 46, 47, 48, 49, 50, 51, NO_LED, 52, 53, 54, 55, 56, NO_LED, 57, NO_LED}, {67, 66, NO_LED, NO_LED, NO_LED, NO_LED, 65, 64, 63, 62, NO_LED, NO_LED, 61, 60, 59, 58}},
                             {{224, 0}, {209, 0}, {194, 0}, {179, 0}, {164, 0}, {149, 0}, {134, 0}, {119, 0}, {105, 0}, {90, 0}, {75, 0}, {60, 0}, {45, 0}, {30, 0}, {15, 0}, {0, 0}, {0, 16}, {15, 16}, {30, 16}, {45, 16}, {60, 16}, {75, 16}, {90, 16}, {105, 16}, {119, 16}, {134, 16}, {149, 16}, {164, 16}, {179, 16}, {194, 16}, {209, 16}, {224, 16}, {179, 32}, {164, 32}, {149, 32}, {134, 32}, {119, 32}, {105, 32}, {90, 32}, {75, 32}, {60, 32}, {45, 32}, {30, 32}, {15, 32}, {0, 32}, {0, 48}, {15, 48}, {30, 48}, {45, 48}, {60, 48}, {75, 48}, {90, 48}, {119, 48}, {134, 48}, {149, 48}, {164, 48}, {179, 48}, {209, 48}, {224, 64}, {209, 64}, {194, 64}, {179, 64}, {134, 64}, {119, 64}, {105, 64}, {90, 64}, {15, 64}, {0, 64}},
                             {// LED Index to Flag
                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

// rgb matrix layer

const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({17, 1, HSV_GREEN}); // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({18, 1, HSV_GREEN}); // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({19, 1, HSV_GREEN}); // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({20, 1, HSV_GREEN}); // 3
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({17, 1, HSV_BLUE});  // 4
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({18, 1, HSV_BLUE});  // 5
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({19, 1, HSV_BLUE});  // 6
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({20, 1, HSV_BLUE});  // 7
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({42, 1, HSV_BLUE});  // 8
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({42, 1, HSV_GREEN}); // 9
const rgb_matrix_adv_layer_segment_t PROGMEM capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({44, 1, HSV_RED});   // 10
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({14, 1, HSV_RED});   // 11
const rgb_matrix_adv_layer_segment_t PROGMEM bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({13, 2, HSV_GREEN}); // 12
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({12, 3, HSV_GREEN}); // 13
const rgb_matrix_adv_layer_segment_t PROGMEM bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({11, 4, HSV_GREEN}); // 14
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({10, 5, HSV_GREEN}); // 15
const rgb_matrix_adv_layer_segment_t PROGMEM bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({9, 6, HSV_GREEN});  // 16
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({8, 7, HSV_GREEN});  // 17
const rgb_matrix_adv_layer_segment_t PROGMEM bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({7, 8, HSV_GREEN});  // 18
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({6, 9, HSV_GREEN});  // 19
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({5, 10, HSV_GREEN}); // 20

const rgb_matrix_adv_layer_segment_t *const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(bt_conn1_layer, bt_conn2_layer, bt_conn3_layer, bt_conn4_layer, bt_pair1_layer, bt_pair2_layer, bt_pair3_layer, bt_pair4_layer, usb_pair_layer, usb_conn_layer, capslock_layer, bat_10_layer, bat_20_layer, bat_30_layer, bat_40_layer, bat_50_layer, bat_60_layer, bat_70_layer, bat_80_layer, bat_90_layer, bat_100_layer);

void rgb_matrix_adv_unblink_all_but_caps_bat_layer(void) {
    for (uint8_t i = 0; i < 10; i++) {
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_batlayer_but_one_layer(uint8_t l) {
    for (uint8_t i = 11; i < 21; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_but_layer(uint8_t l) {
    for (uint8_t i = 0; i < 21; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

extern rgb_task_states rgb_task_state;

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(10, host_keyboard_led_state().caps_lock);
    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}

#    ifdef BIU_BLE5_ENABLE
bool ble_led_update_kb(uint8_t channle, uint8_t state) {
    /*
    _ble_channle:
        BLE: 0-7
        USB: 0xa
        2G4: 0xb
    _ble_state:
        NRF_WORKING：1
        NRF_ADVING_NO_WL：8
        NRF_ADVING_WITH_WL：7

        USB_ACTIVE: 0xA0
        USB_DISCONNECTION：0xA1
    */
    rgb_matrix_adv_unblink_all_but_caps_bat_layer();
    if (channle == 0xa) {
        if (state != 0xa0) {
            rgb_matrix_adv_blink_layer_repeat(8, 500, 8);
        } else {
            rgb_matrix_adv_blink_layer_repeat(9, 1000, 1);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgb_matrix_adv_blink_layer_repeat(channle % 4, 500, 8);
        } else if (state == 8) {
            rgb_matrix_adv_blink_layer_repeat(channle % 4 + 4, 200, 20);
        } else if (state == 1) {
            rgb_matrix_adv_blink_layer_repeat(channle % 4, 3000, 1);
        }
    }
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}
#    endif
#endif

#if (YR_DEBUG_DIS_QP == TRUE)

// Initialisation
static painter_device_t       lcd;
static painter_image_handle_t my_image = NULL;
static deferred_token         my_anim  = INVALID_DEFERRED_TOKEN;
// static bool my_anim;
static bool lcd_power_flag      = false;
static bool is_in_flash_writing = false;
static bool use_default_ui      = false;

#    define IMG_BUFFER_MAX_LEN 10240

uint8_t head_buf[28];
uint8_t img_buf[IMG_BUFFER_MAX_LEN + 5];

flash_status_t fa;
uint8_t        page_buffer[EXTERNAL_FLASH_PAGE_SIZE + 5];

#    ifndef BACKLIGHT_ENABLE
#        define LCD_BLK_ON writePinHigh(ST7735_BLK_PIN)
#        define LCD_BLK_OFF writePinLow(ST7735_BLK_PIN)
#    else
#        define LCD_BLK_ON backlight_enable()
#        define LCD_BLK_OFF backlight_disable()
#    endif

static void inline show_default_img(void) {
    if (my_anim != INVALID_DEFERRED_TOKEN) {
        qp_stop_animation(my_anim);
    }
    my_image = qp_load_image_mem_force(gfx_xiongmaotou_st7735s);
    if (my_image != NULL) {
        my_anim = qp_drawimage(lcd, 0, 0, my_image);
    } else {
        qp_rect(lcd, 0, 0, 79, 159, HSV_PINK, true);
    }
}

static void init_lcd_once(void) {
    // Initialise the LCD
    lcd             = qp_st7735s_make_spi_device(80, 160, ST7735_CS_PIN, ST7735_DC_PIN, ST7735_RES_PIN, 1, 0);
    bool rec        = qp_init(lcd, 0);
    int  retry_time = 0;
    while (rec == 0 && retry_time < 10) {
        retry_time++;
        rec = qp_init(lcd, 0);
        wait_ms(100);
    }

    qp_set_viewport_offsets(lcd, 26, 1);

    if (!rec) {
        lcd_power_flag = false;
        use_default_ui = true;
        lcd = NULL;
    } else {
        // Turn on the LCD
        // clear the display
        qp_rect(lcd, 0, 0, 79, 159, HSV_BLACK, true);

        lcd_power_flag = true;

        // init gif
        my_image = qp_load_image_spi_flash(head_buf, img_buf, IMG_BUFFER_MAX_LEN, 0);
        if (my_image != NULL) {
            my_anim        = qp_animate(lcd, 0, 0, my_image);
            use_default_ui = false;
        } else {
            use_default_ui = true;
            show_default_img();
        }
    }
}

#endif

void keyboard_post_init_kb(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

#ifdef EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN
    setPinOutput(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN);
    writePinHigh(EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN);
#endif // EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN

    wait_ms(50);
#if (YR_DEBUG_DIS_QP == TRUE)
    // For w25qx
    flash_init();
#endif

    // Turn on the LCD backlight
#ifndef BACKLIGHT_ENABLE
    setPinOutput(ST7735_BLK_PIN);
    writePinHigh(ST7735_BLK_PIN);
#else
    backlight_enable();
    backlight_level(BACKLIGHT_LEVELS);
#endif

    // Let the LCD get some power...
    wait_ms(150);

#if (YR_DEBUG_DIS_QP == TRUE)
    init_lcd_once();
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
#endif

    // Allow for user post-init
    keyboard_post_init_user();
}
#if (YR_DEBUG_DIS_QP == TRUE)
extern void qp_force_init(void) {
    if (lcd_power_flag) {
        LCD_BLK_ON;
    }
    // // init gif
    my_image = qp_load_image_spi_flash(head_buf, img_buf, IMG_BUFFER_MAX_LEN, 0);
    if (my_image != NULL) {
        my_anim        = qp_animate(lcd, 0, 0, my_image);
        use_default_ui = false;
    } else {
        use_default_ui = true;
        show_default_img();
    }
}
extern void qp_force_deinit(void) {
    if (my_anim != INVALID_DEFERRED_TOKEN) {
        qp_stop_animation(my_anim);
    }
    LCD_BLK_OFF;
    use_default_ui = true;
    qp_rect(lcd, 0, 0, 79, 159, HSV_BLACK, true);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case TOG_TFT_SCREEN:
            if (record->event.pressed) {
                lcd_power_flag = !lcd_power_flag;
                // qp_power(lcd, lcd_power_flag);
                if (lcd_power_flag)
                    LCD_BLK_ON;
                else
                    LCD_BLK_OFF;
            }
            return false;
        default:
            break;
    }
    return true;
}

inline void clear_page_buffer(void) {
    memset(page_buffer, 0, sizeof(page_buffer));
}

int write_one_page_into_w25q(uint8_t *command_data, uint8_t length) {
    static uint32_t byte_offset = 0;
    static uint32_t write_addr  = 0;
    uint32_t        saddr       = 0;
    saddr                       = 0 | command_data[2] << 16 | command_data[3] << 8 | command_data[4];
    uint8_t pkg_id = command_data[5], pkg_data_len = command_data[6];
    bool    is_end = command_data[7];
    if (pkg_id == 0) {
        byte_offset = 0;
        write_addr  = saddr;
    }
    memcpy(page_buffer + byte_offset, command_data + 8, pkg_data_len);
    byte_offset += pkg_data_len;
    dprintf("Write page of addr:%ld pkg_id:%d dlen: %d is_end:%d!!\n", saddr, pkg_id, pkg_data_len, is_end);
    if (is_end && write_addr != 0x3f3f3f3f) {
        uint8_t try_times = 0;
        do {
            fa = flash_write_block(write_addr, page_buffer, sizeof(uint8_t) * byte_offset);
            if (fa == FLASH_STATUS_SUCCESS) break;
            wait_ms(16);
            try_times++;
        } while (try_times < 32);
        if (try_times >= 32) {
            command_data[0] = 0x97;
        }
        dprintf("Write page of addr %ld state: %d fdata: %d datal: %ld!!\n", write_addr, fa, *(page_buffer), byte_offset);
        byte_offset = 0;
        write_addr  = 0x3f3f3f3f;
    }
    return fa;
}

void read_one_page_from_w25q(uint8_t *command_data) {
    uint32_t saddr    = 0;
    saddr             = 0 | command_data[2] << 16 | command_data[3] << 8 | command_data[4];
    uint32_t data_len = 0;
    data_len          = 0 | command_data[5] << 16 | command_data[6] << 8 | command_data[7];

    uint8_t page_count = (data_len + EXTERNAL_FLASH_PAGE_SIZE - 1) / EXTERNAL_FLASH_PAGE_SIZE;

    dprintf("Read %d pages from addr %ld!!\n", page_count, saddr);
    uint32_t page_read_data_len = EXTERNAL_FLASH_PAGE_SIZE;
    for (uint8_t i = 0; i < page_count; ++i) {
        if (i == page_count - 1) {
            page_read_data_len = data_len % EXTERNAL_FLASH_PAGE_SIZE;
            if (page_read_data_len == 0) page_read_data_len = EXTERNAL_FLASH_PAGE_SIZE;
        }
        fa = flash_read_block(saddr + i * EXTERNAL_FLASH_PAGE_SIZE, page_buffer, sizeof(uint8_t) * page_read_data_len);
        dprintf("Read pkg of addr %ld with len: %ld state: %d!!\n", saddr, page_read_data_len, fa);
    }
    dprintf("Read %d pages from addr %ld of fdata:%d!!\n", page_count, saddr, (int16_t)page_buffer[0]);
}

/*
load a new img into flash and display in the screen:
step by step:
1. star flash, 0x5, wait(100ms)
2. show defaule img, 0x7, wait(100ms)
3. erash chip, 0x3, wait(60s)
4. write img, 0x1, wait(60s)
5. show img, 0x4, wait(2s)
6. reboot kb, 0x6
*/
// // void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id   = &(data[0]);
    uint8_t *command_data = &(data[1]);
    if (*command_id == 0x03 && command_data[0] == 0x96) {
        dprintf(">>Recv a pkg with cmd_data1: [%d]!!\n", command_data[1]);
        if (command_data[1] == 0x1) { // write data
            is_in_flash_writing = true;
            //  0     1                                                                8       9
            //  cid   cdata[0] cdata[1] cdata[2] cdata[3] cdata[4] cdata[5] cdata[6]  cdata[7]
            // [0x03, 0x96,    0x01,    saddr1,  saddr2,  saddr3,  pkg_id,  data_len  is_end,  pkg_data1 .... pkg_data[len-8]]
            write_one_page_into_w25q(command_data, length);
            raw_hid_send(data, length);
        } else if (command_data[1] == 0x2) { // read data
            //  cid   cdata[0] cdata[1] cdata[2] cdata[3] cdata[4] cdata[5] cdata[6] cdata[7]
            // [0x03, 0x96,    0x02,    saddr1,  saddr2,  saddr3,  dlen1,   dlen2,   dlen3]
            read_one_page_from_w25q(command_data);
        } else if (command_data[1] == 0x3) { // erase chip
            //  cid   cdata[0] cdata[1] cdata[2] cdata[3] cdata[4]
            // [0x03, 0x96,    0x03,    saddr1,  saddr2,  saddr3]
            // flash_erase_sector(0 | command_data[2] << 16 | command_data[3] << 8 | command_data[4]);
            flash_erase_chip();
            dprintf("Erase a sector of addr%ld!\n", (uint32_t)(0 | command_data[2] << 16 | command_data[3] << 8 | command_data[4]));
        } else if (command_data[1] == 0x4) { // load new img in e_flash
            my_image = qp_load_image_spi_flash(head_buf, img_buf, IMG_BUFFER_MAX_LEN, 0);
            if (my_image != NULL) {
                qp_stop_animation(my_anim);
                my_anim        = qp_animate(lcd, 0, 0, my_image);
                use_default_ui = false;
            } else {
                use_default_ui = true;
                show_default_img();
                dprint("No Image!!\n");
            }
            is_in_flash_writing = false;
            dprintf("Image des-w: %d h: %d fc: %d!!\n", my_image->width, my_image->height, my_image->frame_count);
        } else if (command_data[1] == 0x5) {
            // start flash write
            use_default_ui      = true;
            is_in_flash_writing = true;
        } else if (command_data[1] == 0x6) {
            // directly reboot keyboard
            NVIC_SystemReset();
        } else if (command_data[1] == 0x7) {
            // just show defaule img
            if (lcd == NULL) {
                dprint("No Image!!\n");
            } else {
                dprint("Yes Image!!\n");
            }
            show_default_img();
        } else if (command_data[1] == 0x8) {
            // into bootloader
            reset_keyboard();
        }
        return true;
    }
    return false;
}

#    ifdef BACKLIGHT_ENABLE
static uint8_t last_backlight = BACKLIGHT_LIMIT_VAL;
#    endif
void suspend_power_down_kb(void) {
#    ifdef BACKLIGHT_ENABLE
    if (last_backlight == BACKLIGHT_LIMIT_VAL) {
        last_backlight = get_backlight_level();
    }
    backlight_set(0);
#    endif
    // qp_power(lcd, false);
    LCD_BLK_OFF;
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    // qp_power(lcd, true);
    LCD_BLK_ON;
    suspend_wakeup_init_user();
}

extern bool should_multi_qp_task(void) {
    return !is_in_flash_writing && !use_default_ui && lcd_power_flag;
}
#endif

#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, RGB_EN_STATE);
}
#endif
