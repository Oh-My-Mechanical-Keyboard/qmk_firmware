// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t bt_devs : 8;
        uint8_t devs : 8;
    };
} confinfo_t;

extern confinfo_t confinfo;

void wls_port_eeconfig_init(void);

void wls_port_init_pre(void);
void wls_port_init_post(void);

void wls_port_mode_scan(bool update);

void wls_port_rgb_indicators_task(void);

bool process_record_wls(uint16_t keycode, keyrecord_t *record);
