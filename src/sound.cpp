/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "config.hpp"
#include "context.hpp"
#include "sound.hpp"
using namespace std;

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager() {
	music = nullptr;
	string effectNames[] = { "wind1", "turn", "victory", "lose", "money",
							"cow", "duck", "electron", "goat", "ice", "pig", "sheep", "tea", "unicorn" };

	for (string item : effectNames) {
		string path = RESOURCE_PREFIX + "/sounds/" + item + ".ogg";
		Mix_Chunk* res = Mix_LoadWAV(path.c_str());
		if (res != NULL) {
			effects.insert(make_pair(item, res));
		}
	}

}

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
void SoundManager::playSound(string sndName, const int loops) {
	try {
		Mix_PlayChannel(-1, effects.at(sndName), loops);
	}
	catch (const out_of_range) {
		string errstring = "Sound effect not found: " + sndName;
		SDL_SetError(errstring.c_str());
	}
}

void SoundManager::changeMode(ContextName &newMode) {
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
	default:
		break;
	}
	music = Mix_LoadMUS(menuMusic.c_str());

	
	if (music != NULL) {
		Mix_PlayMusic(music, -1);
	}
}

void SoundManager::close() {
	Mix_HaltMusic();
	if (music) {
		Mix_FreeMusic(music);
		music = nullptr;
	}
	Mix_HaltChannel(-1);

	for (auto &item : effects) {
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
