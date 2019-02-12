/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_gfxPrimitives.h>
#include <tinyxml2.h>
#include "config.hpp"
#include "gamemap.hpp"
using namespace std;

/**
 * Constructor
 * Only actually loads the preview, to save space
 */
GameMap::GameMap(string mapName) {
    // Open XML and read it
}

GameMap::~GameMap() {
    SDL_DestroyRenderer(mapRenderer);
    if(background) {
        SDL_DestroyTexture(background);
    }
    if(foreground) {
        SDL_DestroyTexture(foreground);
    }
    if(preview) {
        SDL_DestroyTexture(preview);
    }
}

void GameMap::load() {
    // Load background
    
    // Load foreground
    
    // Set colorkey
    
    // Set renderer, target foreground
}

void GameMap::unload() {
    SDL_DestroyTexture(background);
    background = nullptr;
    SDL_DestroyTexture(foreground); // mandatory: we will have to restart from a clean one
    foreground = nullptr;
}

/**
 * Implementation of terrain destruction
 * \param x x coord of the point of impact, expressed in map coordinates
 * \param y y coord of the point of impact, expressed in map coordinates
 * \param radius hole radius in pixels
 */
void GameMap::makeHole(const int x, const int y, const int radius) {
    filledCircleRGBA(mapRenderer, x, y, radius, 0xff, 0, 0xff, 0); // transparent magenta
}

SDL_Texture *GameMap::getBackground(){
    return background;
}

SDL_Texture *GameMap::getForeground() {
    return foreground;
}

SDL_Texture *GameMap::getPreview() {
    return preview;
}
