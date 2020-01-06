/**
 * \file chatballoon.cpp
 * \brief Balloon to display messages from the players
 * \author G. B.
 * \version 0.1a
 * \date 13/02/2019
 */
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

TTF_Font *ChatBalloon::font = nullptr;

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

/**
 * Perform the drawing of the balloon
 * \param renderer object to perform drawing
 * \param xOffset value >= 0, used only in Room mode
 * \param yOffset value >= 0, used only in Room mode
 */
void ChatBalloon::draw(SDL_Renderer *renderer, const int xOffset, const int yOffset) {
	// Update line width if necessary
    if(nbCharsDisplayed < message.size()) {
        Uint32 delta = SDL_GetTicks() - creationTime;
        nbCharsDisplayed = 1 + delta / (1000 / CHARACTERS_PER_SECOND);
    }

	int x = _x - xOffset;
	int y = _y - yOffset;
    
	// Compute balloon size
    int charsInLine = nbCharsDisplayed >= BALLOON_WIDTH ? BALLOON_WIDTH : nbCharsDisplayed;
	int textWidth = 0;
	int lineHeight = 0;
	string testText(charsInLine, 'M');
	TTF_SizeText(font, testText.c_str(), &textWidth, &lineHeight);
    int nbLines = 1 + nbCharsDisplayed / BALLOON_WIDTH;
    if(nbCharsDisplayed > 0 && nbCharsDisplayed % BALLOON_WIDTH == 0) {
        nbLines -= 1;
    }
    
    // Draw white balloon and black outline
	roundedBoxColor(renderer, x - PADDING - textWidth / 2, y - 9 - 2 * PADDING - nbLines * lineHeight,
		x + textWidth / 2 + PADDING, y - 9, 3, 0xffffffff);
	roundedRectangleColor(renderer, x - PADDING - textWidth / 2, y - 9 - 2 * PADDING - nbLines * lineHeight,
		x + textWidth / 2 + PADDING, y - 9, 3, 0x000000ff);

	// Draw white tip and black outline
	filledTrigonRGBA(renderer, x, y, x + 10, y - 10, x - 10, y - 10, 0xff, 0xff, 0xff, 0xff);
	lineColor(renderer, x, y, x + 10, y - 10, 0x000000ff);
	lineColor(renderer, x, y, x - 10, y - 10, 0x000000ff);
    
    // Draw text, line by line
	int idx = 0;
	SDL_Color black;
	black.a = 0xff;
	SDL_Rect dest;
	dest.y = y - 9 - PADDING - nbLines * lineHeight;
	
	while (idx < nbCharsDisplayed) {
		int len = BALLOON_WIDTH;
		// Count the right number of characters
		if (idx + len > nbCharsDisplayed) {
			len = nbCharsDisplayed - idx;
		}

		// Create text surface
		string text = message.substr(idx, len);
		SDL_Surface *textLine = TTF_RenderUTF8_Solid(font, text.c_str(), black);
		SDL_Texture *tx = SDL_CreateTextureFromSurface(renderer, textLine);
		dest.x = x - textLine->w / 2;
		dest.w = textLine->w;
		dest.h = textLine->h;

		// Place it in the balloon, and update coords for next line
		SDL_RenderCopy(renderer, tx, NULL, &dest);
		idx += BALLOON_WIDTH;
		dest.y += textLine->h;

		// Cleanup
		SDL_DestroyTexture(tx);
		SDL_FreeSurface(textLine);
	}
    
}

/**
 * Determine if the balloon should be drawn or not
 */
bool ChatBalloon::isVisible() const {
    return SDL_GetTicks() <= creationTime + FULL_DELAY + (message.size() - 1) * 1000 / CHARACTERS_PER_SECOND;
}

/**
 * Set the TTF_Font object to use for all balloons
 * \param textFont the font to use. Should have been already loaded beforehand. 
 */
void ChatBalloon::setFont(TTF_Font * textFont) {
	font = textFont;
}
