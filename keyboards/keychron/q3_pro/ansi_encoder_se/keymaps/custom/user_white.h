RGB_MATRIX_EFFECT(white_user)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

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

uint8_t zone_hsv[12] = {
    5,
    10,
    20,
    20,
    40,
    15,
    0,
    30,
    5,
    90,
    150,
    0
};


static bool white_user(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv = rgb_matrix_config.hsv;
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    uint8_t wpm = get_current_wpm();
    for (uint8_t i = 0; i < 12; i++) {
        for (uint8_t j = 0; j < 14; j++) {
            hsv = rgb_matrix_config.hsv;
            hsv.h = qadd8(wpm, zone_hsv[i]);
            if(i <= 7){
                hsv.v = 255;
            } else {
                hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            }
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(zone[i][j], rgb.r, rgb.g, rgb.b);
        }
    }

    if(indicator_dynamic_macro == 1)  {
        for(uint8_t i = 5; i < 13; i++){
            rgb_matrix_set_color(i, RGB_RED);
        }
    }

    if (host_keyboard_led_state().caps_lock){
        rgb_matrix_set_color(52, RGB_RED);
    }
    rgb_matrix_set_color(indicator_encoder + 1, RGB_RED);

    return rgb_matrix_check_finished_leds(led_max);
}
#endif
