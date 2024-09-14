// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "gpio.h"

#define ADC_BUFFER_DEPTH 1
#define ADC_NUM_CHANNELS 1
// 采样时间+ 12.5个周期
// SYS: 170MHZ, ADC: SYS/4 = 42.5MHZ
// ADC: = 15*1/42.5 =352ns
// #define ADC_SAMPLING_RATE ADC_SMPR_SMP_2P5
// #define ADC_SAMPLING_RATE ADC_SMPR_SMP_6P5
// #define ADC_SAMPLING_RATE ADC_SMPR_SMP_12P5
#define ADC_SAMPLING_RATE ADC_SMPR_SMP_24P5
#define ADC_RESOLUTION ADC_CFGR_RES_12BITS

int16_t analogReadPin_my(pin_t pin);
