#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  FAST_LEFT,
  FAST_RIGHT
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE TT(_RAISE) // Tap raise twice to lock, twice to unlock
// TODO: LEDs on when on layer 2.  May help: https://www.reddit.com/r/olkb/comments/7y0290/make_backlight_leds_turn_on_on_a_certain_layer/
// TODO: Layer keys for ctrl-win-left & right (for switching Windows virtual desktop)
// TODO: Context menu, tilde, scrlock, pause, insert, capslock, macros... separate layer for rarely-used commands?  Maybe accessed by pressing both modifier keys.

// Under consideration for relocation:
//  Shift to right thumb cluster, probably innermost position to replace backspace.  So many shift combos, currently need to have two mapped just to make 'em less awkward.  Shift-enter is the only combo that would be present in that thumb cluster, and that's usually quite deliberate so it shouldn't be too bad.  Also moves a very common key off a pinkie.
//      \_ Or left thumb cluster inner space if moving CTRL?  No, makes shift+arrows awkward, and that's very common. 
//		\_ Well, I'd have to move numpad dot to make this work!  Works great, IMO, but that thumb is a period on the numpad layer!  Need to be able to use shift with the arrow keys.  Also need to be able to enter periods when using the numpad.  Maybe put enter in the stretch position, backspace back where it was, and shift in enter's space?
//  Backspace to upper stretch position on right thumb cluster. It should be less of a constant-use key (at least, once I get the hang of this! =) ), so a stretch seems permissible. Delete is used more rarely and can be moved to a pinkie.
//  CTRL to... somewhere.  Running into a number of combos of CTRL+arrows.  Could move to left pinkie if going to be moving shift.  It's a kind of common key, but not as common as shift.  Will make CTRL+Z awkward, but it always has been.
//       \_ This makes CTRL+Win+arrows (change virtual desktop) about the same as ALT+Win+arrows (move window to VD), so that's nice.
//
/************************************************
	Reasoning for keys:
	Escape: Standard position. Like to be able to hit it without centering my hands first.
	Tab:	Standard position. Not frequently used... but enough.  Not high-value real estate anyway.
	Alt:	IDK. Has to go somewhere. Kinda nice next to Control, since they fulfill similar roles. Maybe muscle memory will benefit from that.
	Control:Sort of standard position. Used frequently, but thumb cluster locations were all awkward.
	Numbers:My time spent with them reversed so symbols are the default has taught me that it's not worth the hassle.  If I'm going to use the symbols, I'd rather they be closer to the home row on the symbol layer.
	Letters:Colemak, for minimal finger strain. Qwerty is inefficient use of finger movement. Dvorak is neat, but I don't need to optimize for typing speed (or else I'd learn stenography, which QMK appears to support!). I think more than I type, and I'm more concerned about minimizing RSI.  Hence this whole project.
	
************************************************/

#define KC_FLFT FAST_LEFT  // Zip ten spaces to the left
#define KC_FRGT FAST_RIGHT  // Zip ten spaces to the right
#define KC_RST RESET
#define KC_BL_S BL_STEP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,PSCR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LALT, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL, Z  , X  , C  , V  , B  ,LGUI,     ENT , K  , M  ,COMM,DOT ,SLSH,DEL ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                            ,LOWR,RASE,       LSFT,SPC ,BSPC
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
	  F1 , F2 , F3 , F4 , F5 , F6, 				      ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      F7 , F8 , F9, F10 ,F11 ,F12 ,                   ,    ,BSLS,    ,PLUS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,LBRC,RBRC,LPRN,RPRN,EQL ,               EXLM,LABK,RABK,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,            ,    ,   
  //                  `----+----+----'        `----+----+----'

),
  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV ,VOLU,MPRV,MPLY,MNXT,    ,               NLCK,CALC,PSLS,PAST,PMNS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,VOLD,HOME, UP ,END ,PGUP,               TAB , P7 , P8 , P9 ,PPLS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,FLFT,LEFT,DOWN,RGHT,FRGT,               BSPC, P4 , P5 , P6, EQL ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,MUTE,    ,    ,    ,PGDN,    ,         ,    , P1 , P2 , P3 ,PENT,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             , P0 ,PDOT
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = KEYMAP(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      RESET  , DEBUG  , RGB_HUD, RGB_SAD, RGB_VAD, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      BL_STEP, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,                  _______, _______, _______
  //                                `--------+--------+--------'                `--------+--------+--------'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FAST_LEFT:
	  SEND_STRING(SS_TAP(X_LEFT)""SS_TAP(X_LEFT)""SS_TAP(X_LEFT)""SS_TAP(X_LEFT)""SS_TAP(X_LEFT));
      return false;
	  break;
	case FAST_RIGHT:
	  SEND_STRING(SS_TAP(X_RIGHT)""SS_TAP(X_RIGHT)""SS_TAP(X_RIGHT)""SS_TAP(X_RIGHT)""SS_TAP(X_RIGHT));
      return false;
	  break;
	case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
