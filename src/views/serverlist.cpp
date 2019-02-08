/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "../protocol.hpp"
#include "../utils.hpp"
#include "serverlist.hpp"
using namespace std;

ServerList::ServerList(ContextName name, gcn::Container * p) : Context(name, p), 
btn_back("< Back"), btn_manualIP("Enter IP"), btn_rescan("Rescan local network")
{

	if (name == ContextName::SERVER_LIST_WEB) {
		btn_rescan.setVisible(false);
	}

	addWidgets();
}

ServerList::~ServerList() {
	// Cleanup our surfaces
	if (background) {
		SDL_FreeSurface(background);
	}
	if (backTexture) {
		SDL_DestroyTexture(backTexture);
	}
}

void ServerList::action(const gcn::ActionEvent & actionEvent) {
	if (actionEvent.getId() == "back") {
		setNextContext(ContextName::MAIN_MENU);
	}
	else if (actionEvent.getId() == "ip") {
		// Open the InputBox
	}
	else if (actionEvent.getId() == "rescan") {
		scanNetwork();
	}
}

void ServerList::drawBackground(SDL_Renderer * screen) {
	if (!backTexture) {
		backTexture = SDL_CreateTextureFromSurface(screen, background);
	}
	SDL_RenderCopy(screen, backTexture, NULL, NULL);
}

void ServerList::processMessage(const Uint8 code, const std::string & message) {
	switch (code) {
	case SERVER_INFO:
		// Analyze message and create button
		break;
	default:
		break;
	}
}

void ServerList::addWidgets() {
	addWidget(&btn_back, 40, background->h - 40);
	addWidget(&btn_manualIP, 700, background->h / 2);
	addWidget(&btn_rescan, 700, btn_manualIP.getY() + 40);
}

/**
 * Send a broadcast message to find other servers
 */
void ServerList::scanNetwork() {
	// TBD
}
