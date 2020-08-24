/**
 *  \file sprite.cpp
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

#include <SDL2/SDL_image.h>
#include "sprite.hpp"
using namespace std;

/**
 * Constructor
 * \param filename path to the image file
 * \param width width of one frame of the sprite (not the full image!)
 * \param height height of one frame of the sprite (not the full image!)
 */
Sprite::Sprite(const std::string &filename, const int width, const int height, const Uint16 duration): 
	stepDuration(duration) {

	surface = IMG_Load(filename.c_str());
	SDL_SetColorKey(surface, SDL_RLEACCEL, SDL_MapRGB(surface->format, 0xff, 0, 0xff));

	nbStates = surface->h / height;
	nbSteps = surface->w / width;

	currentRect.x = 0;
	currentRect.y = 0;
	currentRect.h = height;
	currentRect.w = width;

	creationTS = SDL_GetTicks();
}

/**
 * Destructor
 */
Sprite::~Sprite() {
	SDL_FreeSurface(surface);
}

/**
 * Get the rectangle corresponding to the current animation step for this sprite
 * Used in conjunction with getSurface() to actually draw it to the screen
 * @return the correct SDL_Rect
 */
SDL_Rect & Sprite::getRect() {
	currentRect.y = currentState * currentRect.h;
	// Find, given current time, at which step we are
	Uint32 current = (SDL_GetTicks() - creationTS) % (stepDuration * nbSteps);
	currentRect.x = currentRect.w * (current / nbSteps);

	return currentRect;
}

/**
 * Get the underlying SDL_Surface
 * @return a pointer to the surface
 */
SDL_Surface * Sprite::getSurface() {
	return surface;
}

/**
 * Change the state of this Sprite
 * @param newState index of the new state
 */
void Sprite::setState(const int newState) {
	if (newState >= 0 && newState < nbStates) {
		currentState = newState;
	} else {
		currentState = 0;
	}
}
