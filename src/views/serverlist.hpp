/**
 * \file serverlist.hpp
 * \brief UI view to pick the server to play on
 * \author G. B.
 * \version 0.1a
 * \date 08/02/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SERVERLIST_
#define _H_SERVERLIST_

#include <string>
#include <vector>
#include <guisan.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "../context.hpp"
#include "../ui/loginwindow.hpp"
#include "../ui/serverlistelement.hpp"

/**
 * View representing the list of servers, used in LAN and web game modes
 */
class ServerList : public Context, public gcn::ActionListener {
public:
	enum class State { NONE,
		LOGIN, // Login sent, waiting for answer
		RECEIVING_BC, // Receiving server data from LAN
		RECEIVING_IP  // Receiving server data from manual IP
	};

	explicit ServerList(ContextName name);
	virtual ~ServerList();
	void action(const gcn::ActionEvent &actionEvent) override;

	virtual void drawBackground(SDL_Renderer *screen) override;
	virtual void processMessage(const Uint8 code, const std::string &message) override;
	virtual void drawOverlay(SDL_Renderer *screen) override {
		// There will never be any overlays in ServerList
	};

	virtual void processEvent(SDL_Event &event) override {
		// No specific handling to be done here, GUI handles everything
	};

	Uint32 getIP() const;

private:
	State state = State::NONE;
	Uint32 currentIP = 0x0;

	gcn::Button btn_back{ "< Back" };
	gcn::Button btn_manualIP{ "Enter IP" };
	gcn::Button btn_rescan{ "Rescan local network" };
	gcn::InputBox input_ip{ "IP", "Enter server address" };
	LoginWindow w_login;

	SDL_Texture *backTexture = nullptr;
	SDL_Surface *background = nullptr;

	const Uint32 REQUEST_TIMEOUT = 5000; // 5 seconds
	Uint32 lastChangeTime; // to handle timeouts

	std::vector<ServerInfo> serversFound;

	void addWidgets();
	void sendRequest(Uint32 ip = INADDR_BROADCAST);
	void login(Uint32 ip, const std::string &login, const std::string &password);
	ServerInfo makeInfo(const std::string &message) const;
};

#endif // !_H_SERVERLIST_
