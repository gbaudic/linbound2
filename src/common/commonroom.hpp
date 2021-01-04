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
#include <vector>
#include <SDL2/SDL.h>
#include "../constants.hpp"
#include "commongameitem.hpp"
#include "commonplayer.hpp"

/**
 * Status of a room
 */
enum class RoomStatus {
    WAITING, //! still accepting players
    FULL,    //! all seats full, entrance not permitted
    PLAYING  //! game being played, players can leave (with penalty) but cannot join
};

/**
 * Type of change when entering sudden death if match lasts too long
 */
enum class SuddenDeathType {
    BIGBOMB, //!< bigger holes with all weapons
    DOUBLE, //!< unlimited use of double ammo
    SS //!< unlimited use of Super Shot 
};

/**
 * Convenience struct to hold room creation data, also required in server view
 * The fields can be changed after creation by the room admin, unless the room 
 * is playing
 */
struct RoomCreationInfo {
    std::string name;
    std::string password; //!< leave blank for none
    Uint8 nbTeams;
    Uint8 playersPerTeam;
    SuddenDeathType sdtype;
    Uint8 sdTurns;
};

/**
 * Basic room info, used in room list to be able to show the buttons
 */
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

/**
 * Shared definitions for a room between client and server
 * Meant to be subclassed at each side
 */
class CommonRoom {
public:
    explicit CommonRoom(const RoomCreationInfo& info);
    virtual void addPlayer(CommonPlayer * player);
    virtual void removePlayer(std::string playerName);
    RoomStatus getStatus() const;
    bool isPlayerAdmin(std::string playerName) const;

protected:
    RoomCreationInfo rcInfo;
    std::vector<CommonPlayer*> players;
};
 
#endif //! _H_COMMONROOM_ 
