RGB_MATRIX_EFFECT(custom_reactive)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// typedef HSV (*reactive_splash_f)(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick);
typedef RGB (*reactive_z)(RGB rgb, uint16_t offset, uint8_t i);

uint8_t static_modifier[13] = {16, 33, 63, 76, 77, 78, 79, 80, 81, 82, 83, 74, 62};
uint8_t static_zone[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 75, 84, 85, 86};
uint8_t indicator_num[10] = {17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
uint8_t global_tracker = 0;
// uint8_t var_r = 0;
// uint8_t var_g = 0;
// uint8_t var_b = 0;

extern uint8_t rgb_var;

// bool custom_runner_reactive_splash(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
bool custom_runner_reactive_splash(effect_params_t* params, reactive_z effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        uint16_t tick = max_tick;
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));
        RGB      rgb    = effect_func(rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv), offset, i);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    // =================================================================


    // uint8_t count = g_last_hit_tracker.count;
    // // uint8_t indicator_var = 0;

    // for (uint8_t i = led_min; i < led_max; i++) {
    //     RGB_MATRIX_TEST_LED_FLAGS();
    //     HSV hsv = rgb_matrix_config.hsv;
    //     hsv.s   = 100;
    //     for (uint8_t j = start; j < count; j++) {
    //         int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
    //         int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
    //         uint8_t  dist = sqrt16(dx * dx + dy * dy);
    //         uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
    //         hsv           = effect_func(hsv, dx, dy, dist, tick);
    //     }
    //     hsv.s   = scale8(hsv.s, rgb_matrix_config.hsv.s);
    //     // indicator_var = hsv.s;
    //     RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    //     rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    // }

    for(uint8_t i = 0; i < 10; i++) {
        HSV hsv_i = rgb_matrix_config.hsv;
        RGB rgb_i = rgb_matrix_hsv_to_rgb(hsv_i);
        rgb_i.g = 0;

        // if(i*15.5 <= indicator_var - 100){
        //     rgb_i.g = i*25.5;
        //     rgb_i.b = 255 - (i*25.5);
        //     rgb_matrix_set_color(indicator_num[i], rgb_i.r, rgb_i.g, rgb_i.b);
        // }
        if(i <= global_tracker/25 ){
            rgb_i.r = i*25.5;
            rgb_i.b = 255 - (i*25.5);
            rgb_matrix_set_color(indicator_num[i], rgb_i.r, rgb_i.g, rgb_i.b);
        }
    }

    for(uint8_t i = 0; i < 13; i++) {
        rgb_matrix_set_color(static_modifier[i], 255 - (i*5), i*20, 0);
    }

    for(uint8_t i = 0; i < 16; i++) {
        HSV hsv_2 = rgb_matrix_config.hsv;
        hsv_2.h = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 8) >> 4);
        hsv_2.s = 255;
        RGB rgb_2 = rgb_matrix_hsv_to_rgb(hsv_2);
        rgb_matrix_set_color(static_zone[i], rgb_2.r, rgb_2.g, rgb_2.b);
    }

    // INDICATORS
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(50, RGB_RED); // CAPS LOCK KEY
    }

    if(rgb_var == 1){
        rgb_matrix_set_color(29, RGB_RED); // BKSP indicator
    }

    //ESC Key always red
    rgb_matrix_set_color(0, RGB_RED);

    return rgb_matrix_check_finished_leds(led_max);
}


// #ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
// #    if defined(ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE) || defined(ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE)

// #        ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// RGB_MATRIX_EFFECT(SOLID_REACTIVE_WIDE)
// #        endif

// #        ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTIWIDE)
// #        endif


// =========================================================================

// static HSV custom_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
//     uint16_t effect = tick + dist * 6;
//     if (effect > 255) effect = 255;
//     hsv.h = global_tracker;
//     hsv.s = qadd8(hsv.s, 255 - effect);
//     return hsv;
// }


// =================================================================
static RGB custom_math(RGB rgb, uint16_t offset, uint8_t i) {
    rgb.r = qsub8(255, offset);
    rgb.g = qsub8(offset, (i*3));
    rgb.b = qsub8((i*3), offset/5);
    return rgb;
}

// static HSV custom_math(HSV hsv, uint16_t offset) {
//     hsv.h = global_tracker;
//     hsv.v = 255;
//     hsv.s = scale8(255 - offset, hsv.s);
//     return hsv;
// }

// #            ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// bool SOLID_REACTIVE_WIDE(effect_params_t* params) {
//     return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_WIDE_math);
// }
// #            endif

// #            ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
bool custom_reactive(effect_params_t* params) {
    return custom_runner_reactive_splash(params, &custom_math);
    // return custom_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &custom_math);
}

#endif

// #        endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
// #    endif     // !defined(ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE) || !defined(ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE)
// #endif         // RGB_MATRIX_KEYREACTIVE_ENABLED
