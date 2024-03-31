#include "qp.h"
#include "gfx/cat240x240.qgf.h"
//#include "gfx/test.qgf.h"
#include "config.h"

painter_device_t lcd;
//static painter_image_handle_t my_image;
//static deferred_token my_anim;

void keyboard_post_init_kb(void) {
    // Display timeout
    wait_ms(LCD_WAIT_TIME);

    lcd = qp_gc9a01_make_spi_device(LCD_HEIGHT, LCD_WIDTH, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, SPI_MODE);

    qp_init(lcd, LCD_ROTATION);

    // Display offset
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);

    // Power on display,
    qp_power(lcd, 1);
    // Paint catpaste/Katten Paste
    painter_image_handle_t logo_image = qp_load_image_mem(gfx_cat);
    qp_drawimage(lcd, 0, 0, logo_image);
    //my_image = qp_load_image_mem(gfx_test);

    //my_anim = qp_animate(lcd, 0, 0, my_image);
    qp_flush(lcd);
    keyboard_post_init_user();

}

// Backlight timeout feature
static uint16_t idle_timer          = 0;
static bool     lcd_on              = true;
static uint8_t  old_backlight_level = -1;

void matrix_scan_user(void) {
    // idle_timer needs to be set one time
    if (idle_timer == 0) {
        idle_timer = timer_read();
    }

    if (lcd_on && timer_elapsed(idle_timer) > QUANTUM_PAINTER_DISPLAY_TIMEOUT) {
        old_backlight_level = get_backlight_level();
        backlight_set(0);
        qp_power(lcd, false);
        lcd_on = false;
        qp_flush(lcd);
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (lcd_on == false || old_backlight_level == -1) {
            if (old_backlight_level == -1) old_backlight_level = get_backlight_level();
            backlight_set(old_backlight_level);
            lcd_on = true;
            qp_power(lcd, true);
        }
        idle_timer = timer_read();
    }
    return true;
}
