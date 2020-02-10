/**
 * \file serverview.hpp
 * \date 17/11/2019
 * \brief UI class for server view, where user can chat and select a game room
 * \author G. B.
 * \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SERVERVIEW_
#define _H_SERVERVIEW_

#include <map>
#include <guisan.hpp>
#include "../context.hpp"
#include "../ui/roombutton.hpp"

/*
 * UI class for server view
 */
class ServerView final : public Context, public gcn::ActionListener {
public:
	explicit ServerView(ContextName previous);
	~ServerView();

	void drawBackground(SDL_Renderer* screen) override;
	void drawOverlay(SDL_Renderer* screen) override {
		// No overlays in ServerView
	};
	void processEvent(SDL_Event& event) override {
		// No specific handling to be done here, GUI handles everything
	};
	// Inherited via ActionListener
	void action(const gcn::ActionEvent& actionEvent) override;

private:
	gcn::Button btn_back{ "Logout" };
	gcn::Button btn_newRoom{ "Create room" };
	gcn::Button btn_goToShop{ "Item shop" };
	gcn::Button btn_addFriend{ "Add friend" };

	gcn::Button btn_prevPage{ "<" };
	gcn::Button btn_nextPage{ ">" };

	gcn::Label lbl_playerName;
	gcn::Label lbl_playerTeam;
	gcn::Label lbl_playerPoints;
	gcn::Label lbl_playerMoney;

	gcn::Label lbl_pages;

	gcn::TextBox tb_chat;
	gcn::ScrollArea sa_chat;
	gcn::TextField tf_message;

	gcn::InputBox in_addFriend{ "Add friend", "Enter player id" };

	ContextName origin;

	SDL_Texture* backTexture = nullptr;
	SDL_Surface* background = nullptr;
	SDL_Texture* playerLvlTexture = nullptr;

	void addWidgets();

	void receiveChatMessage(const std::string& user, const std::string& message);
	void playerStateChanged();
	void roomChanged();
};

#endif // !_H_SERVERVIEW_
