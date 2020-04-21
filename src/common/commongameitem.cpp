/**
 * \file commongameitem.cpp
 * \brief Common definitions for in-game items
 * \author G. B.
 * \version 0.1a
 * \date 21/04/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "../config.hpp"
#include "commongameitem.hpp"

/**
 * \brief Get the number of slots taken by this item in the item store
 * Valid values are 1 or 2
 * \param type item type
 * \return the number of slots
 */
int GameItem::getSize(GameItemType type) {
    if (type == GameItemType::BUNGE || type == GameItemType::HEALTH || type == GameItemType::NONE_1) {
        return 1;
    }
    return 2;
}

/**
 * \brief Get the delay cost of using an item in-game
 * \param type item type
 * \return delay value
 */
unsigned int GameItem::getDelay(GameItemType type) {
    unsigned int result = 0;
    switch (type) {
    case GameItemType::DUAL:
        result = 600;
        break;
    case GameItemType::DUAL_PLUS:
        result = 250;
        break;
    case GameItemType::TELEPORT: // fallthrough * 3
    case GameItemType::TEAM_TELEPORT:
    case GameItemType::THUNDER:
    case GameItemType::BUNGE:
        result = 50;
        break;
    case GameItemType::HEALTH:
        result = 150;
        break;
    case GameItemType::HEALTH_PACK:
        result = 200;
        break;
    default:
        break;
    }
    return result;
}

/**
 * \brief Get the name of the file to represent an item in UI
 * \param type item type
 * \return filename for the image of the corresponding "button"
 */
std::string GameItem::getFilename(GameItemType type) {
    switch (type) {
    case GameItemType::DUAL:
        return RESOURCE_PREFIX + "/dual.png";
    case GameItemType::DUAL_PLUS:
        return RESOURCE_PREFIX + "/dual_plus.png";
    case GameItemType::HEALTH:
        return RESOURCE_PREFIX + "/health.png";
    case GameItemType::HEALTH_PACK:
        return RESOURCE_PREFIX + "/health_pack.png";
    default:
        return "";
    }
}

