/**
 * \file settingswindow.cpp
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../settings.hpp" 
#include "settingswindow.hpp"

/**
 * \brief Constructor
 */
SettingsWindow::SettingsWindow() : 
btn_ok("OK"), btn_cancel("Cancel"),
lbl_music("Music volume"), lbl_effects("Effects volume"),
sl_music(0, MIX_MAX_VOLUME), sl_effects(0, MIX_MAX_VOLUME)
{
	setCaption("Settings");
	setWidth(Settings::getInstance()->getWidth() / 2);
	setHeight(Settings::getInstance()->getHeight() / 2);
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
	setBaseColor(color);
	addWidgets();

	setVisible(false);
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

void SettingsWindow::addWidgets() {
	add(&btn_ok, getWidth() / 2 - 2 - btn_ok.getWidth(), 100);
	add(&btn_cancel, getWidth() / 2 + 2, 100);
	add(&lbl_music, 10, 30);
	add(&lbl_effects, 10, 60);
	add(&sl_music, 60, 30);
	add(&sl_effects, 60, 60);
}


