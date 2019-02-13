/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */ 

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "chatballoon.hpp"
using namespace std;

/**
 * Constructor
 * \param text message to display
 * \param x x coord of the tip (bottom) of the balloon
 * \param y y coord of the tip (bottom) of the balloon
 */
ChatBalloon::ChatBalloon(const string &text, const int x, const int y) : message(text), 
_x(x), _y(y), nbCharsDisplayed(1), creationTime(SDL_GetTicks()) {
    if(message.size() == 0) {
        message = " ";
    }
}

ChatBalloon::~ChatBalloon() {
    
}

void ChatBalloon::draw(SDL_Renderer *renderer) {
    if(nbCharsDisplayed < message.size()) {
        Uint32 delta = SDL_GetTicks() - creationTime;
        nbCharsDisplayed = 1 + delta / (1000 / CHARACTERS_PER_SECOND);
    }
    
    int textWidth = nbCharsDisplayed >= BALLOON_WIDTH ? BALLOON_WIDTH : nbCharsDisplayed;
    int nbLines = 1 + nbCharsDisplayed / BALLOON_WIDTH;
    if(nbCharsDisplayed % BALLOON_WIDTH == 0) {
        nbLines -= 1;
    }
    
    // Draw tip
    filledTrigonRGBA(renderer, _x, _y, _x + 10, _y - 10, _x - 10, _y - 10, 0xff, 0xff, 0xff, 0xff);
    
    // Draw balloon
    
    // Draw text, line by line
    
}

bool ChatBalloon::isVisible() const {
    return SDL_Ticks() <= creationTime + FULL_DELAY + (message.size() - 1) * 1000 / CHARACTERS_PER_SECOND;
}
