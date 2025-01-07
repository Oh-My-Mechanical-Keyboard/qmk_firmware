// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "wireless.h"
#include "eeconfig.h"

#include "wls_port.h"

// 键盘回连超时时间
#ifndef WLS_LBACK_TIMEOUT
#   define WLS_LBACK_TIMEOUT (30*1000)
#endif

// 键盘配对超时时间
#ifndef WLS_PAIR_TIMEOUT
#   define WLS_PAIR_TIMEOUT (30*1000)
#endif

// 键盘回连或配对成功时，模式指示灯常亮时间
#ifndef WLS_SUCCEED_TIME
#   define WLS_SUCCEED_TIME (2*1000)
#endif

#ifndef WLS_MODEIO_DETECTION_TIME
#    define WLS_MODEIO_DETECTION_TIME 100
#endif

#ifndef WLS_STATE_DETECTION_TIME
#    define WLS_STATE_DETECTION_TIME 103
#endif

#ifndef WLS_POWER_DETECTION_TIME
#    define WLS_POWER_DETECTION_TIME 107
#endif

#ifndef WLS_KEYCODE_PAIR_TIME
#    define WLS_KEYCODE_PAIR_TIME 3000
#endif

// 无线初始化
uint32_t post_init_timer = 0x00;
bool post_init_f = false;

// 长按键处理
bool wls_mode_in_pairing = false; // 长按到了配对模式
bool wls_mode_key_pressed = false; // 模式切换按键按下
uint32_t wls_mode_long_press_timer = 0;
uint16_t wls_mode_keycode_shadow = 0x00;

// 设备或者模式切换
bool wls_mode_reset_f = false; // 需要重新绑定

// 无线模式灯光
bool wls_rgb_indicator_reset             = false;
uint32_t wls_rgb_indicator_timer         = 0x00;
uint32_t wls_rgb_indicator_keep_timer    = 0x00;
uint32_t wls_rgb_indicator_connect_timer = 0x00;
uint32_t wls_rgb_indicator_interval      = 0;
uint32_t wls_rgb_indicator_times         = 0;
uint32_t wls_rgb_indicator_index         = 0;
bool inqbat_flag  = false;
RGB wls_rgb_indicator_rgb                = {0};
uint8_t bat_rgb_map[] = RGB_MATRIX_BAT_INDEX_MAP;

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t bt_devs : 8;
        uint8_t devs : 8;
    };
} confinfo_t;
confinfo_t confinfo;


void rgb_matrix_wls_indicator_set(uint8_t index, RGB rgb, uint32_t interval, uint8_t times) {

    wls_rgb_indicator_timer = timer_read32();

    wls_rgb_indicator_index    = index;
    wls_rgb_indicator_interval = interval;
    wls_rgb_indicator_times    = times * 2;
    wls_rgb_indicator_rgb      = rgb;
}

void wls_port_eeconfig_init(void) {
    confinfo.raw = eeprom_read_dword((uint32_t *)WIRELESS_EECONFIG_ADDR);
    if (confinfo.flag != true) {
        confinfo.flag = true;
        confinfo.bt_devs = DEVS_BT1;
        confinfo.devs = DEVS_USB;
        eeprom_update_dword((uint32_t *)WIRELESS_EECONFIG_ADDR, confinfo.raw);
    }
}

void wls_port_init_pre(void) {
    confinfo.raw = eeprom_read_dword((uint32_t *)WIRELESS_EECONFIG_ADDR);

    gpio_set_pin_output(LED_POWER_EN_PIN);
    gpio_write_pin_high(LED_POWER_EN_PIN);

}
void wls_port_init_post(void) {
    wireless_init(); // 无线UART初始化

    post_init_timer = timer_read32(); // 无线初始化计时，上电后等待一小会无线才初始化
    post_init_f = false;

}

// 无线模块状态检测
void wls_port_state_scan(void){
    static uint8_t last_status = 0xff;

    static uint32_t state_scan_timer = 0x00;
    if (timer_elapsed32(state_scan_timer) <= WLS_STATE_DETECTION_TIME) {
        return;
    }
    state_scan_timer = timer_read32();

    if (last_status != *md_getp_state()){
        last_status = *md_getp_state();
        if (!wls_mode_reset_f) wireless_devs_change(wireless_get_current_devs(), wireless_get_current_devs(), false);
    }
}

void usb_power_connect(void) {}

void usb_power_disconnect(void) {}

