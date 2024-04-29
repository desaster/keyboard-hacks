// Copyright 2023 Upi Tamminen desaster@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "desaster.h"
#include "brightness_cycle.h"

// map this to a key
bool brightness_cycle(void)
{
    ddebug("brightness_cycle()\r\n");

    // get current brightness
    HSV curr_hsv = rgb_matrix_get_hsv();
    unsigned char brightness = curr_hsv.v;

    // step through 3 possible values.
    if (brightness < BRIGHTNESS_CYCLE_MID) {
        brightness = BRIGHTNESS_CYCLE_MID;
    } else if (brightness < BRIGHTNESS_CYCLE_HIGH) {
        brightness = BRIGHTNESS_CYCLE_HIGH;
    } else {
        brightness = BRIGHTNESS_CYCLE_OFF;
    }

    // store new values
#if BRIGHTNESS_CYCLE_EEPROM == 1
    // ..in eeprom
    rgb_matrix_sethsv(curr_hsv.h, curr_hsv.s, brightness);
#else
    // ..just in ram
    rgb_matrix_sethsv_noeeprom(curr_hsv.h, curr_hsv.s, brightness);
#endif

    return false;
}

