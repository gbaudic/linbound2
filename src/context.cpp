/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "sound.hpp"
#include "context.hpp"
#include "views/menu.hpp"
#include "views/serverlist.hpp"
using namespace std;

Context* Context::currentContext = nullptr;
Context* Context::lastContext = nullptr;
gcn::Container* Context::parent = nullptr;

Context::Context(ContextName type) : 
    name(type)
{
	top.setWidth(parent->getWidth());
	top.setHeight(parent->getHeight());
	top.setOpaque(false);
}

Context::~Context() {
}

ContextName const Context::getName() {
    return name;
}

ContextName const Context::getNextContextName() {
	return next;
}

void Context::setParent(gcn::Container * topContainer) {
	parent = topContainer;
}

void Context::enter() {
	parent->add(&top);
}

void Context::leave() {
	parent->remove(&top);
}

Context * Context::getNextContext(ContextName nextName) {
	switch (nextName) {
	case ContextName::MAIN_MENU:
		if (currentContext) {
			currentContext->leave();
			delete currentContext;
		}
		currentContext = new Menu();
		currentContext->enter();
		break;
	case ContextName::SERVER_LIST_LAN: // fallthrough
	case ContextName::SERVER_LIST_WEB:
		if (currentContext) {
			currentContext->leave();
			delete currentContext;
		}
		currentContext = new ServerList(nextName);
		currentContext->enter();
		break;
	default:
		break;
	}
	return currentContext;
}

void Context::addWidget(gcn::Widget * widget, int x, int y){
	top.add(widget, x, y);
}

/**
 *  Helper function to insert widgets centered w.r.t. a parent
 *  \param widget widget to insert
 */
void Context::addCenteredWidget(gcn::Widget * widget) {
	int x = (top.getWidth() - widget->getWidth()) / 2;
	int y = (top.getHeight() - widget->getHeight()) / 2;

	addWidget(widget, x, y);
}

void Context::setNextContext(const ContextName newContext) {
	next = newContext;
}
