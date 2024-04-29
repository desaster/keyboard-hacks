// Copyright 2023 Upi Tamminen desaster@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "keychron_common.h"

#include "brightness_cycle.h"
#include "countdown_timer.h"
#include "layer_spellout.h"
#include "anti_idle.h"

#if DESASTER_DEBUG == 1
#include "print.h"
#define ddebug(...) uprintf(__VA_ARGS__)
#else
#define ddebug(...)
#endif

void rgb_matrix_init_user(void);
void rgb_matrix_set_color_by_keycode(
        uint8_t led_min,
        uint8_t led_max,
        uint8_t layer,
        bool (*is_keycode)(uint16_t),
        uint8_t red,
        uint8_t green,
        uint8_t blue);
