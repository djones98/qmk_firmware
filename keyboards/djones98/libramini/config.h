#pragma once

#include "config_common.h"

#define VENDOR_ID 0xDEED
#define PRODUCT_ID 0x6970
#define DEVICE_VER 0x0001
#define MANUFACTURER Daz
#define PRODUCT Daz Libra Mini
#define DESCRIPTION Daz Libra Mini

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS \
    { E6, B4, B5, B2 }
#define MATRIX_COL_PINS \
    { B3, B1, F7, F6, F5, F4, C6, D4, D0, D1, D2, D3 }
#define UNUSED_PINS

#define ANALOG_JOYSTICK_X_AXIS_PIN D7
#define ANALOG_JOYSTICK_Y_AXIS_PIN B6
#define POINTING_DEVICE_ROTATION_180
#define ANALOG_JOYSTICK_SPEED_REGULATOR 5

#define DIODE_DIRECTION ROW2COL
#define DEBOUNCING_DELAY 5
#define FORCE_NKRO
