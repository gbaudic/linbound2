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
#include <vector>
#include <SDL2/SDL.h>
#include "commonitem.hpp"

enum class PlayerLevel : unsigned int {
    ROOKIE,
    WOOD_HAMMER,
    WOOD_HAMMER2,
    STONE_HAMMER,
    STONE_HAMMER2,
    AXE,
    AXE_DOUBLE,
    SILVER_AXE,
    SILVER_AXE_DOUBLE,
    GOLDEN_AXE,
    GOLDEN_AXE_DOUBLE, // TBC
    ADMIN
};

enum class PlayerLocationType {
    DISCONNECTED,
    SERVER,
    ROOM
};

/**
 * Data for the player currently connected to a client app
 * Sent by the server
 */
struct PlayerBasicInfo {
    std::string name;
    PlayerLevel level;
    std::string guild;
    Uint8 rankingInGuild;
    Uint8 totalInGuild;
    Uint32 points;
    Uint32 gold;
    Uint32 cash; //! only here for compatibility, but unsupported
};

struct PlayerStats {
    std::string name;
    unsigned int worldRanking;
    unsigned int countryRanking;
    unsigned int guildRanking; // 0 means no guild
    unsigned int winningRate; // [0-100]%
};

/**
 * Used client-side for match result and server-side for computations
 */
struct PlayerResult {
    std::string name;
    PlayerLevel level;
    char team;
    Sint8 gpEarned;
    int goldEarned;
    unsigned int damageInflicted;
    bool wins;
};

/**
 * Common class for server and client representing a Player
 */
class CommonPlayer {
public:
    CommonPlayer();
    void setInfo(const PlayerBasicInfo &newInfo);
    void setTeam(char newTeam);
    int getRewardAmount(const int baseAmount);
private:
    PlayerBasicInfo info;
    char team = 'A';
    std::vector<CommonItem*> items;
    int properties[8]{ 0, 0, 0, 0, 0, 0, 0, 0 }; // convenience; sum computed from items
};

#endif //! _H_COMMONPLAYER_ 
