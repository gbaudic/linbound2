/**
 * \file commongameitem.hpp
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

#ifndef _H_COMMONGAMEITEM_
#define _H_COMMONGAMEITEM_

#include <string>

/**
 * Available types of items
 */
enum class GameItemType {
    DUAL,
    DUAL_PLUS,
    TELEPORT,
    TEAM_TELEPORT,
    THUNDER,
    BUNGE,
    HEALTH,
    HEALTH_PACK,
    NONE_1,
    NONE_2
};

/**
 * Abstract representation of a game item
 */
class GameItem {
public:
    static int getSize(GameItemType type);
    static unsigned int getDelay(GameItemType type);
    static std::string getFilename(GameItemType type);
};

#endif //! _H_COMMONGAMEITEM_
