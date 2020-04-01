/**
 * \file commonroom.hpp
 * \brief Common definitions for a room in client and server side
 * \author G. B.
 * \version 0.1a
 * \date 13/01/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#ifndef _H_COMMONROOM_
#define _H_COMMONROOM_

#include <string>
#include <SDL2/SDL.h>
#include "../constants.hpp"

/**
 * Status of a room
 */
enum class RoomStatus {
	WAITING, //! still accepting players
	FULL,    //! all seats full, entrance not permitted
	PLAYING  //! game being played
};

/**
 * Type of change when entering sudden death if match lasts too long
 */
enum class SuddenDeathType {
    BIGBOMB, //!< bigger holes with all weapons
    DOUBLE, //!< unlimited use of double ammo
    SS //!< unlimited use of Super Shot 
};

struct RoomCreationInfo {
    std::string name;
    std::string password; //!< leave blank for none
    Uint8 nbTeams;
    Uint8 playersPerTeam;
    SuddenDeathType sdtype;
    Uint8 sdTurns;
};

struct RoomBasicInfo {
    Uint16 number;
    std::string name;
    bool hasPassword;
    RoomStatus status;
    GameMode mode;
    std::string mapName;
    Uint8 nbTeams;
    Uint8 playersPerTeam;
};
 
#endif //! _H_COMMONROOM_ 
