// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "my_adc_drv.h"
#include <hal.h>
#include "util.h"
#include "sumqueue_kalman.h"

adcsample_t sampleBuffer[8];

RingBuffer adc_bufs[MATRIX_ROWS][MATRIX_COLS];


// B1 -> ADC1_IN9
ADCConversionGroup adcConversionGroup = {
    .circular     = FALSE,
    .num_channels = (uint16_t)(5),
    .end_cb       = NULL,
    .cfgr         = ADC_CFGR_CONT | ADC_CFGR_RES_12BITS,
    .smpr         = {
        ADC_SMPR1_SMP_AN0(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN1(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN2(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN3(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN4(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN5(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN6(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN7(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN8(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN9(ADC_SAMPLING_RATE),
        ADC_SMPR2_SMP_AN10(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN11(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN12(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN13(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN14(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN15(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN16(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN17(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN18(ADC_SAMPLING_RATE)
    },
    .sqr          = {
        ADC_SQR1_SQ1_N(ADC_CHANNEL_IN3) | ADC_SQR1_SQ2_N(ADC_CHANNEL_IN3) | ADC_SQR1_SQ3_N(ADC_CHANNEL_IN3) | ADC_SQR1_SQ4_N(ADC_CHANNEL_IN3),
        ADC_SQR2_SQ5_N(ADC_CHANNEL_IN3),
        0,
        0
    }
};

void analogInit_my(void) {

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++)
        {
            initqueue(&adc_bufs[r][c], ADC_WINDOW_SIZE + 1);
        }
    }

    // 初始化行的读取脚为ADC引脚
    palSetLineMode(ADC_READ_PIN, PAL_MODE_INPUT_ANALOG);

    adcStart(&ADCD2, NULL);
}

void analogStart_my(void) {
    adcConvert(&ADCD2, &adcConversionGroup, sampleBuffer, 1);
}

uint16_t analogReadPin_my(uint8_t row, uint8_t col) {
    uint16_t min_adc = 4096;
    uint16_t max_adc = 0;
    uint32_t sum_adc = 0;
    for (uint8_t i = 1; i < 5; i++) {
        sum_adc += sampleBuffer[i];
        min_adc = MIN(min_adc, sampleBuffer[i]);
        max_adc = MAX(max_adc, sampleBuffer[i]);
    }
    sum_adc -= (max_adc+min_adc);
    sum_adc >>= 1;

    f_enqueue(&adc_bufs[row][col], sum_adc);
    return sumqueue(&adc_bufs[row][col]);
    // return sortqueue(&adc_bufs[row][col]);
}
