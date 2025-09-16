// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum keyboard_keycodes {
    LOCK_GUI_MAC = QK_KB,
    TOG_MACOS_KEYMAP_MAC,
    KC_MISSION_CONTROL_MAC,
    KC_LAUNCHPAD_MAC
};

#define MKC_LG    LOCK_GUI_MAC
#define MKC_MACOS TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL  KC_MISSION_CONTROL_MAC
#define MKC_LPAD  KC_LAUNCHPAD_MAC
