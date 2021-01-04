/**
 * \file serverplayer.cpp
 * \brief Player redefinition, server-side 
 * \author G. B.
 * \version 0.1a
 * \date 31/12/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include "serverplayer.hpp"
using namespace std;

/**
 * Constructor
 */
ServerPlayer::ServerPlayer() : CommonPlayer() {
    
}

/**
 * Set the IP for the player
 * Used to route packets and perform basic origin checks for security
 * \param address address to use
 */
void ServerPlayer::setIp(const IPaddress address) {
    ip = address;
}

/**
 * Get the IP address (not the port) for this player
 * \return ip address
 */
Uint32 ServerPlayer::getIp() const {
    return ip.host;
}

/**
 * Set the current location (room number) for this player
 * 0 means that we are in the channel
 * Should actually be a pointer to a Room object
 * Used for buddy lists and message forwarding
 * \param room room number
 */
void ServerPlayer::setLocation(const Uint32 room) {
    location = room;
}

/**
 * Get the current location of the player
 * \return room number if any, otherwise 0
 */
Uint32 ServerPlayer::getLocation() const {
    return location;
}
