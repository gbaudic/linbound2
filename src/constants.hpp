/**
 *  \file constants.hpp
 *  \brief Some useful constants
 *  \author G. B.
 *  \date 15/12/2019
 *  \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is �Incompatible With Secondary Licenses�,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_CONSTANTS_
#define _H_CONSTANTS_

#include <SDL2/SDL.h>

const Sint16 MAX_LIFE = 1000; //! Max player life in general case
const Sint16 DUO_INITIAL_LIFE = 450;  //! Initial life for second mobile in Duo mode
const Sint16 CRITICAL_LIFE = 200;  //! Threshold to trigger UI changes

enum class GameMode {
	SOLO,
	DUO,
	MULTI,
	POINTS
};

#endif // !_H_CONSTANTS_
