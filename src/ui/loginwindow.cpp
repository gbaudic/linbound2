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
btn_ok("Login"), btn_cancel("Cancel"), lbl_status("")
{
	btn_ok.adjustSize();
	btn_cancel.adjustSize();

	btn_ok.setActionEventId("ok");
	btn_ok.addActionListener(this);
	btn_cancel.setActionEventId("cancel");
	btn_cancel.addActionListener(this);
}

void LoginWindow::action(const gcn::ActionEvent & event)
{
	if (event.getId() == "cancel") {
		setVisible(false);
	}
}

string LoginWindow::getPassword() const
{
	return tf_password.getText();
}

string LoginWindow::getLogin() const
{
	return tf_login.getText();
}
