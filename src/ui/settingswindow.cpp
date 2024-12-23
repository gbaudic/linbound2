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

#include "../settings.hpp" 
#include "settingswindow.hpp"

/**
 * \brief Constructor
 */
SettingsWindow::SettingsWindow() : gcn::Window()
{
	setCaption("Settings");
	setWidth(Settings::getInstance()->getWidth() / 2);
	setHeight(120);
	
	sl_music.setValue(Settings::getInstance()->getMusicVolume());
	sl_music.setWidth(getWidth() / 2);
	sl_music.setHeight(20);
	sl_music.setActionEventId(ACTION_MUSIC);
	sl_music.addActionListener(this);
	
	sl_effects.setValue(Settings::getInstance()->getEffectsVolume());
	sl_effects.setWidth(getWidth() / 2);
	sl_effects.setHeight(20);
	sl_effects.setActionEventId(ACTION_EFFECTS);
	sl_effects.addActionListener(this);
	
	btn_cancel.adjustSize();
	btn_ok.setWidth(btn_cancel.getWidth());
	btn_ok.setHeight(btn_cancel.getHeight()); //just for aesthetics
	btn_ok.setActionEventId(ACTION_OK);
	btn_ok.addActionListener(this);
	btn_cancel.setActionEventId(ACTION_CANCEL);
	btn_cancel.addActionListener(this);
	
	gcn::Color color(0x1f, 0x75, 0xf5);
	setBaseColor(color);
	addWidgets();

	setVisible(false);
}

/** 
 * \copydoc gcn::ActionListener::action(ActionEvent&)
 */
void SettingsWindow::action(const gcn::ActionEvent& actionEvent) {
	if (actionEvent.getId() == ACTION_CANCEL) {
		// Revert values in SDL_Mixer and in GUI
		sl_music.setValue(Settings::getInstance()->getMusicVolume());
		sl_effects.setValue(Settings::getInstance()->getEffectsVolume());
		Mix_Volume(-1, Settings::getInstance()->getEffectsVolume());
		Mix_VolumeMusic(Settings::getInstance()->getMusicVolume());
		setVisible(false);
	} else if (actionEvent.getId() == ACTION_OK) {
		// Save and hide
		Settings *params = Settings::getInstance();
		params->setEffectsVolume(static_cast<Uint8>(sl_effects.getValue()));
		params->setMusicVolume(static_cast<Uint8>(sl_music.getValue()));
        params->save();
		setVisible(false);
	} else if (actionEvent.getId() == ACTION_MUSIC) {
		// Update music volume for immediate user feedback
		Mix_VolumeMusic(static_cast<int>(sl_music.getValue()));
	} else if (actionEvent.getId() == ACTION_EFFECTS) {
		// Update volume for all effects
		Mix_Volume(-1, static_cast<int>(sl_effects.getValue()));
	}
}

void SettingsWindow::addWidgets() {
	add(&btn_ok, getWidth() / 2 - 2 - btn_ok.getWidth(), 70);
	add(&btn_cancel, getWidth() / 2 + 2, 70);
	add(&lbl_music, 20, 10);
	add(&lbl_effects, 20, 40);
	add(&sl_music, lbl_effects.getX() + lbl_effects.getWidth() + 10 * mPadding, 10 - 3);
	add(&sl_effects, lbl_effects.getX() + lbl_effects.getWidth() + 10 * mPadding, 40 - 3);
}


