#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0001
#define MANUFACTURER Daz
#define PRODUCT Magicforce Handwired
#define DESCRIPTION Magicforce Handwired

#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS \
    { D4, D7, D5, C7, C6 }
#define MATRIX_COL_PINS \
    { B0, B1, B2, B3, F4, F5, B7, F6, D0, F7, D1, B6, D2, B5, D3, B4 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCING_DELAY 5

#endif
