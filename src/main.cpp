/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

#include "main.hpp"
#include "config.hpp"
#include "settings.hpp"
#include "sound.hpp"
#include "utils.hpp"

using namespace std;

/**
 * Minimalistic main function
 */
int main(int argc, char* argv[]) {
	if (argc > 1) {
		usage();
		return 0;
	}

	Settings *settings = Settings::getInstance();

	//Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		cout << "FATAL : Cannot init SDL : " << SDL_GetError() << endl;
		return -1;
	}

	//Initializing SDL_ttf, needed for text display
	if (TTF_Init() != 0) {
		cout << "FATAL : Cannot init SDL_ttf " << SDL_GetError() << endl;
		return -1;
	}

	string fontPath = RESOURCE_PREFIX + "/fonts/LiberationSans-Regular.ttf";
	//TTF is initialized correctly, so let's load the font
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 12);
	if (font == NULL) {
		cout << "Font opening failed! " << TTF_GetError() << endl;
		return -1;
	}

	gcn::SDLImageLoader *imageLoader = nullptr;
	gcn::SDLTrueTypeFont *gcnfont = nullptr;
	gcn::SDLInput input;
	gcn::SDLGraphics graphics;

	if (!settings->isAServer()) {
		// Init sound
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			cout << "Mix_OpenAudio: " << Mix_GetError() << endl;
			return -1;
		}

		int flags = MIX_INIT_OGG | MIX_INIT_MP3; //MP3 is unlikely to work everywhere...

		if (Mix_Init(flags) != flags) {
			cout << "Error loading audio decoding libraries: " << Mix_GetError() << endl;
		}

		int channels = 4;
		if (Mix_AllocateChannels(channels) != channels) {
			cout << "All channels haven't been allocated, exiting" << endl;
			return -1;
		}

		//Set the volume according to settings
		Mix_VolumeMusic(settings->getMusicVolume());
		Mix_Volume(-1, settings->getEffectsVolume());

		//Create GUI base objects
		imageLoader = new gcn::SDLImageLoader();
		gcn::Image::setImageLoader(imageLoader);
		gcnfont = new gcn::SDLTrueTypeFont(fontPath, 12);
		gcn::Widget::setGlobalFont(gcnfont);

		SDL_DisableScreenSaver();
	}

	SoundManager sndMgr;

	// insert call to loop here

	TTF_CloseFont(font);
	TTF_Quit();

	delete gcnfont;
	delete imageLoader;

	Mix_Quit();
	Mix_CloseAudio();

	SDL_Quit();
    
	return 0;
}

void usage() {
    cout << "Linbound v" << linbound::getVersionString() << endl
         << "(C) 2007-2019 G. Baudic" << endl;
    return;
}

void loop() {
	for (;;) {

	}
}
