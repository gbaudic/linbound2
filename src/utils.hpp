/**
 *  \file utils.hpp
 *  \brief Utility functions
 *  \author G. B.
 *  \date /11/2016
 *  \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#ifndef _H_UTILS_
#define _H_UTILS_

#include <SDL2/SDL.h>
#include <string>
#include <guisan.hpp>
 
#include "config.hpp"

namespace linbound {
 
    Sint16 normalizeAngle(Sint16 angle);
    double getDistance(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2);
    Sint16 getShotAngle(Sint16 angle);
    bool flip(Sint16 angle);
    std::string getVersionString();
    int getVersion();
    std::string prettifyIP(Uint32 address);
	Uint32 stringToIP(const std::string &input);
}
 
#endif 
