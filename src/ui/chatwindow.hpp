/**
 * A subwindow to conduct a chat with one of your in-game friends
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_CHATWINDOW_
#define _H_CHATWINDOW_

#include <SDL2/SDL.h>
#include <string>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

class LB_ChatWindow final : public gcn::Window, public gcn::ActionListener {
public:
	explicit LB_ChatWindow(std::string friendName);
	LB_ChatWindow(std::string friendName, std::string message);
	void addMessage(std::string author, std::string message);
	void action(const gcn::ActionEvent &actionEvent);
	std::string const getRecipientName();

private:
	gcn::TextField tf_msg;
	gcn::ScrollArea sa_scroll;
	gcn::TextBox tb_chat;
	gcn::Button btn_close;
	gcn::Button btn_send;
	std::string recipient; //! necessary if caption displays other infos
	// TODO: reference to the chat manager
};

#endif // !_H_CHATWINDOW_

