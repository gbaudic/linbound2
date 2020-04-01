/**
 * \file newroomdialog.hpp
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

#ifndef _H_NEWROOMDIALOG_
#define _H_NEWROOMDIALOG_

#include <string>
#include <map>
#include <guisan.hpp>
#include "../common/commonroom.hpp"
using namespace gcn;

class TeamListModel : public ListModel {
public:
    TeamListModel();
    int getNumberOfElements() override;
    std::string getElementAt(int i) override;
    Uint8 getNbTeams(const int i) const;
    Uint8 getPlayersPerTeam(const int i) const;

private:
    std::map<std::string, std::pair<Uint8, Uint8>> data;
    std::pair<std::string, std::pair<Uint8, Uint8>> getElement(const int i) const;
};

class NewRoomDialog : public Window, public ActionListener {
public:
    NewRoomDialog();
    void action(const ActionEvent &event) override;
    RoomCreationInfo getInfo() const;

private:
    Label lbl_name{ "Name" };
    TextField tf_name;
    Label lbl_password{ "Password (leave empty for none)" };
    TextField tf_password;
    Label lbl_teams{ "Teams" };
    ListBox lb_teams;
    Label lbl_turns{ "Sudden death turns" };
    RadioButton rd_48{ "48", "turns", true };
    RadioButton rd_60{ "60", "turns" };
    RadioButton rd_72{ "72", "turns" };
    Label lbl_type{ "Sudden death type" };
    RadioButton rd_bigbomb{ "Bigbomb", "type", true };
    RadioButton rd_double{ "Double", "type" };
    RadioButton rd_ss{ "SS", "type" };
    TeamListModel listModel;

    Button btn_ok{ "OK" };
    Button btn_cancel{ "Cancel" };

    void addWidgets();
};

#endif // !_H_NEWROOMDIALOG_
