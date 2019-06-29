/* Copyright 2018 Ben Lewis (FollowingGhosts)
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

/* This is adapted from the official ANSI layout provided by the KBP V60 Type R
* as depicted in their manual and on the stock keycaps.
*/
#include QMK_KEYBOARD_H

// -- Layers
enum layers {
    _DL, // Default
    _SL, // Symbolic
    _APL, // APL
    _AAL, // APL (Alt)
    _ASL, // APL (Shift + Alt)
    _FL, // Fn
    _EL, // Extra
    _AL, // Arrow
};

// -- Tap Dance
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    TRIPLE_TAP = 5,
    TRIPLE_HOLD = 6
};

int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed) return SINGLE_HOLD;
        else return SINGLE_TAP;
    }
    else if (state->count == 2) {
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8;
}

static int td_state = 0;

enum tap_dance_names {
    TD_SL = 0,
};

void td_sl(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);

    switch (td_state) {
        case SINGLE_TAP: set_oneshot_layer(_SL, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case SINGLE_HOLD: layer_on(_SL); break;
        case DOUBLE_TAP: layer_invert(_SL); break;
    }
}

void td_sl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_HOLD: layer_off(_SL); break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_sl, td_sl_reset)
};

// -- Unicode
enum unicode_names {
    EN,
    EM,
    PM,
    NEQ,
    INTBNG,
    APPROX,

    // Greek
    UALPH,
    UBETA,
    UGAMM,
    UDELT,
    UEPSI,
    UZETA,
    UETA,
    UTHET,
    UIOTA,
    UKAPP,
    ULAMB,
    UMU,
    UNU,
    UXI,
    UOMIC,
    UPI,
    URHO,
    USIGM,
    UTAU,
    UUPSI,
    UPHI,
    UCHI,
    UPSI,
    UOMEG,

    LALPH,
    LBETA,
    LGAMM,
    LDELT,
    LEPSI,
    LZETA,
    LETA,
    LTHET,
    LIOTA,
    LKAPP,
    LLAMB,
    LMU,
    LNU,
    LXI,
    LOMIC,
    LPI,
    LRHO,
    LSIGM,
    LTAU,
    LUPSI,
    LPHI,
    LCHI,
    LPSI,
    LOMEG,

    FSIGM,

    // APL
    AOME,
    ELEM,
    UEPS,
    ARHO,
    TLDD,
    ARRU,
    ARRD,
    AIOT,
    UIOT,
    RING,
    JOTD,
    CIRC,
    CIRD,
    STAR,
    STRD,
    ARRL,
    ARRR,
    BQUO,
    ZILD,
    TACL,
    TACR,
    BEAM,
    DIAE,
    AALP,
    CEIL,
    FLOR,
    MCRN,
    DEC,
    INC,
    SUBS,
    SPER,
    INTR,
    UNIO,
    TUP,
    TDWN,
    DLTL,
    SMLA,
    CMBA,
    UDEL,
    QDIV,
    DIV,
    MULT,
    AND,
    OR,
    GEQ,
    LEQ,
    DELD,
    DELU,
    CRLV,
    CRLD,
    CRLH,
    CRST,
    ORTL,
    ANTL,
    DASL,
    DABK,
    QCOL,
    QUAD,
    QSML,
    TCRU,
    TCRD,
    EQDF,
    NEQD,
    DIVS,
    VERT,
};

