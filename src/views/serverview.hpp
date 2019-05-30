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

class ServerView final : public Context, public gcn::ActionListener {
public:
	ServerView();
	virtual ~ServerView();

	virtual void drawBackground(SDL_Renderer* screen) override;
	virtual void drawOverlay(SDL_Renderer* screen) override {
		// No overlays in ServerView
	};
	virtual void processEvent(SDL_Event& event) override {
		// No specific handling to be done here, GUI handles everything
	};
	// Inherited via ActionListener
	void action(const gcn::ActionEvent& actionEvent) override;

private:
	gcn::Button btn_back;
	gcn::Button btn_newRoom;
	gcn::Button btn_goToShop;
	gcn::Button btn_addFriend;

	gcn::Button btn_prevPage;
	gcn::Button btn_nextPage;

	gcn::Label lbl_playerName;
	gcn::Label lbl_playerTeam;
	gcn::Label lbl_playerPoints;
	gcn::Label lbl_playerMoney;

	gcn::Label lbl_pages;

	gcn::TextBox tb_chat;
	gcn::ScrollArea sa_chat;
	gcn::TextField tf_message;

	gcn::InputBox in_addFriend;

	SDL_Texture* backTexture = nullptr;
	SDL_Surface* background = nullptr;
	SDL_Texture* playerLvlTexture = nullptr;

	void addWidgets();
};

#endif // !_H_SERVERVIEW_
