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
#include "sound.hpp"

enum class ContextName {
	MAIN_MENU,
	SERVER_LIST,
	ROOM_LIST,
	ROOM_LOBBY,
	ROOM,
	ITEM_SHOP
};

class Context {
public:
	Context(ContextName type, gcn::Container *topContainer);
	virtual ~Context();
	ContextName const getName();
	virtual void drawBackground() = 0;
	virtual void drawMiddleground() = 0;

	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void processMessage(const Uint16 code, const std::string &message) = 0;
	virtual void processEvent(SDL_Event &event) = 0;

private:
	gcn::Container *parent;
	ContextName name;
	gcn::Container top;
};

#endif // !_H_CONTEXT_


