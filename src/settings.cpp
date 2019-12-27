/**
 * \file settings.cpp
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

#include <iostream>
#include <fstream>
#include <exception>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "settings.hpp"

using namespace std;

Settings* Settings::instance = nullptr;

Uint16 Settings::getEffectsVolume() {
	return values["EffectsVolume"];
}

void Settings::setEffectsVolume( Uint8 newEffectsVolume) {
	values["EffectsVolume"] = newEffectsVolume;
}

Uint16 Settings::getHeight() {
	return values["Height"];
}

void Settings::setHeight( Uint16 newHeight) {
	values["Height"] = newHeight;
}

Settings* Settings::getInstance() {
	if(instance == nullptr){
		instance = new Settings();
	}
	return instance;
}

Uint16 Settings::getMusicVolume() {
	return values["MusicVolume"];
}

void Settings::setMusicVolume( Uint8 newMusicVolume) {
	values["MusicVolume"] = newMusicVolume;
}

Uint16 Settings::getWidth() {
	return values["Width"];
}

void Settings::setWidth( Uint16 newWidth) {
	values["Width"] = newWidth;
}

Settings::Settings() {
	init();
}

Settings::~Settings() {
}

bool Settings::isAServer() {
	return isServer;
}

/**
 * \brief Set this program to run as a server
 */
void Settings::setServer( bool server) {
	if(!isServerSet){
		isServer = server;
		isServerSet = true;
	}
}

/**
 * \brief Initialize settings from external config file
 */
void Settings::init(){
	//Try to read the config file
	ifstream input("linbound.config", ios::in);
	string line;
	
	if(input.is_open()) {
        while(getline(input, line) && !input.eof()){
            if(!line.empty() && line.front() != '['){
                size_t eqpos = line.find('=');
                if(eqpos != string::npos){
                    //Maybe a value here
                    //determine if we know this key
                    string key = line.substr(0, eqpos);
                    string value = line.substr(eqpos + 1);
                    //if yes, check value consistency and inject; if no, ignore
                    try {
                        values[key] = stoi(value);
                    } catch (invalid_argument) {
                        cout << "Error loading settings key: " << key << endl;
						values[key] = 0;
					}
					catch (out_of_range) {
						values[key] = 0;
					}
                }
            }
        }
    } else {
        cout << "Error opening settings file -- using defaults value" << endl;
    }

	checkConsistency();	

	input.close();
}

/**
 * \brief Check that all parsed configuration values are in the correct range
 */
void Settings::checkConsistency() {
	if (values.count("Width") == 0 || values["Width"] < 300) {
		values["Width"] = 800;
	}

	if (values.count("Height") == 0 || values["Height"] < 200) {
		values["Height"] = 600;
	}

	if (values.count("MusicVolume") == 0) {
		values["MusicVolume"] = MIX_MAX_VOLUME / 2;
	}

	if (values.count("EffectsVolume") == 0) {
		values["EffectsVolume"] = MIX_MAX_VOLUME / 2;
	}
}

/**
 * \@brief Write setting changes to disk
 */
void Settings::save() {
	
	ofstream output("linbound.config", ios::out);
    
    if(output.is_open()) {
        output << "[Display]" << endl;
        output << "Height=" << values["Height"] << endl
               << "Width=" << values["Width"] << endl << endl;
        output << "[Audio]" << endl;
        output << "MusicVolume=" << values["MusicVolume"] << endl
               << "EffectsVolume=" << values["EffectsVolume"] << endl;
    } else {
        cout << "Error opening settings file for writing" << endl;
    }
	output.close();
}
