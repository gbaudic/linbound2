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
    GameMap(const GameMap & other);
    GameMap & operator=(const GameMap & other);
    ~GameMap();
    void unload();
    void useBSide(const bool use);
    void makeHole(const Sint16 x, const Sint16 y, const Sint16 radius);
    SDL_Texture *getBackground(SDL_Renderer *rdr);
    SDL_Texture *getForeground(SDL_Renderer *rdr);
    SDL_Texture *getPreview(SDL_Renderer *rdr);
    std::string getMusicFile() const;
    std::string getPathToBack() const;
    std::string getPathToPreview() const;
    std::string getName() const;
    std::string getPathToFrontA() const;
    std::string getPathToFrontB() const;
    
private:
    SDL_Renderer *mapRenderer; //! internal one

    SDL_Texture *background = nullptr;
    SDL_Texture *foreground = nullptr;
    SDL_Texture *preview = nullptr;
    SDL_Surface *front = nullptr;
    
    std::string name;
    std::string pathToPreview;
    std::string pathToBack;
    std::string pathToFrontA;
    std::string pathToFrontB;
    std::string musicFile;
    
    bool hasBSide = false;
    bool bSide = false;
    
    void storePath(const std::string &key, const std::string &value);
};

#endif // _H_GAMEMAP_
