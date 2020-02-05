/**
 * \file main.cpp
 * \brief Starting point of the program and main loop
 * \author G. B.
 * \version 0.1a
 * \date 08/11/2018
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_framerate.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

#include "main.hpp"
#include "config.hpp"
#include "settings.hpp"
#include "sound.hpp"
#include "utils.hpp"
#include "context.hpp"
#include "views/menu.hpp"

using namespace std;

Context *currentContext = nullptr;
FPSmanager fpsMgr;
gcn::Gui *gui = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;
SDL_Surface *guiSurface = nullptr;
SDL_Texture *guiTexture = nullptr;

/**
 * Main function
 */
int main(int argc, char* argv[]) {
	if (argc > 1) {
		usage();
		return 0;
	}

	Settings *settings = Settings::getInstance();

	//Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "FATAL: Cannot init SDL: %s", SDL_GetError());
		return -1;
	}

	//Initializing SDL_ttf, needed for text display
	if (TTF_Init() != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "FATAL: Cannot init SDL_ttf: %s", SDL_GetError());
		return -1;
	}

	string fontPath = RESOURCE_PREFIX + "/fonts/LiberationSans-Regular.ttf";
	//TTF is initialized correctly, so let's load the font
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 12);
	if (font == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Font opening failed! %s", TTF_GetError());
		return -1;
	}

	window = SDL_CreateWindow("LinBound", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		settings->getWidth(), settings->getHeight(), SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "FATAL: Cannot create window: %s", SDL_GetError());
		return 1;
	}
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "FATAL: Cannot create renderer: %s", SDL_GetError());
		return 1;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	//Give an icon to the window
	string iconPath = RESOURCE_PREFIX + "/linbound.gif";
	SDL_Surface* icon = IMG_Load(iconPath.c_str());
	SDL_SetWindowIcon(window, icon);

	string cursorPath = RESOURCE_PREFIX + "/cursor.png";
	SDL_Surface *cursor = IMG_Load(cursorPath.c_str());

	if (SDL_SetColorKey(cursor, SDL_TRUE, SDL_MapRGB(cursor->format, 0xff, 0, 0xff)) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
	}
	SDL_SetSurfaceRLE(cursor, 1);

	SDL_Cursor* mousePointer = SDL_CreateColorCursor(cursor, 0, 0);
	if (!mousePointer) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "FATAL: Cannot create cursor: %s", SDL_GetError());
		return 1;
	}
	SDL_SetCursor(mousePointer);

	//The next function puts the cursor at the center of our screen
	SDL_WarpMouseInWindow(window, settings->getWidth() / 2, settings->getHeight() / 2);

	gcn::SDLImageLoader *imageLoader = nullptr;
	gcn::SDLTrueTypeFont *gcnfont = nullptr;
	gcn::SDLInput input;
	gcn::SDL2Graphics graphics;
	gcn::Container top;

	if (!settings->isAServer()) {
		// Init sound
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Mix_OpenAudio: %s", Mix_GetError());
			return -1;
		}

		int flags = MIX_INIT_OGG | MIX_INIT_MP3; //MP3 is unlikely to work everywhere...

		if (Mix_Init(flags) != flags) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error loading audio decoding libraries: %s", Mix_GetError());
		}

		int channels = 4;
		if (Mix_AllocateChannels(channels) != channels) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "All channels haven't been allocated, exiting");
			return -1;
		}

		//Set the volume according to settings
		Mix_VolumeMusic(settings->getMusicVolume());
		Mix_Volume(-1, settings->getEffectsVolume());

		//Create GUI base objects
		imageLoader = new gcn::SDLImageLoader();
		imageLoader->setRenderer(renderer);
		gcn::Image::setImageLoader(imageLoader);
		gcnfont = new gcn::SDLTrueTypeFont(fontPath, 12);
		gcn::Widget::setGlobalFont(gcnfont);

		top.setOpaque(false);
		top.setDimension(gcn::Rectangle(0, 0, settings->getWidth(), settings->getHeight()));
		graphics.setTarget(renderer, settings->getWidth(), settings->getHeight());

		gui = new gcn::Gui();
		gui->setGraphics(&graphics);
		gui->setInput(&input);
		gui->setTop(&top);		

		SDL_DisableScreenSaver();
	}

	SDL_setFramerate(&fpsMgr, 30);

	Context::setParent(&top);
	currentContext = Context::getNextContext(ContextName::MAIN_MENU);
	SoundManager::getInstance()->changeMode(ContextName::NONE, ContextName::MAIN_MENU);

	// insert call to loop here
	try {
		loop(input);
	}
	catch (const gcn::Exception &e) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", e.getMessage().c_str());
		return 1;
	}
	catch (const std::exception &e) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Std exception: %s", e.what());
		return 1;
	}
	catch (...) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", "Unknown exception");
		return 1;
	}

	TTF_CloseFont(font);

	currentContext->leave();
	delete currentContext; // once complete, should not be done like this
	delete gui;
	delete imageLoader;
	delete gcnfont;
	TTF_Quit();

	SDL_FreeCursor(mousePointer);
	SDL_FreeSurface(cursor);
	SDL_FreeSurface(icon);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SoundManager::getInstance()->close();
	Mix_CloseAudio();
	Mix_Quit();
	
	SDL_Quit();
    
	return 0;
}

/**
 * Basic usage string
 */
void usage() {
    cout << "Linbound v" << linbound::getVersionString() << endl
         << "(C) 2007-2020 G. Baudic" << endl;
    return;
}

/**
 * Main loop of the game
 */
void loop(gcn::SDLInput &input) {
	SDL_Event event;

	for (;;) {
		// Change context if necessary
		ContextName next = currentContext->getNextContextName();
		if (next != currentContext->getName()) {
			currentContext = Context::getNextContext(next);
		}

		// handle user events
		while (SDL_PollEvent(&event) == 1) {
			if (event.type == SDL_QUIT)
				return;

			currentContext->processEvent(event);
			
			input.pushInput(event);
		}
		// Handle received messages
		currentContext->receive();

		gui->logic();

		SDL_RenderClear(renderer);

		//** Background (and foreground if necessary)
		currentContext->drawBackground(renderer);

		//** GUI
		gui->draw();

		//** Overlay (if any)
		currentContext->drawOverlay(renderer);

		SDL_RenderPresent(renderer);

		SDL_framerateDelay(&fpsMgr);
	}
}
