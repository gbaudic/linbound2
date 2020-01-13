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
#include <SDL2/SDL.h>

/**
 * Status of a room
 */
enum class RoomStatus {
	WAITING, //! still accepting players
	FULL,    //! all seats full, entrance not permitted
	PLAYING  //! game being played
};

struct RoomBasicInfo {
	Uint16 number;
	std::string name;
	bool hasPassword;
	RoomStatus status;
	std::string mapName;
};
 
#endif //! _H_COMMONROOM_ 
