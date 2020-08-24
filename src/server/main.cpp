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
// Settings variables -- put here just for simplicity
string serverName = "server";
Uint8 minLevel = 0;
Uint8 maxLevel = 255;

void loop(NetworkManager &manager);

/**
 * Print a basic help in case of improper arguments
 */
void usage() {
    cout << "Linbound server" << endl
        << "Supported options:" << endl
        << "--debug  : enable debug output" << endl
        << "--help   : print this help and exit" << endl
        << "--name n : give this server a name (default: server)" << endl
        << "--min x  : set minimum level to enter (default: no limit)" << endl
        << "--max x  : set maximum level to enter (default: no limit)" << endl;
}

/**
 * Process command-line arguments if any
 * \param argIndex counter for arguments processed so far
 * \param code return code to use in case of error during parsing
 * \param argc number of arguments supplied
 * \param argv text of arguments supplied
 */
void processArgs(int &argIndex, int &code, int argc, char *argv[]) {
    while (argIndex < argc) {
        if (SDL_strncmp("--debug\0", argv[argIndex], 7) == 0) {
            SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
            argIndex++;
        } else if (SDL_strncmp("--help\0", argv[argIndex], 6) == 0) {
            code = 0;
            break;
        } else if (SDL_strncmp("--name\0", argv[argIndex], 6) == 0) {
            if (argIndex + 1 < argc) {
                // Use name
                serverName = string(argv[argIndex + 1]);
                argIndex += 2;
            } else {
                // Error
                break;
            }
        } else if (SDL_strncmp("--min\0", argv[argIndex], 5) == 0) {
            if (argIndex + 1 < argc) {
                // Use min
                minLevel = strtol(argv[argIndex + 1], nullptr, 10);
                argIndex += 2;
            } else {
                // Error
                break;
            }
        } else if (SDL_strncmp("--max\0", argv[argIndex], 5) == 0) {
            if (argIndex + 1 < argc) {
                // Use max
                maxLevel = strtol(argv[argIndex + 1], nullptr, 10);
                argIndex += 2;
            } else {
                // Error
                break;
            }
        } else {
            // Unknown option = error
            break;
        }
    }
    return;
}

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    
    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "FATAL: Cannot init SDL: %s", SDL_GetError());
        return -1;
    }

    // Basic argument parsing
    if (argc >= 2) {
        int argIndex = 1;
        int code = -1;
        processArgs(argIndex, code, argc, argv);
        if (argIndex < argc || minLevel > maxLevel) {
            // Premature stop, exit
            usage();
            SDL_Quit();
            return code;
        }

        // TODO range detection
    }
    
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Starting LinBound server v%s", linbound::getVersionString().c_str());

    NetworkManager manager(true);

    loop(manager);
    
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Exiting");
    SDL_Quit();
    
    return 0;
}

/**
 * Main loop of the program
 * @param manager network component to send/receive packets
 */
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
            case STATUS_PING:
                manager.send(STATUS_PONG, "", NetworkManager::getAddress(p));
                break;
            default:
                break;
            }
        }
    }
}
