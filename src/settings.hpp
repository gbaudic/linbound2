/**
 * \file settings.hpp
 * \brief Settings-related classes
 * \version 0.1a
 * \author G. B.
 * \date 29/10/2016
 */

/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SETTINGS_
#define _H_SETTINGS_

#include <map>
#include <string>
#include <SDL2/SDL.h>

/**
 * \brief Singleton to encapsulate game settings
 */
class Settings {
public:
    Uint16 getEffectsVolume();
    void setEffectsVolume(Uint8 newEffectsVolume);
    Uint16 getHeight();
    void setHeight(Uint16 newHeight);
    static Settings* getInstance();
    Uint16 getMusicVolume();
    void setMusicVolume(Uint8 newMusicVolume);
    Uint16 getWidth();
    void setWidth(Uint16 newWidth);
    bool isAServer() const;
    void setServer(bool server);
    void save();

private:
    std::map<std::string,Uint16> values;
    bool isServer = false;
    bool isServerSet = false; //ensure boolean above is only touched once
    static Settings* instance;
    Settings();
    void init();
    void checkConsistency();
    Settings& operator= (const Settings&) = delete; //ensure singleton
    Settings (const Settings&) = delete;
};


#endif /* _H_SETTINGS_ */
