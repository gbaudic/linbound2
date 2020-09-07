/**
 * \file overlays.cpp
 * \brief Definitions for overlays in Room and Lobby views
 * \author G. B.
 * \version 0.1a
 * \date 06/09/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "../config.hpp"
#include "overlays.hpp"
using namespace std;

map<OverlayType, shared_ptr<Sprite>> OverlayFactory::overlays;

/**
 * @brief Get the overlay Sprite for a given type
 * @param type type of overlay to display
 * @return the object, or null if not supported yet
*/
shared_ptr<Sprite> OverlayFactory::getOverlay(OverlayType type) {
    shared_ptr<Sprite> result{ nullptr };

    switch (type) {
    case OverlayType::SOLO_START:
        load(type, "solo_start.png");
        result = overlays[type];
        break;
    case OverlayType::DUO_START:
        load(type, "duo_start.png");
        result = overlays[type];
        break;
    case OverlayType::MULTI_START:
        load(type, "multi_start.png");
        result = overlays[type];
        break;
    case OverlayType::POINTS_START:
        load(type, "points_start.png");
        result = overlays[type];
        break;
    case OverlayType::SUDDEN_DEATH:
        load(type, "sudden_death.png");
        result = overlays[type];
        break;
    default:
        break; // Unsupported value, the image is probably missing
    }
    return result;
}

/**
 * @brief Helper function to actually create the sprite
 * @param type type of overlay to display
 * @param filename file to load
*/
void OverlayFactory::load(OverlayType type, std::string filename) {
    const int height = 60;
    const int width = 400;
    const Uint16 duration = 4000; // in milliseconds

    if (overlays.count(type) == 0) {
        overlays[type] = make_shared<Sprite>(RESOURCE_PREFIX + "/overlays/" + filename, width, height, duration);
    }
}
