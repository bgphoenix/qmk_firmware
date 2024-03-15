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

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.

bool is_alt_shift_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_shift_tab_timer = 0;     // we will be using them soon.

// clang-format off
enum layers{
  MAC_BASE,
  MAC_FN,
  MAC_FN2,
  WIN_BASE,
  WIN_FN,
};

// enum combo_events {
//     PW_MAC,
//     PW_MHC,
//     TX_EMAIL,
//     TX_ADDR,
//     COMBO_LENGTH
// };

// uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

enum custom_keycodes {
    MRO_1 = QK_KB_15,
    MRO_2,
    MRO_SL,
    MRO_COPY,
    MRO_PASTE, // Paste
    MRO_BKSPC,
    // MRO_BKSPC_TOGGLE,
    ENC_1,
    ENC_2,
    ENC_3,
    ENC_4,
    MPW_1,
    MPW_2,
    MPW_3,
    MTS,
    MEMAIL,
    MNAME,
    MPHONE,
    // MRO_ENC_HSV_U,
    // MRO_ENC_HSV_D,
    MRO_ENC_CCW,
    MRO_ENC_CW,
    MRO_ALTTAB,
    MRO_ALSHTB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_92(
        MO(WIN_FN),     KC_ESC,                 ENC_1,    ENC_2,    ENC_3,          ENC_4,  KC_MCTL,  KC_LPAD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  DM_PLY1,    DM_PLY2,  KC_WH_D,  QK_LOCK,  RGB_MOD,
                        KC_GRV,     KC_1,       KC_2,     KC_3,     KC_4,           KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_BTN1,   KC_MS_U,  KC_BTN2,
        MO(MAC_FN2),   KC_TAB,     KC_Q,       KC_W,     KC_E,     KC_R,           KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_MS_L,   KC_MS_D,   KC_MS_R,
        CW_TOGG,        MRO_BKSPC,  KC_A,       KC_S,     KC_D,     KC_F,           KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        MRO_SL,         KC_LSFT,    KC_Z,       KC_X,     KC_C,     KC_V,           KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        MRO_ALTTAB,      KC_LCTL,    KC_LOPT,    KC_LCMD,                                KC_SPC,                                 KC_RCMD,  MO(WIN_FN),  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_92(
        RGB_TOG,        DM_RSTP,                KC_F1,    KC_F2,    KC_F3,          KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   DM_REC1,    DM_REC2,   _______,  _______,  RGB_TOG,
                        _______,    BT_HST1,    BT_HST2,  BT_HST3,  _______,        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        MRO_1,          CW_TOGG,    RGB_MOD,    RGB_VAI,  RGB_HUI,  RGB_SAI,        RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  QK_BOOT,  _______,  _______,
        MRO_COPY,     KC_CAPS,    RGB_RMOD,   RGB_VAD,  RGB_HUD,  RGB_SAD,        RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        MRO_SL,         _______,                _______,  _______,  _______,        _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,
        MRO_PASTE,       _______,    _______,    _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),

    [MAC_FN2] = LAYOUT_ansi_92(
        RGB_TOG,        _______,                KC_F1,      KC_F2,     KC_F3,        KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   DM_REC1,    DM_REC2,   _______,  _______,  RGB_TOG,
                        _______,    MPW_1,      MPW_2,      MPW_3,     _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        _______,        KC_MCTL,    _______,    _______,    MEMAIL,    _______,       MTS,      _______,  _______,  _______,  _______,  MPHONE,  _______,  _______,    _______,  QK_BOOT,  _______,  _______,
        _______,        KC_CAPS,    _______,    _______,    _______,   _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,        _______,    MNAME,      _______,    MRO_COPY,  MRO_PASTE,      _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        VK_TOGG,        _______,    _______,    _______,                                MRO_SL,                                _______,  _______,  _______,    _______,  _______,  _______,  _______),


    [WIN_BASE] = LAYOUT_ansi_92(
        KC_MUTE,  KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PSCR,  KC_CTANA, RGB_MOD,
                  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        _______,  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        _______,  KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_92(
        RGB_TOG,  _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    _______,  _______,  RGB_TOG,
                  _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        KC_BTN1,  RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        KC_BTN2,  _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,  _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            KC_MS_U,
        _______,  KC_ACL0,  KC_ACL1,  KC_ACL2,                                _______,                                _______,  _______,  _______,    _______,  KC_MS_L,  KC_MS_D,  KC_MS_R),
};

// extern uint8_t indicator_rgb;
// extern uint8_t indicator_backspace;
extern uint8_t indicator_encoder;
extern uint8_t indicator_dynamic_macro;
// extern uint8_t indicator_hsv_diff;

// const uint16_t PROGMEM combo_pass_mac[] = {MRO_1, KC_M, COMBO_END};
// const uint16_t PROGMEM combo_pass_mhc[] = {MRO_1, KC_P, COMBO_END};
// const uint16_t PROGMEM combo_email[] = {MRO_1, KC_E, COMBO_END};
// const uint16_t PROGMEM combo_address[] = {MRO_1, KC_A, COMBO_END};

// combo_t key_combos[] = {
//   [PW_MAC] = COMBO_ACTION(combo_pass_mac),
//   [PW_MHC] = COMBO_ACTION(combo_pass_mhc),
//   [TX_EMAIL] = COMBO_ACTION(combo_email),
//   [TX_ADDR] = COMBO_ACTION(combo_address)
// };


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(MRO_ENC_CCW, MRO_ENC_CW)},
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [MAC_FN2]   = { ENCODER_CCW_CW(MRO_ALSHTB, MRO_ALTTAB)},
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_white_user);
}

