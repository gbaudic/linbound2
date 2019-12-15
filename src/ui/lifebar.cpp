/**
 * \file lifebar.cpp
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

#include "../constants.hpp"
#include "lifebar.hpp"

/**
 * \brief Constructor
 */
Lifebar::Lifebar() : value(0) {

}

/**
 * \brief Draw the lifebar at the requested coordinates
 *  Set the clipping rectangle beforehand to avoid surprises
 * \param renderer surface to target
 * \param x x coordinate of top-left hand corner of lifebar
 * \param y y coordinate of top left hand corner of lifebar
 */
void Lifebar::draw(SDL_Renderer* renderer, Sint16 x, Sint16 y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    // White outline
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);
    // Black background
    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);

    // Lifebar (red if critical, green otherwise)
    if (value > 0 && value <= MAX_LIFE) {
        if (value > CRITICAL_LIFE) {
            SDL_SetRenderDrawColor(renderer, 0x14, 0x66, 0, SDL_ALPHA_OPAQUE);
        } else {
            SDL_SetRenderDrawColor(renderer, 0x93, 0x0c, 0, SDL_ALPHA_OPAQUE);
        }
        rect.w = value * (width - 2) / MAX_LIFE;

        SDL_RenderDrawRect(renderer, &rect);
    }
}

/**
 * \brief Set the value to display
 * \param value new value
 */
void Lifebar::setValue(Sint16 value) {
    this->value = value;
}


