/**
 * \file lifebar.hpp
 * \date 15/12/2019
 * \brief UI class for component showing life points of a player
 * \author G. B.
 * \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_LIFEBAR_
#define _H_LIFEBAR_

#include <SDL2/SDL.h>

class Lifebar {
    static const Sint16 width = 100; // pixels
    static const Sint16 height = 10; // pixels

public:
    Lifebar();
    void draw(SDL_Renderer* renderer, Sint16 x, Sint16 y) const;
    void setValue(Sint16 value);

private:
    // current value of life for player -- negative values show as 0 but are allowed
    Sint16 value = 0; 

};

#endif // !_H_LIFEBAR_
