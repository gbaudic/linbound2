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

CreditsWindow::CreditsWindow() : tb_text(), sa_scroll(), btn_close("Close") {

	setCaption("Credits");
	setWidth(Settings::getInstance()->getWidth() / 2);
	setHeight(Settings::getInstance()->getHeight() / 2);
	setVisible(false); //we will show it on demand afterwards
	btn_close.adjustSize();
	tb_text.setEditable(false);

	sa_scroll.setContent(&tb_text);

	//Add text to tb_text	
	ifstream input("AUTHORS", ios::in);
	string line;

	while (getline(input, line) && !input.eof()) {
		if (!line.empty()) {
			tb_text.addRow(line);
		}
	}
	// Check if we managed to get some text
	if (tb_text.getNumberOfRows() == 0) {
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

void CreditsWindow::addWidgets() {
	add(&sa_scroll, 2, 20);
	add(&btn_close, getWidth() - 2 * getBorderSize() - 2 * mPadding - btn_close.getWidth(), 
		getHeight() - (int)getTitleBarHeight() - 2 * getBorderSize() - 2 * mPadding - btn_close.getHeight());
}
