RGB_MATRIX_EFFECT(custom_rgb_effect_2)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

uint8_t rgb_var = 0;  // global variable shared with keymap.c

uint8_t count_number_2 = 10;
uint8_t count_modifier_2 = 13;
uint8_t count_char_left_2 = 14;
uint8_t count_char_right_2 = 12;
uint8_t count_arrow_2 = 4;
uint8_t count_fn_2 = 4;
uint8_t count_system_2 = 9;
uint8_t count_punctuation_2 = 10;
uint8_t count_esc_2 = 3;

uint8_t keys_number_2[10] = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
uint8_t keys_modifier_2[13] = {16, 33, 63, 76, 77, 78, 79, 80, 81, 82, 83, 74, 62};
uint8_t keys_char_left_2[14] = {34, 35, 36, 37, 38, 51, 52, 53, 54, 55, 64, 65, 66, 67};
uint8_t keys_char_right_2[12] = {39, 40, 41, 42, 43, 56, 57, 58, 59, 68, 69, 70};
uint8_t keys_arrow_2[4] = {75, 84, 85, 86};
uint8_t keys_fn_1_2[4] = {1, 2, 3, 4};
uint8_t keys_fn_2_2[4] = {5, 6, 7, 8};
uint8_t keys_fn_3_2[4] = {9, 10, 11, 12};
uint8_t keys_system_2[9] = {13, 14, 15, 30, 31, 32, 47, 48, 49};
uint8_t keys_punctuation_2[10] = {27, 28, 44, 45, 46, 60, 61, 71, 72, 73};
uint8_t keys_esc_2[3] = {0, 29, 50};

// static HSV reactive_math(HSV hsv, uint16_t offset) {
// #            ifdef RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
//     hsv.h = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 8) >> 4);
// #            endif
//     hsv.s = scale8(255 - offset, hsv.s);
//     return hsv;
// }

// typedef HSV (*reactive_f)(HSV hsv, uint16_t offset);

// bool effect_reactive(effect_params_t* params, reactive_f effect_func) {
//     RGB_MATRIX_USE_LIMITS(led_min, led_max);

//     uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);
//     for (uint8_t i = led_min; i < led_max; i++) {
//         RGB_MATRIX_TEST_LED_FLAGS();
//         uint16_t tick = max_tick;
//         // Reverse search to find most recent key hit
//         for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
//             if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
//                 tick = g_last_hit_tracker.tick[j];
//                 break;
//             }
//         }

//         uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
//         RGB      rgb    = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, offset));
//         rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//     }
//     return rgb_matrix_check_finished_leds(led_max);
// }

static bool effect_function_2(uint8_t *array, uint8_t array_size, uint8_t color_code) {
    // HSV hsv = rgb_matrix_config.hsv;
    // // if(rgb_var >= 255){
    // //     hsv.h = 255;
    // // } else if(rgb_var <= 0){
    // //     hsv.h = 0;
    // // } else {
    // //     hsv.h = rgb_var;
    // // }
    // RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);

    for (uint8_t i = 0; i < array_size; i++) {
        RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);

        switch(color_code) {
            case 0:
                rgb_matrix_set_color(array[i], RGB_GREEN);
            break;

            case 1:
                rgb.g = 165 + ((i/array_size)*90);
                rgb.r = 255;
                rgb.b = 0;
                rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
                // rgb_matrix_set_color(array[i], RGB_ORANGE);
            break;

            case 2:
                rgb_matrix_set_color(array[i], RGB_PURPLE);
            break;

            case 3:
                if (host_keyboard_led_state().caps_lock) {
                    rgb_matrix_set_color(array[i], RGB_RED);
                } else {
                    // RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
                    rgb.r = 0;
                    rgb.b = 255*i/array_size;
                    rgb.g = 255 - rgb.r;
                    rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
                }
            break;

            case 4:
                // RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
                rgb.g = 255*i/array_size;
                rgb.r = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
                rgb.b = 255 - rgb.r;
                // rgb.g = 255 - rgb.r;
                rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
                // rgb_matrix_set_color(array[i], RGB_PURPLE);
            break;

            case 5:
                rgb.r = 255 - (255*i/array_size);
                rgb.g = 255 - (255*i/array_size);
                rgb.b = 255*i/array_size;
                rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
            break;

            case 6:
                if (rgb_var == 0) {
                    rgb_matrix_set_color(array[i], RGB_WHITE);
                } else {
                    RGB rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
                    rgb.b = 0;
                    rgb.g = 0;
                    rgb.r = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
                    rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
                }
                // rgb_matrix_set_color(array[i], rgb.r, rgb.g, rgb.b);
            break;
        }
    }

    return true;
}

static bool custom_rgb_effect_2(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    effect_function_2(keys_number_2, count_number_2, 1);
    effect_function_2(keys_modifier_2, count_modifier_2, 1);
    effect_function_2(keys_char_left_2, count_char_left_2, 3);
    effect_function_2(keys_char_right_2, count_char_right_2, 3);
    effect_function_2(keys_fn_1_2, count_fn_2, 4);
    effect_function_2(keys_fn_2_2, count_fn_2, 4);
    effect_function_2(keys_fn_3_2, count_fn_2, 4);
    effect_function_2(keys_punctuation_2, count_punctuation_2, 5);
    effect_function_2(keys_arrow_2, count_arrow_2, 5);
    effect_function_2(keys_system_2, count_system_2, 5);
    effect_function_2(keys_esc_2, count_esc_2, 6);


    // return effect_reactive(params, &reactive_math);
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
