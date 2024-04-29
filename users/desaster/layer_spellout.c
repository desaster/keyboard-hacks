// Copyright 2023 Upi Tamminen desaster@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "desaster.h"
#include "layer_spellout.h"

// TODO: could try using deferred callbacks instead
// https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md#deferred-executor-callbacks

// timer for how long to light up a key, and when to move to the next key
uint16_t spellout_timer = 0;

// position in the indicator array, incrased when timer is up
char *spellout_pos = NULL;

// was layer enabled or disabled? this should affect the color we display
bool layer_enabled = true;

void layer_spellout_start(const char *indicator, bool enabled)
{
#if DESASTER_DEBUG == 1
    char *ipos = (char *) indicator;
#endif
    spellout_pos = (char *) indicator;
    spellout_timer = timer_read32();
    layer_enabled = enabled;

    ddebug("layer_spellout_start()\r\n");

#if DESASTER_DEBUG == 1
    ddebug("indicator:");
    while (*ipos != 0) {
        ddebug(" %d", *ipos);
        ipos++;
    }
    ddebug("\r\n");
#endif
}

// call this in the housekeeping task
void layer_spellout_update(void)
{
    if (timer_elapsed(spellout_timer) < 200) {
        return;
    }

    // if position is pointing to a zero, disable timer
    if (*spellout_pos == 0) {
        spellout_pos = NULL;
        return;
    }

    spellout_timer = timer_read32();
    spellout_pos++;
}

// callback for rgb_matrix_set_color_by_keycode
static bool layer_spellout_keycode_is_lit(uint16_t keycode)
{
    // -93 to check against the ascii value of the keycode
    return (keycode == (*spellout_pos) - 93);
}

// should be called by rgb_matrix_indicators_advanced_user
void layer_spellout_set_colors(uint8_t led_min, uint8_t led_max)
{
    // not active, or at the end of the message
    if (spellout_pos == NULL || *spellout_pos == 0) {
        return;
    }

    if (timer_elapsed(spellout_timer) < 50) {
        rgb_matrix_set_color_by_keycode(
            led_min,
            led_max,
            0,
            layer_spellout_keycode_is_lit,
            0, 0, 0);
    } else if (layer_enabled) {
        rgb_matrix_set_color_by_keycode(
            led_min,
            led_max,
            0,
            layer_spellout_keycode_is_lit,
            LAYER_SPELLOUT_ENABLE_RGB);
    } else {
        rgb_matrix_set_color_by_keycode(
            led_min,
            led_max,
            0,
            layer_spellout_keycode_is_lit,
            LAYER_SPELLOUT_DISABLE_RGB);
    }
}
