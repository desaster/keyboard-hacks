// Copyright 2023 Upi Tamminen desaster@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "keychron_common.h"

void layer_spellout_start(const char *indicator, bool enabled);
void layer_spellout_update(void);
void layer_spellout_set_colors(uint8_t led_min, uint8_t led_max);
