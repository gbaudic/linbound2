/**
 * \file chatwindow.hpp
 * \brief A subwindow to conduct a chat with one of your in-game friends
 * \author G. B.
 * \version 0.1a
 * \date 07/01/2019
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

/**
 * A subwindow to conduct a chat with one of your in-game friends
 */
class ChatWindow final : public gcn::Window, public gcn::ActionListener {
public:
	explicit ChatWindow(const std::string &friendName);
	ChatWindow(const std::string &friendName, const std::string &message);
	void addMessage(const std::string &author, const std::string &message);
	void action(const gcn::ActionEvent &actionEvent) override;
	std::string getRecipientName() const;
	std::string getMessage() const;
	static void setMyName(const std::string &myName);

private:
	const std::string ACTION_SEND{ "send" };
	const std::string ACTION_CLOSE{ "close" };

	gcn::TextField tf_msg;
	gcn::ScrollArea sa_scroll;
	gcn::TextBox tb_chat;
	gcn::Button btn_close{ "x" };
	gcn::Button btn_send{ "Send" };
	std::string recipient; //! necessary if caption displays other infos
	static std::string sender; //! name of the player
	std::string messageSent;
	
	void addWidgets();
};

#endif // !_H_CHATWINDOW_

