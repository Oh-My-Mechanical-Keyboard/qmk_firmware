/* Copyright 2020 zvecr <git@zvecr.com>
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
#pragma once

#include "quantum.h"

#define LAYOUT( \
        kr00,    kr01,    kr02,     kr03,     kr04,     kr05,     kr06,      kr07,           kl00,    kl01,    kl02,     kl03,     kl04,     kl05,     kl06,      kl07,\
        kr10,    kr11,    kr12,               kr14,     kr15,     kr16,      kr17,           kl10,    kl11,    kl12,     kl13,     kl14,     kl15,     kl16,      kl17,\
        kr20,    kr21,    kr22,               kr24,     kr25,     kr26,      kr27,           kl20,    kl21,    kl22,     kl23,     kl24,     kl25,                kl27,\
        kr30,    kr31,    kr32,               kr34,     kr35,     kr36,      kr37,           kl30,    kl31,    kl32,     kl33,     kl34,     kl35,     kl36,      kl37,\
                 kr41,    kr42,                         kr45,     kr46,                               kl41,              kl43,     kl44,     kl45,     kl46,      kl47 \
    ) { \
    {   kl00,    kl01,    kl02,     kl03,     kl04,     kl05,     kl06,      kl07, \
        kl10,    kl11,    kl12,     kl13,     kl14,     kl15,     kl16,      kl17, \
        kl20,    kl21,    kl22,     kl23,     kl24,     kl25,     KC_NO,     kl27, \
        kl30,    kl31,    kl32,     kl33,     kl34,     kl35,     kl36,      kl37, \
        KC_NO,   kl41,    KC_NO,    kl43,     kl44,     kl45,     kl46,      kl47, \
        kr00,    kr01,    kr02,     kr03,     kr04,     kr05,     kr06,      kr07, \
        kr10,    kr11,    kr12,     KC_NO,    kr14,     kr15,     kr16,      kr17, \
        kr20,    kr21,    kr22,     KC_NO,    kr24,     kr25,     kr26,      kr27, \
        kr30,    kr31,    kr32,     KC_NO,    kr34,     kr35,     kr36,      kr37, \
        KC_NO,   kr41,    kr42,     KC_NO,    KC_NO,    kr45,     kr46,      KC_NO }}


