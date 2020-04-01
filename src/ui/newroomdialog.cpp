/**
 * \file newroomdialog.cpp
 * \brief Dialog in server view to create a new room
 * \author G. B.
 * \version 0.1a
 * \date 01/04/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "newroomdialog.hpp"

/**
 * Constructor
 */
NewRoomDialog::NewRoomDialog() : Window("Create room")
{
    lbl_name.adjustSize();
    lbl_password.adjustSize();
    lbl_teams.adjustSize();
    lbl_turns.adjustSize();
    lbl_type.adjustSize();
    lb_teams.setListModel(&listModel);

    btn_cancel.setActionEventId("cancel");
    btn_cancel.addActionListener(this);
    btn_ok.setActionEventId("ok");
    btn_ok.addActionListener(this);

    setWidth(200);
    setHeight(300);
    addWidgets();
    setVisible(false); // hidden at startup
}

void NewRoomDialog::action(const ActionEvent& event) {
    if (event.getId() == "ok") {
        setVisible(false);
        generateAction();
    } else if (event.getId() == "cancel") {
        // Reset fields
        tf_name.clear();
        tf_password.clear();
        setVisible(false);
    }
}

RoomCreationInfo NewRoomDialog::getInfo() const {
    RoomCreationInfo rci;
    rci.name = tf_name.getText();
    rci.password = tf_password.getText();
    rci.sdTurns = 48;
    rci.sdtype = SuddenDeathType::BIGBOMB;
    
    if (rd_60.isSelected()) {
        rci.sdTurns = 60;
    } else if (rd_72.isSelected()) {
        rci.sdTurns = 72;
    }

    if (rd_double.isSelected()) {
        rci.sdtype = SuddenDeathType::DOUBLE;
    } else if (rd_ss.isSelected()) {
        rci.sdtype = SuddenDeathType::SS;
    }
    
    return rci;
}

void NewRoomDialog::addWidgets() {
    int margin = 2;
    add(&lbl_name, margin, margin);
    add(&tf_name, margin, lbl_name.getY() + lbl_name.getHeight() + margin);
    add(&lbl_password, margin, tf_name.getY() + tf_name.getHeight() + margin);
    add(&tf_password, margin, lbl_password.getY() + lbl_password.getHeight() + margin);
    // TODO add missing widgets
    add(&btn_ok, margin, getHeight() - margin - btn_ok.getHeight());
    add(&btn_cancel, getWidth() - margin - btn_cancel.getWidth(), getHeight() - margin - btn_cancel.getHeight());
}

/**
 * Constructor
 */
TeamListModel::TeamListModel() {
    // Fill the model
    data.emplace("1v1", std::make_pair(2, 1));
    data.emplace("2v2", std::make_pair(2, 2));
    data.emplace("3v3", std::make_pair(2, 3));
    data.emplace("4v4", std::make_pair(2, 4));
}

int TeamListModel::getNumberOfElements() {
    return data.size();
}

std::string TeamListModel::getElementAt(int i){
    return getElement(i).first;
}

Uint8 TeamListModel::getNbTeams(const int i) const {
    return getElement(i).second.first;
}

Uint8 TeamListModel::getPlayersPerTeam(const int i) const {
    return getElement(i).second.second;
}

std::pair<std::string, std::pair<Uint8, Uint8>> TeamListModel::getElement(const int i) const {
    int index = 0;
    for (std::map<std::string, std::pair<Uint8, Uint8>>::const_iterator it = data.begin(); index <= i; it++, index++) {
        if (index == i) {
            return *it;
        }
    }
}