const uint32_t PROGMEM unicode_map[] = {
    [EN]      = 0x2013,
    [EM]      = 0x2014,
    [PM]      = 0x00B1,
    [NEQ]     = 0x2260,
    [INTBNG]  = 0x203D,
    [APPROX]  = 0x2248,

    // greek letters
    [UALPH] = 0x0391,
    [UBETA] = 0x0392,
    [UGAMM] = 0x0393,
    [UDELT] = 0x0394,
    [UEPSI] = 0x0395,
    [UTHET] = 0x0398,
    [UIOTA] = 0x0399,
    [UKAPP] = 0x039A,
    [ULAMB] = 0x039B,
    [UMU] = 0x039C,
    [UNU] = 0x039D,
    [UXI] = 0x039E,
    [UOMIC] = 0x039F,
    [UPI] = 0x03A0,
    [URHO] = 0x03A1,
    [USIGM] = 0x03A3,
    [UTAU] = 0x03A4,
    [UUPSI] = 0x03A5,
    [UPHI] = 0x03A6,
    [UCHI] = 0x03A7,
    [UPSI] = 0x03A8,
    [UOMEG] = 0x03A9,

    [LALPH] = 0x03B1,
    [LBETA] = 0x03B2,
    [LGAMM] = 0x03B3,
    [LDELT] = 0x03B4,
    [LEPSI] = 0x03B5,
    [LZETA] = 0x03B6,
    [LETA] = 0x03B7,
    [LTHET] = 0x03B8,
    [LIOTA] = 0x03B9,
    [LKAPP] = 0x03BA,
    [LLAMB] = 0x03BB,
    [LMU] = 0x03BC,
    [LNU] = 0x03BD,
    [LXI] = 0x03BE,
    [LOMIC] = 0x03BF,
    [LPI] = 0x03C0,
    [LRHO] = 0x03C1,
    [LSIGM] = 0x03C3,
    [LTAU] = 0x03C4,
    [LUPSI] = 0x03C5,
    [LPHI] = 0x03C6,
    [LCHI] = 0x03C7,
    [LPSI] = 0x03C8,
    [LOMEG] = 0x03C9,

    [FSIGM] = 0x03C2,

    // APL
    [AOME]  = 0x2375,
    [ELEM]  = 0x220A,
    [UEPS]  = 0x2377,
    [ARHO]  = 0x2374,
    [TLDD]  = 0x2368,
    [ARRU]  = 0x2191,
    [ARRD]  = 0x2193,
    [AIOT]  = 0x2373,
    [UIOT]  = 0x2378,
    [RING]  = 0x2218,
    [JOTD]  = 0x2364,
    [CIRC]  = 0x25CB,
    [CIRD]  = 0x2365,
    [STAR]  = 0x22C6,
    [STRD]  = 0x2363, 
    [ARRL]  = 0x2190,
    [ARRR]  = 0x2192,
    [BQUO]  = 0x235E,
    [ZILD]  = 0x236C,
    [TACL]  = 0x22A3,
    [TACR]  = 0x22A2,
    [BEAM]  = 0x2336,
    [DIAE]  = 0x00A8,
    [AALP]  = 0x237A,
    [CEIL]  = 0x2308,
    [FLOR]  = 0x230A,
    [MCRN]  = 0x00AF,
    [DEC]   = 0x2207,
    [INC]   = 0x2206,
    [SUBS]  = 0x2282,
    [SPER]  = 0x2283,
    [INTR]  = 0x2229,
    [UNIO]  = 0x222A,
    [TUP]   = 0x22A5,
    [TDWN]  = 0x22A4,
    [DLTL]  = 0x236B,
    [SMLA]  = 0x235D,
    [CMBA]  = 0x236A,
    [UDEL]  = 0x2359,
    [QDIV]  = 0x2339,
    [DIV]   = 0x00F7,
    [MULT]  = 0x00D7,
    [AND]   = 0x2227,
    [OR]    = 0x2228,
    [GEQ]   = 0x2265,
    [LEQ]   = 0x2264,
    [DELD]  = 0x2352,
    [DELU]  = 0x234B,
    [CRLV]  = 0x233D,
    [CRLD]  = 0x2349,
    [CRLH]  = 0x2296,
    [CRST]  = 0x235F,
    [ORTL]  = 0x2371,
    [ANTL]  = 0x2372,
    [DASL]  = 0x233F,
    [DABK]  = 0x2340,
    [QCOL]  = 0x2360,
    [QUAD]  = 0x2395,
    [QSML]  = 0x2337,
    [TCRU]  = 0x234E,
    [TCRD]  = 0x2355,
    [EQDF]  = 0x2261,
    [NEQD]  = 0x2262,
    [DIVS]  = 0x2223,
    [VERT]  = 0x2502,
};

