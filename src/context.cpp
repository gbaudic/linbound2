/**
 * \file context.cpp
 * \brief Parent class for the views/states of the software
 * \author G. B.
 * \version 0.1a
 * \date 18/01/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "sound.hpp"
#include "context.hpp"
#include "views/menu.hpp"
#include "views/serverlist.hpp"
#include "views/serverview.hpp"
#include "views/roomview.hpp"
using namespace std;

// Init of static class members
Context* Context::currentContext = nullptr;
Context* Context::lastContext = nullptr;
gcn::Container* Context::parent = nullptr;
NetworkManager Context::network;

/**
 * Constructor
 * \param type name of the context being created
 */
Context::Context(ContextName type) : 
    name(type) {
	top.setWidth(parent->getWidth());
	top.setHeight(parent->getHeight());
	top.setOpaque(false);
}

Context::~Context() {

}

/**
 * \brief Getter for context name
 * \return name of the current context
 */
ContextName const Context::getName() {
    return name;
}

/**
 * \brief Getter for next context name, i.e., the context we should move to
 * if an operation triggering a change happened in this Context
 * \return name of next context
 */
ContextName const Context::getNextContextName() {
	return next;
}

/**
 * Set the main top gui container
 * As per Guisan design, there is only one of these for the whole application,
 * so it makes sense to make it static in Context
 * Must be set before instantiating any of the child classes of Context!
 * \param topContainer top Container in Guisan
 */
void Context::setParent(gcn::Container * topContainer) {
	parent = topContainer;
}

/**
 * Call this function when entering this Context
 */
void Context::enter() {
	parent->add(&top);
}

/**
 * Call this function when leaving a Context, either to another one or when exiting the app
 */
void Context::leave() {
	parent->remove(&top);
}

/**
 * Receive a message from the network manager and process them
 * It is up to the Context to do the processing
 */
void Context::receive() {
    // Get messages from network manager
    vector<UDPpacket *> data = network.receive();
    
    // Unpack and feed context, one by one
    for(const UDPpacket *p : data) {
        processMessage(NetworkManager::getCode(p), NetworkManager::getMessage(p));
    }
}

void Context::send(const Uint8 code, const std::string & message) {
    network.send(code, message);
}

void Context::setServerIP(const Uint32 ip) {
	network.setServerInfo(ip);
}

/**
 * Getter for height
 * Useful for subclasses when placing widgets if you do not want to code all coordinates in absolute
 * \return height of the container, in pixels
 */
const int Context::getHeight() const {
	return top.getHeight();
}

/**
 * Getter for width
 * Useful for subclasses when placing widgets if you do not want to code all coordinates in absolute
 * \return width of the container, in pixels
 */
const int Context::getWidth() const {
	return top.getWidth();
}

/**
 * Create and replace the current Context in the application
 * Closely related to the Factory design pattern
 * \param nextName name for the context to go to
 */
Context * Context::getNextContext(ContextName nextName) {
	ContextName currentName = ContextName::NONE;

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
	case ContextName::ROOM_LIST:
		if (currentContext) {
			currentName = currentContext->getName();
			currentContext->leave();
			delete currentContext;
		}
		currentContext = new ServerView(currentName);
		currentContext->enter();
		break;
	default:
		break;
	}
	return currentContext;
}

/**
 * Let child classes add their widgets to the Context top container, which is itself
 * added to the application main container
 * \param widget widget to add
 * \param x x coordinate, in screen coordinates
 * \param y y coordinate, in screen coordinates
 * \see Context::addCenteredWidget(gcn::Widget*)
 */
void Context::addWidget(gcn::Widget * widget, int x, int y){
	top.add(widget, x, y);
}

/**
 *  Helper function to insert widgets centered w.r.t. a parent
 *  Highly useful for message boxes and input boxes
 *  \param widget widget to insert
 */
void Context::addCenteredWidget(gcn::Widget * widget) {
	int x = (top.getWidth() - widget->getWidth()) / 2;
	int y = (top.getHeight() - widget->getHeight()) / 2;

	addWidget(widget, x, y);
}

/**
 * \brief Set next context to use, to mark that a transition is requested
 * \param newContext new context to use
 */
void Context::setNextContext(const ContextName newContext) {
	next = newContext;
}
