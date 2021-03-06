/**
 * \file serverlistelement.cpp
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

#include "../utils.hpp"
#include "serverlistelement.hpp"
using namespace std;

/**
 * Constructor
 * \param info struct containing the data to display
 */
ServerListElement::ServerListElement(const ServerInfo &info) : 
_info(info) {
    setWidth(500);
    setHeight(60);
    setOpaque(false);

    lbl_name.setCaption(info.name);
    lbl_name.adjustSize();

    lbl_ip.setCaption(linbound::prettifyIP(info.ip));
    lbl_ip.adjustSize();

    // Levels are displayed as text for the moment...
    lbl_lvlMin.setCaption("Level min: " + to_string(info.levelMin));
    lbl_lvlMin.adjustSize();

    lbl_lvlMax.setCaption("Level max: " + to_string(info.levelMax));
    lbl_lvlMax.adjustSize();

    string business = "";
    switch (info.busy) {
        case 0: business = "Low"; break;
        case 1: business = "Medium"; break;
        case 2: business = "High"; break;
        case 255: business = "Full"; break;
        default: break;
    }

    lbl_busy.setCaption(business);
    lbl_busy.adjustSize();

    btn_connect.setWidth(100);
    btn_connect.setHeight(getHeight() - 10);
    btn_connect.addActionListener(this);

    addWidgets();
}

/**
 * Getter for server info
 * \return the server info
 */
ServerInfo ServerListElement::getInfo() const {
    return _info;
}

/**
 * \copydoc gcn::ActionListener::action(gcn::ActionEvent &)
 */
void ServerListElement::action(const gcn::ActionEvent & event) {
    if (event.getSource() == &btn_connect) {
        generateAction();
    }
}

void ServerListElement::addWidgets() {
    int padding = 5;
    add(&lbl_name, padding, padding);
    add(&lbl_ip, lbl_name.getWidth() + 2 * padding, padding);
    add(&btn_connect, getWidth() - padding - btn_connect.getWidth(), padding);

    add(&lbl_lvlMin, padding, getHeight() - padding - lbl_lvlMin.getHeight());
    add(&lbl_lvlMax, 100, getHeight() - padding - lbl_lvlMin.getHeight());
    add(&lbl_busy, btn_connect.getX() - padding - lbl_busy.getWidth(), getHeight() - padding - lbl_lvlMin.getHeight());
}
