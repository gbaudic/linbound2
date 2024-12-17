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

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

/**
 * \brief Subwindow to control settings from main menu
 */
class SettingsWindow final : public gcn::Window, public gcn::ActionListener {
public:
	SettingsWindow();
	void action(const gcn::ActionEvent& actionEvent) override;
	
private:
    const std::string ACTION_OK{ "ok" };
    const std::string ACTION_CANCEL{ "cancel" };
    const std::string ACTION_MUSIC{ "music" };
    const std::string ACTION_EFFECTS{ "effects" };

    gcn::Button btn_ok{ "OK" };
    gcn::Button btn_cancel{ "Cancel" };
    gcn::Label lbl_music{ "Music volume" };
    gcn::Label lbl_effects{ "Effects volume" };
    gcn::Slider sl_music{ 0, MIX_MAX_VOLUME };
    gcn::Slider sl_effects{ 0, MIX_MAX_VOLUME };
	
	void addWidgets();
};

#endif // _H_SETTINGSWINDOW_