#include "63key.h"
#include "config.h"

typedef struct {
    bool    is_press_action;
    uint8_t state;
} tap;

enum { SINGLE_HOLD, CAPS_TAP };

enum {
    CAPS_LAYR,
};

uint8_t cur_dance(qk_tap_dance_state_t *state);

void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

enum layer_names { _BASE, _FN, _OTHER, _RESET };
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_BASE] = KEYMAP(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
		TD(CAPS_LAYR), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_DEL, KC_NUBS,
		KC_LCTL, KC_LGUI, KC_LALT, MO(_FN), KC_SPC, KC_SFTENT, KC_RALT, TT(_FN), KC_RCTL, KC_BSPC, KC_NUHS),

	[_FN] = KEYMAP(
		KC_GRAVE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_F13, KC_F14,
		KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_BSPC, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE, KC_DEL, KC_END, KC_PGDN, KC_TRNS, KC_INSERT, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_OTHER), KC_TRNS, KC_TRNS, KC_TRNS, KC_F15),

	[_OTHER] = KEYMAP(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_RESET), KC_TRNS, KC_TRNS, KC_TRNS),

    [_RESET] = KEYMAP(
		RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
};

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 3)
        return CAPS_TAP;
    else
        return SINGLE_HOLD;
};

static tap ql_tap_state = {.is_press_action = true, .state = 0};

void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_HOLD:
            layer_on(_FN);
            break;
        case CAPS_TAP:
            tap_code(KC_CAPS);
            break;
    }
};

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (ql_tap_state.state == SINGLE_HOLD) {
        layer_off(_FN);
    }
    ql_tap_state.state = 0;
};

qk_tap_dance_action_t tap_dance_actions[] = {[CAPS_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)};
