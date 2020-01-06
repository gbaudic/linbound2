/**
 * \file sound.hpp
 * \brief Sound-related functions
 * \author G. B.
 * \version 0.1a
 * \date 13/01/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SOUND_
#define _H_SOUND_

#include <map>
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "context.hpp"

class SoundManager final {
public:
	static SoundManager* getInstance();

	void playSound(const std::string &sndName, const int loops = 1);
	void changeMode(const ContextName &currentMode, const ContextName &newMode);
	void close();

	static int countGoldRepeat(const Sint16 value);
	static std::string pickGameMusic();

private:
	SoundManager();
	static SoundManager* instance;

	std::map<std::string, Mix_Chunk*> effects;
	Mix_Music* music = nullptr;
	SoundManager& operator= (const SoundManager&) = delete; //ensure singleton
	SoundManager(const SoundManager&) = delete;
};

#endif // !_H_SOUND_
