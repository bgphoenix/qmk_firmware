RGB_MATRIX_EFFECT(rgb_user)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern bool is_alt_tab_active;
extern bool modifier_pressed;

static bool rgb_user(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t layer = get_highest_layer(layer_state);
    for (uint8_t i = 0; i < led_max; i++) {
        switch(layer){
            case 0:
                if(modifier_pressed){
                    rgb_matrix_set_color(i, RGB_GREEN);
                } else {
                    rgb_matrix_set_color(i, RGB_CYAN);
                }
                break;

            case 1:
                rgb_matrix_set_color(i, RGB_PURPLE);
            break;

            case 2:
                rgb_matrix_set_color(i, RGB_RED);
            break;

            case 3:
                rgb_matrix_set_color(i, RGB_ORANGE);
            break;
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}
#endif
