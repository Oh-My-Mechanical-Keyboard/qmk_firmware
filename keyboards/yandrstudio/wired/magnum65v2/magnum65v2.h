#pragma once
#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       K115, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,       K213,       K215, \
    K300, K301, K306, K305, K304, K303, K302, K307, K308, K309, K310, K311, K312, K313,       K315, \
    K400, K401, K402,                         K407, K408, K409,             K412, K413,       K415  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  KC_NO, K115 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  KC_NO, K213,  KC_NO, K215 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315 }, \
    { K400,  K401,  K402,  KC_NO, KC_NO, KC_NO, KC_NO, K407,  K408,  K409,  KC_NO, KC_NO, K412,  K413,  KC_NO, K415 }  \
}



typedef struct {
    uint8_t  caps_brightness: 8;
    uint8_t  caps_color_h: 8;
    uint8_t  caps_color_s: 8;

} kb_cstm_config_t;

enum via_caps_value {
    via_caps_brightness = 1,
    via_caps_color = 2
};

void caps_config_set_value(uint8_t *data);
void caps_config_get_value(uint8_t *data);
void caps_config_save (void);

extern bool yr_factory_test;
