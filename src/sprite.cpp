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

    // Autocompute nb of states and nb of steps
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
    if (surface) {
        SDL_FreeSurface(surface);
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }
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
 * This is the full surface, use getRect() to take only the relevant part
 * @return a pointer to the surface
 */
SDL_Surface* Sprite::getSurface() {
    return surface;
}

/**
 * @brief Get the underlying SDL_Texture, creating it if needed
 * @param rdr renderer to use
 * @return a pointer to the texture
*/
SDL_Texture* Sprite::getTexture(SDL_Renderer* rdr) {
    if (surface && texture == nullptr) {
        texture = SDL_CreateTextureFromSurface(rdr, surface);
    }
    return texture;
}

/**
 * @brief Get the width of the sprite
 * This is the width of one frame, not the whole surface!
 * @return the width in pixels
*/
int Sprite::getWidth() const {
    return currentRect.w;
}

/**
 * @brief Get the height of the sprite
 * This is the height of one frame, not the whole surface! 
 * @return the height in pixels
*/
int Sprite::getHeight() const {
    return currentRect.h;
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
