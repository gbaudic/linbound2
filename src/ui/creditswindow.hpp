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

#ifndef _H_CREDITSWINDOW_
#define _H_CREDITSWINDOW_

#include <guisan.hpp>
#include <guisan/sdl.hpp>

class CreditsWindow final : public gcn::Window, public gcn::ActionListener {
public:
	CreditsWindow();
	void action(const gcn::ActionEvent& actionEvent) override;

private:
	gcn::TextBox tb_text;
	gcn::ScrollArea sa_scroll;
	gcn::Button btn_close;

	void addWidgets();
};

#endif // !_H_CREDITSWINDOW_
