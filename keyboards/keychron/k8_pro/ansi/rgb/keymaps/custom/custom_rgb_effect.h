RGB_MATRIX_EFFECT(custom_rgb_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t count_number = 10;
uint8_t count_modifier = 13;
uint8_t count_char_left = 14;
uint8_t count_char_right = 12;
uint8_t count_arrow = 4;
uint8_t count_fn = 4;
uint8_t count_system = 9;
uint8_t count_punctuation = 10;
uint8_t count_esc = 3;

uint8_t keys_number[10] = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
uint8_t keys_modifier[13] = {16, 33, 63, 76, 77, 78, 79, 80, 81, 82, 83, 74, 62};
uint8_t keys_char_left[14] = {34, 35, 36, 37, 38, 51, 52, 53, 54, 55, 64, 65, 66, 67};
uint8_t keys_char_right[12] = {39, 40, 41, 42, 43, 56, 57, 58, 59, 68, 69, 70};
uint8_t keys_arrow[4] = {75, 84, 85, 86};
uint8_t keys_fn_1[4] = {1, 2, 3, 4};
uint8_t keys_fn_2[4] = {5, 6, 7, 8};
uint8_t keys_fn_3[4] = {9, 10, 11, 12};
uint8_t keys_system[9] = {13, 14, 15, 30, 31, 32, 47, 48, 49};
uint8_t keys_punctuation[10] = {27, 28, 44, 45, 46, 60, 61, 71, 72, 73};
uint8_t keys_esc[3] = {0, 29, 50};


static bool effect_function(uint8_t *array, uint8_t array_size, uint8_t offset, uint8_t code) {

    HSV hsv = rgb_matrix_config.hsv;
    uint8_t calc_value = 0;
    uint8_t wpm = get_current_wpm();
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    // uint16_t max_tick = 6553 / qadd8(rgb_matrix_config.speed, 1);

    uint8_t calc_hue = hsv.h + offset;
    if (calc_hue > 255) {
        calc_hue = calc_hue - 255;
    }
    hsv.h = calc_hue;

    RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);

    switch(code) {

        case 0: // static color
            for (uint8_t i = 0; i < array_size; i++) {
                rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
            }
        break;

        case 1: // breathing clolor
            hsv.v     = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            rgb       = rgb_matrix_hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < array_size; i++) {
                rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
            }
        break;

        case 2: // WPM
            calc_value = (wpm / 7);
            for (uint8_t i = 0; i < array_size; i++) {
                if (calc_value > i) {
                    rgb_matrix_set_color(array[i], RGB_TEAL);
                } else {
                    rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
                }
            }
        break;

        case 3: // WPM
            if(wpm > 50) {
                hsv.h = 255;
            } else {
                hsv.h = wpm * 5;
            }

            rgb = rgb_matrix_hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < array_size; i++) {
                rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
            }
        break;

        case 5: // CAPS Lock indicator
            for (uint8_t i = 0; i < array_size; i++) {
                 if (host_keyboard_led_state().caps_lock) {
                    rgb_matrix_set_color(array[i], RGB_RED);
                 } else {
                    rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
                 }
            }
        break;

    }


    return true;

}

static bool custom_rgb_effect(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_function(keys_number, count_number, rgb_matrix_config.speed / 3, 2);
    effect_function(keys_modifier, count_modifier, 0, 0);
    effect_function(keys_char_left, count_char_left, rgb_matrix_config.speed / 2, 5);
    effect_function(keys_char_right, count_char_right, rgb_matrix_config.speed, 5);
    effect_function(keys_fn_1, count_fn, rgb_matrix_config.speed/2, 0);
    effect_function(keys_fn_2, count_fn, rgb_matrix_config.speed/3, 0);
    effect_function(keys_fn_3, count_fn, rgb_matrix_config.speed/4, 0);
    effect_function(keys_punctuation, count_punctuation, rgb_matrix_config.speed / 4, 0);
    effect_function(keys_arrow, count_arrow, rgb_matrix_config.speed / 2, 0);
    effect_function(keys_system, count_system, rgb_matrix_config.speed, 1);
    effect_function(keys_esc, count_esc, 70, 0);


    // return effect_reactive(params, &reactive_math);
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
