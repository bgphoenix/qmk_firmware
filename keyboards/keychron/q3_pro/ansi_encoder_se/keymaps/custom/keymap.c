/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;


// clang-format off
enum layers{
  MAC_BASE,
  MAC_FN,
  MAC_FN2,
  WIN_BASE,
  WIN_FN,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

enum custom_keycodes {
    M_SLCT = QK_KB_15,
    M_SRCH,
    M_COPY,
    M_PSTE,
    M_BSPC,
    M_ALTB,
    E_M001,
    E_M002,
    E_M003,
    E_M004,
    EM_CCW,
    EM_CW,
    P_OSPW,
    P_SMHC,
    P_SGML,
    T_TSMP,
    T_MAIL,
    T_NAME,
    T_PHON,
    T_NOTE
};

enum {
    TD_CAPS,
    TD_INFO,
    TD_PMHC,
    TD_CLBD,
    TD_ENCD,
    TD_RALT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_92(
        MO(WIN_FN),         KC_ESC,                  E_M001,            E_M002,    E_M003,  E_M004,     KC_MCTL,  KC_LPAD,  KC_MPRV,  KC_MPLY,          KC_MNXT,            KC_MUTE,  DM_PLY1,    DM_PLY2,        TD(TD_INFO),  TD(TD_ENCD),  RGB_MOD,
                            KC_GRV,      KC_1,       KC_2,              KC_3,      KC_4,    KC_5,       KC_6,     KC_7,     KC_8,     KC_9,             KC_0,               KC_MINS,  KC_EQL,     KC_BSPC,        KC_BTN1,      KC_MS_U,      KC_BTN2,
        OSL(MAC_FN2),       KC_TAB,      KC_Q,       KC_W,              KC_E,      KC_R,    KC_T,       KC_Y,     KC_U,     KC_I,     KC_O,             KC_P,               KC_LBRC,  KC_RBRC,    KC_BSLS,        KC_MS_L,      KC_MS_D,      KC_MS_R,
        TD(TD_PMHC),        M_BSPC,      KC_A,       KC_S,              KC_D,      KC_F,    KC_G,       KC_H,     KC_J,     KC_K,     KC_L,             KC_SCLN,            KC_QUOT,              KC_ENT,
        TD(TD_CLBD),        KC_LSFT,     KC_Z,       KC_X,              KC_C,      KC_V,    KC_B,       KC_N,     KC_M,     KC_COMM,  KC_DOT,           KC_SLSH,                                  KC_RSFT,                      KC_UP,
        M_ALTB,             KC_LCTL,     KC_LOPT,    LCMD_T(KC_DOT),                        KC_SPC,                                   RCMD_T(KC_BSPC),  ROPT_T(KC_EXLM),    MO(MAC_FN),           KC_RCTL,        KC_LEFT,      KC_DOWN,      KC_RGHT),

     [MAC_FN] = LAYOUT_ansi_92(
        RGB_TOG,            QK_BOOT,                 KC_F1,             KC_F2,     KC_F3,   KC_F4,      KC_F5,    KC_F6,    KC_F7,    KC_F8,            KC_F9,              KC_F10,   DM_REC1,    DM_REC2,        _______,      _______,      RGB_TOG,
                            _______,     BT_HST1,    BT_HST2,           BT_HST3,   _______, _______,    _______,  _______,  _______,  _______,          _______,            _______,  _______,    _______,        _______,      _______,      _______,
        M_SLCT,             CW_TOGG,     RGB_MOD,    RGB_VAI,           RGB_HUI,   RGB_SAI, RGB_SPI,    _______,  _______,  _______,  _______,          _______,            _______,  _______,    _______,        KC_DEL,       _______,      _______,
        M_COPY,             KC_CAPS,     RGB_RMOD,   RGB_VAD,           RGB_HUD,   RGB_SAD, RGB_SPD,    _______,  _______,  _______,  _______,          _______,            _______,              _______,
        M_SRCH,             _______,     _______,    _______,           _______,   _______, BAT_LVL,    NK_TOGG,  _______,  _______,  _______,          _______,                                  _______,                      _______,
        M_PSTE,             _______,     _______,    _______,                               _______,                                  _______,          _______,            _______,              _______,        _______,      _______,      _______),

