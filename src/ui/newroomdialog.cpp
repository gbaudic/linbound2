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
using namespace gcn;

/**
 * Constructor
 */
NewRoomDialog::NewRoomDialog() : Window("Create room") {
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
    setMovable(false);
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

/**
 * \brief Get the data placed in the dialog
 * \return a RoomCreationInfo with all the data
 */
RoomCreationInfo NewRoomDialog::getInfo() const {
    RoomCreationInfo rci;
    rci.name = tf_name.getText();
    rci.password = tf_password.getText();
    rci.sdTurns = 48;
    rci.sdtype = SuddenDeathType::BIGBOMB;
    int index = lb_teams.getSelected();
    rci.nbTeams = listModel.getNbTeams(index);
    rci.playersPerTeam = listModel.getPlayersPerTeam(index);
    
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

/**
 * Put the widgets at their place and please Sonar
 */
void NewRoomDialog::addWidgets() {
    int margin = 2;
    add(&lbl_name, margin, margin);
    add(&tf_name, margin, lbl_name.getY() + lbl_name.getHeight() + margin);
    add(&lbl_password, margin, tf_name.getY() + tf_name.getHeight() + margin);
    add(&tf_password, margin, lbl_password.getY() + lbl_password.getHeight() + margin);
    add(&lbl_teams, margin, tf_password.getY() + tf_password.getHeight() + margin);
    add(&lb_teams, margin, lbl_teams.getY() + lbl_teams.getHeight() + margin);
    
    add(&lbl_turns, margin, lb_teams.getY() + lb_teams.getHeight() + margin);
    add(&rd_48, margin, lbl_turns.getY() + lbl_turns.getHeight() + margin);
    add(&rd_60, (getWidth() - rd_60.getWidth()) / 2, rd_48.getY());
    add(&rd_72, getWidth() - rd_72.getWidth() - margin, rd_48.getY());
    
    add(&lbl_type, margin, rd_48.getY() + rd_48.getHeight() + margin);
    add(&rd_bigbomb, margin, lbl_type.getY() + lbl_type.getHeight() + margin);
    add(&rd_double, (getWidth() - rd_double.getWidth()) / 2, rd_bigbomb.getY());
    add(&rd_ss, getWidth() - rd_ss.getWidth() - margin, rd_bigbomb.getY());
    
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

/**
 * \copydoc gcn::ListModel::getNumberOfElements()
 */
int TeamListModel::getNumberOfElements() {
    return data.size();
}

/**
 * \brief Get the string for element i
 * \param i requested index. No range check is done here.
 * \return the string element to be displayed for this index
 */
std::string TeamListModel::getElementAt(int i) {
    return getElement(i).first;
}

/**
 * \brief Get the number of teams corresponding to the current element.
 * It may not be equal to two.
 * \param i requested index
 * \return number of teams (>= 2) for this index
 */
Uint8 TeamListModel::getNbTeams(const int i) const {
    return getElement(i).second.first;
}

/**
 * \brief Get the number of players per teams corresponding to the current element.
 * \param i requested index
 * \return number of players per team for this index
 */
Uint8 TeamListModel::getPlayersPerTeam(const int i) const {
    return getElement(i).second.second;
}

/**
 * \brief Get the i-th element of the map
 * \param i requested index
 * \return full element (key + value) as present in the map
 */
std::pair<std::string, std::pair<Uint8, Uint8>> TeamListModel::getElement(const int i) const {
    int index = 0;
    for (std::map<std::string, std::pair<Uint8, Uint8>>::const_iterator it = data.begin(); it != data.end() && index <= i; it++, index++) {
        if (index == i) {
            return *it;
        }
    }
}
