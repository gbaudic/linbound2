/**
 * \file serverview.cpp
 * \date 17/11/2019
 * \brief UI class for server view, where user can chat and select a game room
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "serverview.hpp"

/**
 * Constructor
 */
ServerView::ServerView(ContextName previous) : Context(ContextName::ROOM_LIST),
 origin(previous) {

    btn_back.setActionEventId("logout");
    btn_back.addActionListener(this);

    btn_newRoom.setActionEventId("new");
    btn_newRoom.addActionListener(this);

    btn_goToShop.setActionEventId("shop");
    btn_goToShop.addActionListener(this);

    btn_addFriend.setActionEventId("friend");
    btn_addFriend.addActionListener(this);

    btn_prevPage.setActionEventId("prev");
    btn_prevPage.addActionListener(this);

    btn_nextPage.setActionEventId("next");
    btn_nextPage.addActionListener(this);

    sa_chat.setContent(&tb_chat);
    tb_chat.setEditable(false); // read-only

    tf_message.setActionEventId("send_msg");
    tf_message.addActionListener(this);

    nrd.setActionEventId("new_request");
    nrd.addActionListener(this);

    addWidgets();
}

ServerView::~ServerView() {
    // Cleanup our surfaces
    if (background) {
        SDL_FreeSurface(background);
    }
    if (backTexture) {
        SDL_DestroyTexture(backTexture);
    }
}

void ServerView::action(const gcn::ActionEvent& actionEvent) {
    if (actionEvent.getId() == "logout") {
        network.logout();
        setNextContext(origin);
    } else if (actionEvent.getId() == "new") {
        nrd.setVisible(true);
    } else if (actionEvent.getId() == "friend") {
        in_addFriend.setVisible(true);
    }
}

void ServerView::addWidgets() {
    // Add player data to display
    addWidget(&lbl_playerName, getWidth() / 3, 2);
    addWidget(&lbl_playerTeam, lbl_playerName.getX() + 50, 2);
    addWidget(&lbl_playerPoints, lbl_playerTeam.getX() + 50, 2);
    addWidget(&lbl_playerMoney, lbl_playerPoints.getX() + 50, 2);

    int xStep = getWidth() / 5;
    addWidget(&btn_back, xStep - btn_back.getWidth(), getHeight() - 2 * btn_back.getHeight());
    addWidget(&btn_newRoom, 2 *xStep - btn_newRoom.getWidth(), btn_back.getY());
    addWidget(&btn_goToShop, 3 * xStep - btn_goToShop.getWidth(), btn_back.getY());
    addWidget(&btn_addFriend, 4 * xStep - btn_addFriend.getWidth(), btn_back.getY());

    // Channel chat area
    addWidget(&tf_message, btn_back.getX(), btn_back.getY() - btn_back.getHeight() - tf_message.getHeight());
    addWidget(&sa_chat, btn_back.getX(), tf_message.getY() - 10 - sa_chat.getHeight());

    // Dialogs
    addCenteredWidget(&in_addFriend);
    addCenteredWidget(&nrd);
}

/**
 * \brief Append a new message to the channel view
 */
void ServerView::receiveChatMessage(const std::string& user, const std::string& message) {
    tb_chat.addRow(user + "] " + message);
}

/**
 * Function to be called when a player status change is received from server
 * \param player info (type to be created)
 */
void ServerView::playerStateChanged() {
    // TBD
}

/**
 * Function to be called when room info changes
 * \param new info for ONE room (type to be created)
 */
void ServerView::roomChanged() {
    // TBD
}

/**
 * \brief Update data for the current player
 * \param info basic data as received from the server
 */
void ServerView::setPlayerData(const PlayerBasicInfo info) {
    lbl_playerName.setCaption(info.name);
    lbl_playerName.adjustSize();
    lbl_playerMoney.setCaption(std::to_string(info.gold) + " G");
    lbl_playerMoney.adjustSize();
    lbl_playerPoints.setCaption(std::to_string(info.points) + " XP");
    lbl_playerPoints.adjustSize();
}

void ServerView::drawBackground(SDL_Renderer* screen) {
    // TBD
}
