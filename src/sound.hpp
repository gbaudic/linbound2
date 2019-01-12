/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SOUND_
#define _H_SOUND_

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SoundManager final {
public:
	SoundManager();
	~SoundManager();

	void playSound(std::string sndName, int loops);
	void changeMode(std::string newMode); // use an enum instead...

	static int countGoldRepeat(Sint16 value);

private:
	std::map<std::string, Mix_Chunk*> effects;
	Mix_Music* music = nullptr;
};

#endif // !_H_SOUND_

