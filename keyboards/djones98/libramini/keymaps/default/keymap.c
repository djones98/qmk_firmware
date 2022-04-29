#include QMK_KEYBOARD_H
#include "libramini.h"
//#include "print.h"

enum custom_keycodes {
    ARROW_KEYS = SAFE_RANGE,
};

bool    set_arrows = false;
int16_t cum_x      = 0;
int16_t cum_y      = 0;
int16_t sensor_x   = 0;
int16_t sensor_y   = 0;
int16_t cur_factor = 24;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_QUOT,
		KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, TG(1), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
		KC_RCTL, KC_LGUI, KC_LALT, LT(1,KC_SPACE), LT(2,KC_BSPC), ARROW_KEYS, KC_BTN1, KC_BTN2, KC_RSFT,KC_DEL),

	LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, 
		KC_TRNS, LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), KC_TRNS, 
		KC_TRNS, KC_NUHS, KC_NUBS, KC_TILD, KC_PIPE, KC_UNDS, KC_TRNS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_PLUS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EQL),

	LAYOUT(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, 
		KC_TRNS, KC_HOME, KC_PGUP, KC_INS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_END, KC_PGDN, KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12),

	LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == ARROW_KEYS && record->event.pressed) {
        set_arrows = !set_arrows;
    }
    return true;
};

int max(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

int min(int num1, int num2) {
    return (num1 > num2) ? num2 : num1;
}

void send_keycode(uint8_t keycode) {
    register_code(keycode);
    unregister_code(keycode);
}

void move_right(void) {
    for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
        send_keycode(KC_RIGHT);
        cum_x = max(cum_x - cur_factor, 0);
    }
    cum_y = 0;
}

void move_left(void) {
    for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
        send_keycode(KC_LEFT);
        cum_x = min(cum_x + cur_factor, 0);
    }
    cum_y = 0;
}

void move_down(void) {
    for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
        send_keycode(KC_DOWN);
        cum_y = max(cum_y - cur_factor, 0);
    }
    cum_x = 0;
}

void move_up(void) {
    for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
        send_keycode(KC_UP);
        cum_y = min(cum_y + cur_factor, 0);
    }
    cum_x = 0;
}

void arrow_key_move(void) {
    if (abs(cum_x) + abs(cum_y) >= cur_factor) {
        if (abs(cum_x) > abs(cum_y)) {
            if (cum_x > 0) {
                move_right();
            } else {
                move_left();
            }
        } else {
            if (cum_y > 0) {
                move_down();
            } else {
                move_up();
            }
        }
    }
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    sensor_x = mouse_report.x;
    sensor_y = mouse_report.y;
    if (set_arrows) {
        cum_x += sensor_x;
        cum_y += sensor_y;
        arrow_key_move();
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// void keyboard_post_init_user(void) {
//     // Customise these values to desired behaviour
//     debug_enable   = true;
//     debug_matrix   = false;
//     debug_keyboard = false;
//     debug_mouse    = false;
// }