     [MAC_FN2] = LAYOUT_ansi_92(
        RGB_TOG,            QK_BOOT,                 KC_F1,             KC_F2,     KC_F3,   KC_F4,      KC_F5,    KC_F6,    KC_F7,    KC_F8,            KC_F9,              KC_F10,   DM_REC1,    DM_REC2,        _______,      _______,      RGB_TOG,
                            _______,     P_OSPW,     P_SMHC,            P_SGML,    _______, _______,    _______,  _______,  _______,  _______,          _______,            _______,  _______,    _______,        _______,      _______,      _______,
        M_SLCT,             KC_MCTL,     _______,    _______,           T_MAIL,    _______, T_TSMP,     _______,  _______,  _______,  _______,          _______,            _______,  _______,    _______,        QK_BOOT,      _______,      _______,
        M_COPY,             KC_CAPS,     _______,    _______,           _______,   _______, _______,    _______,  _______,  _______,  _______,          _______,            _______,              _______,
        M_SRCH,             _______,     T_NAME,     _______,           M_COPY,    M_PSTE,  BAT_LVL,    _______,  _______,  _______,  _______,          _______,                                  _______,                      _______,
        VK_TOGG,            DM_PLY1,     _______,    DM_PLY2,                               T_NOTE,                                   DM_REC2,          _______,            _______,              DM_REC1,        _______,      _______,      _______),


    [WIN_BASE] = LAYOUT_ansi_92(
        KC_MUTE,            KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  KC_CTANA, RGB_MOD,
                            KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        _______,            KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        _______,            KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        _______,            KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        _______,            KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_92(
        RGB_TOG,            _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    _______,  _______,  RGB_TOG,
                            _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        KC_BTN1,            RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        KC_BTN2,            _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            KC_MS_U,
        _______,            KC_ACL0,  KC_ACL1,  KC_ACL2,                                _______,                                _______,  _______,  _______,    _______,  KC_MS_L,  KC_MS_D,  KC_MS_R),
};


extern uint8_t indicator_encoder;
extern uint8_t indicator_dynamic_macro;

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(EM_CCW, EM_CW)},
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [MAC_FN2]   = { ENCODER_CCW_CW(KC_MCTL, M_ALTB)},
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_white_user);
}

