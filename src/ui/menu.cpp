/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "menu.hpp"
#include "../utils.hpp"
#include "../config.hpp"
using namespace std;

Menu::Menu() : btn_newGame(RESOURCE_PREFIX + "/menu/newgame.png"),
btn_credits(RESOURCE_PREFIX + "/menu/credits.png"), 
btn_settings(RESOURCE_PREFIX + "/menu/settings.png"),
btn_quit(RESOURCE_PREFIX + "/menu/quit.png"),
btn_back(RESOURCE_PREFIX + "/menu/back.png"),
btn_lanGame(RESOURCE_PREFIX + "/menu/langame.png"),
btn_localGame(RESOURCE_PREFIX + "/menu/localgame.png"),
btn_webGame(RESOURCE_PREFIX + "/menu/webgame.png")
{
	lbl_version.setCaption("Version " + linbound::getVersionString());

	btn_newGame.setActionEventId("new");
	btn_newGame.addActionListener(this);
	btn_credits.setActionEventId("credits");
	btn_settings.setActionEventId("settings");
	btn_credits.addActionListener(this);
	btn_settings.addActionListener(this);
	btn_back.setActionEventId("back");
	btn_back.addActionListener(this);
	btn_quit.setActionEventId("quit");
	btn_quit.addActionListener(this);

	btn_back.setVisible(false);
	btn_lanGame.setVisible(false);
	btn_localGame.setVisible(false);
	btn_webGame.setVisible(false);

	linbound::addCenteredWidget(&credits, this);
	linbound::addCenteredWidget(&settings, this);

	addWidgets();
}

void Menu::action(const gcn::ActionEvent & actionEvent)
{
	if (actionEvent.getId() == "credits") {
		credits.setVisible(true);
	}

	if (actionEvent.getId() == "settings") {
		settings.setVisible(true);
	}

	if (actionEvent.getId() == "back") {
		moveToGame(false);
	}
	else if (actionEvent.getId() == "new") {
		moveToGame(true);
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

void Menu::addWidgets() {

}
