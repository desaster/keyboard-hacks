// Copyright 2023 Upi Tamminen desaster@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "desaster.h"
#include "countdown_timer.h"

// TODO: could try using deferred callbacks instead
// https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md#deferred-executor-callbacks

bool countdown_active = false;
bool alarm_active = false;
uint8_t countdown_minutes = 0;
uint32_t countdown_timer = 0;
uint16_t tick_timer = 0;
bool tick_state = false;

extern rgb_config_t rgb_matrix_config;
rgb_config_t orig_config;

const uint16_t number_keycodes[] = {
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0
};

static void save_rgb_config(void)
{
    orig_config.enable = rgb_matrix_config.enable;
    orig_config.mode = rgb_matrix_get_mode();
    orig_config.speed = rgb_matrix_config.speed;
    orig_config.hsv = rgb_matrix_config.hsv;
}

static void restore_rgb_config(void)
{
    rgb_matrix_config.speed = orig_config.speed;
    rgb_matrix_mode_noeeprom(orig_config.mode);
    rgb_matrix_sethsv_noeeprom(orig_config.hsv.h, orig_config.hsv.s, orig_config.hsv.v);
    if (orig_config.enable) {
        rgb_matrix_enable_noeeprom();
    } else {
        rgb_matrix_disable_noeeprom();
    }
}

// call this in the housekeeping task
void countdown_timer_update(void)
{
    if (!countdown_active) {
        return;
    }

    // tick state for blinking the number keys
    if (!alarm_active && timer_elapsed(tick_timer) >= 500) {
        tick_state = !tick_state;
        tick_timer = timer_read();
    }

    // countdown done, start alarm
    if (!alarm_active && timer_elapsed32(countdown_timer) >= (countdown_minutes * 60000)) {
        ddebug("countdown alarm activated!\r\n");
        save_rgb_config();
        rgb_matrix_mode_noeeprom(COUNTDOWN_EFFECT); // effect
        rgb_matrix_sethsv_noeeprom(COUNTDOWN_ALARM_HSV); // color
        rgb_matrix_config.speed = 255; // faster
        alarm_active = true;
        countdown_timer = timer_read32(); // reuse timer for alarm
    }

    // alarm has played long enough
    else if (alarm_active && (timer_elapsed32(countdown_timer) >= 5000)) {
        ddebug("countdown alarm ended.\r\n");
        restore_rgb_config();
        alarm_active = false;
        countdown_active = false;
    }
}

// callback for rgb_matrix_set_color_by_keycode
bool countdown_keycode_is_lit(uint16_t keycode)
{
    // +1 so it doesn't initially light up a higher key
    uint16_t elapsed_seconds =
        timer_elapsed32(countdown_timer) / 1000 + 1;
    uint16_t remaining_minutes =
        ((countdown_minutes * 60) - elapsed_seconds) / 60;
    remaining_minutes = remaining_minutes >= 9 ? 9 : remaining_minutes;

    return tick_state && (keycode == number_keycodes[remaining_minutes]);
}

// should be called by rgb_matrix_indicators_advanced_user
void countdown_timer_set_colors(uint8_t led_min, uint8_t led_max)
{
    if (!countdown_active || alarm_active) {
        return;
    }

    rgb_matrix_set_color_by_keycode(
        led_min,
        led_max,
        0,
        countdown_keycode_is_lit,
        COUNTDOWN_BLINK_RGB);
}

// map this to a key
bool countdown_timer_add(void)
{
    ddebug("countdown_timer_add()\r\n");

    // ignore if alarm is currently active
    if (alarm_active) {
        return false;
    }

    if (!countdown_active) {
        // start countdown with one minute
        countdown_timer = timer_read32();
        countdown_active = true;
        countdown_minutes = 1;
        tick_timer = timer_read();
    } else {
        // add another minute
        countdown_minutes = countdown_minutes >= 10 ?
            countdown_minutes :
            countdown_minutes + 1;
    }

    return false;
}

// map this to a key
bool countdown_timer_reset(void)
{
    ddebug("countdown_timer_reset()\r\n");

    // ignore if alarm is currently active
    if (alarm_active) {
        return false;
    }

    countdown_active = false;
    countdown_minutes = 0;

    return false;
}