void matrix_scan_user(void) { // The very important timer.
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_alt_tab_active = false;
        }
    }

    if (is_alt_shift_tab_active) {
        if (timer_elapsed(alt_shift_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT);
            is_alt_shift_tab_active = false;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
        case MRO_1:
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_LEFT);
                unregister_code(KC_LCMD);
                unregister_code(KC_LEFT);

                register_code(KC_LCMD);

                register_code(KC_LSFT);
                register_code(KC_RGHT);
                unregister_code(KC_LSFT);
                unregister_code(KC_RGHT);

                register_code(KC_C);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_C);
            }
        break;

        case MRO_2:
            // if (record->event.pressed) {
            //     register_code(KC_LCTL);
            //     register_code(KC_RGHT);
            // } else {
            //     unregister_code(KC_LCTL);
            //     unregister_code(KC_RGHT);
            // }
        break;

        case MRO_SL:
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
                unregister_code(KC_LCMD);
            }
        break;

        case MRO_COPY:
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_C);
            } else {
                unregister_code(KC_C);
                unregister_code(KC_LCMD);
            }
        break;

        case MRO_PASTE:
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_LSFT);
                register_code(KC_V);
            } else {
                unregister_code(KC_V);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCMD);
            }
        break;

        case MRO_BKSPC:
            if (record->event.pressed) {
            //     if(indicator_backspace == 0) {
            //         register_code(KC_BSPC);
            //     } else {
                    register_code(KC_RALT);
                    register_code(KC_BSPC);
                // }
            } else {
                // if(indicator_backspace == 0) {
                    // unregister_code(KC_BSPC);
                // } else {
                    unregister_code(KC_BSPC);
                    unregister_code(KC_RALT);
                // }
            }
        break;

        // case MRO_BKSPC_TOGGLE:
        //     if (record->event.pressed) {
        //         if(indicator_backspace == 0) {
        //             indicator_backspace = 1;
        //         } else {
        //             indicator_backspace = 0;
        //         }
        //     }
        // break;

        case ENC_1:
            if (record->event.pressed) {
                indicator_encoder = 0;
            }
        break;

        case ENC_2:
            if (record->event.pressed) {
                indicator_encoder = 1;
            }
        break;

        case ENC_3:
            if (record->event.pressed) {
                indicator_encoder = 2;
            }
        break;

        case ENC_4:
            if (record->event.pressed) {
                indicator_encoder = 3;
            }
        break;

        case MRO_ENC_CW:
            switch(indicator_encoder){
                case 0:
                    if (record->event.pressed) {
                        register_code(KC_LCTL);
                        register_code(KC_RGHT);
                    } else {
                        unregister_code(KC_LCTL);
                        unregister_code(KC_RGHT);
                    }
                break;

                case 1:
                    if (record->event.pressed) {
                        register_code(KC_VOLU);
                    } else {
                        unregister_code(KC_VOLU);
                    }
                break;

                case 2:
                    if (record->event.pressed) {
                        register_code(KC_RGHT);
                    } else {
                        unregister_code(KC_RGHT);
                    }
                break;

                case 3:
                    if (record->event.pressed) {
                        register_code(KC_WH_D);
                    } else {
                        unregister_code(KC_WH_D);
                    }
                break;
            }
        break;

        case MRO_ENC_CCW:
            switch(indicator_encoder){
                case 0:
                    if (record->event.pressed) {
                        register_code(KC_LCTL);
                        register_code(KC_LEFT);
                    } else {
                        unregister_code(KC_LCTL);
                        unregister_code(KC_LEFT);
                    }
                break;

                case 1:
                    if (record->event.pressed) {
                        register_code(KC_VOLD);
                    } else {
                        unregister_code(KC_VOLD);
                    }
                break;

                case 2:
                    if (record->event.pressed) {
                        register_code(KC_LEFT);
                    } else {
                        unregister_code(KC_LEFT);
                    }
                break;

                case 3:
                    if (record->event.pressed) {
                        register_code(KC_WH_U);
                    } else {
                        unregister_code(KC_WH_U);
                    }
                break;
            }
        break;

        case MRO_ALTTAB:
            if (record->event.pressed) {
                if (is_alt_shift_tab_active) {
                        unregister_code(KC_LGUI);
                        unregister_code(KC_LSFT);
                        is_alt_shift_tab_active = false;
                }
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

        case MRO_ALSHTB:
            if (record->event.pressed) {
                if (is_alt_tab_active) {
                        unregister_code(KC_LGUI);
                        is_alt_tab_active = false;
                }
                if (!is_alt_shift_tab_active) {
                    is_alt_shift_tab_active = true;
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                }
                alt_shift_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
        break;

        case MPW_1:
            if (record->event.pressed) {
                SEND_STRING("zee$han\n");
                // register_code(KC_ENT);
            } else {
                // unregister_code(KC_ENT);
            }
        break;

        case MPW_2:
            if (record->event.pressed) {
                SEND_STRING("Zee$han11\n");
                // register_code(KC_ENT);
            } else {
                // unregister_code(KC_ENT);
            }
        break;

        case MPW_3:
            if (record->event.pressed) {
                SEND_STRING("fohjog-nidquf-3sAxre\n");
            }
        break;

        case MTS:
            if (record->event.pressed) {
                SEND_STRING("!ts ");
            }
        break;

        case MEMAIL:
            if (record->event.pressed) {
                SEND_STRING("zeeshan.mujawar@live.com");
            }
        break;

        case MNAME:
            if (record->event.pressed) {
                SEND_STRING("Dr Zeeshan Mujawar");
            }
        break;

        case MPHONE:
            if (record->event.pressed) {
                SEND_STRING("9625951107");
            }
        break;


    }

    return true;
}

// void process_combo_event(uint16_t combo_index, bool pressed) {
//   switch(combo_index) {
//     case PW_MAC:
//       if (pressed) {
//         SEND_STRING("zee$han");
//       }
//     break;

//     case PW_MHC:
//       if (pressed) {
//         SEND_STRING("tashad-5bivsy-Gabtix");
//       }
//     break;

//     case TX_EMAIL:
//       if (pressed) {
//         SEND_STRING("zeeshan.mujawar@live.com");
//       }
//     break;

//     case TX_ADDR:
//       if (pressed) {
//         SEND_STRING("K1105, Emaar Emerald Estate, Sector 65, Gurgaon (HR) - 122018");
//       }
//     break;

//   }
// }

void dynamic_macro_record_start_user(void){
    indicator_dynamic_macro = 1;
    // return true;
}

void dynamic_macro_record_end_user(int8_t direction){
    indicator_dynamic_macro = 0;
    // return true;
}

        // case MRO_:
        //     if (record->event.pressed) {
        //         register_code();
        //     } else {
        //         unregister_code();
        //     }
        // break;
