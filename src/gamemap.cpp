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
 * This Source Code Form is "Incompatible With Secondary Licenses",
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
    if (sides) {
        sides->QueryIntText(&nbSides);
    }
    hasBSide = nbSides == 2;
    
    // Map name (mandatory)
    const XMLElement *nameEl = root->FirstChildElement("name");
    name.assign(nameEl->GetText());
    
    // Music recommendation (optional)
    const XMLElement *music = root->FirstChildElement("music_playlist");
    if (music) {
        musicFile.assign(music->GetText());
    }
    
    // File paths (mandatory)
    XMLElement *surface = root->FirstChildElement("surface");
    while (surface) {
        string type(surface->Attribute("name"));
        string value(surface->Attribute("file"));
        
        storePath(type, RESOURCE_PREFIX + "/maps/" + mapName + "/" + value);
        
        // repeat while there is another sibling
        surface = surface->NextSiblingElement("surface");
    }    
}

/**
 * Convenience function to store an image path in the right attribute
 * \param key XML key
 * \param value path to store
 */
void GameMap::storePath(const string &key, const string &value) {
    if(key == "preview") {
        pathToPreview.assign(value);
    } else if(key == "background") {
        pathToBack.assign(value);
    } else if(key == "mapA") {
        pathToFrontA.assign(value);
    } else if(key == "mapB") {
        pathToFrontB.assign(value);
    }
}

/**
 * Destructor
 */
GameMap::~GameMap() {
    if (mapRenderer) {
        SDL_DestroyRenderer(mapRenderer);
        mapRenderer = nullptr;
    }
    if (background) {
        SDL_DestroyTexture(background);
        background = nullptr;
    }
    if (foreground) {
        SDL_DestroyTexture(foreground);
        foreground = nullptr;
    }
    if (front) {
        SDL_FreeSurface(front);
        front = nullptr;
    }
    if (preview) {
        SDL_DestroyTexture(preview);
        preview = nullptr;
    }
}

/**
 * Copy constructor
 */
GameMap::GameMap(const GameMap & other) {
    name = other.name;
    pathToPreview = other.pathToPreview;
    pathToBack = other.pathToBack;
    pathToFrontA = other.pathToFrontA;
    pathToFrontB = other.pathToFrontB;
    musicFile = other.musicFile;
    hasBSide = other.hasBSide;
    bSide = other.bSide;
}

/**
 * Assignment operator
 */
GameMap::GameMap & operator=(const GameMap & other){
    if (this != &other) {
        // Cleanup existing object
        if (mapRenderer) {
            SDL_DestroyRenderer(mapRenderer);
            mapRenderer = nullptr;
        }
        if (background) {
            SDL_DestroyTexture(background);
            background = nullptr;
        }
        if (foreground) {
            SDL_DestroyTexture(foreground);
            foreground = nullptr;
        }
        if (front) {
            SDL_FreeSurface(front);
            front = nullptr;
        }
        if (preview) {
            SDL_DestroyTexture(preview);
            preview = nullptr;
        }
        
        name = other.name;
        pathToPreview = other.pathToPreview;
        pathToBack = other.pathToBack;
        pathToFrontA = other.pathToFrontA;
        pathToFrontB = other.pathToFrontB;
        musicFile = other.musicFile;
        hasBSide = other.hasBSide;
        bSide = other.bSide;
        // No need to create surfaces, it will be done automatically when needed
    }

    return *this;
}

/**
 * \brief Destroy the loaded data in memory
 * Used to rebuild the map from scratch after a game so the terrain is in a clean state for the next one
 */
void GameMap::unload() {
    SDL_DestroyTexture(background);
    background = nullptr;
    SDL_DestroyTexture(foreground); // mandatory: we will have to restart from a clean one
    foreground = nullptr;
    SDL_FreeSurface(front);
    front = nullptr;
}

/**
 * Implementation of terrain destruction
 * \param x x coord of the point of impact, expressed in map coordinates
 * \param y y coord of the point of impact, expressed in map coordinates
 * \param radius hole radius in pixels
 */
void GameMap::makeHole(const Sint16 x, const Sint16 y, const Sint16 radius) {
    filledCircleRGBA(mapRenderer, x, y, radius, 0xff, 0, 0xff, 0); // transparent magenta
    // Remove the texture so it gets updated
    SDL_DestroyTexture(foreground);
    foreground = nullptr;
}

/**
 * Getter for the background texture
 * Used to draw the map on screen
 * \return the desired texture
 */
SDL_Texture *GameMap::getBackground(SDL_Renderer *rdr){
    if (background == nullptr) {
        background = IMG_LoadTexture(rdr, pathToBack.c_str());
    }
    return background;
}

/**
 * Getter for the foreground texture
 * Used to draw the map on screen
 * \return the desired texture
 */
SDL_Texture *GameMap::getForeground(SDL_Renderer* rdr) {
    if (foreground == nullptr) {
        if (front == nullptr) {
            // Refresh surface too
            front = IMG_Load(bSide ? pathToFrontB.c_str() : pathToFrontA.c_str());
        }
        foreground = SDL_CreateTextureFromSurface(rdr, front);
    }
    return foreground;
}

/**
 * Getter for the preview texture
 * Used to introduce the map in Room and Room list view (on the buttons)
 * \return the desired texture
 */
SDL_Texture *GameMap::getPreview(SDL_Renderer* rdr) {
    if (preview == nullptr) {
        preview = IMG_LoadTexture(rdr, pathToPreview.c_str());
    }
    return preview;
}

/**
 * Getter for music file name if one was specified
 * This is the "preferred" one which will be used every time when playing this map
 * \return name of the music file with the extension
 */
string GameMap::getMusicFile() const {
    return musicFile;
}

/**
 * @brief Getter for path to background
 * Mostly useful for unit testing
 * @return path to background image, without animations
 */
string GameMap::getPathToBack() const {
    return pathToBack;
}

/**
 * @brief Getter for path to preview
 * Mostly useful for unit testing
 * @return path to preview image
 */
string GameMap::getPathToPreview() const {
    return pathToPreview;
}

/**
 * @brief Getter for map name
 * @return the name as found in the XML file
 */
string GameMap::getName() const {
    return name;
}

/**
 * @brief Getter for foreground file, A side
 * @return path to foreground image A side
 */
string GameMap::getPathToFrontA() const {
    return pathToFrontA;
}

/**
 * @brief Getter for foreground file, B side
 * There may be none!
 * @return path to foreground image B side
 */
string GameMap::getPathToFrontB() const {
    return pathToFrontB;
}

/**
 * Toggle between A and B side, if possible
 * \param use true for B, false for A
 */
void GameMap::useBSide(const bool use) {
    if (hasBSide) {
        bSide = use;
    }
}
