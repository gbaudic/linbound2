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
#include "creditswindow.hpp"
#include "settingswindow.hpp"

class Menu : public gcn::Container, public gcn::ActionListener {
public:
	Menu();
	void action(const gcn::ActionEvent &actionEvent);

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
};

#endif // !_H_MENU_
