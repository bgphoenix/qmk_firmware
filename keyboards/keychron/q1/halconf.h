/* Copyright 2020 QMK
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

#pragma once

<<<<<<<< HEAD:keyboards/keychron/q1/halconf.h
#define HAL_USE_I2C TRUE
#ifdef ENCODER_ENABLE
#    define PAL_USE_CALLBACKS TRUE
#endif

========
#define HAL_USE_PWM TRUE
#define HAL_USE_PAL TRUE

#define HAL_USE_I2C TRUE

>>>>>>>> playground_new:keyboards/acheron/shark/beta/halconf.h
#include_next <halconf.h>