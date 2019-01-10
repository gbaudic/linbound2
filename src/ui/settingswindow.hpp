/**
 * \file settingswindow.hpp
 * \brief Subwindow to set a few parameters
 * \version 0.1a
 * \author G. B.
 * \date 29/10/2016
 */

/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_SETTINGSWINDOW_
#define _H_SETTINGSWINDOW_

#include <guisan.hpp>
#include <guisan/sdl.hpp>

/**
 *  \brief Subwindow to control settings from main menu
 */
class SettingsWindow final : public gcn::Window, public gcn::ActionListener {
public:
	SettingsWindow();
	~SettingsWindow();
	void action(const gcn::ActionEvent& actionEvent);
	
private:
	gcn::Button btn_ok;
	gcn::Button btn_cancel;
	gcn::Label lbl_music;
	gcn::Label lbl_effects;
	gcn::Slider sl_music;
	gcn::Slider sl_effects;
	
};

#endif // _H_SETTINGSWINDOW_