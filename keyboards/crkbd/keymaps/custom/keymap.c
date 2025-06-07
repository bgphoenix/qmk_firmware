#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "via.h"
#include "print.h"

bool is_alt_tab_active = false;
bool is_del_active = false;
bool modifier_pressed = false;
uint16_t alt_tab_timer = 0;
uint16_t del_timer = 0;

enum custom_keycodes {
    M_SLCT = QK_KB_15,
    M_CMDL,
    M_CMDR,
    M_PSBR,
    M_COPY,
    M_PSTE,
    M_ALTB,
    M_ALSH,
    M_CLST,
    M_ZMR,
    M_BSPC,
    E_SPLT,
    E_SPRT,
    E_ZMI,
    E_ZMO,
    P_OSPW,
    L_GUI
};

enum {
    TD_ESC_GRAVE,
    TD_SFT_BSPC
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_GRAVE] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRAVE),
    [TD_SFT_BSPC]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, M_BSPC)
};

#ifdef LAYOUT_split_3x6_3_ex2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  M_ZMR,    M_BSPC,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LALT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  M_BSPC,   KC_RCTL,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,             KC_M, KC_COMM,  KC_DOT, KC_SLSH,  TD(TD_ESC_GRAVE),
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          L_GUI, MO(2),  KC_ENT,       KC_SPC, MO(1), KC_LSFT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_LCTL,    KC_RCTL,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_ALSH,    KC_RALT, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_LLCK,                      KC_MINS, XXXXXXX,  KC_EXLM, KC_DOT, XXXXXXX, P_OSPW,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______, KC_ENT,     KC_SPC, _______, KC_LSFT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_LCTL,    KC_RCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, M_PSBR,    KC_RALT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_LLCK,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_ENT,     KC_SPC, MO(3), KC_RGUI
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, P_OSPW,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, QK_LLCK,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  )
};
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(E_ZMO,         E_ZMI),             ENCODER_CCW_CW(E_SPLT,          E_SPRT),        ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
  [1] = { ENCODER_CCW_CW(KC_VOLD,       KC_VOLU),           ENCODER_CCW_CW(M_CMDL,          M_CMDR),        ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
  [2] = { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT),    ENCODER_CCW_CW(KC_MS_WH_DOWN,   KC_MS_WH_UP),   ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
  [3] = { ENCODER_CCW_CW(_______,       _______),           ENCODER_CCW_CW(RGB_VAD,         RGB_VAI),       ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), },
};
#endif

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(1);
}

void matrix_scan_user(void){
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_alt_tab_active = false;
        }
    }
    if (is_del_active) {
        if (timer_elapsed(del_timer) > 1000) {
            is_del_active = false;
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        uint8_t layer = get_highest_layer(layer_state);
        HSV hsv = rgb_matrix_config.hsv;

        switch(layer) {
            case 0:
                if(modifier_pressed) {
                    hsv.h = 85; //Green
                    hsv.s = 170;
                } else {
                    if(is_del_active){
                        hsv.h = 0; //red
                        hsv.s = 255;
                    } else {
                        hsv.h = 0;
                        hsv.s = 0;
                    }
                }
            break;

            case 1:
                hsv.h = 191;
                hsv.s = 255;
            break;

            case 2:
                hsv.h = 20; //orange
                hsv.s = 255;
            break;

            case 3:
                hsv.h = 170;
                hsv.s = 255;
            break;

            default:
                hsv.h = 0;
                hsv.s = 0;
            break;
        }
        rgb_matrix_sethsv(hsv.h, hsv.s, hsv.v);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col,row});
                HSV hsv_key = rgb_matrix_config.hsv;
                RGB rgb = hsv_to_rgb(hsv_key);

                if (index >= led_min && index < led_max && index) {
                    if(modifier_pressed){
                        switch(kc){
                            case KC_Q:
                                hsv_key.h = 0;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_W:
                                hsv_key.h = 30;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_Z:
                                hsv_key.h = 128;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_S:
                                hsv_key.h = 128;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_C:
                                hsv_key.h = 200;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_V:
                                hsv_key.h = 200;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_E:
                                hsv_key.h = 0;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_T:
                                hsv_key.h = 80;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                        }
                    } else {
                        switch(kc){
                            case KC_LCTL:
                                hsv_key.h = 128;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;

                            case KC_RCTL:
                                hsv_key.h = 128;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;

                            case KC_LALT:
                                hsv_key.h = 213;
                                hsv_key.s = 127;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;

                            case KC_RALT:
                                hsv_key.h = 213;
                                hsv_key.s = 127;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;

                            case L_GUI:
                                hsv_key.h = 191;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;

                            case KC_ESC:
                                hsv_key.h = 21;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;

                            case KC_LSFT:
                                hsv_key.h = 64;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;

                            case KC_LEFT:
                                hsv_key.h = 21;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_DOWN:
                                hsv_key.h = 40;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_UP:
                                hsv_key.h = 30;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_RIGHT:
                                hsv_key.h = 25;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case M_BSPC:
                                hsv_key.h = 0;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case QK_LLCK:
                                hsv_key.h = 0;
                                hsv_key.s = 255;
                                rgb = hsv_to_rgb(hsv_key);
                                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                            break;
                            case KC_TRNS:
                                rgb_matrix_set_color(index,0, 0, 0);
                            break;
                            case XXXXXXX:
                                rgb_matrix_set_color(index,0,0,0);
                            break;
                        }
                    }
                }
            }
        }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record){

    switch (keycode) {
        case CTL_T(M_ALTB):
            if (record->tap.count && record->event.pressed) {
                tap_code16(M_ALTB);
                return false; // Return false to ignore further processing of key
            }
        break;

        case CTL_T(M_BSPC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(M_BSPC);
                return false; // Return false to ignore further processing of key
            }
        break;

        case M_SLCT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_LEFT)) SS_LCMD(SS_LSFT(SS_TAP(X_RIGHT))));
            }
            break;

        case M_CMDL:
            if (record->event.pressed) {
                SEND_STRING(SS_LOPT(SS_TAP(X_LEFT)));
            }
            break;

        case M_CMDR:
            if (record->event.pressed) {
                SEND_STRING(SS_LOPT(SS_TAP(X_RIGHT)));
            }
            break;

        case M_PSBR:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_LSFT(SS_TAP(X_V))));
            }
            break;
        case M_COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_C)));
            }
            break;

        case M_PSTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_V)));
            }
            break;


        case M_CLST:
             if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_W)));
            }
            break;
        case M_ALSH:
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LSFT);
           } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
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
        case M_ZMR: //Zoom reset
            if (record->event.pressed) {
               SEND_STRING(SS_LCMD(SS_TAP(X_0)));
           }
        case M_BSPC:
           if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_BSPC);
                if (!is_del_active) {
                    is_del_active = true;
                }
                del_timer = timer_read();
            } else {
                unregister_code(KC_BSPC);
                unregister_code(KC_LALT);
            }
        break;
        case E_SPLT:
           if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
                unregister_code(KC_LCTL);
            }
        break;
        case E_SPRT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_RIGHT);
            } else {
                unregister_code(KC_RIGHT);
                unregister_code(KC_LCTL);
            }
        break;
        case E_ZMI:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_EQUAL)));
            }
            break;

        case E_ZMO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCMD(SS_TAP(X_MINUS)));
            }
            break;

        case L_GUI:
            if (record->event.pressed) {
                modifier_pressed = true;
                register_code(KC_LGUI);
            } else {
                modifier_pressed = false;
                unregister_code(KC_LGUI);
            }
            break;
    }

    return true;
}


