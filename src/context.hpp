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

enum class ContextName {
	MAIN_MENU,
	SERVER_LIST,
	ROOM_LIST,
	ROOM_LOBBY,
	ROOM,
	ITEM_SHOP,
	EXIT // for quitting
};

class Context {
public:
	Context(ContextName type, gcn::Container *topContainer);
	virtual ~Context();
	ContextName const getName();
	ContextName const getNextContext();
	virtual void drawBackground(SDL_Renderer *screen) = 0;
	virtual void drawOverlay(SDL_Renderer *screen) = 0;

	virtual void enter();
	virtual void leave();
	virtual void processMessage(const Uint16 code, const std::string &message) { 
		// Left empty because some derived classes will not need this
	};
	virtual void processEvent(SDL_Event &event) = 0;

protected:
	void addWidget(gcn::Widget *widget, int x = 0, int y = 0);
	void addCenteredWidget(gcn::Widget *widget);
	void setNextContext(const ContextName newContext);

private:
	gcn::Container *parent;
	ContextName name;
	ContextName next;
	gcn::Container top;
};

#endif // !_H_CONTEXT_


