/**
 * \file creditswindow.cpp
 * \brief A subwindow so you know who to send pizza to if you like the software
 * \author G. B.
 * \version 0.1a
 * \date 07/01/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "creditswindow.hpp"
#include "../settings.hpp"
using namespace std;

/**
 * Constructor
 */
CreditsWindow::CreditsWindow() { 
	setCaption("Credits");
	setWidth(Settings::getInstance()->getWidth() / 2);
	setHeight(Settings::getInstance()->getHeight() / 2);
	setVisible(false); //we will show it on demand afterwards
	btn_close.adjustSize();
	tb_text.setEditable(false);

	sa_scroll.setContent(&tb_text);
	sa_scroll.setWidth(getWidth() - 4 * mPadding - 2 * getBorderSize());
	sa_scroll.setHeight(getHeight() - 6*mPadding - 2*getBorderSize() - (int)getTitleBarHeight() - btn_close.getHeight());

	//Add text to tb_text	
	// Data is fetched from the AUTHORS file, if found
	ifstream input("AUTHORS", ios::in);
	string line;
	bool hasText = false;

	if (input.is_open()) {
		while (!input.eof()) {
			getline(input, line);
			tb_text.addRow(line);
			hasText = true;
		}
	}
	// Check if we managed to get some text
	if (!hasText) {
		tb_text.addRow("Error while trying to open AUTHORS credits file. ");
	}

	input.close();
	
	btn_close.setActionEventId("close");
	btn_close.addActionListener(this);

	//Add widgets to window
	addWidgets();
}

void CreditsWindow::action(const gcn::ActionEvent& actionEvent) {
	if(actionEvent.getId() == "close") {
		setVisible(false);
	}
}

/**
 * Add the widgets to the window
 */
void CreditsWindow::addWidgets() {
	add(&sa_scroll, mPadding, mPadding);
	add(&btn_close, getWidth() - 2 * getBorderSize() - 2 * mPadding - btn_close.getWidth(), 
		getHeight() - (int)getTitleBarHeight() - 2 * getBorderSize() - 2 * mPadding - btn_close.getHeight());
}
