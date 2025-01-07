// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum wls_port_mio_mode {
    mio_none = 0,
    mio_usb = 1,
    mio_bt = 2,
    mio_2g4 = 3
};

void wls_port_eeconfig_init(void);

void wls_port_init_pre(void);
void wls_port_init_post(void);

void wls_port_mode_scan(bool update);

void wls_port_rgb_indicators_task(void);

bool process_record_wls(uint16_t keycode, keyrecord_t *record);
