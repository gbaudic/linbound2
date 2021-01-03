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

/**
 * Weapon, among the 3 available
 */
enum class WeaponType : unsigned int {
    ONE = 1,
    TWO = 2,
    SUPERSHOT = 55
};

/**
 * Superclass for all messages
 */
class NetworkMessage {
public:
    /**
     * Fill in the message fields from the text representation
     * \param message the message as extracted from the packet
     */
    virtual void fromMessage(const std::string & message) = 0;
    
    /**
     * Produce the string for sending over the network
     * Using strings for everything avoids having to deal with endianness for numbers
     */
    virtual std::string toString() = 0;
};

/**
 * Announce rewards or penalties in-game
 */
struct RewardMessage : public NetworkMessage {
    std::string user;
    std::string reward;
    Sint16 gold;
    Sint16 xp;
    
    void fromMessage(const std::string & message) override;
    std::string toString() override;
};

/**
 * Represents a shot from a player
 */
struct ShotMessage : public NetworkMessage {
    std::string user;
    WeaponType type;
    Sint16 power;
    Sint16 angle;
    
    void fromMessage(const std::string & message) override;
    std::string toString() override;
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

/**
 * Login request
 */
struct LoginMessage : public NetworkMessage {
    std::string login;
    std::string password;
    
    void fromMessage(const std::string & message) override;
    std::string toString() override;
};

/**
 * Logout request
 */
struct LogoutMessage : public NetworkMessage {
    std::string login;
    
    void fromMessage(const std::string & message) override;
    std::string toString() override;
};

#endif // !_H_MESSAGES_

