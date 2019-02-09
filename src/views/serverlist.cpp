/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL_net.h>
#include "../protocol.hpp"
#include "../utils.hpp"
#include "serverlist.hpp"
using namespace std;

ServerList::ServerList(ContextName name, gcn::Container * p) : Context(name, p), 
state(State::NONE), currentIP(0x0), 
btn_back("< Back"), btn_manualIP("Enter IP"), btn_rescan("Rescan local network")
{
	btn_back.setActionEventId("back");
	btn_back.addActionListener(this);
	btn_manualIP.setActionEventId("ip");
	btn_manualIP.addActionListener(this);
	btn_rescan.setActionEventId("rescan");
	w_login.setActionEventId("login");
	w_login.addActionListener(this);
	w_login.setVisible(false);

	if (name == ContextName::SERVER_LIST_WEB) {
		btn_rescan.setVisible(false); // this is useless for a web game
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
	else if (actionEvent.getId() == "connect") {
		currentIP = linbound::stringToIP("127.0.0.1"); // To be replaced once InputBox is in
		if (currentIP != 0) {
			sendRequest(currentIP);
		}
	}
	else if (actionEvent.getId() == "login") {
		login(currentIP, w_login.getLogin(), w_login.getPassword());
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
		// Analyze message and create button, store in vector
		break;
	case LOGIN_MSG:
		// Analyze message, warn of errors
		setNextContext(ContextName::ROOM_LIST);
		break;
	default:
		break;
	}
}

/**
 * Getter so the RoomList can know where to connect to when changing Context
 * \return IP of the server for which connection was accepted
 */
Uint32 ServerList::getIP() const
{
	return currentIP;
}

void ServerList::addWidgets() {
	addWidget(&btn_back, 40, background->h - 40);
	addWidget(&btn_manualIP, 700, background->h / 2);
	addWidget(&btn_rescan, 700, btn_manualIP.getY() + 40);

	addCenteredWidget(&w_login);
}

/**
 * Send a broadcast message to find other servers
 */
void ServerList::scanNetwork() {
	// TBD

	state = State::RECEIVING_BC;
}

/**
 * Try to see if a server exists at a given IP
 * \param ip IPv4 as an Uint32, fetched from the user
 */
void ServerList::sendRequest(Uint32 ip) {
	// Create message

	// Send it

	state = State::RECEIVING_IP;
}

void ServerList::login(Uint32 ip, const std::string & login, const std::string & password) {

	state = State::LOGIN;
}
