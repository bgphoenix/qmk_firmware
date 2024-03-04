/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN
};

enum custom_keycodes{
    ZM_ORG = QK_KB_15,
    ZM_CMD,
    ZM_CTR,
    ZM_CU3,
    ZM_CU4,
    ZM_STA,
    ZM_CMT,
    ZM_SPL,
    ZM_SPR,
    ZM_CMS,
    ZM_BKT,
    ZM_BKS,
    ZM_ZON,
    ZM_MUT
};


#define SWITCH_MODE 0x1688

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_tkl_ansi(
     KC_ESC,   ZM_CU3,  ZM_CU4,  KC_MCTL,  KC_LPAD,  RGB_HUD,  RGB_HUI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,           TO(MAC_FN),   ZM_ORG,  RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   ZM_BKS, ZM_CMT,    ZM_CMS,  ZM_SPL,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, ZM_MUT,    ZM_BKT,   ZM_SPR,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,            KC_UP,
     ZM_CTR,  KC_LOPTN, ZM_CMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN, MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_tkl_ansi(
     KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             TO(MAC_BASE),  SWITCH_MODE,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  ZM_STA,  KC_TRNS,  KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  ZM_CU4,  ZM_CU3,  QK_BOOT,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_ACL0,  KC_ACL1,  KC_ACL2,            KC_TRNS,            KC_MS_U,
     KC_BTN1,  KC_TRNS,  KC_BTN2,                                ZM_ZON,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MS_L,  KC_MS_D,  KC_MS_R),

[WIN_BASE] = LAYOUT_tkl_ansi(
     KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,   KC_CTANA, RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,    KC_HOME,  KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,    KC_END,   KC_PGDN,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,             KC_UP,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RGUI, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_tkl_ansi(
     KC_TRNS,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,            KC_TRNS,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)

};

extern uint8_t is_orgb_mode;
extern uint8_t rgb_var;
extern uint8_t global_tracker;
extern uint8_t global_row;
extern uint8_t global_col;
uint8_t current_mode;

extern uint8_t active_zone;
// uint8_t active_zone = 0;

void keyboard_post_init_user(void) {
    current_mode = 0;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    switch(get_highest_layer(layer_state|default_layer_state)) {

        case MAC_BASE:
        break;

        case MAC_FN:
            rgb_matrix_set_color_all(RGB_OFF);
            rgb_matrix_set_color(active_zone+1, RGB_RED);
            rgb_matrix_set_color(13, RGB_TEAL);
            rgb_matrix_set_color(75, RGB_ORANGE); //arrow keys
            rgb_matrix_set_color(84, RGB_ORANGE);
            rgb_matrix_set_color(85, RGB_ORANGE);
            rgb_matrix_set_color(86, RGB_ORANGE);
            rgb_matrix_set_color(76, RGB_RED); //L CTRL
            rgb_matrix_set_color(78, RGB_RED); //L CMD
            rgb_matrix_set_color(79, RGB_OFF); // Space
            // rgb_matrix_set_color(34, RGB_PURPLE); // Q
            rgb_matrix_set_color(35, RGB_RED); // Q
            rgb_matrix_set_color(36, RGB_GREEN); // Q
            rgb_matrix_set_color(37, RGB_RED); // Q
            rgb_matrix_set_color(38, RGB_PINK); // Q
            // rgb_matrix_set_color(51, RGB_PURPLE); // Q
            rgb_matrix_set_color(52, RGB_PINK); // Q
            rgb_matrix_set_color(53, RGB_YELLOW); // Q
            rgb_matrix_set_color(54, RGB_WHITE); // Q
            rgb_matrix_set_color(55, RGB_PINK); // Q
            rgb_matrix_set_color(30, RGB_GREEN); // Q
            rgb_matrix_set_color(31, RGB_ORANGE); // Q
            rgb_matrix_set_color(33, RGB_ORANGE); // Q
            rgb_matrix_set_color(47, RGB_GREEN); // Q
            rgb_matrix_set_color(48, RGB_GREEN); // Q
            rgb_matrix_set_color(49, RGB_RED); // Q
            rgb_matrix_set_color(71, RGB_YELLOW); // Q
            rgb_matrix_set_color(72, RGB_YELLOW); // Q
            rgb_matrix_set_color(73, RGB_YELLOW); // Q
        break;

    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case KC_A... KC_Z:
            if (record->event.pressed) {
                global_tracker = global_tracker + 25;
                global_row = record->event.key.row;
                global_col = record->event.key.col;
                if (global_tracker >= 255) {
                    global_tracker = 0;
                }
            }
        break;

        case SWITCH_MODE:
        #ifdef OPENRGB_ENABLE
            if (record->event.pressed) {
                is_orgb_mode = !is_orgb_mode;
            }
        #endif
        return false;

        case ZM_CMD:
            if (record->event.pressed) {
                current_mode = rgb_matrix_get_mode();
                rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_my_effect_cmd);
                register_code(KC_LGUI);
            } else {
                rgb_matrix_mode_noeeprom(current_mode);
                unregister_code(KC_LGUI);
            }
        return false;

        case ZM_CTR:

            if (record->event.pressed) {
                current_mode = rgb_matrix_get_mode();
                rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_my_effect_ctrl);
                register_code(KC_LCTL);
            } else {
                rgb_matrix_mode_noeeprom(current_mode);
                unregister_code(KC_LCTL);
            }
        return false;

        case ZM_CU3:
            if(record->event.pressed) {
                SEND_STRING("tashad-5bivsy-Gabtix");
                register_code(KC_ENT);
                // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
            } else {
                unregister_code(KC_ENT);
            }
        return false;

        case ZM_CU4:
            if(record->event.pressed) {
                SEND_STRING("SHG1127");
                register_code(KC_ENT);
                // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
            } else {
                unregister_code(KC_ENT);
            }
        return false;

        case ZM_ORG:
            if(record->event.pressed) {
                if(rgb_matrix_get_mode() != RGB_MATRIX_OPENRGB_DIRECT) {
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_OPENRGB_DIRECT);
                } else {
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_custom_rgb_effect);
                }

            } else {
            }
        return false;

        case ZM_STA:
            if(record->event.pressed) {
                rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_custom_rgb_effect_2);
            }
        break;

        case ZM_CMT:
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

        case ZM_SPL:
            if (record->event.pressed) {
                register_code(KC_RCTL);
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
                unregister_code(KC_RCTL);
            }
        break;

        case ZM_SPR:
            if (record->event.pressed) {
                register_code(KC_RCTL);
                register_code(KC_RGHT);
            } else {
                unregister_code(KC_RGHT);
                unregister_code(KC_RCTL);
            }
        break;

        case ZM_CMS:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
                unregister_code(KC_LGUI);
            }
        break;

        case ZM_BKT:
            if (record->event.pressed) {
                if(rgb_var == 0) {
                    rgb_var = 1;
                } else {
                    rgb_var = 0;
                }
            }
        break;

        case ZM_BKS:
            if(record->event.pressed) {
                if(rgb_var == 1) {
                    register_code(KC_RALT);
                    register_code(KC_BSPC);
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                if(rgb_var == 1) {
                    unregister_code(KC_BSPC);
                    unregister_code(KC_RALT);
                } else {
                    unregister_code(KC_BSPC);
                }
            }
        break;

        case ZM_ZON:
            if(record->event.pressed) {
                active_zone += 1;
                if (active_zone >= 11) {
                    active_zone = 0;
                }
            }
        break;

        case ZM_MUT:
            if(record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                register_code(KC_W);
            } else {
                unregister_code(KC_W);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
         break;
    }

    return true;
}
