// Copyright 2023 Upi Tamminen desaster@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "desaster.h"

keypos_t led_index_key_position[RGB_MATRIX_LED_COUNT];

void rgb_matrix_init_user(void)
{
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED) {
                led_index_key_position[led_index] = (keypos_t) {
                    .row = row,
                    .col = col
                };
            }
        }
    }
}

void rgb_matrix_set_color_by_keycode(
        uint8_t led_min,
        uint8_t led_max,
        uint8_t layer,
        bool (*is_keycode)(uint16_t),
        uint8_t red,
        uint8_t green,
        uint8_t blue)
{
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(
                layer,
                led_index_key_position[i]);
        if ((*is_keycode) (keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}

