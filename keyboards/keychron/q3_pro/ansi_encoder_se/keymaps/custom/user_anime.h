RGB_MATRIX_EFFECT(anim_user)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool anim_user(effect_params_t *params){
    uint16_t time     = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    return rgb_matrix_check_finished_leds(led_max);
}
#endif
