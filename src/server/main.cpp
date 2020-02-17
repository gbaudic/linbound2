/**
 * \file main.cpp
 * \brief Main method for the server
 * \author G. B.
 * \version 0.1a
 * \date 07/02/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "../config.hpp"
#include "../network.hpp"
#include "database.hpp"
using namespace std;


int main(int argc, char *argv[]) {
	
	//Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "FATAL: Cannot init SDL: %s", SDL_GetError());
		return -1;
	}
	
	cout << "Hello world" << endl;
	
	SDL_Quit();
	
	return 0;
}
