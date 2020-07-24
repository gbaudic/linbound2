/**
 *  \file menu.hpp
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

#ifndef _H_MENU_
#define _H_MENU_

#include <guisan.hpp>
#include "../context.hpp"
#include "../config.hpp"
#include "../ui/creditswindow.hpp"
#include "../ui/settingswindow.hpp"

class Menu : public Context, public gcn::ActionListener {
public:
	Menu();
	virtual ~Menu();
	void action(const gcn::ActionEvent &actionEvent) override;
	void moveToGame(bool move);

	virtual void drawBackground(SDL_Renderer *screen) override;
	virtual void drawOverlay(SDL_Renderer *screen) override {
		// There will never be any overlays in Menu
	};

	virtual void processEvent(SDL_Event &event) override {
		// No specific handling to be done here, GUI handles everything
	};

private:
	gcn::ImageButton btn_newGame{ RESOURCE_PREFIX + "/menu/newgame.png" };
	gcn::ImageButton btn_credits{ RESOURCE_PREFIX + "/menu/credits.png" };
	gcn::ImageButton btn_settings{ RESOURCE_PREFIX + "/menu/settings.png" };
	gcn::ImageButton btn_quit{ RESOURCE_PREFIX + "/menu/quit.png" };
	gcn::ImageButton btn_back{ RESOURCE_PREFIX + "/menu/back.png" };
	gcn::ImageButton btn_lanGame{ RESOURCE_PREFIX + "/menu/langame.png" };
	gcn::ImageButton btn_localGame{ RESOURCE_PREFIX + "/menu/localgame.png" };
	gcn::ImageButton btn_webGame{ RESOURCE_PREFIX + "/menu/webgame.png" };
	gcn::Label lbl1{ "New game" };
	gcn::Label lbl2{ "Settings" };
	gcn::Label lbl3{ "Credits" };
	gcn::Label lbl4{ "Quit" };

	gcn::Label lbl_version;

	CreditsWindow credits;
	SettingsWindow settings;

	SDL_Texture *backTexture = nullptr;
	SDL_Surface *background = nullptr;

	void addWidgets();
};

#endif // !_H_MENU_
