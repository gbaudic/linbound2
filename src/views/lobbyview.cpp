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

/**
 * Constructor
 * \param name ???
 */
LobbyView::LobbyView(ContextName name): Context(name), itemBox(name) {

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
    itemBox.setActionEventId("itembox");
    itemBox.addActionListener(this);

    Color darkblue{ 0, 0, 0xff };
    Color white{ 0xff, 0xff, 0xff };
    tf_message.setForegroundColor(white);
    tf_message.setBackgroundColor(darkblue);
    tb_messages.setForegroundColor(white);
    tb_messages.setBackgroundColor(darkblue);

    pg_loading.setVisible(false);
}

void LobbyView::action(const gcn::ActionEvent& actionEvent) {
    if (actionEvent.getId() == "editname" && isCurrentPlayerAdmin) {
        // TODO open edit box
    } else if (actionEvent.getId() == "config" && isCurrentPlayerAdmin) {
        // TODO open specific edition box
    } else if (actionEvent.getId() == "message") {
        std::string msg = tf_message.getText();
        tf_message.clear();
        // Handle special processing of commands
        std::regex pattern{ "^(/kick|/mute)\\s+" };
        if (std::regex_match(msg, pattern)) {
            // TODO send as command
        } else {
            // Send as text message
        }
    }
}

/**
 * Update the data about the room
 * \param new info about the room (sudden death type, turns, team size...)
 */
void LobbyView::updateRoomInfo(const RoomBasicInfo &info) {
    // TBD: refresh the view accordingly
    roomBasicInfo = info;
}

/**
 * Update the data (and the representation) of a given player
 * In this mode, changes are most likely to be a mobile or team change, or the current player becomes an admin
 */
void LobbyView::updatePlayerInfo() {
    // TBD
}

/**
 * Update the list of items which are available or not
 */
void LobbyView::updateItemInfo() {
    // TBD
}

/**
 * Make a new message appear in the UI
 * \param user name of sender of message
 * \param message text of the message
 * \param showBalloon if true, also draw the balloon above the player who said the message
 */
void LobbyView::addMessage(const std::string &user, const std::string &message, bool showBalloon) {
    tb_messages.addRow(user + "] " + message);
    if (showBalloon) {
        // Reset the balloon for this user
    }
}

/**
 * \brief Convenience function to get currently selected game mode
 * \return the GameMode
 * \see GameMode
 */
GameMode LobbyView::getMode() const {
    return roomBasicInfo.mode;
}

/**
 * \brief Convenience function to get currently selected map
 * \return the name of the map
 */
std::string LobbyView::getMap() const {
    return roomBasicInfo.mapName;
}

/**
 * \brief Convenience function to get the name of the player currently connected with this client
 * \return the name
 */
std::string LobbyView::getCurrentPlayerName() const {
    return currentPlayerName;
}

/**
 * \brief Convenience function to get currently selected sudden death type
 * \return the type of sudden death
 * \see SuddenDeathType
 */
SuddenDeathType LobbyView::getSuddenDeathType() const {
    return sdType;
}

void LobbyView::addWidgets() {
    addWidget(&lbl_number, 5, 5);
    addWidget(&lbl_name, 20, 5);
    addWidget(&btn_editName, 100, 5);

    addWidget(&tabs, 15, getHeight() - 3 * btn_back.getHeight() - tf_message.getHeight());
    addWidget(&tf_message, 15, getHeight() - 3 * btn_back.getHeight() - tf_message.getHeight());

    addWidget(&itemBox, getWidth() - 15 - itemBox.getWidth(), tabs.getY());

    addWidget(&btn_back, 5, getHeight() - 2 * btn_back.getHeight());
    addWidget(&btn_ready, getWidth() - 5 - btn_ready.getWidth(), getHeight() - 2 * btn_back.getHeight());
    addWidget(&btn_teamSwitch, btn_ready.getX() - 15 - btn_teamSwitch.getWidth(), btn_ready.getY());
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


