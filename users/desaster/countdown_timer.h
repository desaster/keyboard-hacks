// Copyright 2023 Upi Tamminen desaster@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "keychron_common.h"

void countdown_timer_update(void);
bool countdown_timer_add(void);
bool countdown_timer_reset(void);
void countdown_timer_set_colors(uint8_t led_min, uint8_t led_max);
