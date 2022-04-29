#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define MATRIX_ROWS 5
#define MATRIX_COLS 13

#define MATRIX_ROW_PINS \
    { B1, F7, F6, F5, F4 }
#define MATRIX_COL_PINS \
    { D3, D2, D1, D0, D4, C6, D7, E6, B4, B5, B6, B2, B3 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCING_DELAY 5

#define LOCKING_RESYNC_ENABLE

#define PREVENT_STUCK_MODIFIERS

#define TAPPING_TOGGLE 3

#define FORCE_NKRO

#endif
