/* Copyright 2020 melonbred
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

#include "features/achordion.h" // customize the tap-hold decision


// Defines names for use in layer keycodes and the keymap
enum layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
    _LAYER4,
    _LAYER5,
    _LAYER6,
};


enum custom_keycodes {
    SCOPE = SAFE_RANGE,
    ARRIN,
    UPDIR,
    COLEQ,
};


// define combo names
enum combos {
    FA_LCTL,
    FS_LALT,
//    DS_NUMS,
    FD_LGUI,
    JK_RGUI,
    KL_LGUILSFT,
    JL_LALT,
    JKL_ENTR,
    JSC_RCTL,
//    ER_TAB,
    GH_CAPSWRD,
    UI_BKSP,
    // more here...

    COMBO_LENGTH
};


uint16_t COMBO_LEN = COMBO_LENGTH;

// define keys that make up combos
const uint16_t PROGMEM fa_combo[] = {KC_F, KC_A, COMBO_END};
const uint16_t PROGMEM fs_combo[] = {KC_F, KC_S, COMBO_END};
//const uint16_t PROGMEM ds_combo[] = {KC_D, KC_S, COMBO_END}; // NUMPAD Toggle
const uint16_t PROGMEM fd_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END}; // Mainly for screen cap and redo
const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM jkl_combo[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM jsc_combo[] = {KC_J, KC_SCLN, COMBO_END};
//const uint16_t PROGMEM er_combo[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM gh_combo[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
// more here...



// map combo names to their keys and the key they trigger
combo_t key_combos[] = {
    [FA_LCTL] = COMBO(fa_combo, KC_LCTL),
    [FS_LALT] = COMBO(fs_combo, KC_LALT),
//    [DS_NUMS] = COMBO(ds_combo,), // TODO
    [FD_LGUI] = COMBO(fd_combo, KC_LGUI),
    [JK_RGUI] = COMBO(jk_combo, KC_RGUI),
    [KL_LGUILSFT] = COMBO(kl_combo, LSFT(KC_LGUI)),
    [JL_LALT] = COMBO(jl_combo, KC_LALT),
    [JKL_ENTR] = COMBO(jkl_combo, KC_ENT),
    [JSC_RCTL] = COMBO(jsc_combo, KC_RCTL),
//    [ER_TAB] = COMBO(er_combo, KC_TAB),
    [GH_CAPSWRD] = COMBO(gh_combo, CAPSWRD),
    [UI_BKSP] = COMBO(ui_combo, KC_BSPC),
    // more here...
};



bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case SCOPE: // Types ::
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;

        case ARRIN: // Types <-
            if (record->event.pressed) {
                SEND_STRING("<-");
            }
            return false;

        case UPDIR: // Types ../
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;
        case COLEQ: // Types :=
            if (record->event.pressed) {
                SEND_STRING(":=");
            }
            return false;
    }
    return true;
};

// Hold TAB to send left ALT, Tap to send TAB
#define ALT_TAB MT(MOD_LALT,KC_TAB)



// Hold SPACE to switch to layer 1, Tap to send SPACE
#define SPC_FN1 LT(1,KC_SPC)


/*
// key overrides
const key_override_t tilde_esc_override = ko_make_basic(MOD_MASK_GUI, ALT_TAB, S(KC_GRV));
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_GUI, ALT_TAB, KC_GRV);


const key_override_t **key_overrides = (const key_override_t *[]){
    &tilde_esc_override,
    &grave_esc_override,
    NULL
};
*/



// Home row mods
#define HOME_A LT(2,KC_A)
//#define HOME_S LALT_T(KC_S)
//#define HOME_D LSFT_T(KC_D)
//#define HOME_F LGUI_T(KC_F)
//#define HOME_J RGUI_T(KC_J)
//#define HOME_K RSFT_T(KC_K)
//#define HOME_L LALT_T(KC_L)
#define HOME_SC LT(2,KC_SCLN)
//#define HOME_SL RCTL_T(KC_SLSH)
//#define HOME_Z LCTL_T(KC_Z)
#define HOME_G LSFT_T(KC_G)
#define HOME_H RSFT_T(KC_H)

// Combos

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200 

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

#define PERMISSIVE_HOLD

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat
#define TAPPING_FORCE_HOLD



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT_default( // Homerow mods (base)
        ALT_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LGUI, HOME_A,  KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    HOME_SC, KC_ENT,
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
        KC_LCTL, KC_LGUI,                            SPC_FN1,                                     MO(3),   MO(4)
    ),

    [_LAYER1] = LAYOUT_default( // Navigation and numerics
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_CAPS, MO(5),   KC_LCTL, KC_LGUI, KC_LALT, MO(6),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______,                            _______,                                     C(KC_1), C(KC_2)
    ),

    [_LAYER2] = LAYOUT_default( // Symbols
        KC_TILD, KC_EXLM, KC_BSLS, KC_GRV,  KC_PERC, KC_LABK, KC_RABK, KC_MINS, KC_PLUS, KC_HASH, _______, _______,
        KC_QUES, KC_AT,   KC_DLR,  KC_LBRC, KC_RBRC, KC_UNDS, KC_PEQL, ARRIN,   SCOPE,   UPDIR,   KC_QUOT, KC_DQUO,
        KC_SLSH, KC_AMPR, KC_PIPE, KC_LCBR, KC_RCBR, KC_TILD, KC_ASTR, KC_CIRC, COLEQ,   _______, _______, _______,
        _______, _______,                            _______,                                     _______, _______
    ),

    [_LAYER3] = LAYOUT_default( // Numpad
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS, KC_MINS, KC_7,    KC_8,    KC_9,    KC_BSPC,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PEQL, XXXXXXX, KC_PAST, KC_PPLS, KC_4,    KC_5,    KC_6,    KC_ENT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PERC, KC_CIRC, KC_1,    KC_2,    KC_3,    KC_RSPC,
        XXXXXXX, XXXXXXX,                            XXXXXXX,                                     KC_0,    KC_PDOT
    ),

    [_LAYER4] = LAYOUT_default( // F row and board management
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F12,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______,                            _______,                                     _______, _______
    ),

    [_LAYER5] = LAYOUT_default( // Navigation 2
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, C(KC_F9), KC_PGDN, KC_PGUP, C(KC_F10), XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX,                                        XXXXXXX, XXXXXXX
    ),

    [_LAYER6] = LAYOUT_default( // Media Control
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,                            XXXXXXX,                                     XXXXXXX, XXXXXXX
    ),
};












    uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
            return TAPPING_TERM - 20;
        case HOME_SC:
            return TAPPING_TERM - 90;
//        case HOME_L:
//            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}



bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to the next key
            return true;

        // Keycodes that continue Caps Word, without shifting
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_MINS:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word
    }
}


bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
    return achordion_opposite_hands(tap_hold_record, other_record);                    
}

/*
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    switch (tap_hold_keycode) {
        case HOME_SC:
        case HOME_Z:
            return 0; // Bypass Achordion for these keys
    }

    return 800; // Otherwise use a timeout of 800 ms
}
*/