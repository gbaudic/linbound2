/**
 * \file overlays.hpp
 * \brief Definitions for overlays in Room and Lobby views
 * \author G. B.
 * \version 0.1a
 * \date 26/08/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_OVERLAYS_
#define _H_OVERLAYS_

#include <SDL2/SDL.h>

/**
 * Convenience enum to pick an overlay among those existing
 */
enum class OverlayType {
    EVENT,
    SOLO_START,
    DUO_START,
    MULTI_START,
    POINTS_START,
    SUDDEN_DEATH,
    AWESOME
};

#endif
