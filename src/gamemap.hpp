 /* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL.h>
#include <string>
 
#ifndef _H_GAMEMAP_
#define _H_GAMEMAP_

/**
 * Abstraction for one of the maps in the game, where players will actually fight
 * Viewports will be handled by the Room class
 */
class GameMap {
public:
    GameMap(std::string mapName);
    ~GameMap();
    void load();
    void unload();
    void makeHole(const int x, const int y, const int radius);
    SDL_Texture *getBackground();
    SDL_Texture *getForeground();
    SDL_Texture *getPreview();
    
private:
    SDL_Renderer *mapRenderer; //! internal one
    SDL_Texture *background;
    SDL_Texture *foreground;
    SDL_Texture *preview;
    
    std::string pathToBack;
    std::string pathToFront;
    
    bool hasBSide;
};

#endif // _H_GAMEMAP_