// TODO: Extra layout enabled with LALT
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DL] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,      KC_0,     KC_MINS, KC_EQL,  KC_BSPC, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,      KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, \
        TT(_FL), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,          KC_ENT,  \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH,           KC_RSPC, \
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                                      TG(_AL), TD(TD_SL), TG(_APL), TT(_EL)),

    [_SL] = LAYOUT_60_ansi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XP(EN, EM), XP(APPROX, PM), KC_TRNS, \
        KC_TRNS, KC_TRNS, XP(LOMEG, UOMEG), XP(LEPSI, UEPSI), XP(LRHO, URHO), XP(LTAU, UTAU), XP(LPSI, UPSI), XP(LUPSI, UUPSI), XP(LIOTA, UIOTA), XP(LOMIC, UOMIC), XP(LPI, UPI), KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, XP(LALPH, UALPH), XP(LSIGM, USIGM), XP(LDELT, UDELT), XP(LPHI, UPHI), XP(LGAMM, UGAMM), XP(LETA, UETA), XP(LTHET, UTHET), XP(LKAPP, UKAPP), XP(LLAMB, ULAMB), KC_TRNS, KC_TRNS, UC_MOD, \
        KC_TRNS, XP(LZETA, UZETA), XP(LXI, UXI), XP(LCHI, UCHI), XP(FSIGM, USIGM), XP(LBETA, UBETA), XP(LNU, UNU), XP(LMU, UMU), KC_TRNS, KC_TRNS, X(INTBNG), KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_APL] = LAYOUT_60_ansi(
        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, \
        KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, \
        KC_TRNS,  KC_TRNS, MO(_AAL),          KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_AAL] = LAYOUT_60_ansi(
        KC_TRNS,  X(DIAE), X(MCRN), KC_LT,   X(LEQ),  KC_EQL,  X(GEQ),  KC_GT,   X(NEQ),  X(OR),   X(AND),  X(MULT), X(DIV),  KC_TRNS, \
        KC_TRNS,  KC_QUES, X(AOME), X(ELEM), X(ARHO), KC_TILD, X(ARRU), X(ARRD), X(AIOT), X(CIRC), X(STAR), X(ARRL), X(ARRR), X(TACR), \
        KC_TRNS,  X(AALP), X(CEIL), X(FLOR), KC_UNDS, X(DEC),  X(INC),  X(RING), X(DIVS), X(QUAD), X(TCRU), X(TCRD),          KC_TRNS, \
        MO(_ASL), X(SUBS), X(SPER), X(INTR), X(UNIO), X(TUP),  X(TDWN), X(VERT), X(SMLA), X(DABK), X(DASL),          KC_TRNS, \
        KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_ASL] = LAYOUT_60_ansi(
        KC_TRNS,  X(BEAM), X(DLTL), X(DELD), X(DELU), X(CRLV), X(CRLD), X(CRLH), X(CRST), X(ORTL), X(ANTL), KC_EXLM, X(QDIV), KC_TRNS, \
        KC_TRNS,  KC_TRNS, KC_TRNS, X(UEPS), KC_TRNS, X(TLDD), KC_TRNS, KC_TRNS, X(UIOT), X(CIRD), X(STRD), X(BQUO), X(ZILD), X(TACL), \
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, X(JOTD), KC_TRNS, X(QSML), X(EQDF), X(NEQD),          KC_TRNS, \
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, X(CMBA), X(UDEL), X(QCOL),          KC_TRNS, \
        KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_FL] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_PAUS, KC_TRNS, KC_TRNS, KC_DEL,  \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,  KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,          KC_TRNS, \
        KC_LCBR, BL_INC,  BL_STEP, BL_DEC,  KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS,          KC_RCBR, \
        KC_TRNS, KC_TRNS, KC_LALT,          KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_EL] = LAYOUT_60_ansi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_AL] = LAYOUT_60_ansi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_UP, \
        KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                                     KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT),

};

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // output low
        DDRE  |=  (1<<PE6);
        PORTE &= ~(1<<PE6);
    } else {
        // Hi-Z
        DDRE  &= ~(1<<PE6);
        PORTE &= ~(1<<PE6);
    }
}
