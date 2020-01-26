/**
 * \file commonplayer.hpp
 * \brief Common definitions for a player in client and server side
 * \author G. B.
 * \version 0.1a
 * \date 25/01/2020
 */
 /* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
  * If a copy of the MPL was not distributed with this file,
  * You can obtain one at http://mozilla.org/MPL/2.0/.
  *
  * This Source Code Form is "Incompatible With Secondary Licenses",
  * as defined by the Mozilla Public License, v. 2.0.
  */

#ifndef _H_COMMONPLAYER_
#define _H_COMMONPLAYER_

#include <string>
#include <SDL2/SDL.h>

enum class PlayerLevel {
    ROOKIE,
    WOOD_HAMMER,
    WOOD_HAMMER2,
    STONE_HAMMER,
    STONE_HAMMER2, // TBC
    ADMIN
};

struct PlayerBasicInfo {
    std::string name;
    PlayerLevel level;
    Uint32 points;
    Uint32 gold;
    Uint32 cash;
};

#endif //! _H_COMMONPLAYER_ 