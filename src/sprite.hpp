/**
 *  \file sprite.hpp
 *  \brief Definition of a sprite, a 2D element used in game
 *  \author G. B.
 *  \date 04/02/2019
 *  \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SPRITE_
#define _H_SPRITE_

#include <string>
#include <SDL2/SDL.h>

class Sprite {
public:
	Sprite(const std::string &filename, const int width, const int height, const Uint16 duration);
	~Sprite();

	SDL_Rect & getRect();
	SDL_Surface* getSurface();
	void setState(const int newState);

private:
	SDL_Rect currentRect;
	SDL_Surface *surface = nullptr;
	int nbSteps;
	int nbStates;
	int currentState;
	Uint16 stepDuration;
	Uint32 creationTS;  //! timestamp of creation
};

#endif // ! _H_SPRITE_

