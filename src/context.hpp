/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_CONTEXT_
#define _H_CONTEXT_

#include <string>
#include <SDL2/SDL.h>
#include <guisan.hpp>
#include "network.hpp"

/**
 * Enum to tell the different states for the software
 */
enum class ContextName {
	NONE, // only used at startup
	MAIN_MENU,
	SERVER_LIST_LAN,
	SERVER_LIST_WEB,
	ROOM_LIST,
	ROOM_LOBBY,
	ROOM_LOBBY_LOCAL,
	ROOM,
	ROOM_SUDDEN_DEATH, // to make it easier for music change
	ITEM_SHOP,
	EXIT // for quitting
};

class Context {
public:
	explicit Context(ContextName type);
	virtual ~Context();
	ContextName const getName();
	ContextName const getNextContextName();
	static void setParent(gcn::Container* topContainer);
	virtual void drawBackground(SDL_Renderer *screen) = 0;
	virtual void drawOverlay(SDL_Renderer *screen) = 0;

	virtual void enter();
	virtual void leave();
    void receive();
	virtual void processMessage(const Uint8 code, const std::string &message) { 
		// Left empty because some derived classes will not need this
	};
	virtual void processEvent(SDL_Event &event) = 0;

	static Context* getNextContext(ContextName nextName);

protected:
	void addWidget(gcn::Widget *widget, int x = 0, int y = 0);
	void addCenteredWidget(gcn::Widget *widget);
	void setNextContext(const ContextName newContext);
    void send(const Uint8 code, const std::string & message);
	void setServerIP(const Uint32 ip);

	const int getHeight() const;
	const int getWidth() const;

	static NetworkManager network;

private:
	static gcn::Container *parent;
	ContextName name;
	ContextName next = ContextName::NONE;
	gcn::Container top;

	static Context* currentContext;
	static Context* lastContext;  
};

#endif // !_H_CONTEXT_