void matrix_scan_user(void){
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_alt_tab_active = false;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    tap_dance_action_t *action;

    switch (keycode) {
        case M_SLCT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_LEFT)) SS_LCMD(SS_LSFT(SS_TAP(X_RIGHT))) SS_LCMD(SS_TAP(X_C)));
            }
            break;

        case M_SRCH:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_SPACE)));
            }
            break;

        case M_COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_C)));
            }
            break;

        case M_PSTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_LSFT(SS_TAP(X_V))));
            }
            break;

        case M_BSPC:
            if (record->event.pressed) {
                SEND_STRING(SS_LOPT(SS_TAP(X_BSPC)));
            }
            break;

        case E_M001:
            if(record->event.pressed){ indicator_encoder = 0; }
            break;

        case E_M002:
            if(record->event.pressed){ indicator_encoder = 1; }
            break;

        case E_M003:
            if(record->event.pressed){ indicator_encoder = 2; }
            break;

        case E_M004:
            if(record->event.pressed){ indicator_encoder = 3; }
            break;

        case EM_CW:
            switch(indicator_encoder){
                case 0:
                    if (record->event.pressed) { SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT))); }
                break;

                case 1:
                    if (record->event.pressed) { SEND_STRING(SS_LALT(SS_TAP(X_RIGHT))); }
                break;

                case 2:
                    if (record->event.pressed) { SEND_STRING(SS_TAP(X_RIGHT)); }
                break;

                case 3:
                    if (record->event.pressed) { SEND_STRING(SS_TAP(X_WH_D)); }
                break;
            }
            break;

        case EM_CCW:
            switch(indicator_encoder){
                case 0:
                    if (record->event.pressed) { SEND_STRING(SS_LCTL(SS_TAP(X_LEFT))); }
                break;

                case 1:
                    if (record->event.pressed) { SEND_STRING(SS_LALT(SS_TAP(X_LEFT))); }
                break;

                case 2:
                    if (record->event.pressed) { SEND_STRING(SS_TAP(X_LEFT)); }
                break;

                case 3:
                    if (record->event.pressed) { SEND_STRING(SS_TAP(X_WH_U)); }
                break;
            }
            break;

        case M_ALTB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LGUI);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;

        case P_OSPW:
            if (record->event.pressed) { SEND_STRING("zee$han\n"); }
            break;

        case P_SMHC:
            if (record->event.pressed) { SEND_STRING("Zee$han11\n"); }
            break;

        case P_SGML:
            if (record->event.pressed) { SEND_STRING("fohjog-nidquf-3sAxre\n"); }
            break;

        case T_TSMP:
            if (record->event.pressed) { SEND_STRING("!ts "); }
            break;

        case T_MAIL:
            if (record->event.pressed) { SEND_STRING("zeeshan.mujawar@live.com"); }
            break;

        case T_NAME:
            if (record->event.pressed) { SEND_STRING("Dr Zeeshan Mujawar"); }
            break;

        case T_PHON:
            if (record->event.pressed) { SEND_STRING("9625951107"); }
            break;

        case T_NOTE:
            if (record->event.pressed) { SEND_STRING("!zm " SS_DELAY(175) SS_TAP(X_DOWN) " Room" SS_TAP(X_TAB) "!note " SS_DELAY(175) SS_TAP(X_TAB) "!mse "); }
            break;

        case TD(TD_CAPS):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(TD_RALT):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
    }

    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

void td_fn_info(tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
        case 1:
            SEND_STRING("!ts ");
            break;
        case 2:
            SEND_STRING("Dr Zeeshan Mujawar\n");
            break;
        case 3:
            SEND_STRING("zeeshan.mujawar@live.com\n");
            break;
    }
}

void td_fn_pmhc(tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
        case 1:
            SEND_STRING("zee$han\n");
            break;
        case 2:
            SEND_STRING("SHG1127\n");
            SEND_STRING(SS_TAP(X_TAB) SS_DELAY(200));
            SEND_STRING("Zee$han11\n");
            break;
    }
}

void td_fn_clbd(tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
        case 1:
            SEND_STRING(SS_LCMD(SS_TAP(X_C)));
            break;
        case 2:
            SEND_STRING(SS_LCMD(SS_LSFT(SS_TAP(X_V))));
            break;
        case 3:
            SEND_STRING(SS_LCMD(SS_TAP(X_SPACE)));
            break;
    }
}

void td_fn_encd(tap_dance_state_t *state, void *user_data) {
    switch(state->count) {
        case 1 ... 4:
            indicator_encoder = state->count - 1;
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPS] = ACTION_TAP_DANCE_TAP_HOLD(M_BSPC, CW_TOGG),
    [TD_INFO] = ACTION_TAP_DANCE_FN(td_fn_info),
    [TD_PMHC] = ACTION_TAP_DANCE_FN(td_fn_pmhc),
    [TD_CLBD] = ACTION_TAP_DANCE_FN(td_fn_clbd),
    [TD_ENCD] = ACTION_TAP_DANCE_FN(td_fn_encd),
    [TD_RALT] = ACTION_TAP_DANCE_TAP_HOLD(OSL(MAC_FN), KC_ROPT),
};

void dynamic_macro_record_start_user(void){
    indicator_dynamic_macro = 1;
}

void dynamic_macro_record_end_user(int8_t direction){
    indicator_dynamic_macro = 0;
}
