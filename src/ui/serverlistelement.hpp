/**
 * \file serverlistelement.hpp
 * \brief UI widget to display info about a server
 * \author G. B.
 * \version 0.1a
 * \date 16/02/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <SDL2/SDL.h>
#include <guisan.hpp>

#ifndef _H_SERVERLISTELEMENT_
#define _H_SERVERLISTELEMENT_

/**
 * Convenience datatype to store server data
 * Only used in this view
 */
struct ServerInfo {
	Uint32 ip;
	std::string name;
	Uint8 levelMin;
	Uint8 levelMax;
	Uint8 busy; //! level of attendance
};

/**
 * Widget to represent server info in the ServerList view
 */
class ServerListElement : public gcn::Container, public gcn::ActionListener {
public:
	explicit ServerListElement(const ServerInfo &info);
	ServerInfo getInfo() const;
	virtual void action(const gcn::ActionEvent &event) override;

private:
	ServerInfo _info;
	gcn::Button btn_connect{ "Connect" };
	gcn::Label lbl_ip;
	gcn::Label lbl_name;
	gcn::Label lbl_lvlMin;
	gcn::Label lbl_lvlMax;
	gcn::Label lbl_busy;

	void addWidgets();
};

#endif // !_H_SERVERLISTELEMENT_

