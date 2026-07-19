/**
 * \file messages.cpp
 * \brief Struct for messages
 * \author G. B., grouiksoft inc.
 * \version 0.1a
 * \date 30/12/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include <vector>
#include "messages.hpp"
#include "../utils.hpp"

void RewardMessage::fromMessage(const std::string & message) {
    std::vector<std::string> pieces = linbound::split(message, '\3');
    
    if (pieces.size() >= 4) {
        user = pieces[0];
        reward = pieces[1];
        gold = stoi(pieces[2]);
        xp = stoi(pieces[3]);
    }
}

std::string RewardMessage::toString() {
    return user + '\3' + reward + '\3' + std::to_string(gold) + '\3' + std::to_string(xp);
}

void ShotMessage::fromMessage(const std::string & message) {
    std::vector<std::string> pieces = linbound::split(message, '\3');
    
    if (pieces.size() >= 4) {
        user = pieces[0];
        type = static_cast<WeaponType>(stoi(pieces[1]));
        power = stoi(pieces[2]);
        angle = stoi(pieces[3]);
    }
}

std::string ShotMessage::toString() {
    return user + '\3' + std::to_string(static_cast<unsigned int>(type)) + '\3' + std::to_string(power) + '\3' + std::to_string(angle);
}

void LoginMessage::fromMessage(const std::string & message) {
    std::vector<std::string> pieces = linbound::split(message, '\3');
    
    if (pieces.size() >= 2) {
        login = pieces[0];
        password = pieces[1];
    }
}

std::string LoginMessage::toString() {
    return login + '\3' + password;  // yup, in clear for now
}

void LogoutMessage::fromMessage(const std::string & message) {
    login = message;
}

std::string LogoutMessage::toString() {
    return login;
}
