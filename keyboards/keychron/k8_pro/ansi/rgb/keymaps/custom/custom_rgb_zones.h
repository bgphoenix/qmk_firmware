RGB_MATRIX_EFFECT(custom_rgb_zones)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t active_zone = 0;

uint16_t zone[11][14] = {
    {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 99, 99, 99, 99},
    {16, 33, 63, 76, 77, 78, 79, 80, 81, 82, 83, 74, 62, 99},
    {34, 35, 36, 37, 38, 51, 52, 53, 54, 55, 64, 65, 66, 67},
    {39, 40, 41, 42, 43, 56, 57, 58, 59, 68, 69, 70, 99, 99},
    {75, 84, 85, 86, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {1, 2, 3, 4, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {5, 6, 7, 8, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {9, 10, 11, 12, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {13, 14, 15, 30, 31, 32, 47, 48, 49, 99, 99, 99, 99, 99},
    {27, 28, 44, 45, 46, 60, 61, 71, 72, 73, 99, 99, 99, 99},
    {0, 29, 50, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}
};

// bool console_init = true;

uint8_t zone_rgb[11][3] = {
    {0,     235,    60},
    {255,   25,    0},
    {200,   55,    150},
    {100,   0,    190},
    {110,   70,    100},
    {165,   155,    255},
    {190,   255,    255},
    {190,   155,    255},
    {200,   255,    255},
    {50,    255,    255},
    {90,    75,    255}
};

static bool custom_rgb_zones(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
    // if(console_init == true) {
    //     for (uint8_t i = 0; i < 11; i++) {
    //         for (uint8_t j = 0; j < 14; j++) {
    //             if(zone[i][j] <= 86){
    //                 uprintf("Value: %d. Row: %d. Column: %d. \n", zone[i][j], i, j);
    //             }
    //         }
    //     }
    //     console_init = false;
    // }

    for (uint8_t i = 0; i < 11; i++) {
        if(i == active_zone) {
            rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
            zone_rgb[i][0] = rgb.r;
            zone_rgb[i][1] = rgb.g;
            zone_rgb[i][2] = rgb.b;
        }

        for (uint8_t j = 0; j < 14; j++) {
            if(zone[i][j] <= 86){
                if (host_keyboard_led_state().caps_lock && i == active_zone){
                    rgb_matrix_set_color(zone[i][j], RGB_RED);
                } else {
                    rgb_matrix_set_color(zone[i][j], zone_rgb[i][0], zone_rgb[i][1], zone_rgb[i][2]);
                }
            }
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
