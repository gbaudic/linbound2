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
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL_image.h>
#include "menu.hpp"
#include "../utils.hpp"
#include "../config.hpp"
using namespace std;

/**
 * Constructor
 * @param p main Container for the GUI
 */
Menu::Menu() : Context(ContextName::MAIN_MENU),
btn_newGame(RESOURCE_PREFIX + "/menu/newgame.png"),
btn_credits(RESOURCE_PREFIX + "/menu/credits.png"), 
btn_settings(RESOURCE_PREFIX + "/menu/settings.png"),
btn_quit(RESOURCE_PREFIX + "/menu/quit.png"),
btn_back(RESOURCE_PREFIX + "/menu/back.png"),
btn_lanGame(RESOURCE_PREFIX + "/menu/langame.png"),
btn_localGame(RESOURCE_PREFIX + "/menu/localgame.png"),
btn_webGame(RESOURCE_PREFIX + "/menu/webgame.png")
{
	lbl_version.setCaption("Version " + linbound::getVersionString());
	lbl_version.adjustSize();

	btn_newGame.setActionEventId("new");
	btn_newGame.addActionListener(this);
	btn_newGame.adjustSize();
	btn_credits.setActionEventId("credits");
	btn_settings.setActionEventId("settings");
	btn_credits.addActionListener(this);
	btn_credits.adjustSize();
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

void Menu::action(const gcn::ActionEvent & actionEvent)
{
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
void Menu::moveToGame(bool move)
{
	btn_quit.setVisible(!move);
	btn_credits.setVisible(!move);
	btn_settings.setVisible(!move);
	btn_newGame.setVisible(!move);

	btn_back.setVisible(move);
	btn_lanGame.setVisible(move);
	btn_localGame.setVisible(move);
	btn_webGame.setVisible(move);
}

void Menu::drawBackground(SDL_Renderer * screen) {
	if (!backTexture) {
		backTexture = SDL_CreateTextureFromSurface(screen, background);
	}
	SDL_RenderCopy(screen, backTexture, NULL, NULL);
}

void Menu::addWidgets() {
	addWidget(&btn_newGame, 70, 225);
	addWidget(&btn_settings, 50 + 2 * 20 + 150, 225);
	addWidget(&btn_credits, 50 + 3 * 20 + 2 * 150, 225);
	addWidget(&btn_quit, 50 + 4 * 20 + 3 * 150, 225);

	addWidget(&btn_back, 70, 225);
	addWidget(&btn_localGame, 50 + 2 * 20 + 150, 225);
	addWidget(&btn_lanGame, 50 + 3 * 20 + 2 * 150, 225);
	addWidget(&btn_webGame, 50 + 4 * 20 + 3 * 150, 225);

	addWidget(&lbl_version, 20, background->h - 40);
}
