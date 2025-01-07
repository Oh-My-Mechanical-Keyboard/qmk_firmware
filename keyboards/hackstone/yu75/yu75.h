// Copyright 2024 Jason
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "wls_port.h"

#define ___ KC_NO

// clang-format off

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,      \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d, k3e, k3f, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,      k4d, k4e, k4f, \
    k50, k51, k52,                k56,           k59, k5a, k5b, k5c, k5d, k5e, k5f  \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, ___ }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, ___, k3d, k3e, k3f }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, ___, k4d, k4e, k4f }, \
    { k50, k51, k52, ___, ___, ___, k56, ___, ___, k59, k5a, k5b, k5c, k5d, k5e, k5f }  \
}

// clang-format on
enum wl_port_keys {
    KC_BT1 = QK_KB_0,
    KC_BT2,
    KC_BT3,
    KC_2G4,
    KC_USB
};
