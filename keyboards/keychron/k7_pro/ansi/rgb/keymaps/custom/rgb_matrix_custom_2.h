RGB_MATRIX_EFFECT(user_custom_2)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t indicator_dynamic_macro;

// INDEX
// ESC | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0  | -  | =  | BKSP | DEL |
// 0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13   | 14  |

// TAB | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  | {  | }  | Slash | Home |
// 15  | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28    | 29   |

// CAP | A  | S  | D  | F  | G  | H  | J  | K  | L  | :  | "  | ENT | PGUP |
// 30  | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 40 | 41 | 42  | 43   |

// SFT | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | /  | SFT | UP | PGDN |
// 44  | 45 | 46 | 47 | 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55  | 56 | 57   |

// CTL | OPT | CMD | SPACE | CMD  | FN | FN | AR | AR | AR |
// 58  | 59  | 60  | 61    | 62   | 63 | 64 | 65 | 66 | 67 |

// ZONES
// 0: ESC, Backspace, CAPS, Space
// 1: Del, Home, Pgup, PgDn
// 2: Number Row
// 3: QWERT ASDFG ZXCV
// 4: YUIOP HJKL BNM
// 5: Punctuation
// 6: Modifier
// 7: Arrow

// const uint16_t zone[8][14] = {
//     {0,  13, 61, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
//     {14, 29, 43, 57, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
//     {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10, 11, 12, 99, 99},
//     {16, 17, 18, 19, 20, 31, 32, 33, 34, 35, 45, 46, 47, 48}, //QWERT ASDFG ZXCV
//     {21, 22, 23, 24, 25, 36, 37, 38, 39, 49, 50, 51, 99, 99}, // Right hand char
//     {26, 27, 28, 40, 41, 52, 53, 54, 30, 99, 99, 99, 99, 99}, // Punctuation Keys
//     {58, 59, 60, 62, 63, 64, 42, 44, 55, 15, 99, 99, 99, 99}, // Modifier Keys
//     {56, 65, 66, 67, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}, // Arrow
// };

uint8_t zone_rgb[8][3] = {
    {255, 0,   0},//RED ESC
    {255, 217, 0}, // RGB_GOLD COLOR
    {255, 255, 255}, // YELLOW - NUM
    {255, 255, 255}, // CYAN  - L
    {255, 255, 255}, //BLUE - R
    {255, 255, 255}, // PINK - PUNCt
    {255, 255, 255}, // GREEN - MOD
    {255, 255, 255}, //BLUE - ARR
};

uint8_t hsv_fade[14] = {
    80,
    130,
    180,
    220,
    240,
    255,
    255,
    240,
    220,
    180,
    130,
    80,
    0,
    0,
};


static bool user_custom_2(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t layer = get_highest_layer(layer_state);
    HSV hsv = rgb_matrix_config.hsv;
    // RGB rgb = rgb_matrix_config.rgb;
    // uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    if(layer == 0){
        for (uint8_t i = 0; i < 8; i++) {
            for (uint8_t j = 0; j < 14; j++) {
                if (host_keyboard_led_state().caps_lock && (i == 3 || i == 4)){
                    rgb_matrix_set_color(zone[i][j], RGB_RED);
                } else {
                    if(i == 2){
                        // hsv.h = time;
                        // hsv.s = hsv_fade[j];
                        // RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
                        rgb_matrix_set_color(zone[i][j], 255, hsv_fade[j], 0);
                    } else {
                        rgb_matrix_set_color(zone[i][j], zone_rgb[i][0], zone_rgb[i][1], zone_rgb[i][2]);
                    }
                }
            }
        }
        rgb_matrix_set_color(34, RGB_GOLD);
        rgb_matrix_set_color(37, RGB_GOLD);
    } else {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED){
                    if(keymap_key_to_keycode(layer, (keypos_t){col,row}) != KC_TRNS) {
                        if(layer == 2){
                            hsv.h = 128;
                            hsv.s = 255 - (row*50);
                            RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv);
                            rgb_matrix_set_color(index, rgb2.r, rgb2.g, rgb2.b);
                        } else {
                            rgb_matrix_set_color(index, RGB_GREEN);
                        }
                    }
                    if(keymap_key_to_keycode(layer, (keypos_t){col,row}) == KC_TRNS) {
                        rgb_matrix_set_color(index, RGB_BLACK);
                    }
                }
            }
        }
    }

    if(indicator_dynamic_macro == 1)  {
        for(uint8_t i = 1; i < 10; i++){
            rgb_matrix_set_color(i, RGB_RED);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}
#endif
