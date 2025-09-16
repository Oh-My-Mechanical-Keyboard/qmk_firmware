/* Copyright 2023 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "tg431.h"

#define ADC_BUFFER_DEPTH 1
#define ADC_NUM_CHANNELS 1
// 采样时间+ 12.5个周期
// SYS: 170MHZ, ADC: SYS/4 = 42.5MHZ
// ADC: = 15*1/42.5 =352ns
// #define ADC_SAMPLING_RATE ADC_SMPR_SMP_2P5
#define ADC_SAMPLING_RATE ADC_SMPR_SMP_12P5
#define ADC_RESOLUTION ADC_CFGR_RES_12BITS

static int16_t analogReadPin_my(pin_t pin) {
    ADCConfig          adcCfg = {};
    adcsample_t        sampleBuffer[ADC_NUM_CHANNELS * ADC_BUFFER_DEPTH];
    ADCDriver         *targetDriver       = &ADCD1;
    ADCConversionGroup adcConversionGroup = {
        .circular     = FALSE,
        .num_channels = (uint16_t)(ADC_NUM_CHANNELS),
        .cfgr         = ADC_RESOLUTION,
    };

    palSetLineMode(pin, PAL_MODE_INPUT_ANALOG);
    adcConversionGroup.smpr[0] = ADC_SMPR1_SMP_AN0(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN1(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN2(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN3(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN4(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN5(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN6(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN7(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN8(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN9(ADC_SAMPLING_RATE);
    adcConversionGroup.smpr[1] = ADC_SMPR2_SMP_AN10(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN11(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN12(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN13(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN14(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN15(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN16(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN17(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN18(ADC_SAMPLING_RATE);
    switch (pin) {
        case A1:
            // 设置规则通道组寄存器
            // 不设置注入通道
            adcConversionGroup.sqr[0]  = ADC_SQR1_SQ1_N(ADC_CHANNEL_IN2);
            sampleBuffer[0]            = 0;
            break;
        case A2:
            adcConversionGroup.sqr[0]  = ADC_SQR1_SQ1_N(ADC_CHANNEL_IN3);
            sampleBuffer[0]            = 0;
            break;
        default:
            return 0;
    }
    adcStart(targetDriver, &adcCfg);
    if (adcConvert(targetDriver, &adcConversionGroup, &sampleBuffer[0], ADC_BUFFER_DEPTH) != MSG_OK) {
        return 0;
    }

    return *sampleBuffer;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }

    switch(keycode) {
        case KC_Q:
            if (record->event.pressed) {
                // 12bit
                // out V:val/4096.0*3.3
                // 可以开启FPU加速浮点运算, G4默认开启
                uint32_t adc_val = analogReadPin_my(A2);
                dprintf("ADC: val %lu, Voltage: %lumv\n", adc_val, adc_val*3300>>12);
            }
            return true;
        default:
            break;
    }
    return true;
}


void keyboard_post_init_kb(void) {
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    debug_mouse=true;
}


void board_init(void) {
    setPinInput(G10);
    setPinInput(B8);
}
