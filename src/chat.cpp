/**
 * \file chat.cpp
 * \brief Chat management system for various buddy chat windows
 * \author G. B.
 * \version 0.1a
 * \date 16/01/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include <iostream>
#include "chat.hpp"
using namespace std;

/**
 * Constructor
 * \param topContainer UI element where windows should be attached
 */
ChatManager::ChatManager(gcn::Container * topContainer) : top(topContainer) {

}

/**
 * Destructor
 */
ChatManager::~ChatManager() {
	for (const auto &w : windows) {
		top->remove(w.second);
		delete w.second;
	}
}

/**
 * Process a new message, creating a new window if necessary
 * \param sender name of the sender (must be a player)
 * \param message message sent
 */
void ChatManager::addMessage(const string &sender, const string &message) {
	try {
		ChatWindow* w = windows.at(sender);
		w->addMessage(sender, message);
		top->moveToTop(w);
	}
	catch (out_of_range) {
		// Unknown sender: create a new window
		windows[sender] = new ChatWindow(sender, message);
		windows[sender]->addActionListener(this);
		top->add(windows[sender], top->getWidth() - 20 - windows[sender]->getWidth(), 20);
	}
}

/**
 * Initiate a conversation from our side, by creating an empty window
 * \param other name of the player receiving the messages
 */
void ChatManager::startConversation(const std::string &other) {
	try {
		// Bring back the window if it exists
		ChatWindow* w = windows.at(other);
		w->setVisible(true);
		top->moveToTop(w);
	}
	catch (out_of_range) {
		// Otherwise, create a new, empty one
		windows[other] = new ChatWindow(other);
		windows[other]->addActionListener(this);
		top->add(windows[other], top->getWidth() - 20 - windows[other]->getWidth(), 20);
	}
}

void ChatManager::action(const gcn::ActionEvent & action) {
	string dest = action.getId();
	try {
	    ChatWindow* w = windows.at(dest);
		string message = w->getMessage();
		// TODO Send the message to the network system
	}
	catch (out_of_range) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Received an action from an unknown widget");
	}
}