// #ifdef RAW_ENABLE
//     void via_qmk_rgb_matrix_set_value(uint8_t *data) {
//         // data = [ value_id, value_data ]
//         uint8_t *value_id   = &(data[0]);
//         uint8_t *value_data = &(data[1]);
//         switch (*value_id) {
//             case id_qmk_backlight_brightness: {
//                 rgb_matrix_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), (value_data[0] * RGB_MATRIX_MAXIMUM_BRIGHTNESS) / 255);
//                 break;
//             }
//             // case id_qmk_rgb_matrix_effect: {
//             //     if (value_data[0] == 0) {
//             //         rgb_matrix_disable_noeeprom();
//             //     } else {
//             //         rgb_matrix_enable_noeeprom();
//             //         rgb_matrix_mode_noeeprom(value_data[0]);
//             //     }
//             //     break;
//             // }
//             // case id_qmk_rgb_matrix_effect_speed: {
//             //     rgb_matrix_set_speed_noeeprom(value_data[0]);
//             //     break;
//             // }
//             // case id_qmk_rgb_matrix_color: {
//             //     rgb_matrix_sethsv_noeeprom(value_data[0], value_data[1], rgb_matrix_get_val());
//             //     break;
//             // }
//         }
//     }

//     void raw_hid_receive(uint8_t *data, uint8_t length) {
//         uint8_t *command_id   = &(data[0]);
//         uint8_t *command_data = &(data[1]);
//         uint8_t *value_id_and_data = &(data[2]);

//         uprintf("Received RAW HID message (length %d): ", length);
//         for (uint8_t i = 0; i < length; i++) {
//             uprintf("%02X ", data[i]);
//         }
//         uprintf("\n");

//         if (*command_id == id_custom_set_value &&
//             *command_data == id_qmk_backlight_channel) {
//             via_qmk_rgb_matrix_set_value(value_id_and_data);
//             return;
//         }
//         *command_id = id_unhandled;
//     }

// #endif



// #else
// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//   [0] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                           L_GUI, TL_LOWR,  KC_SPC,     KC_ENT, TL_UPPR, KC_RALT
//                                       //`--------------------------'  `--------------------------'

//   ),

//   [1] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//        KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                           KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
//                                       //`--------------------------'  `--------------------------'
//   ),

//   [2] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//        KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                           KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
//                                       //`--------------------------'  `--------------------------'
//   ),

//   [3] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//       QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                           KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
//                                       //`--------------------------'  `--------------------------'
//   )
// };
