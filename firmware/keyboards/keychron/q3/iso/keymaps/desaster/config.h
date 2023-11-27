// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

//Vial Keyboard UID
#define VIAL_KEYBOARD_UID {0x0A, 0x74, 0x0C, 0x7A, 0x62, 0xA7, 0xDA, 0x12}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

// increased number of layers from 4
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// 9009 style colors, where are these from?
#define RGB_GMK_3C 216, 151, 147        // #D89793
#define RGB_GMK_D8 129, 162, 145        // #81A291

// https://matrixzj.github.io/docs/gmk-keycaps/ColorCodes/
#define RGB_GMK_N7 0, 119, 58           // #00773a
#define RGB_GMK_P3 188, 37, 30          // #bc251e
#define RGB_GMK_CV 248, 194, 0          // #f8c200

//
// options for countdown timer feature (user/desaster/countdown_timer.c)
//

#define COUNTDOWN_BLINK_RGB RGB_GMK_3C
#define COUNTDOWN_ALARM_HSV 3, 81, 216
#define COUNTDOWN_EFFECT RGB_MATRIX_BREATHING

//
// options for layer spellout feature (users/desaster/layer_spellout.c)
//

#define LAYER_SPELLOUT_ENABLE_RGB RGB_GMK_N7
#define LAYER_SPELLOUT_DISABLE_RGB RGB_GMK_P3

//
// options for brightness cycle feature (users/desaster/brightness_cycle.c)
//

// store brightness cycle state in EEPROM?
#define BRIGHTNESS_CYCLE_EEPROM 0

#define BRIGHTNESS_CYCLE_OFF    0x00
#define BRIGHTNESS_CYCLE_MID    0x40
#define BRIGHTNESS_CYCLE_HIGH   0x80

// Disable some effects that I don't need. These are normally enabled in
// keyboards/keychron/q3/config.h

// ENABLE_RGB_MATRIX_BREATHING // this needs to be kept for stopwatch
// ENABLE_RGB_MATRIX_TYPING_HEATMAP // and keep this since it's cool
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
