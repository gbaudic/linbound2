/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL_image.h>
#include "../protocol.hpp"
#include "../utils.hpp"
#include "serverlist.hpp"
using namespace std;

ServerList::ServerList(ContextName name) : Context(name), 
state(State::NONE), currentIP(0x0), 
btn_back("< Back"), btn_manualIP("Enter IP"), btn_rescan("Rescan local network"),
input_ip("IP", "Enter server address")
{
	btn_back.setActionEventId("back");
	btn_back.addActionListener(this);
	btn_manualIP.setActionEventId("ip");
	btn_manualIP.addActionListener(this);
	btn_rescan.setActionEventId("rescan");
	w_login.setActionEventId("login");
	w_login.addActionListener(this);
	w_login.setVisible(false);
    input_ip.setVisible(false);
    input_ip.setActionEventId("connect");
    input_ip.addActionListener(this);
	btn_manualIP.setWidth(btn_rescan.getWidth());

	string imgPath = RESOURCE_PREFIX + "/menu/lb_serverlist.png";
	background = IMG_Load(imgPath.c_str());

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
		input_ip.setVisible(true);
	}
	else if (actionEvent.getId() == "rescan") {
		sendRequest();
	}
	else if (actionEvent.getId() == "connect") {
		currentIP = linbound::stringToIP(input_ip.getText());
		if (currentIP != 0) {
			sendRequest(currentIP);
			input_ip.setVisible(false);
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
	
	Uint32 currentTime = SDL_GetTicks();
    if(state != State::NONE && currentTime - lastChangeTime > REQUEST_TIMEOUT) {
        switch(state) {
            case State::LOGIN:
                w_login.onLogin(5); // code for timeouts
                break;
            case State::RECEIVING_IP:
                // Show a MessageBox warning of timeout
                break;
            default:
                break;
        }
        state = State::NONE;
    }
	
	
	SDL_RenderCopy(screen, backTexture, NULL, NULL);
}

void ServerList::processMessage(const Uint8 code, const string & message) {
	switch (code) {
	case SERVER_INFO:
		// Analyze message and create button, store in vector
		serversFound.push_back(makeInfo(message));
		break;
	case LOGIN_MSG: {
		// Analyze message, warn of errors
		int result = stoi(message);
		w_login.onLogin(result);

		if (result == 0) {
			setNextContext(ContextName::ROOM_LIST);
		}
	}
		break;
	default:
        // Other message types will be ignored
		break;
	}
}

/**
 * Getter so the RoomList can know where to connect to when changing Context
 * \return IP of the server for which connection was accepted
 */
Uint32 ServerList::getIP() const {
	return currentIP;
}

void ServerList::addWidgets() {
	addWidget(&btn_back, 40, background->h - 40);
	addWidget(&btn_manualIP, 600, background->h / 2);
	addWidget(&btn_rescan, 600, btn_manualIP.getY() + 40);

	addCenteredWidget(&w_login);
	addCenteredWidget(&input_ip);
}

/**
 * Try to see if a server exists at a given IP
 * \param ip IPv4 as an Uint32, fetched from the user
 */
void ServerList::sendRequest(Uint32 ip) {
	// Set IP
	setServerIP(ip);

	// Send it
	send(HELLO_MSG, "HELLO");

	if (ip == INADDR_BROADCAST) {
		state = State::RECEIVING_BC;
	}
	else {
		state = State::RECEIVING_IP;
	}
    lastChangeTime = SDL_GetTicks();
}

void ServerList::login(Uint32 ip, const string & login, const string & password) {
    // Set IP in NetworkManager
	setServerIP(ip);
    
    string message = login + '\3' + password; // yup, in clear
    
    // Send it
    send(LOGIN_MSG, message);

	state = State::LOGIN;
    lastChangeTime = SDL_GetTicks();
}

ServerInfo ServerList::makeInfo(const std::string & message) {
	ServerInfo result;
	vector<string> pieces = linbound::split(message, '\3');

	if (pieces.size() >= 4) {
		result.name = pieces[0];
		result.levelMin = static_cast<Uint8>(pieces[1].at(0));
		result.levelMax = static_cast<Uint8>(pieces[2].at(0));
		result.busy = static_cast<Uint8>(pieces[3].at(0));
	}

	return result;
}
