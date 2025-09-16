// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "f6501.h"

// #define YR_DEBUG_DIS_QP FALSE
#define YR_DEBUG_DIS_QP TRUE

#if (YR_DEBUG_DIS_QP == TRUE)
#include "qp.h"
#include "color.h"
#include "print.h"
#include <string.h>
#include "ptg.qgf.h"
#include "raw_hid.h"
#include "flash_spi.h"
#include "spi_master.h"
#endif


// bool ble_led_update_kb(uint8_t channle, uint8_t state) {
//     /*
//     _ble_channle:
//         BLE: 0-7
//         USB: 0xa
//         2G4: 0xb
//     _ble_state:
//         NRF_WORKING：1
//         NRF_ADVING_NO_WL：8
//         NRF_ADVING_WITH_WL：7

//         USB_ACTIVE: 0xA0
//         USB_DISCONNECTION：0xA1
//     */
//     return true;
// }

// bool led_update_kb(led_t led_state) {
//     return true;
// }


#if (YR_DEBUG_DIS_QP == TRUE)

// Initialisation
static painter_device_t lcd;
static painter_image_handle_t my_image = NULL;
static deferred_token my_anim = INVALID_DEFERRED_TOKEN;
// static bool my_anim;
static bool lcd_power_flag = false;
static bool is_in_flash_writing = false;
static bool use_default_ui = false;

#define IMG_BUFFER_MAX_LEN 3000

uint8_t head_buf[28];
uint8_t img_buf[IMG_BUFFER_MAX_LEN+5];

flash_status_t fa;
uint8_t page_buffer[EXTERNAL_FLASH_PAGE_SIZE+5];

#ifndef BACKLIGHT_ENABLE
# define LCD_BLK_ON  writePinHigh(ST7735_BLK_PIN)
# define LCD_BLK_OFF writePinLow(ST7735_BLK_PIN)
#else
# define LCD_BLK_ON  backlight_enable()
# define LCD_BLK_OFF backlight_disable()
#endif

/*
实际屏幕显示区域大小为：
60*140
*/
static void inline show_default_img(void) {
    if (my_anim != INVALID_DEFERRED_TOKEN) {
        qp_stop_animation(my_anim);
    }
    my_image = qp_load_image_mem_force(gfx_ptg);
    if (my_image != NULL) {
        // my_anim = qp_drawimage(lcd, 0, 0, my_image);
        my_anim = qp_animate(lcd, 0, 0, my_image);
    } else {
        qp_rect(lcd, 0, 0, 128-1, 128-1, HSV_PINK, true);
    }
}
#endif

void keyboard_post_init_kb(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
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
    // Initialise the LCD
#ifdef QUANTUM_PAINTER_ST7735_SPI_ENABLE
    lcd = qp_st7735_make_spi_device(128, 128, ST7735_CS_PIN, ST7735_DC_PIN, ST7735_RES_PIN, 8, 0);
    qp_set_viewport_offsets(lcd, 0, 0);
#else
    lcd = qp_st7735s_make_spi_device(128, 128, ST7735_CS_PIN, ST7735_DC_PIN, ST7735_RES_PIN, 8, 0);
    qp_set_viewport_offsets(lcd, 0, 0);
#endif
    bool rec = qp_init(lcd, 0);
    int retry_time = 0;
    while (rec == 0 && retry_time < 10)
    {
        retry_time++;
        rec = qp_init(lcd, 0);
        wait_ms(100);
    }

    // Turn on the LCD
    // clear the display
    qp_rect(lcd, 0, 0, 128-1, 128-1, HSV_BLACK, true);

    lcd_power_flag = true;


    // init gif
    my_image = qp_load_image_spi_flash(head_buf, img_buf, IMG_BUFFER_MAX_LEN, 0);
    if (my_image != NULL) {
        my_anim = qp_animate(lcd, 0, 0, my_image);
        use_default_ui = false;
    } else {
        use_default_ui = true;
        show_default_img();
    }
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
        my_anim = qp_animate(lcd, 0, 0, my_image);
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
    qp_rect(lcd, 0, 0, 128-1, 128-1, HSV_BLACK, true);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch(keycode) {
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

int write_one_page_into_w25q(uint8_t * command_data, uint8_t length) {
    static uint32_t byte_offset = 0;
    static uint32_t write_addr = 0;
    uint32_t saddr = 0;
    saddr = 0 | command_data[2] << 16 | command_data[3] << 8 | command_data[4];
    uint8_t pkg_id = command_data[5], pkg_data_len = command_data[6];
    bool is_end = command_data[7];
    if (pkg_id == 0) {
        byte_offset = 0;
        write_addr = saddr;
    }
    memcpy(page_buffer+byte_offset, command_data+8, pkg_data_len);
    byte_offset += pkg_data_len;
    dprintf("Write page of addr:%ld pkg_id:%d dlen: %d is_end:%d!!\n", saddr, pkg_id, pkg_data_len, is_end);
    if (is_end && write_addr != 0x3f3f3f3f) {
        uint8_t try_times = 0;
        do
        {
            fa = flash_write_block(write_addr, page_buffer, sizeof(uint8_t)*byte_offset);
            if (fa == FLASH_STATUS_SUCCESS) break;
            wait_ms(16);
            try_times++;
        } while (try_times < 32);
        if (try_times>=32) {
            command_data[0] = 0x97;
        }
        dprintf("Write page of addr %ld state: %d fdata: %d datal: %ld!!\n", write_addr, fa, *(page_buffer), byte_offset);
        byte_offset = 0;
        write_addr = 0x3f3f3f3f;
    }
    return fa;
}

void read_one_page_from_w25q(uint8_t * command_data) {
    uint32_t saddr = 0;
    saddr = 0 | command_data[2] << 16 | command_data[3] << 8 | command_data[4];
    uint32_t data_len = 0;
    data_len = 0 | command_data[5] << 16 | command_data[6] << 8 | command_data[7];

    uint8_t page_count = (data_len+EXTERNAL_FLASH_PAGE_SIZE-1)/EXTERNAL_FLASH_PAGE_SIZE;

    dprintf("Read %d pages from addr %ld!!\n", page_count, saddr);
    uint32_t page_read_data_len = EXTERNAL_FLASH_PAGE_SIZE;
    for (uint8_t i = 0; i < page_count; ++i)
    {
        if (i == page_count-1) {
            page_read_data_len = data_len % EXTERNAL_FLASH_PAGE_SIZE;
            if (page_read_data_len == 0) page_read_data_len = EXTERNAL_FLASH_PAGE_SIZE;
        }
        fa = flash_read_block(saddr+i*EXTERNAL_FLASH_PAGE_SIZE, page_buffer, sizeof(uint8_t)*page_read_data_len);
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
    uint8_t *command_id = &(data[0]);
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
                my_anim = qp_animate(lcd, 0, 0, my_image);
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
            use_default_ui = true;
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

#ifdef BACKLIGHT_ENABLE
static uint8_t last_backlight = BACKLIGHT_LIMIT_VAL;
#endif
void suspend_power_down_kb(void) {
#ifdef BACKLIGHT_ENABLE
    if (last_backlight == BACKLIGHT_LIMIT_VAL) {
        last_backlight = get_backlight_level();
    }
    backlight_set(0);
#endif
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


void keyboard_pre_init_kb(void) {
    palSetLineMode(C11, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(C11, 1);
}
