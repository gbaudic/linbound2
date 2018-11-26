/**
 * \file settings.cpp
 * \brief Settings-related classes
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../settings.hpp" 
#include "settingswindow.hpp"

/**
 * \brief Constructor
 */
SettingsWindow::SettingsWindow() : settings("Settings"),
btn_ok("OK"), btn_cancel("Cancel"),
lbl_music("Music volume"), lbl_effects("Effects volume"),
sl_music(0, MIX_MAX_VOLUME), sl_effects(0, MIX_MAX_VOLUME)
{
	sl_music.setValue(Settings::getInstance()->getMusicVolume());
	sl_effects.setValue(Settings::getInstance()->getEffectsVolume());
	btn_cancel.adjustSize();
	btn_ok.setWidth(btn_cancel.getWidth());
	btn_ok.setHeight(btn_cancel.getHeight()); //just for aesthetics
	btn_ok.setActionEventId("ok");
	btn_ok.addActionListener(this);
	btn_cancel.setActionEventId("cancel");
	btn_cancel.addActionListener(this);
	
	gcn::Color color(0x1f, 0x75, 0xf5, 0);
	settings.setBaseColor(color);
	settings.add(&btn_ok, settings.getWidth() / 2 - 2 - btn_ok.getWidth(), 100);
	settings.add(&btn_cancel, settings.getWidth() / 2 + 2, 100);
	settings.add(&lbl_music, 10, 30);
	settings.add(&lbl_effects, 10, 60);
	settings.add(&sl_music, 60, 30);
	settings.add(&sl_effects, 60, 60);

	settings.setVisible(true);
}

/**
 * \brief Destructor
 */
SettingsWindow::~SettingsWindow() {

}

/**
 * \brief Handle button clicks
 */
void SettingsWindow::action(const gcn::ActionEvent& actionEvent) {
	if(actionEvent.getId() == "cancel") {
		setVisible(false);
	} else if(actionEvent.getId() == "ok") {
		// Save and hide
		Settings *params = Settings::getInstance();
		params->setEffectsVolume((Uint8) sl_effects.getValue());
		params->setMusicVolume((Uint8) sl_music.getValue());
        params->save();
		setVisible(false);
	}
}

/**
 * \brief Shows or hides the settings window
 * \param visible new visibility
 */
void SettingsWindow::setVisible(bool visible) {
	settings.setVisible(visible);
}

