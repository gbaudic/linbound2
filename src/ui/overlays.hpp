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

#include <map>
#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include "../sprite.hpp"

/**
 * Convenience enum to pick an overlay among those existing
 */
enum class OverlayType {
    NONE,
    EVENT,
    SOLO_START,
    DUO_START,
    MULTI_START,
    POINTS_START,
    SUDDEN_DEATH,
    AWESOME
};

class OverlayFactory {
public :
    static std::shared_ptr<Sprite> getOverlay(OverlayType type);

private:
    static void load(OverlayType type, std::string filename);

    static std::map<OverlayType, std::shared_ptr<Sprite>> overlays;
};

#endif
