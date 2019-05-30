/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "serverview.hpp"

ServerView::ServerView() : Context(ContextName::ROOM_LIST),
btn_back("Logout"), btn_newRoom("Create room"), btn_goToShop("Item shop"),
btn_addFriend("Add friend"), btn_prevPage("<"), btn_nextPage(">"),
in_addFriend("Add friend", "Enter player id") {


	addWidgets();
}

ServerView::~ServerView() {
	// Cleanup our surfaces
	if (background) {
		SDL_FreeSurface(background);
	}
	if (backTexture) {
		SDL_DestroyTexture(backTexture);
	}
}

void ServerView::action(const gcn::ActionEvent& actionEvent) {

}

void ServerView::addWidgets() {

	int xStep = getWidth() / 5;
	addWidget(&btn_back, xStep - btn_back.getWidth(), getHeight() - 2 * btn_back.getHeight());
	addWidget(&btn_newRoom, 2 *xStep - btn_newRoom.getWidth(), btn_back.getY());
	addWidget(&btn_goToShop, 3 * xStep - btn_goToShop.getWidth(), btn_back.getY());
	addWidget(&btn_addFriend, 4 * xStep - btn_addFriend.getWidth(), btn_back.getY());
}

void ServerView::drawBackground(SDL_Renderer* screen) {

}
