/**
 * \file lobbyview.cpp
 * \brief Implementation for the Lobby view
 * \author G. B.
 * \version 0.1a
 * \date 07/04/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <regex>
#include "lobbyview.hpp"
using namespace gcn;

LobbyView::LobbyView(): Context(ContextName::ROOM_LOBBY) {

    btn_back.setActionEventId("back");
    btn_back.addActionListener(this);
    btn_ready.setActionEventId("ready");
    btn_ready.addActionListener(this);
    btn_editName.setActionEventId("editname");
    btn_editName.addActionListener(this);
    btn_editConfig.setActionEventId("config");
    btn_editConfig.addActionListener(this);
    btn_teamSwitch.setActionEventId("switch");
    btn_teamSwitch.addActionListener(this);
    tf_message.setActionEventId("message");
    tf_message.addActionListener(this);

    pg_loading.setVisible(false);
}

void LobbyView::action(const gcn::ActionEvent& actionEvent) {
    if (actionEvent.getId() == "editname" && isCurrentPlayerAdmin) {
        // TODO open edit box
    } else if (actionEvent.getId() == "config" && isCurrentPlayerAdmin) {
        // TODO open specific edition box
    } else if (actionEvent.getId() == "message") {
        std::string msg = tf_message.getText();
        // Handle special processing of commands
        std::regex pattern{ "^(/kick|/mute)\\s+" };
        if (std::regex_match(msg, pattern)) {
            // TODO send as command
        } else {
            // Send as text message
        }
    }
}

void LobbyView::updateRoomInfo() {
    // TBD
}

void LobbyView::updatePlayerInfo() {
    // TBD
}

void LobbyView::updateItemInfo() {
    // TBD
}

void LobbyView::addMessage(std::string user, std::string message, bool showBalloon) {
    tb_messages.addRow(user + "] " + message);
    if (showBalloon) {
        // Reset the balloon for this user
    }
}

void LobbyView::addWidgets() {
    addWidget(&lbl_number, 5, 5);
    addWidget(&lbl_name, 20, 5);
    addWidget(&btn_editName, 100, 5);

    addWidget(&btn_back, 5, getHeight() - 2 * btn_back.getHeight());
    addWidget(&btn_ready, getWidth() - 5 - btn_ready.getWidth(), getHeight() - 2 * btn_back.getHeight());
}

void LobbyView::drawBackground(SDL_Renderer* screen) {
    // TBD
}

void LobbyView::processMessage(const Uint8 code, const std::string& message) {
    // TBD
}

void LobbyView::drawOverlay(SDL_Renderer* screen) {
    // TBD
}


