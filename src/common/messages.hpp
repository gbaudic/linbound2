/**
 * \file messages.hpp
 * \brief Struct for messages
 * \author G. B.
 * \version 0.1a
 * \date 07/04/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_MESSAGES_
#define _H_MESSAGES_

#include <string>
#include <map>
#include <SDL2/SDL.h>

enum class WeaponType {
    ONE,
    TWO,
    SUPERSHOT
};

/**
 * Announce rewards or penalties in-game
 */
struct RewardMessage {
    std::string user;
    std::string reward;
    Sint16 gold;
    Sint16 xp;
};

/**
 * Represents a shot from a player
 */
struct ShotMessage {
    std::string user;
    WeaponType type;
    Sint16 power;
    Sint16 angle;
};

/**
 * For anything falling from the sky
 */
struct FallingItem {
    std::string item; //!< player, bonus or weather
    Uint16 x;
    Uint8 turnsLeft;
};

/**
 * Wind change during game
 */
struct WindChange {
    Uint8 newPower;
    Uint16 newAngle;
};

#endif // !_H_MESSAGES_

