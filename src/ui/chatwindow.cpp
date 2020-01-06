/**
 * \file chatwindow.cpp
 * \brief A subwindow to conduct a chat with one of your in-game friends
 * \author G. B.
 * \version 0.1a
 * \date 07/01/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "chatwindow.hpp"
using namespace std;

std::string ChatWindow::sender; // init

/**
  Constructor
  \param friendName username of the friend
*/
ChatWindow::ChatWindow(const string &friendName) : 
	btn_close("x"), btn_send("Send"), recipient(friendName) {
	setCaption(friendName);
	setWidth(200);
	setHeight(300);
	gcn::Color color(0x1f, 0x75, 0xf5, 0);
	gcn::Color bckColor(0, 0, 0x66, 0);
	gcn::Color textColor(0xff, 0xff, 0xff, 0);
	setBaseColor(color);
	setActionEventId(friendName);

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

	tf_msg.setWidth(getWidth() - 3 * getPadding() - btn_send.getWidth()); //avoid overlap between textfield and button
	tf_msg.setBackgroundColor(bckColor);
	tf_msg.setForegroundColor(textColor);
	tf_msg.addActionListener(this);

	//Add widgets
	addWidgets();
}

/**
 *  2-parameter constructor to start new conversation from incoming message
 * \param friendName name of the friend
 * \param message message to show
 */
ChatWindow::ChatWindow(const string &friendName, const string &message) : ChatWindow(friendName) {
	addMessage(friendName, message);
}

/**
 * Actually add the widgets to the container
 * Put outside the constructor to please Sonar
 */
void ChatWindow::addWidgets() {
	add(&sa_scroll, getPadding(), getPadding());
	add(&btn_close, getWidth() - getPadding() - btn_close.getWidth(), getPadding());
	add(&tf_msg, getPadding(), sa_scroll.getHeight() + 2 * getPadding());
	add(&btn_send, getWidth() - getPadding() - btn_send.getWidth(), sa_scroll.getHeight() + 2 * getPadding());
}

void ChatWindow::action(const gcn::ActionEvent &actionEvent) {
	if (actionEvent.getId() == "close") {
		setVisible(false);
	}
	else if (actionEvent.getId() == "send" || actionEvent.getSource() == &tf_msg) {
		messageSent = tf_msg.getText();
		if (!messageSent.empty()) {
			addMessage(sender, messageSent);
			generateAction();
			tf_msg.setText("");
		}
	}
}

/**
 * Add a new message at the end of the current conversation
 * \param author writer name
 * \param message text message
 */
void ChatWindow::addMessage(const std::string &author, const std::string &message) {
	tb_chat.addRow(author + "] " + message);
	setVisible(true); //put the window back in foreground if necessary
}

/**
 *  Get the name of the friend you are chatting with
 *  When a new message is received, this method will come in handy to know if this is part
 *  of an ongoing conversation (existing window) or if it is a new one (constructor call necessary)
 *  \return the friend name, as a std::string
 */
string const ChatWindow::getRecipientName() {
	return recipient;
}

string const ChatWindow::getMessage() {
	return messageSent;
}

/**
 * Set the name of the player currently connected
 * It is static because there is only one user connected...
 * \param myName player name
 */
void ChatWindow::setMyName(const string &myName) {
	sender = myName;
}
