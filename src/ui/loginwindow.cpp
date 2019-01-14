/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "loginwindow.hpp"
using namespace std;

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

void LoginWindow::action(const gcn::ActionEvent & event)
{
	if (event.getId() == "cancel") {
		setVisible(false);
	}

	if (event.getId() == "ok") {
		btn_ok.setVisible(false);
		btn_cancel.setVisible(false);
		tf_login.setEnabled(false);
		tf_password.setEnabled(false);
		lbl_status.setCaption("Logging in...");
		generateAction();
	}
}

/**
  Getter for password value
 */
string LoginWindow::getPassword() const
{
	return tf_password.getText();
}

/**
  Getter for login value
 */
string LoginWindow::getLogin() const
{
	return tf_login.getText();
}

void LoginWindow::onLogin(bool success)
{
	btn_ok.setVisible(true);
	btn_cancel.setVisible(true);
	tf_login.setEnabled(true);
	tf_password.setEnabled(true);

	if (success) {
		// Hide and prepare for reuse
		setVisible(false);
		tf_login.clear();
		tf_password.clear();
	}
	else {
		lbl_status.setCaption("Login failed. Please retry.");
	}
}

void LoginWindow::addWidgets()
{
	add(&lbl_login, getPadding(), getPadding());
	add(&lbl_password, getPadding(), 2 * getPadding() + lbl_login.getHeight());
	add(&lbl_status, getPadding(), lbl_password.getY() + getPadding() + lbl_password.getHeight());

	int tfX = lbl_login.getWidth() > lbl_password.getWidth() ? lbl_login.getWidth() : lbl_password.getWidth();
	add(&tf_login, 2 * getPadding() + tfX, getPadding());
	add(&tf_password, 2 * getPadding() + tfX, lbl_password.getY());

	add(&btn_ok, 3 * getPadding() + tfX + tf_login.getWidth(), getPadding());
	add(&btn_cancel, 3 * getPadding() + tfX + tf_login.getWidth(), tf_password.getY());
}
