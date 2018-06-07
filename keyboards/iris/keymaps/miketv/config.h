/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

/* Use I2C or Serial, not both */

//#define USE_SERIAL
#define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 12
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#define TAPPING_TOGGLE 3

// See docs at https://github.com/qmk/qmk_firmware/pull/2246/commits/21992562d6246c9601c1c64936af60e5952d7f9a
#define MK_3_SPEED // 3-speed constant speed enabled (remove this to restore default acceleration mode)
#define MK_MOMENTARY_ACCEL // comment this out for tap-to-select acceleration
//#define MOUSEKEY_INTERVAL          50
// cursor speeds:
//#define MOUSEKEY_MAX_SPEED         10
//#define MOUSEKEY_TIME_TO_MAX       20
#define MK_C_OFFSET_SLOW     1 // pixels
#define MK_C_INTERVAL_SLOW  16 // milliseconds
#define MK_C_OFFSET_MED      6
#define MK_C_INTERVAL_MED   16
#define MK_C_OFFSET_FAST    18
#define MK_C_INTERVAL_FAST  16
// scroll wheel speeds:
#define MK_W_OFFSET_SLOW     1 // wheel clicks
#define MK_W_INTERVAL_SLOW  75 // milliseconds
#define MK_W_OFFSET_MED      1
#define MK_W_INTERVAL_MED   25
#define MK_W_OFFSET_FAST     1
#define MK_W_INTERVAL_FAST   1

// Found at https://www.reddit.com/r/olkb/comments/72u8ou/qmk_mouse_keys_rock/?st=ji4sk0lh&sh=3d00d293
#define MOUSEKEY_DELAY                              0
#define MOUSEKEY_INTERVAL                           16
#define MOUSEKEY_MAX_SPEED                          7
#define MOUSEKEY_TIME_TO_MAX                        60
#define MOUSEKEY_WHEEL_DELAY                        0
#define MOUSEKEY_WHEEL_MAX_SPEED                    8
#define MOUSEKEY_WHEEL_TIME_TO_MAX              40


#endif
