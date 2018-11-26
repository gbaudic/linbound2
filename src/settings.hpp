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

#include <SDL2/SDL.h>

/**
 *  \brief Singleton to encapsulate game settings
 */
class Settings {
public:
	Uint8 getEffectsVolume();
	void setEffectsVolume(Uint8 effectsVolume);
	Uint16 getHeight();
	void setHeight(Uint16 height);
	static Settings* getInstance();
	Uint8 getMusicVolume();
	void setMusicVolume(Uint8 musicVolume);
	Uint16 getWidth();
	void setWidth(Uint16 width);
	bool isAServer();
	void setServer(bool isServer);
	void save();

private:
	Uint8 musicVolume;
	Uint8 effectsVolume;
	Uint16 height, width; //! window size
	bool isServer;
	bool isServerSet; //ensure boolean above is only touched once
	static Settings* instance;
	Settings();
	~Settings();
	void init();
	Settings& operator= (const Settings&) = delete; //ensure singleton
	Settings (const Settings&) = delete;
};


#endif /* _H_SETTINGS_ */
