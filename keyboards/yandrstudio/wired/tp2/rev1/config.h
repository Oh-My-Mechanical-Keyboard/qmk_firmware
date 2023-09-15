// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define DEVICE_VER      0x0001

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 19

#define NUM_OF_74HC595 11
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }

// 从第一行开始
//                             c15          c16  

// c0          1             2           3             4             5           6            7           8           9            10           11           12           13            14        **15            16           17           18**
// io1          2            3                                                                8           9           10           11           12           13           14            15          
// io16        17           18           19           20           21            22           23          24            25          26            27           28           29
// io30       31            32           33           34          35            36           37           38            39          40           41            42
// io43       44            45           46           47            48          49           50           51           52           53            54           55
// io56       57            58                                      59                       60           61           62
#define MATRIX_OF_74HC595 \
{{0xA, 0x40}, {0xA, 0x20}, {0xA, 0x10}, {0xA, 0x08}, {0xA, 0x04}, {0xA, 0x02}, {0xA, 0x01}, {0x3, 0x20}, {0x3, 0x10}, {0x3, 0x08}, {0x3, 0x04}, {0x3, 0x02}, {0x3, 0x01}, {0x3, 0x80}, {0x3, 0x40}, {0x0, 0x08}, {0x0, 0x04}, {0x0, 0x02}, {0x0, 0x01},\
 {0xA, 0x80}, {0x9, 0x40}, {0x9, 0x20}, {0x9, 0x10}, {0x9, 0x08}, {0x9, 0x04}, {0x9, 0x02}, {0x9, 0x01}, {0x4, 0x40}, {0x4, 0x20}, {0x4, 0x10}, {0x4, 0x08}, {0x4, 0x04}, {0x4, 0x02},              {0x2, 0x04}, {0x0, 0x10}, {0x0, 0x20}, {0x0, 0x40},\
 {0x9, 0x80}, {0x8, 0x20}, {0x8, 0x10}, {0x8, 0x08}, {0x8, 0x04}, {0x8, 0x02}, {0x8, 0x01}, {0x5, 0x40}, {0x5, 0x20}, {0x5, 0x10}, {0x5, 0x08}, {0x5, 0x04},  {0x4, 0x1},                           {0x2, 0x08}, {0x1, 0x04}, {0x1, 0x02},\
 {0x8, 0x40}, {0x7, 0x20}, {0x7, 0x10}, {0x7, 0x08}, {0x7, 0x04}, {0x7, 0x02}, {0x7, 0x01}, {0x6, 0x40}, {0x6, 0x20}, {0x6, 0x10}, {0x6, 0x08}, {0x5, 0x02}, {0x5, 0x01},                           {0x2, 0x10}, {0x1, 0x08}, {0x1,0x10}, {0x1, 0x40},\
 {0x8, 0x80}, {0x7, 0x40}, {0x7, 0x80}                            {0x6, 0x80},              {0x6, 0x01}, {0x6, 0x02}, {0x6, 0x04},                                                                 {0x2, 0x20}, {0x1, 0x20}}

