/**
 * \file serverplayer.hpp
 * \brief Player redefinition, server-side 
 * \author G. B.
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

#ifndef _H_SERVERPLAYER_
#define _H_SERVERPLAYER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "../common/commonplayer.hpp"

class ServerPlayer : public CommonPlayer {
public:
    ServerPlayer();
    
    void setIp(const IPaddress address);
    Uint32 getIp() const;
    void setLocation(const Uint32 room);
    Uint32 getLocation() const;
private:
    Uint32 location = 0;
    IPaddress ip;
    // current room    
};

#endif //! _H_SERVERPLAYER_
