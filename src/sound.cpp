/**
 * \file sound.cpp
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

#include <stdexcept>
#include <random>
#include "config.hpp"
#include "sound.hpp"
using namespace std;

SoundManager* SoundManager::instance = nullptr;

/**
 * Constructor
 * Note that the sound system must have been initialized before
 */
SoundManager::SoundManager() {
	string effectNames[] = { "wind1", "turn", "victory", "lose", "money",
							"cow", "duck", "electron", "goat", "ice", "pig", "sheep", "tea", "unicorn" };

	for (string item : effectNames) {
		string path = RESOURCE_PREFIX + "/sounds/" + item + ".ogg";
		Mix_Chunk* res = Mix_LoadWAV(path.c_str());
		if (res != nullptr) {
			effects.insert(make_pair(item, res));
		}
	}

}

/**
 * \brief Getter for singleton pattern
 */
SoundManager * SoundManager::getInstance() {
	if (instance == nullptr) {
		instance = new SoundManager();
	}
	return instance;
}

/**
 * Plays a sound which is not the background music, e.g. SFX
 * @param sndName the name of the effect to play
 * @param loops the number of iterations of the sound
 */
void SoundManager::playSound(const string &sndName, const int loops) {
	try {
		Mix_PlayChannel(-1, effects.at(sndName), loops);
	}
	catch (const out_of_range) {
		string errstring = "Sound effect not found: " + sndName;
		SDL_SetError("%s", errstring.c_str());
	}
}

/**
 * \brief Switch the music theme when changing application context
 * \param newMode destination context
 */
void SoundManager::changeMode(const ContextName &currentMode, const ContextName &newMode) {
	if (newMode == ContextName::ITEM_SHOP || currentMode == ContextName::ITEM_SHOP) {
		// ITEM_SHOP is the only mode where we do not change the music
		return;
	}

	if (Mix_PlayingMusic() == 1) {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		Mix_HaltChannel(-1);
	}
	
	// load and pick the right music depending on the mode
	string menuMusic = RESOURCE_PREFIX + "/music/";
	switch (newMode) {
	case ContextName::MAIN_MENU:
		menuMusic += "diabolicux.ogg";
		break;
	case ContextName::SERVER_LIST_LAN: // fallthrough
	case ContextName::SERVER_LIST_WEB:
		menuMusic += "diabolicux.ogg";  // change once we have several files...		
		break;
	case ContextName::ROOM_LOBBY: // fallthrough
	case ContextName::ROOM_LOBBY_LOCAL:
		menuMusic += "diabolicux.ogg";
		break;
	case ContextName::ROOM:
		menuMusic += pickGameMusic();
		break;
	case ContextName::ROOM_SUDDEN_DEATH:
		menuMusic += "suddendeath.ogg";
		break;
	default:
		break;
	}
	music = Mix_LoadMUS(menuMusic.c_str());

	
	if (music != nullptr) {
		Mix_PlayMusic(music, -1);
	}
}

/**
 * \brief Free the memory used and clean up nicely
 */
void SoundManager::close() {
	Mix_HaltMusic();
	if (music) {
		Mix_FreeMusic(music);
		music = nullptr;
	}
	Mix_HaltChannel(-1);

	for (const auto &item : effects) {
		Mix_FreeChunk(item.second);
	}
}

/**
 *  Determine how many times we have to repeat the sound for money
 *  @return the number of times to play between 1 and 5
 */
int SoundManager::countGoldRepeat(const Sint16 value) {
	int repeats = 1;
	int absolute = abs(value);
	if (absolute > 50)
		repeats++;
	if (absolute > 100)
		repeats++;
	if (absolute > 200)
		repeats++;
	if (absolute > 500)
		repeats++;

	return repeats;
}

/**
 * Choose a track at random among the ones available
 * @return filename for the track to play
 */
std::string SoundManager::pickGameMusic() {
	string musics[] = { "diabolicux.ogg" };

	default_random_engine generator(SDL_GetTicks());
	uniform_int_distribution<int> distribution(0, 1);

	int index = distribution(generator);
	return musics[index];
}
