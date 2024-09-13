// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "my_adc_drv.h"
#include <hal.h>

// adc1
ADCConversionGroup adc1ConversionGroup = {
    .circular     = FALSE,
    .num_channels = (uint16_t)(2),
    .cfgr         = ADC_CFGR_CONT | ADC_RESOLUTION,
    .smpr         = {
        ADC_SMPR1_SMP_AN0(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN1(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN2(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN3(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN4(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN5(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN6(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN7(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN8(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN9(ADC_SAMPLING_RATE),
        ADC_SMPR2_SMP_AN10(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN11(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN12(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN13(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN14(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN15(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN16(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN17(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN18(ADC_SAMPLING_RATE)
    },
    .sqr          = {
        ADC_SQR1_SQ1_N(ADC_CHANNEL_IN15) | ADC_SQR1_SQ2_N(ADC_CHANNEL_IN14),
        0,
        0,
        0
    }
    
};
// adc2
ADCConversionGroup adc2ConversionGroup = {
    .circular     = FALSE,
    .num_channels = (uint16_t)(3),
    .cfgr         = ADC_CFGR_CONT | ADC_RESOLUTION,
    .smpr         = {
        ADC_SMPR1_SMP_AN0(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN1(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN2(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN3(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN4(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN5(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN6(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN7(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN8(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN9(ADC_SAMPLING_RATE),
        ADC_SMPR2_SMP_AN10(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN11(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN12(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN13(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN14(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN15(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN16(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN17(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN18(ADC_SAMPLING_RATE)
    },
    .sqr          = {
        ADC_SQR1_SQ1_N(ADC_CHANNEL_IN13) | ADC_SQR1_SQ2_N(ADC_CHANNEL_IN4) | ADC_SQR1_SQ3_N(ADC_CHANNEL_IN12),
        0,
        0,
        0
    }
};
adcsample_t sampleBuffer1[2 * ADC_BUFFER_DEPTH];
adcsample_t sampleBuffer2[3 * ADC_BUFFER_DEPTH];



void analogInit_my(void) {
    // // 初始化行的读取脚为ADC引脚
    // const pin_t adc_pins[MATRIX_ROWS] = ROW_ADC_PINS;
    // for (uint8_t i = 0; i < MATRIX_ROWS; ++i) {
    //     palSetLineMode(adc_pins[i], PAL_MODE_INPUT_ANALOG);
    // }
    adcStart(&ADCD1, NULL);
    adcStart(&ADCD2, NULL);
}
//adc  2   2   1   2   1
//    {A5, A7, B0, B2, B11}
void analogReadRows_my(void) {
    adcConvert(&ADCD1, &adc1ConversionGroup, sampleBuffer1, ADC_BUFFER_DEPTH);
    adcConvert(&ADCD2, &adc2ConversionGroup, sampleBuffer2, ADC_BUFFER_DEPTH);
}


int16_t analogReadPin_my(pin_t pin) {
    // ADC PIN
    switch (pin) {
        case B0:
            return (sampleBuffer1[0] + sampleBuffer1[2]) >> 1;
        case B11:
            return (sampleBuffer1[1] + sampleBuffer1[3]) >> 1;
        case A5:
            return (sampleBuffer2[0] + sampleBuffer2[3]) >> 1;
        case A7:
            return (sampleBuffer2[1] + sampleBuffer2[4]) >> 1;
        case B2:
            return (sampleBuffer2[2] + sampleBuffer2[5]) >> 1;
        default:
            return 0;
    }

    return 0;
}
