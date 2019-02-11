/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */
/**
 * \file loginwindow.cpp
 * \date 12/2018
 * \author G. Baudic
 */

#include "loginwindow.hpp"
using namespace std;

/**
 * Constructor
 */
LoginWindow::LoginWindow() : gcn::Window("Login"),
btn_ok("Login"), btn_cancel("Cancel"), lbl_status(" "),
lbl_login("Login"), lbl_password("Password")
{
	setWidth(250);
	setHeight(120);
	setVisible(false);

	btn_ok.adjustSize();
	btn_cancel.adjustSize();
	btn_ok.setWidth(btn_ok.getWidth() > btn_cancel.getWidth() ? btn_ok.getWidth() : btn_cancel.getWidth());
	btn_cancel.setWidth(btn_ok.getWidth());
	lbl_login.adjustSize();
	lbl_password.adjustSize();
	tf_login.setWidth(90);
	tf_password.setWidth(90);

	btn_ok.setActionEventId("ok");
	btn_ok.addActionListener(this);
	btn_cancel.setActionEventId("cancel");
	btn_cancel.addActionListener(this);

	addWidgets();
}

void LoginWindow::action(const gcn::ActionEvent & event) {
	if (event.getId() == "cancel") {
		setVisible(false);
	}

	if (event.getId() == "ok") {
		// Validation logic
		if(tf_login.getText().size() < 2) {
			lbl_status.setCaption("Invalid login.");
            lbl_status.adjustSize();
			return;
		}
		
		btn_ok.setVisible(false);
		btn_cancel.setVisible(false);
		tf_login.setEnabled(false);
		tf_password.setEnabled(false);
		lbl_status.setCaption("Logging in...");
        lbl_status.adjustSize();
		generateAction();
	}
}

/**
 * Getter for password value
 * \return password (may be empty) 
 */
string LoginWindow::getPassword() const {
	return tf_password.getText();
}

/**
 * Getter for login value
 * \return user login
 */
string LoginWindow::getLogin() const {
	return tf_login.getText();
}

/**
 * Receive result of the login action triggered by the user
 * \param success an error code. 0=success, 1=password, 2=login, 3=level, 4=full, 5=unreachable
 */
void LoginWindow::onLogin(const int success) {
	btn_ok.setVisible(true);
	btn_cancel.setVisible(true);
	tf_login.setEnabled(true);
	tf_password.setEnabled(true);
    
    switch(success) {
        case 0:
            // Hide and prepare for reuse
            setVisible(false);
            tf_login.clear();
            tf_password.clear();
            break;
        case 1:
            // Wrong password
            lbl_status.setCaption("Wrong password. Please retry.");
            break;
        case 2:
            // Unknown login
            lbl_status.setCaption("This login does not exist.");
            break;
        case 3:
            // Wrong level
            lbl_status.setCaption("Level outside this server range.");
            break;
        case 4:
            // Server full
            lbl_status.setCaption("Sorry, the server is already full.");
            break;
        case 5:
            // Connection timed out
            lbl_status.setCaption("Connection timed out.");
            break;
        default:
            break;
    }
    lbl_status.adjustSize();
}

/*
 * Helper function to actually add the widgets and please Sonar
 */
void LoginWindow::addWidgets() {
	add(&lbl_login, getPadding(), getPadding());
	add(&lbl_password, getPadding(), 2 * getPadding() + lbl_login.getHeight());
	add(&lbl_status, getPadding(), lbl_password.getY() + getPadding() + lbl_password.getHeight());

	int tfX = lbl_login.getWidth() > lbl_password.getWidth() ? lbl_login.getWidth() : lbl_password.getWidth();
	add(&tf_login, 2 * getPadding() + tfX, getPadding());
	add(&tf_password, 2 * getPadding() + tfX, lbl_password.getY());

	add(&btn_ok, 3 * getPadding() + tfX + tf_login.getWidth(), getPadding());
	add(&btn_cancel, 3 * getPadding() + tfX + tf_login.getWidth(), tf_password.getY());
}