void lpwr_stop_hook_pre(void) {
    gpio_write_pin_low(LED_POWER_EN_PIN);
}

void lpwr_stop_hook_post(void) {
    matrix_scan();
}

void lpwr_wakeup_hook(void) {
    gpio_write_pin_high(LED_POWER_EN_PIN);
    wireless_devs_change(wireless_get_current_devs(), wireless_get_current_devs(), false);
}

void suspend_power_down_kb(void) {
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    suspend_wakeup_init_user();
}

bool lpwr_is_allow_timeout_hook(void) { /* USB 模式不休眠,wl lib已经处理 */
    return true;
}

void wls_mode_key_process(bool reset) {
    wls_mode_reset_f = reset;
    switch (wls_mode_keycode_shadow) {
        case KC_BT1: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, reset);
        } break;
        case KC_BT2: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, reset);
        } break;
        case KC_BT3: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, reset);
        } break;
        case KC_2G4: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, reset);
        } break;
        case KC_USB: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
        }
        default:
            break;
    }
}

void wls_process_long_press_task(void) {
    if (!wls_mode_key_pressed) {
        wls_mode_long_press_timer = 0;
        wls_mode_in_pairing = false;
        return;
    }
    if (timer_elapsed32(wls_mode_long_press_timer) < WLS_KEYCODE_PAIR_TIME) {
        return;
    }
    if (!wls_mode_in_pairing) {
        wls_mode_in_pairing = true; // 超过了长按限制，进入配对模式，抬起失效, 只需要进入一次即可
        wls_mode_key_process(true);
    }
}

bool rgb_power_is_allow_off(void) {
    if (kb_cstm_config.key_rgb_sw != 0) return false;
    if (kb_cstm_config.box_rgb_mode != 0) return false;
    if (host_keyboard_led_state().caps_lock) return false;
    if (keymap_config.no_gui) return false;
    if (inqbat_flag) return false;
    if (wls_rgb_indicator_timer) return false;
    if (wls_rgb_indicator_connect_timer) return false;
    return true;
}

void wls_power_scan(void) {
    static uint32_t power_scan_timer = 0x00;
    if (timer_elapsed32(power_scan_timer) <= WLS_POWER_DETECTION_TIME) {
        return;
    }
    power_scan_timer = timer_read32();
    if (rgb_power_is_allow_off()) {
        gpio_write_pin_low(LED_POWER_EN_PIN);
    } else {
        gpio_write_pin_high(LED_POWER_EN_PIN);
    }
}

void wireless_post_task(void) {
    // auto switching devs
    if (!post_init_f && timer_elapsed32(post_init_timer) >= 200) { // 100ms后第一次初始化无线模块
        md_send_devctrl(MD_SND_CMD_DEVCTRL_FW_VERSION);   // get the module fw version.
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);  // timeout 30min to sleep in bt mode, enable
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN); // timeout 30min to sleep in 2.4g mode, enable
        wireless_devs_change(!confinfo.devs, confinfo.devs, false);
        post_init_timer = 0x00;
        post_init_f = true;
    }
    if (!post_init_f) return;
    // 定期自动更新模式
    wls_port_state_scan();
    wls_process_long_press_task();
    // 功耗管理，管理RGB灯电源
    wls_power_scan();
}

bool process_record_wls(uint16_t keycode, keyrecord_t *record) {
    wls_mode_keycode_shadow = keycode;
    switch (keycode) {
        case KC_BT1:
        case KC_BT2:
        case KC_BT3:
        case KC_2G4:
        case KC_USB:
        {
            if (record->event.pressed) {
                wls_mode_key_pressed = true;
                wls_mode_long_press_timer = timer_read32();
            } else {
                if (!wls_mode_in_pairing) {
                    wls_mode_key_process(false);
                }
                wls_mode_in_pairing = false;
                wls_mode_key_pressed = false;
                wls_mode_long_press_timer = 0;
            }
            return false;
        } break;
        case KC_BATQ: {
            inqbat_flag = record->event.pressed;
            return false;
        } break;
        default:
            return true;
    }
    return true;
}

