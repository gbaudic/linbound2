/**
 * A subwindow to display the credits directly from the menu
 * Data will be fetched from the existing AUTHORS file, if any
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_CREDITSWINDOW_
#define _H_CREDITSWINDOW_

#include <guisan.hpp>
#include <guisan/sdl.hpp>

class CreditsWindow : public gcn::ActionListener {
public:
	CreditsWindow();
	void setVisible(bool visible);
	void action(const gcn::ActionEvent& actionEvent);

private:
	gcn::Window creditsWindow;
	gcn::TextBox tb_text;
	gcn::ScrollArea sa_scroll;
	gcn::Button btn_close;
};

#endif // !_H_CREDITSWINDOW_
