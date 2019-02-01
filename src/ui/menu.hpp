/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_MENU_
#define _H_MENU_

#include <guisan.hpp>
#include "../context.hpp"
#include "creditswindow.hpp"
#include "settingswindow.hpp"

class Menu : public Context, public gcn::ActionListener {
public:
	Menu(gcn::Container *parent);
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
	gcn::ImageButton btn_newGame;
	gcn::ImageButton btn_credits;
	gcn::ImageButton btn_settings;
	gcn::ImageButton btn_quit;
	gcn::ImageButton btn_back;
	gcn::ImageButton btn_lanGame;
	gcn::ImageButton btn_localGame;
	gcn::ImageButton btn_webGame;

	gcn::Label lbl_version;

	CreditsWindow credits;
	SettingsWindow settings;

	SDL_Texture *backTexture = nullptr;
	SDL_Surface *background = nullptr;

	void addWidgets();
};

#endif // !_H_MENU_
