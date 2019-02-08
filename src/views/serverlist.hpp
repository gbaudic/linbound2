/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SERVERLIST_
#define _H_SERVERLIST_

#include <string>
#include <vector>
#include <guisan.hpp>
#include <SDL2/SDL.h>
#include "../context.hpp"

class ServerList : public Context, public gcn::ActionListener {
public:
	ServerList(ContextName name, gcn::Container *p);
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

private:
	gcn::Button btn_back;
	gcn::Button btn_manualIP;
	gcn::Button btn_rescan;
	// gcn::InputBox input_ip;

	SDL_Texture *backTexture = nullptr;
	SDL_Surface *background = nullptr;

	void addWidgets();
	void scanNetwork();
};

#endif // !_H_SERVERLIST_
