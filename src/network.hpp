/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "context.hpp"

#ifndef _H_NETWORK_
#define _H_NETWORK_

class NetworkManager final {
public:
    NetworkManager();
    ~NetworkManager();
    void send(Uint8 code, const std::string & message);
    void findServer();
    void setServerInfo(Uint32 ip, Uint16 port);
    void receive(Context* currentContext);
    
private:
    const Uint16 SERVER_PORT = 6545;
    
    UDPsocket clientSock; //! to send data
    IPaddress serverInfo;
};

#endif //! _H_NETWORK_
