// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "my_adc_drv.h"
#include <hal.h>
#include "util.h"

int16_t analogReadPin_my(pin_t pin) {
    ADCConfig          adcCfg = {};
    adcsample_t        sampleBuffer[ADC_NUM_CHANNELS * ADC_BUFFER_DEPTH];
    ADCDriver         *targetDriver       = &ADCD2;
    ADCConversionGroup adcConversionGroup = {
        .circular     = FALSE,
        .num_channels = (uint16_t)(ADC_NUM_CHANNELS),
        .cfgr         = ADC_CFGR_CONT | ADC_RESOLUTION,
    };

    palSetLineMode(pin, PAL_MODE_INPUT_ANALOG);
    adcConversionGroup.smpr[0] = ADC_SMPR1_SMP_AN0(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN1(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN2(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN3(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN4(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN5(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN6(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN7(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN8(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN9(ADC_SAMPLING_RATE);
    adcConversionGroup.smpr[1] = ADC_SMPR2_SMP_AN10(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN11(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN12(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN13(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN14(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN15(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN16(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN17(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN18(ADC_SAMPLING_RATE);
    // ADC PIN
    // #define MUX_OUT_PIN2MCU {B15, B12, A3, B14, B11}
    switch (pin) {
        case A6: {
            targetDriver = &ADCD2;
            adcConversionGroup.sqr[0]  = ADC_SQR1_SQ1_N(ADC_CHANNEL_IN3);
            for (uint8_t i = 0; i < ADC_BUFFER_DEPTH; i++) {
                sampleBuffer[i] = 0;
            }
        } break;
        default:
            return 0;
    }
    adcStart(targetDriver, &adcCfg);
    if (adcConvert(targetDriver, &adcConversionGroup, sampleBuffer, ADC_BUFFER_DEPTH) != MSG_OK) {
        return 0;
    }
    uint16_t sum_adc = 0;
    uint16_t mx_ad = 0;
    uint16_t mi_ad = 9999;
    for (uint8_t i = 0; i < ADC_BUFFER_DEPTH; i++) {
        sum_adc += sampleBuffer[i];
        mx_ad = MAX(mx_ad, sampleBuffer[i]);
        mi_ad = MIN(mi_ad, sampleBuffer[i]);
    }
    uint16_t avg_adc = 0;
    if (ADC_BUFFER_DEPTH > 2) {
        avg_adc = (sum_adc - mx_ad - mi_ad) / (ADC_BUFFER_DEPTH - 2);
    } else {
        avg_adc = sum_adc / ADC_BUFFER_DEPTH;
    }

    return avg_adc;
}
