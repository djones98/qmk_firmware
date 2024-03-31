// Copyright 2024 djones98 (@djones98)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define FORCE_NKRO

#define GC_9A01

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN NO_PIN

/* LCD Configuration */
#define LCD_DC_PIN GP8
#define LCD_CS_PIN GP9
#define LCD_RST_PIN GP12

//#define LCD_BLK_PIN GP25 // Unused in this configuration
#define LCD_SPI_DIVISOR 32
#define LCD_WAIT_TIME 150
#define LCD_ROTATION QP_ROTATION_0
#define LCD_OFFSET_X 0
#define LCD_OFFSET_Y 0
//#define LCD_INVERT_COLOR

// QP Configuration
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE
//#define ST7789_NO_AUTOMATIC_VIEWPORT_OFFSETS

// Timeout configuration, default 30000 (30 sek). 0 = No timeout. Beware of image retention.
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0


#define LCD_WIDTH 240
#define LCD_HEIGHT 240
#define SPI_MODE 0

#define BACKLIGHT_PWM_DRIVER PWMD4
#define BACKLIGHT_PWM_CHANNEL 2
