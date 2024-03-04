RGB_MATRIX_EFFECT(my_effect_cmd)
RGB_MATRIX_EFFECT(my_effect_ctrl)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

    static bool my_effect_cmd(effect_params_t* params) {
        RGB_MATRIX_USE_LIMITS(led_min, led_max);

        rgb_matrix_set_color_all(RGB_OFF);
        rgb_matrix_set_color(33, RGB_PURPLE);
        rgb_matrix_set_color(34, RGB_RED);
        rgb_matrix_set_color(35, RGB_RED);
        rgb_matrix_set_color(37, RGB_ORANGE);
        rgb_matrix_set_color(38, RGB_YELLOW);
        rgb_matrix_set_color(54, RGB_WHITE);
        rgb_matrix_set_color(63, RGB_TEAL);
        rgb_matrix_set_color(65, RGB_ORANGE);
        rgb_matrix_set_color(66, RGB_BLUE);
        rgb_matrix_set_color(67, RGB_BLUE);
        rgb_matrix_set_color(68, RGB_ORANGE);
        rgb_matrix_set_color(73, RGB_RED);
        rgb_matrix_set_color(78, RGB_GREEN);
        rgb_matrix_set_color(79, RGB_RED);
        rgb_matrix_set_color(80, RGB_GREEN);

        return rgb_matrix_check_finished_leds(led_max);
    }

    static bool my_effect_ctrl(effect_params_t* params) {
        RGB_MATRIX_USE_LIMITS(led_min, led_max);

        rgb_matrix_set_color_all(RGB_OFF);
        rgb_matrix_set_color(79, RGB_BLUE);
        rgb_matrix_set_color(76, RGB_RED);
        rgb_matrix_set_color(83, RGB_RED);
        rgb_matrix_set_color(84, RGB_BLUE);
        rgb_matrix_set_color(86, RGB_BLUE);
        rgb_matrix_set_color(16, RGB_PURPLE);

        return rgb_matrix_check_finished_leds(led_max);
    }

#endif
