RGB_MATRIX_EFFECT(custom_rgb_coordinate)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t global_row = 0;
uint8_t global_col = 0;

static bool custom_rgb_coordinate(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
    rgb.r = 0;

    for(uint8_t r = 0; r < MATRIX_ROWS; r++){
        if (r == global_row) {
            rgb.g = 255;
        } else {
            rgb.g = r*40;
        }
        for(uint8_t c = 0; c < MATRIX_COLS; c++){
            if(r == global_row || c == global_col) {
                rgb.b = 0;
                rgb.r = 0;
            } else {
                rgb.b = 255 - (c*15);
                rgb.r = c*15;
            }
            rgb_matrix_set_color(g_led_config.matrix_co[r][c], rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
