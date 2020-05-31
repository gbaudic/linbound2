/**
 *  \file menu.cpp
 *  \brief Main menu, allows to select mode and tweak options
 *  \author G. B.
 *  \date 09/01/2019
 *  \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL_image.h>
#include "menu.hpp"
#include "../utils.hpp"
using namespace std;

/**
 * Constructor
 */
Menu::Menu() : Context(ContextName::MAIN_MENU) {
	lbl_version.setCaption("Version " + linbound::getVersionString());
	lbl_version.adjustSize();

	btn_newGame.setActionEventId("new");
	btn_newGame.addActionListener(this);
	btn_newGame.adjustSize();
	btn_credits.setActionEventId("credits");
	btn_credits.addActionListener(this);
	btn_credits.adjustSize();
	btn_settings.setActionEventId("settings");
	btn_settings.addActionListener(this);
	btn_settings.adjustSize();
	btn_back.setActionEventId("back");
	btn_back.addActionListener(this);
	btn_back.adjustSize();
	btn_quit.setActionEventId("quit");
	btn_quit.addActionListener(this);
	btn_quit.adjustSize();

	btn_back.setVisible(false);
	btn_back.adjustSize();
	btn_lanGame.setVisible(false);
	btn_lanGame.adjustSize();
	btn_lanGame.setActionEventId("lan");
	btn_lanGame.addActionListener(this);
	btn_localGame.setVisible(false);
	btn_localGame.adjustSize();
	btn_localGame.setActionEventId("local");
	btn_localGame.addActionListener(this);
	btn_webGame.setVisible(false);
	btn_webGame.adjustSize();
	btn_webGame.setActionEventId("web");
	btn_webGame.addActionListener(this);

	lbl1.setAlignment(gcn::Graphics::CENTER);
	lbl2.setAlignment(gcn::Graphics::CENTER);
	lbl3.setAlignment(gcn::Graphics::CENTER);
	lbl4.setAlignment(gcn::Graphics::CENTER);
	lbl1.setWidth(150);
	lbl2.setWidth(150);
	lbl3.setWidth(150);
	lbl4.setWidth(150);
	lbl1.setHeight(15);
	lbl2.setHeight(15);
	lbl3.setHeight(15);
	lbl4.setHeight(15);

	string backgroundPath = RESOURCE_PREFIX + "/menu/LB_menu.png";
	background = IMG_Load(backgroundPath.c_str());

	addWidgets();

	addCenteredWidget(&credits);
	addCenteredWidget(&settings);

	setNextContext(ContextName::MAIN_MENU);
}

Menu::~Menu() {
	// Cleanup our surfaces
	if (background) {
		SDL_FreeSurface(background);
	}
	if (backTexture) {
		SDL_DestroyTexture(backTexture);
	}
}

void Menu::action(const gcn::ActionEvent & actionEvent) {
	if (actionEvent.getId() == "credits") {
		credits.setVisible(true);
	}

	if (actionEvent.getId() == "settings") {
		settings.setVisible(true);
	}

	if (actionEvent.getId() == "quit") {
		SDL_Event exit;
		exit.type = SDL_QUIT;
		SDL_PushEvent(&exit);
	}

	if (actionEvent.getId() == "back") {
		moveToGame(false);
	}
	else if (actionEvent.getId() == "new") {
		moveToGame(true);
	}
	else if (actionEvent.getId() == "lan") {
		setNextContext(ContextName::SERVER_LIST_LAN);
	} 
	else if (actionEvent.getId() == "web") {
		setNextContext(ContextName::SERVER_LIST_WEB);
	}
	else if (actionEvent.getId() == "local") {
		setNextContext(ContextName::ROOM_LOBBY_LOCAL);
	}
}

/**
  \brief Toggle visibility of buttons between the two modes
  \param move true to show game choice buttons, false to show main menu
*/
void Menu::moveToGame(bool move) {
	btn_quit.setVisible(!move);
	btn_credits.setVisible(!move);
	btn_settings.setVisible(!move);
	btn_newGame.setVisible(!move);

	btn_back.setVisible(move);
	btn_lanGame.setVisible(move);
	btn_localGame.setVisible(move);
	btn_webGame.setVisible(move);

	lbl1.setCaption(move ? "Back" : "New game");
	lbl2.setCaption(move ? "LAN game" : "Settings");
	lbl3.setCaption(move ? "Local game" : "Credits");
	lbl4.setCaption(move ? "Web game" : "Quit");
}

/**
 * \brief Draw the background image
 * \param screen renderer to use
 */
void Menu::drawBackground(SDL_Renderer * screen) {
	if (!backTexture) {
		backTexture = SDL_CreateTextureFromSurface(screen, background);
	}
	SDL_RenderCopy(screen, backTexture, NULL, NULL);
}

/**
 * \brief Add the widgets to the container
 */
void Menu::addWidgets() {
	addWidget(&btn_newGame, 50 + 20, 225);
	addWidget(&btn_settings, 50 + 2 * 20 + 150, 225);
	addWidget(&btn_credits, 50 + 3 * 20 + 2 * 150, 225);
	addWidget(&btn_quit, 50 + 4 * 20 + 3 * 150, 225);

	addWidget(&btn_back, 50 + 20, 225);
	addWidget(&btn_localGame, 50 + 2 * 20 + 150, 225);
	addWidget(&btn_lanGame, 50 + 3 * 20 + 2 * 150, 225);
	addWidget(&btn_webGame, 50 + 4 * 20 + 3 * 150, 225);

	int captions_y = 225 + 20 + btn_newGame.getHeight();
	addWidget(&lbl1, btn_newGame.getX(), captions_y);
	addWidget(&lbl2, btn_settings.getX(), captions_y);
	addWidget(&lbl3, btn_credits.getX(), captions_y);
	addWidget(&lbl4, btn_quit.getX(), captions_y);

	addWidget(&lbl_version, 20, background->h - 40);
}
