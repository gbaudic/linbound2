/**
 * \file network.hpp
 * \brief Network-related functions
 * \author G. B.
 * \version 0.1a
 * \date 19/02/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "common/commonplayer.hpp"

#ifndef _H_NETWORK_
#define _H_NETWORK_

class NetworkManager final {
public:
    NetworkManager(bool isServer);
    ~NetworkManager();
    void send(Uint8 code, const std::string & message, IPaddress target);
    void sendToServer(Uint8 code, const std::string& message);
    void setServerInfo(Uint32 ip);
    std::vector<UDPpacket*> & receive();

    void logout();
    
    static Uint8 getCode(const UDPpacket *p);
    static std::string getMessage(const UDPpacket *p);
    static IPaddress getAddress(const UDPpacket* p);

    static bool isExpected(Uint8 code, PlayerLocationType location, bool isPlaying = false);

    
private:
    const Uint16 SERVER_PORT = 6545;

    UDPsocket socket; //! to send data
    IPaddress serverInfo;
    
    std::vector<UDPpacket*> packets;
};

#endif //! _H_NETWORK_
