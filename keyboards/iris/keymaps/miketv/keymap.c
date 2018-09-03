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
  LOWER, // Symbol layer
  RAISE, // Function/numpad layer
  ADJUST,
  FAST_LEFT,
  FAST_RIGHT,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

#define KC_LOWR LOWER
#define KC_RASE TT(_RAISE) // Tap raise thrice to lock, thrice to unlock
// TODO: LEDs on when on layer 2.  May help: https://www.reddit.com/r/olkb/comments/7y0290/make_backlight_leds_turn_on_on_a_certain_layer/
// TODO: scrlock, pause, insert, macros... separate layer for rarely-used commands?  Maybe accessed by pressing both modifier keys.
// TODO: Assign something to lower-'.  Don't need | there, as that's easy to access at lower-shift-/
// TODO: Mouse click-lock for easier dragging.  See: https://www.reddit.com/r/olkb/comments/72u3ky/toggle_mouse_button_hold/

// Currently considering:
//	 + as the combo lower-shift-D (shift-=) rather than its own key.  Initial use suggests this is a positive move.
//      Update 2018-06 - Success.  Using shift-= for + regularly.  Also using shift-\ for | (lower-shift-/), so I could assign something else to lower-'
//	 Arrow keys on lower symbol layer, to match their position on the PKL script I use on other computers.  I wonder how this will feel?  Leaving them also as-is on the numpad layer until a clear direction is established.
//      Update 2018-06 - It's good, when I remember to use it.  Getting rid of the ones on the numpad layer to force myself to adopt arrows on the symbol layer entirely.
//	 Backslash in same position as forward slash, but on symbol layer.  Its old position above the home row was... unnatural?  The two keys' positions didn't relate.  This may be more memorable.  And if I do keep hitting the wrong one, it'll just be a press of the symbol layer key to flip back and forward between them.
//      Update 2018-06 - This is much easier to remember.
//  2018-06 - Mouse control on numpad layer left hand.  To cut down on mouse usage for rudimentary stuff at least.

/************************************************
	Reasoning for keys:
	Escape: Standard position. Like to be able to hit it without centering my hands first.
	Tab:	Standard position. Not frequently used... but enough.  Not high-value real estate anyway.
	Alt:	IDK. Has to go somewhere. Kinda nice next to Control, since they fulfill similar roles. Maybe muscle memory will benefit from that.
	Control:Sort of standard position. Used frequently, but thumb cluster locations were all awkward.  Ctrl-Z isn't as bad as it looks, just shift left hand down and left one.
	Shift:	Shift is used so much, it has to be in easy reach. Under the right thumb, the only combo that isn't convenient is shift-enter, but that's a rare one and quite deliberate.  I've been moving my right pointer over to hit enter in those cases, and that appears to be working fine. 
	Delete: I use backspace more frequently than delete, so it gets preferred seating (reason: typos!).  Delete is primarily deleting files?  This could go on a modifier layer if needed, but the pinkie stretch is an awkward position that it's fine to fill.  It's also a position that's easy to hit without centering, which is convenient when mousing around email or file explorer.
	
	Number row: My time spent with them reversed (so symbols are the default) has taught me that it's not worth the hassle.  If I'm going to use the symbols, I'd rather they be closer to the home row on the symbol layer. (Update a couple months later: With this keyboard being ortholinear, I'm actually successfully building a muscle memory for top-row numbers and symbols that I never had with a staggered keyboard.  Neat!  Maybe don't need those symbols near the home row after all.  (Still keeping '!' and '(', ')' on the home row because of very frequent use and awkward reaching. '$' is fine where it is though.)
	
  Letter layout: Colemak, for minimal finger strain. Qwerty is inefficient use of finger movement. Dvorak is neat, but I don't need to optimize for typing speed (or else I'd learn stenography, which QMK appears to support!). I think more than I type, and I'm more concerned about minimizing RSI.  Hence this whole project.
	
	Mentioned earlier in individual key notes, but worth noting on its own: There's value in placing some keys so they can be hit super easily without centering one's hands on the keyboard.  The corners work well for this.  Four of the five keys I find myself hitting as one-offs while mousing or otherwise are assigned to the outside corners: Escape (panic! and dismissing dialogs), Print Screen (quick screengrab for an email), Delete (pruning emails or files), Enter/Space (confirming dialog boxes) Control (triggers mouse pointer location beacon, and flips past the Windows 10 login screen first tier without interacting with the second tier).  There's only four spots, but having the enter key on an inside corner appears to be good enough, though noticeably not as good as an outside corner for random access.
************************************************/

#define KC_FLFT FAST_LEFT  // Zip ten spaces to the left
#define KC_FRGT FAST_RIGHT  // Zip ten spaces to the right
#define KC_CLP1 LALT(LCTL(KC_F1)) // Ditto quick clipboard #1 (hold Shift to paste)
#define KC_CLP2 LALT(LCTL(KC_F2)) // Ditto quick clipboard #2 (hold Shift to paste)
#define KC_CLP3 LALT(LCTL(KC_F3)) // Ditto quick clipboard #3 (hold Shift to paste)
#define KC_RST RESET
#define KC_BL_S BL_STEP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,PSCR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LALT, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LCTL, Z  , X  , C  , V  , B  ,LGUI,     ENT , K  , M  ,COMM,DOT ,SLSH,DEL ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                        APP,LOWR,RASE,       LSFT,SPC ,BSPC
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
	  F1 , F2 , F3 , F4 , F5 , F6, 				          PGUP,HOME, UP ,END ,PGDN,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      F7 , F8 , F9, F10 ,F11 ,F12 ,               FLFT,LEFT,DOWN,RGHT,FRGT,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,LBRC,RBRC,LPRN,RPRN,EQL ,               EXLM,LABK,RABK,LCBR,RCBR,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,CLP3,CLP2,CLP1,    ,    ,         ,GRV ,    ,    ,    ,BSLS,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,            ,    ,   
  //                  `----+----+----'        `----+----+----'

),
  [_RAISE] = LAYOUT_kc(
  //,----+----+---------+----------+---------+----.              ,----+----+----+----+----+----.
     GRV ,VOLU,MPRV     ,MPLY      ,MNXT     ,MUTE,               NLCK,CALC,PSLS,PAST,PMNS,    ,
  //|----+----+---------+----------+---------+----|              |----+----+----+----+----+----|
     CAPS,VOLD,MS_BTN2  ,MS_UP     ,MS_BTN1  ,WH_U,               TAB , P7 , P8 , P9 ,PPLS,    ,
  //|----+----+---------+----------+---------+----|              |----+----+----+----+----+----|
         ,ACL0,MS_LEFT  ,MS_DOWN   ,MS_RIGHT ,WH_D,               BSPC, P4 , P5 , P6, EQL ,    ,
  //|----+----+---------+----------+---------+----+----.    ,----|----+----+----+----+----+----|
         ,ACL2,WH_L     ,BTN3     ,WH_R     ,BTN4,    ,         ,    , P1 , P2 , P3 ,PENT,    ,
  //`----+----+---------+----+-+-------------+----+----/    \----+----+----+----+----+----+----'
                                            ,    ,    ,          , P0 ,PDOT
  //                                `--------+----+----'    `----+----+----'
  ),
  
  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RTOG,RMOD,RHUI,RSAI,RVAI,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,DBUG,RHUD,RSAD,RVAD,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     BL_S,RST ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
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
