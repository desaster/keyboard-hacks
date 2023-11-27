// Copyright 2023 Upi Tamminen desaster@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "desaster.h"

enum layers {
    DEF_BASE,   // default layer
    AUX1,       // toggleable layers
    AUX2,
    AUX3,
    AUX4,
    DEF_FN      // momentary layer (Fn key)
};

// List of strings for each layer. The corresponding keys will be lit up in
// order when the layer is activated or deactivated.  Must be lowercase so
// they are properly mapped to keycodes!
//
// TODO: perhaps these could be stored as settings in the eeprom
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_eeprom.md#persistent-configuration-eeprom
const char *layer_indicators[] = {
    "def",      // won't be used
    "alpha",
    "bravo",
    "charlie",
    "delta",
    "fn",       // won't be used
};

enum keycodes_user {
    KC_BRCYCLE = KC_CORTANA + 1, // continue from keychron keycodes
    KC_TIMER_ADD,
    KC_TIMER_RESET
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF_BASE] = LAYOUT_tkl_iso(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  KC_CRTA,  RGB_MOD,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,              KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,    KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(DEF_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [AUX1] = LAYOUT_tkl_iso(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [AUX2] = LAYOUT_tkl_iso(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [AUX3] = LAYOUT_tkl_iso(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [AUX4] = LAYOUT_tkl_iso(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [DEF_FN] = LAYOUT_tkl_iso(
        _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),
};

void matrix_init_user(void)
{
    rgb_matrix_init_user();
}

void housekeeping_task_user(void)
{
    housekeeping_task_keychron();
    countdown_timer_update();
    layer_spellout_update();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!process_record_keychron(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case KC_BRCYCLE:
            if (!record->event.pressed) {
                return false;
            }
            return brightness_cycle();

        case KC_TIMER_ADD:
            if (!record->event.pressed) {
                return false;
            }

            return countdown_timer_add();

        case KC_TIMER_RESET:
            if (!record->event.pressed) {
                return false;
            }

            return countdown_timer_reset();
    }

    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
    countdown_timer_set_colors(led_min, led_max);
    layer_spellout_set_colors(led_min, led_max);

    return false;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    static layer_state_t prev_state = 0;
    layer_state_t enabled, disabled;

    // check which layer was enabled or disabled, but only check layers 1-4
    enabled = get_highest_layer(((prev_state ^ state) & state) & 0b011110);
    disabled = get_highest_layer(((prev_state ^ state) & prev_state) & 0b011110);

    prev_state = state;

    // none of the layers we care about changed
    if (!enabled && !disabled) {
        return state;
    }

    ddebug("layer_state_set_user(0x%X), enabled: %d, disabled: %d\r\n",
            state, enabled, disabled);

    layer_spellout_start(
            layer_indicators[enabled ? enabled : disabled],
            enabled ? true : false);

    return state;
}
