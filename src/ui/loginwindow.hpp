/**
 * \file loginwindow.hpp
 * \date 12/2018
 * \brief Window overload to get connection details
 * \author G. B.
 * \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_LOGINWINDOW_
#define _H_LOGINWINDOW_

#include <string>
#include <guisan.hpp>
#include <guisan/sdl.hpp>

/**
 * Utility window to get identification details from the user
 */
class LoginWindow final : public gcn::Window, public gcn::ActionListener {

public:
	LoginWindow();
	void action(const gcn::ActionEvent &event) override;
	std::string getPassword() const;
	std::string getLogin() const;
	void onLogin(const int success);

private:
	const std::string ACTION_OK{"ok"};
	const std::string ACTION_CANCEL{"cancel"};

	gcn::Button btn_ok{"Login"};
	gcn::Button btn_cancel{"Cancel"};
	gcn::Label lbl_status{" "};	 //! Communicate info to the user
	gcn::TextField tf_login;
	gcn::TextField tf_password;
	gcn::Label lbl_login{"Login"};
	gcn::Label lbl_password{"Password"};

	void addWidgets();
};

#endif // !_H_LOGINWINDOW_
