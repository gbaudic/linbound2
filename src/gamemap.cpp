/**
 * \file gamemap.cpp
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

#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <tinyxml2.h>
#include "config.hpp"
#include "gamemap.hpp"
using namespace std;
using namespace tinyxml2;

/**
 * Constructor
 * Only actually loads the preview, to save space
 * \param mapName name of the map, corresponds to its folder name
 */
GameMap::GameMap(const string &mapName) {
    // Open XML and read it
    XMLDocument doc;
    string fullPath = RESOURCE_PREFIX + "/maps/" + mapName + "/map.xml";
    doc.LoadFile(fullPath.c_str());
    
    XMLElement *root = doc.RootElement();
    // Number of sides (1 or 2) (optional)
    const XMLElement *sides = root->FirstChildElement("sides");
    int nbSides = 0;
    if(sides) {
        sides->QueryIntText(&nbSides);
    }
    hasBSide = nbSides == 2;
    
    // Map name (mandatory)
    const XMLElement *nameEl = root->FirstChildElement("name");
    name.assign(nameEl->GetText());
    
    // Music recommendation (optional)
    const XMLElement *music = root->FirstChildElement("music_playlist");
    if(music) {
        musicFile.assign(music->GetText());
    }
    
    // File paths (mandatory)
    XMLElement *surface = root->FirstChildElement("surface");
    while(surface) {
        string type(surface->Attribute("name"));
        string value(surface->Attribute("file"));
        
        storePath(type, RESOURCE_PREFIX + "/maps/" + mapName + "/" + value);
        
        // repeat while there is another sibling
        surface = surface->NextSiblingElement("surface");
    }    
}

void GameMap::storePath(const string &key, const string &value) {
    if(key == "preview") {
        // Load preview
    } else if(key == "background") {
        pathToBack.assign(value);
    } else if(key == "mapA") {
        pathToFrontA.assign(value);
    } else if(key == "mapB") {
        pathToFrontB.assign(value);
    }
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
void GameMap::makeHole(const Sint16 x, const Sint16 y, const Sint16 radius) {
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

string GameMap::getMusicFile() const {
    return musicFile;
}

/**
 * Toggle between A and B side, if possible
 * \param use true for B, false for A
 */
void GameMap::useBSide(const bool use) {
    if(hasBSide) {
        bSide = use;
    }
}
