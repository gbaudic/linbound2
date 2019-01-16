/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
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

void ChatManager::addMessage(string sender, string message) {
	try {
		ChatWindow* w = windows.at(sender);
		w->addMessage(sender, message);
	}
	catch (out_of_range) {
		windows[sender] = new ChatWindow(sender, message);
		windows[sender]->addActionListener(this);
		top->add(windows[sender], top->getWidth() - 20 - windows[sender]->getWidth(), 20);
	}
}

void ChatManager::action(const gcn::ActionEvent & action) {

}
