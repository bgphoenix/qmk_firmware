RGB_MATRIX_EFFECT(opaque_user)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// uint8_t indicator_rgb = 0;
extern uint8_t indicator_backspace;
extern uint8_t indicator_encoder;
extern uint8_t indicator_dynamic_macro;

// ZONES
// 0: ESC
// 1: FN1
// 2: FN2
// 3: FN3
// 4: Keychron Specific Keys ie SS, Voice, Light
// 5: Number Row
// 6: QWERT ASDFG ZXCV
// 7: Right Hand Char
// 8: Punctuation
// 9: Modifier
// 10: Arrow
// 11: Macro

// const uint16_t zone[12][14] = {
//     {0, 16, 27, 28, 29, 30, 31, 32, 99, 99, 99, 99, 99, 99},
//     {1, 2, 3, 4, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
//     {5, 6, 7, 8, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
//     {9, 10, 11, 12, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},
//     {13, 14, 15, 30, 31, 32, 48, 49, 50, 99, 99, 99, 99, 99},
//     {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 99, 99, 99, 99},
//     {35, 36, 37, 38, 39, 53, 54, 55, 56, 57, 67, 68, 69, 70}, //QWERT ASDFG ZXCV
//     {40, 41, 42, 43, 44, 58, 59, 60, 61, 72, 73, 71, 99, 99}, // Right hand char
//     {45, 46, 47, 62, 63, 74, 75, 76, 99, 99, 99, 99, 99, 99}, // Punctuation Keys
//     {34, 52, 66, 80, 81, 82, 64, 77, 83, 84, 85, 86, 87, 99}, // Modifier Keys
//     {78, 88, 89, 90, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99}, // Arrow
//     {33, 51, 65, 79, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99} // Macro Keys
// };

uint8_t zone_opaque[12][3] = {
    {0,     0,      0}, //ESC
    {0,     0,      0}, //FN1 Off
    {0,     0,      0}, //FN2
    {0,     0,      0}, //FN3
    {0,     255,    255}, // Special Keys
    {0,     0,      0}, //Num Row
    {0,     255,    255}, //L
    {0,     255,    0}, //R
    {255,   128,    0}, //Pun
    {255,   255,    255}, //Mod
    {0,     255,    0}, //Arr
    {0,     0,      255}
};

static bool opaque_user(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    // RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);

    for (uint8_t i = 0; i < 12; i++) {
        for (uint8_t j = 0; j < 14; j++) {
            if(zone[i][j] != 99) {
                if((i == 6 || i == 7 ) && host_keyboard_led_state().caps_lock){
                    rgb_matrix_set_color(zone[i][j], RGB_RED);
                } else {
                    rgb_matrix_set_color(zone[i][j], zone_opaque[i][0], zone_opaque[i][1], zone_opaque[i][2]);
                }
            }
        }
    }

    if(indicator_backspace == 1) {
        rgb_matrix_set_color(29, RGB_RED);
    }

    if(indicator_dynamic_macro == 1)  {
        for(uint8_t i = 5; i < 13; i++){
            rgb_matrix_set_color(i, RGB_RED);
        }
    }

    // if (host_keyboard_led_state().caps_lock){
    //     rgb_matrix_set_color(52, RGB_RED);
    // }
    rgb_matrix_set_color(indicator_encoder + 1, RGB_RED);
    rgb_matrix_set_color(11, RGB_RED);
    rgb_matrix_set_color(12, RGB_RED);

    return rgb_matrix_check_finished_leds(led_max);
}
#endif