void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset) {
    wls_mode_reset_f = reset;
    if (confinfo.devs != wireless_get_current_devs()) {
        confinfo.devs = wireless_get_current_devs();
        if ((wireless_get_current_devs() != DEVS_USB) && (wireless_get_current_devs() != DEVS_2G4)) {
            confinfo.bt_devs = wireless_get_current_devs();
        }
        eeprom_update_dword((uint32_t *)WIRELESS_EECONFIG_ADDR, confinfo.raw);
    }
    switch (new_devs) {
        case DEVS_BT1: {
            if (reset) {
                rgb_matrix_wls_indicator_set(15, (RGB){.r = 0, .g = 0, .b = 0xff}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(15, (RGB){.r = 0, .g = 0xff, .b = 0}, 500, 1);
            }
        } break;
        case DEVS_BT2: {
            if (reset) {
                rgb_matrix_wls_indicator_set(16, (RGB){.r = 0, .g = 0, .b = 0xff}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(16, (RGB){.r = 0, .g = 0xff, .b = 0}, 500, 1);
            }
        } break;
        case DEVS_BT3: {
            if (reset) {
                rgb_matrix_wls_indicator_set(17, (RGB){.r = 0, .g = 0, .b = 0xff}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(17, (RGB){.r = 0, .g = 0xff, .b = 0}, 500, 1);
            }
        } break;
        case DEVS_2G4: {
            if (reset) {
                rgb_matrix_wls_indicator_set(18, (RGB){.r = 0, .g = 0, .b = 0xff}, 200, 1);
            } else {
                rgb_matrix_wls_indicator_set(18, (RGB){.r = 0, .g = 0xff, .b = 0}, 500, 1);
            }
        } break;
        case DEVS_USB: {
            rgb_matrix_wls_indicator_set(19, (RGB){.r = 0, .g = 0xff, .b = 0}, 500, 1);
        } break;
        default:
            break;
    }
}

bool rgb_matrix_wls_indicator_cb(void) {
    // 无线模式下没有连接正确持续闪
    if (wireless_get_current_devs() != DEVS_USB && *md_getp_state() != MD_STATE_CONNECTED) {
        switch (*md_getp_state())
        {
            case MD_STATE_NONE: {
                wls_rgb_indicator_keep_timer = 0;
                return false;
            } break;
            case MD_STATE_PAIRING: {
                if (timer_elapsed32(wls_rgb_indicator_keep_timer) >= WLS_PAIR_TIMEOUT) {
                    wls_rgb_indicator_keep_timer = 0;
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
                    wait_ms(100);
                    lpwr_set_timeout_manual(true);
                    return false;
                }
            } break;
            case MD_STATE_REJECT:
            case MD_STATE_DISCONNECTED: {
                if (timer_elapsed32(wls_rgb_indicator_keep_timer) >= WLS_LBACK_TIMEOUT) {
                    wls_rgb_indicator_keep_timer = 0;
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
                    wait_ms(100);
                    lpwr_set_timeout_manual(true);
                    return false;
                }
            } break;
        }
        wireless_devs_change_kb(wireless_get_current_devs(), wireless_get_current_devs(), wls_mode_reset_f);
        return true;
    }

    // USB模式或者无线状态为连接模式
    if (wireless_get_current_devs() == DEVS_USB || *md_getp_state() == MD_STATE_CONNECTED) {
        // 长亮一次
        wls_rgb_indicator_connect_timer = timer_read32();
    }
    // refresh led
    led_wakeup();

    return false;
}

void wls_rgb_blink(void) {
    if (wls_rgb_indicator_timer) {
        if (wls_rgb_indicator_keep_timer == 0) {
            wls_rgb_indicator_keep_timer = timer_read32();
        }
        if (timer_elapsed32(wls_rgb_indicator_timer) >= wls_rgb_indicator_interval) {
            wls_rgb_indicator_timer = timer_read32();

            if (wls_rgb_indicator_times) {
                wls_rgb_indicator_times--;
            }

            if (wls_rgb_indicator_times <= 0) {
                wls_rgb_indicator_timer = 0x00;
                if (rgb_matrix_wls_indicator_cb() != true) {
                    return;
                }
            }
        }
        if (wls_rgb_indicator_times % 2) {
            rgb_matrix_set_color(wls_rgb_indicator_index, wls_rgb_indicator_rgb.r, wls_rgb_indicator_rgb.g, wls_rgb_indicator_rgb.b);
        } else {
            rgb_matrix_set_color(wls_rgb_indicator_index, 0x00, 0x00, 0x00);
        }
    } else {
        wls_rgb_indicator_keep_timer = 0;
    }
    if (wls_rgb_indicator_connect_timer != 0 && timer_elapsed32(wls_rgb_indicator_connect_timer) <= 2000) {
        switch (wireless_get_current_devs())
        {
        case DEVS_BT1:
            rgb_matrix_set_color(15, 0x00, 0xFF, 0x00);
            break;
        case DEVS_BT2:
            rgb_matrix_set_color(16, 0x00, 0xFF, 0x00);
            break;
        case DEVS_BT3:
            rgb_matrix_set_color(16, 0x00, 0xFF, 0x00);
            break;
        case DEVS_2G4:
            rgb_matrix_set_color(18, 0x00, 0xFF, 0x00);
            break;
        case DEVS_USB:
            rgb_matrix_set_color(19, 0x00, 0xFF, 0x00);
            break;
        }
    } else {
        wls_rgb_indicator_connect_timer = 0;
    }
}

void wls_port_rgb_indicators_task(void) {
    // 电池灯光
    if (inqbat_flag) {
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        uint8_t i = (*md_getp_bat() / 10);
        for (uint8_t bi = 0; bi < i; bi++) {
            rgb_matrix_set_color(bat_rgb_map[bi], 0, 255, 0);
        }
    } else {
        // 无线模式灯光
        wls_rgb_blink();
    }
}


void wireless_send_nkro(report_nkro_t *report) {
    static report_keyboard_t temp_report_keyboard = {0};
    uint8_t wls_report_nkro[MD_SND_CMD_NKRO_LEN]  = {0};

#ifdef NKRO_ENABLE

    if (report != NULL) {
        report_nkro_t temp_report_nkro = *report;
        uint8_t key_count              = 0;

        temp_report_keyboard.mods = temp_report_nkro.mods;
        for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
            key_count += __builtin_popcount(temp_report_nkro.bits[i]);
        }

        /*
         * Use NKRO for sending when more than 6 keys are pressed
         * to solve the issue of the lack of a protocol flag in wireless mode.
         */

        for (uint8_t i = 0; i < key_count; i++) {
            uint8_t usageid;
            uint8_t idx, n = 0;

            for (n = 0; n < NKRO_REPORT_BITS && !temp_report_nkro.bits[n]; n++) {}
            usageid = (n << 3) | biton(temp_report_nkro.bits[n]);
            del_key_bit(&temp_report_nkro, usageid);

            for (idx = 0; idx < WLS_KEYBOARD_REPORT_KEYS; idx++) {
                if (temp_report_keyboard.keys[idx] == usageid) {
                    goto next;
                }
            }

            for (idx = 0; idx < WLS_KEYBOARD_REPORT_KEYS; idx++) {
                if (temp_report_keyboard.keys[idx] == 0x00) {
                    temp_report_keyboard.keys[idx] = usageid;
                    break;
                }
            }
        next:
            if (idx == WLS_KEYBOARD_REPORT_KEYS && (usageid < (MD_SND_CMD_NKRO_LEN * 8))) {
                wls_report_nkro[usageid / 8] |= 0x01 << (usageid % 8);
            }
        }

        temp_report_nkro = *report;

         // find key up and del it.
        uint8_t nkro_keys = key_count;
        for (uint8_t i = 0; i < WLS_KEYBOARD_REPORT_KEYS; i++) {
            report_nkro_t found_report_nkro;
            uint8_t usageid = 0x00;
            uint8_t n;

            found_report_nkro = temp_report_nkro;

            for (uint8_t c = 0; c < nkro_keys; c++) {
                for (n = 0; n < NKRO_REPORT_BITS && !found_report_nkro.bits[n]; n++) {}
                usageid = (n << 3) | biton(found_report_nkro.bits[n]);
                del_key_bit(&found_report_nkro, usageid);
                if (usageid == temp_report_keyboard.keys[i]) {
                    del_key_bit(&temp_report_nkro, usageid);
                    nkro_keys--;
                    break;
                }
            }

            if (usageid != temp_report_keyboard.keys[i]) {
                temp_report_keyboard.keys[i] = 0x00;
            }
        }
    } else {
        memset(&temp_report_keyboard, 0, sizeof(temp_report_keyboard));
    }
#endif
    void wireless_task(void);
    bool smsg_is_busy(void);
    while(smsg_is_busy()) {
        wireless_task();
    }
    extern host_driver_t wireless_driver;
    wireless_driver.send_keyboard(&temp_report_keyboard);
    md_send_nkro(wls_report_nkro);
}
