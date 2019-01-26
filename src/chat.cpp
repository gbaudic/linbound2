/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is �Incompatible With Secondary Licenses�,
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include <iostream>
#include "chat.hpp"
using namespace std;

ChatManager::ChatManager(gcn::Container * topContainer) : top(topContainer) {

}

ChatManager::~ChatManager() {
	for (auto &w : windows) {
		top->remove(w.second);
		delete w.second;
	}
}

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

void ChatManager::action(const gcn::ActionEvent & action) {
	string dest = action.getId();
	try {
	    ChatWindow* w = windows.at(dest);
		string message = w->getMessage();
		// Send the message to the network system
	}
	catch (out_of_range) {
		cerr << "Received an action from an unknown widget" << endl;
	}
}