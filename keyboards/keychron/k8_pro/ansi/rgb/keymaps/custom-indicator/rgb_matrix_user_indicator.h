RGB_MATRIX_EFFECT(rgb_matrix_indicator)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t indicator_macro = 0;
uint8_t indicator_mute = 0;
uint8_t indicator_backspace = 0;
uint8_t indicator_hid = 0;

// ----------------------------------------------------------------
// ZONES
// 0: Number Row
// 1: Modifier (CMD, CTRL, ALT)
// 2; Left Characters
// 3: Right Characters
// 4: Arrow Keys
// 5: Function Group 1
// 6: Function Group 2
// 7: Function Group 3
// 8: System Keys (Del, home, insert)
// 9: Punctuation Keys
// 10: Esc, Caps Lock, Backspace
// ----------------------------------------------------------------

// ----------------------------------------------------------------
// Plan: FN1-4 will act as indicator as well as change the indicator to set layer
// 48: END key - Backspace toggle / indicator status
//
// ----------------------------------------------------------------

const uint16_t zone[11][14] = {
    {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 99, 99, 99, 99},
    {16, 33, 63, 76, 77, 78, 79, 80, 81, 82, 83, 74, 62, 99},
    {34, 35, 36, 37, 38, 51, 52, 53, 54, 55, 64, 65, 66, 67},
    {39, 40, 41, 42, 43, 56, 57, 58, 59, 68, 69, 70, 99, 99},
    {75, 84, 85, 86, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {1, 2, 3, 4, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {5, 6, 7, 8, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {9, 10, 11, 12, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {13, 14, 15, 30, 31, 32, 47, 49, 99, 99, 99, 99, 99, 99},
    {27, 28, 44, 45, 46, 60, 61, 71, 72, 73, 99, 99, 99, 99},
    {0, 29, 50, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}
};


uint8_t zone_rgb[11][3] = {
    {255,   100,   0},
    {255,   0,     0},
    {255,   255,   255},
    {255,   240,   120},
    {0,     255,   255},
    {0,     0,     0},
    {0,     0,     0},
    {0,     0,     0},
    {0,     255,   255},
    {255,   0,     255},
    {0,     255,   0}
};

static bool rgb_matrix_indicator(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);

    for (uint8_t i = 0; i < 11; i++) {
        if(i == 5){
            for (uint8_t j = 0; j < 4; j++) {
                if(j == indicator_macro) {
                    rgb_matrix_set_color(zone[i][j], RGB_TEAL);
                } else {
                    rgb_matrix_set_color(zone[i][j], zone_rgb[i][0], zone_rgb[i][1], zone_rgb[i][2]);
                }
            }
        } else if (i == 6 || i == 7) {
            for (uint8_t j = 0; j < 14; j++) {
                if(zone[i][j] <= 86){
                    if(indicator_mute == 1){
                        rgb_matrix_set_color(zone[i][j], RGB_RED);
                    } else {
                        rgb_matrix_set_color(zone[i][j], zone_rgb[i][0], zone_rgb[i][1], zone_rgb[i][2]);
                    }
                }
            }
        }
        else {
            for (uint8_t j = 0; j < 14; j++) {
                if(zone[i][j] <= 86){
                    if (host_keyboard_led_state().caps_lock && zone[i][j] == 29){
                        rgb_matrix_set_color(zone[i][j], RGB_RED);
                    } else {
                        rgb_matrix_set_color(zone[i][j], zone_rgb[i][0], zone_rgb[i][1], zone_rgb[i][2]);
                    }
                }
            }
        }
    }

    // ----------------------------------------------------------------
    // Indicator Functions
    // ----------------------------------------------------------------

    if(indidactor_backspace == 0) {
        rgb_matrix_set_color(48, RGB_RED);
        rgb_matric_Set_color(29, RGB_TEAL);
    } else {
        rgb_matrix_set_color(48, RGB_TEAL);
        rgb_matric_Set_color(29, RGB_RED);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
