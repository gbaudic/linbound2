/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "chatwindow.hpp"
using namespace std;

LB_ChatWindow::LB_ChatWindow(string friendName) : tf_msg(), sa_scroll(),
tb_chat(), btn_close("x"), btn_send("Send"), recipient(friendName) {
	setCaption(friendName);
	setWidth(200);
	setHeight(300);
	gcn::Color color(0x1f, 0x75, 0xf5, 0);
	gcn::Color bckColor(0, 0, 0x66, 0);
	gcn::Color textColor(0xff, 0xff, 0xff, 0);
	setBaseColor(color);

	tb_chat.setEditable(false);
	tb_chat.setBackgroundColor(bckColor);
	tb_chat.setForegroundColor(textColor);
	sa_scroll.setContent(&tb_chat);
	sa_scroll.setHorizontalScrollPolicy(gcn::ScrollArea::SHOW_NEVER);
	sa_scroll.setWidth(190);
	sa_scroll.setHeight(250);

	btn_close.adjustSize();
	btn_close.setActionEventId("close");
	btn_close.addActionListener(this);
	btn_send.adjustSize(); //precaution for i18n
	btn_send.setActionEventId("send");
	btn_send.addActionListener(this);

	tf_msg.setWidth(200 - 3 * 2 - btn_send.getWidth()); //avoid overlap between textfield and button
	tf_msg.setBackgroundColor(bckColor);
	tf_msg.setForegroundColor(textColor);
	tf_msg.addActionListener(this);

	//Add widgets
	add(&btn_close, 200 - 2 - btn_close.getWidth(), 2);
	add(&sa_scroll, 2, 20);
	add(&tf_msg, 2, 20 + 250 + 2);
	add(&btn_send, 200 - 2 - btn_send.getWidth(), 20 + 250 + 2);
}

/**
 *  2-parameter constructor to start new conversation from incoming message
 */
LB_ChatWindow::LB_ChatWindow(string friendName, string message) : LB_ChatWindow(friendName) {
	this->addMessage(friendName, message);
}

void LB_ChatWindow::action(const gcn::ActionEvent &actionEvent) {
	if (actionEvent.getId() == "close") {
		setVisible(false);
	}
	else if (actionEvent.getId() == "send" || actionEvent.getSource() == &tf_msg) {
		string message = tf_msg.getText();
		if (!message.empty()) {
			//TODO: forward message to the connection mgr
			tf_msg.setText("");
		}
	}
}

/**
 * Add a new message at the end of the current conversation
 * \param author writer name
 * \param message text message
 */
void LB_ChatWindow::addMessage(std::string author, std::string message) {
	tb_chat.addRow(author + "] " + message);
	setVisible(true); //put the window back in foreground if necessary
}

/**
 *  Get the name of the friend you are chatting with
 *  When a new message is received, this method will come in handy to know if this is part
 *  of an ongoing conversation (existing window) or if it is a new one (constructor call necessary)
 *  \return the friend name, as a std::string
 */
string const LB_ChatWindow::getRecipientName() {
	return recipient;
}
