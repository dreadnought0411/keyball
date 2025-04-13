/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_Q           , KC_W           , KC_E           , KC_R           , KC_T           ,                                    KC_Y           , KC_U           , KC_I           , KC_O           , KC_P           ,
    LCTL_T(KC_A)   , KC_S           , KC_D           , KC_F           , KC_G           ,                                    KC_H           , KC_J           , KC_K           , KC_L           , RCTL_T(KC_ENT) ,
    LSFT_T(KC_Z)   , KC_X           , LALT_T(KC_C)   , LCMD_T(KC_V)   , KC_B           ,                                    KC_N           , RCMD_T(KC_M)   , KC_COMM        , KC_DOT         , RSFT_T(KC_MINS),
    KC_ESC         , KC_LGUI        , KC_LALT        , LCMD_T(KC_LNG2), LT(1,KC_SPC)   ,  LT(3,KC_TAB)   , KC_BSPC        , LT(2,KC_LNG1)  , LSFT_T(KC_LNG2), KC_RALT        , KC_RGUI        , MO(2)
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      _______    , _______    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),

  [4] = LAYOUT_universal(
    KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    G(KC_A), G(KC_S), KC_NO  , KC_NO  , KC_NO  ,                            KC_NO  , KC_BTN1, KC_BTN3, KC_BTN2, KC_NO  ,
    G(KC_Z), G(KC_X), G(KC_C), G(KC_V), KC_NO  ,                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Check if layer 3 is active
    keyball_set_scroll_mode((state & (1 << 3)) != 0);
    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
      keyball_handle_auto_mouse_layer_change(state);
    #endif
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LGUI_T(KC_LNG2):
    case LT(1, KC_SPC):
    case LT(2, KC_LNG1):
    case LSFT_T(KC_Z):
    case LCTL_T(KC_A):
    case LALT_T(KC_C):
    case CMD_T(KC_V):
    case RCTL_T(KC_ENT):
    case RSFT_T(KC_MINS):
    case RGUI_T(KC_M):
      return true;
    default:
      return false;
  }
}