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
using namespace std;

CreditsWindow::CreditsWindow() : creditsWindow(), tb_text(), sa_scroll(), btn_close("Close") {

	creditsWindow.setCaption("Credits");
	creditsWindow.setVisible(false); //we will show it on demand afterwards
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
	//TODO: check if we managed to get some text
	if (tb_text.getNumberOfRows() == 0) {
		tb_text.addRow("Error while trying to open AUTHORS credits file. ");
	}

	input.close();
	
	btn_close.setActionEventId("close");
	btn_close.addActionListener(this);

	//Add widgets to window
	creditsWindow.add(&sa_scroll, 2, 20);
	creditsWindow.add(&btn_close, 100, 200); //TODO: adjust coords
}

/**
 * Change visibility of the internal gcn::window
 */
void CreditsWindow::setVisible(bool visible) {
	creditsWindow.setVisible(visible);
}

void CreditsWindow::action(const gcn::ActionEvent& actionEvent) {
	if(actionEvent.getId() == "close") {
		setVisible(false);
	}
}
