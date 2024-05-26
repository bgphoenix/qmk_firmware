RGB_MATRIX_EFFECT(user_custom)

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

const uint16_t zone[8][14] = {
    {0,  13, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {14, 29, 43, 57, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
    {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10, 11, 12, 99, 99},
    {16, 17, 18, 19, 20, 31, 32, 33, 34, 35, 45, 46, 47, 48}, //QWERT ASDFG ZXCV
    {21, 22, 23, 24, 25, 36, 37, 38, 39, 49, 50, 51, 99, 99}, // Right hand char
    {26, 27, 28, 40, 41, 52, 53, 54, 30, 99, 99, 99, 99, 99}, // Punctuation Keys
    {58, 59, 60, 62, 63, 64, 42, 44, 55, 15, 99, 99, 99, 99}, // Modifier Keys
    {56, 65, 66, 67, 61, 99, 99, 99, 99, 99, 99, 99, 99, 99}, // Arrow
};

uint8_t zone_hsv[8] = {
    0, //RED ESC
    28, // ORANGE DEL
    42, // YELLOW - NUM
    126, // CYAN  - L
    160, //BLUE - R
    214, // PINK - PUNCt
    90, // GREEN - MOD
    160, //BLUE - ARR
};


static bool user_custom(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 14; j++) {
            hsv = rgb_matrix_config.hsv;

            if (host_keyboard_led_state().caps_lock && (i == 3 || i == 4)){
                hsv.h = 0;
            } else {
                hsv.h = zone_hsv[i];
            }

            if(i <= 5){
                hsv.v = 255;
            } else {
                hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            }

            rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(zone[i][j], rgb.r, rgb.g, rgb.b);
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
