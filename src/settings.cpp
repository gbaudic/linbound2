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
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "settings.hpp"

using namespace std;

Settings* Settings::instance = NULL;

Uint8 Settings::getEffectsVolume() {
	return effectsVolume;
}

void Settings::setEffectsVolume( Uint8 effectsVolume) {
	this->effectsVolume = effectsVolume;
}

Uint16 Settings::getHeight() {
	return height;
}

void Settings::setHeight( Uint16 height) {
	this->height = height;
}

Settings* Settings::getInstance() {
	if(instance == NULL){
		instance = new Settings();
	}
	return instance;
}

Uint8 Settings::getMusicVolume() {
	return musicVolume;
}

void Settings::setMusicVolume( Uint8 musicVolume) {
	this->musicVolume = musicVolume;
}

Uint16 Settings::getWidth() {
	return width;
}

void Settings::setWidth( Uint16 width) {
	this->width = width;
}

Settings::Settings() {
	init();
}

Settings::~Settings() {
}

bool Settings::isAServer() {
	return isServer;
}

void Settings::setServer( bool isServer) {
	if(!isServerSet){
		this->isServer = isServer;
		this->isServerSet = true;
	}
}

/**
 * \brief Initialize settings from external config file
 */
void Settings::init(){
	//Try to read the config file
	ifstream input("linbound.config", ios::in);
	string line;
	Uint8 flags = 0; //to know which fields were set
	
	while(getline(input, line) && !input.eof()){
		if(!line.empty() && line.front() != '['){
			int eqpos = line.find('=');
			if(eqpos != string::npos){
				//Maybe a value here
				//determine if we know this key
				string key = line.substr(0, eqpos);
				string value = line.substr(eqpos + 1);
				//if yes, check value consistency and inject; if no, ignore
				if(key == "Height") {
					height = stoi(value);
					flags |= 1;
				} else if(key == "Width") {
					width = stoi(value);
					flags |= 2;
				} else if(key == "MusicVolume") {
					musicVolume = stoi(value);
					flags |= 4;
				} else if(key == "EffectsVolume") {
					effectsVolume = stoi(value);
					flags |= 16;
				}
			}
		}
	}

	//Consistency check
	if(!(flags & 2) || width < 300) {
		width = 800;
	}
	
	if(!(flags & 1) || height < 200) {
		height = 600;
	}
	
	if(!(flags & 4))
		musicVolume = MIX_MAX_VOLUME / 2;
	
	if(!(flags & 16))
		effectsVolume = MIX_MAX_VOLUME / 2;

	input.close();
}

/**
 * \@brief Write setting changes to disk
 */
void Settings::save() {
	
	ofstream output("linbound.config", ios::out);
	output << "[Display]" << endl;
	output << "Height=" << height << endl
	       << "Width=" << width << endl << endl;
	output << "[Audio]" << endl;
	output << "MusicVolume=" << musicVolume << endl
	       << "EffectsVolume=" << effectsVolume << endl;
	output.close();
}
