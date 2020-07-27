/**
 * \file chatballoon.hpp
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#ifndef _H_CHATBALLOON_
#define _H_CHATBALLOON_

class ChatBalloon final {
public:
    const int BALLOON_WIDTH = 20; //! in characters
    const int CHARACTERS_PER_SECOND = 10; //! used when deploying the balloon
    const Uint32 FULL_DELAY = 5000; //! time to leave the full balloon visible
    
    ChatBalloon(const std::string &text, const Sint16 x, const Sint16 y);
    
    void draw(SDL_Renderer *renderer, const Sint16 xOffset = 0, const Sint16 yOffset = 0);
    bool isVisible() const;

	static void setFont(TTF_Font *textFont);
    
private:
    std::string message;
    Sint16 _x;
    Sint16 _y;
    int nbCharsDisplayed = 1;
    Uint32 creationTime{ SDL_GetTicks() };
    
    const Sint16 PADDING = 5; //! in pixels

	static TTF_Font* font;
};

#endif // _H_CHATBALLOON_
