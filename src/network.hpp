/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>

#ifndef _H_NETWORK_
#define _H_NETWORK_

class NetworkManager final {
public:
    NetworkManager();
    ~NetworkManager();
    void send(Uint8 code, const std::string & message);
    void setServerInfo(Uint32 ip);
    std::vector<UDPpacket*> & receive();
    
    static Uint8 getCode(UDPpacket *p);
    static std::string getMessage(UDPpacket *p);
    
private:
    const Uint16 SERVER_PORT = 6545;
    
    UDPsocket clientSock; //! to send data
    UDPsocket serverSock; //! only useful if also a server
    IPaddress serverInfo;
    
    std::vector<UDPpacket*> packets;
};

#endif //! _H_NETWORK_
