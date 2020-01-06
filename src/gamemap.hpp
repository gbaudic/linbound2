/**
 * \file gamemap.hpp
 * \brief A map on which to play
 * \author G. B.
 * \version 0.1a
 * \date 12/02/2019
 */
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
    explicit GameMap(const std::string &mapName);
    ~GameMap();
    void load();
    void unload();
    void useBSide(const bool use);
    void makeHole(const int x, const int y, const int radius);
    SDL_Texture *getBackground();
    SDL_Texture *getForeground();
    SDL_Texture *getPreview();
    std::string getMusicFile() const;
    
private:
    SDL_Renderer *mapRenderer; //! internal one
    SDL_Texture *background;
    SDL_Texture *foreground;
    SDL_Texture *preview;
    
    std::string name;
    std::string pathToBack;
    std::string pathToFrontA;
    std::string pathToFrontB;
    std::string musicFile;
    
    bool hasBSide = false;
    bool bSide = false;
    
    void storePath(const std::string &key, const std::string &value);
};

#endif // _H_GAMEMAP_
