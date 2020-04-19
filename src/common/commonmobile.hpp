/**
 * \file commonmobile.hpp
 * \brief Common definitions for a mobile in client and server side
 * \author G. B.
 * \version 0.1a
 * \date 18/04/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_COMMONMOBILE_
#define _H_COMMONMOBILE_

#include "messages.hpp" // for WeaponType

/**
 * Mobiles that will be available in the game, once all graphics are ready
 */
enum class MobileName {
    CABBAGE,
    COFFEE,
    COW,
    DIAMOND,
    DOLPHIN,
    DUCK,
    GOAT,
    ICEBERG,
    ORANGE,
    PIG,
    PLANE,
    RANDOM,
    RASPBERRY,
    RESISTOR,
    ROCK,
    ROSE,
    SHEEP,
    TANK,
    TEAPOT,
    TRASH,
    TREE,
    UNICORN
};

enum class MobileStatus : unsigned int {
    ALIVE,
    DYING,
    DEAD, //!< dead in solo mode
    FALLING, //!< when respawning in multi mode
    FLYING //!< when dying in multi mode
};

class CommonMobile {

private:
    int minAngles[3]{ 0, 0, 0 };  // in degrees
    int maxAngles[3]{ 0, 0, 0 };
    MobileName name;
    MobileStatus status{ MobileStatus::ALIVE };
};

#endif // !_H_COMMONMOBILE_

