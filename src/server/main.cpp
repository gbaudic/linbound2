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
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "../config.hpp"
#include "../network.hpp"
#include "../utils.hpp"
#include "../protocol.hpp"
#include "database.hpp"
using namespace std;

Database db;

void loop(NetworkManager &manager);

int main(int argc, char *argv[]) {
    
    //Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "FATAL: Cannot init SDL: %s", SDL_GetError());
        return -1;
    }

    // Basic argument parsing
    if (argc >= 2) {
        if (SDL_strncmp("--debug\0", argv[1], 7) == 0) {
            SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
        }
    }
    
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Starting LinBound server v%s", linbound::getVersionString().c_str());

    NetworkManager manager(true);

    loop(manager);
    
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Exiting");
    SDL_Quit();
    
    return 0;
}

void loop(NetworkManager &manager) {
    SDL_Event event;

    for (;;) {
        while (SDL_PollEvent(&event) == 1) {
            // Make sure the server can be stopped using e.g. Ctrl+C (Unix)
            if (event.type == SDL_QUIT)
                return;
        }

        // Process network events (packets)
        vector<UDPpacket*> packets = manager.receive();
        for (const UDPpacket* p : packets) {
            Uint8 code = NetworkManager::getCode(p);
            switch (code) {
            case HELLO_MSG:
                manager.send(SERVER_INFO, "server\0030\003255\0030", NetworkManager::getAddress(p));
                break;
            default:
                break;
            }
        }
    }
}
