/**
 * \file lobbyview.hpp
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

#ifndef _H_LOBBYVIEW_
#define _H_LOBBYVIEW_

#include <string>
#include <guisan.hpp>
#include "../context.hpp"
#include "../common/commonroom.hpp"
#include "../common/messages.hpp"

class LobbyView : public Context, public gcn::ActionListener {
public:
    LobbyView();
    void action(const gcn::ActionEvent& actionEvent) override;

    void updateRoomInfo();
    void updatePlayerInfo();
    void updateItemInfo();
    void addMessage(std::string user, std::string message, bool showBalloon = true);

    virtual void drawBackground(SDL_Renderer* screen) override;
    virtual void processMessage(const Uint8 code, const std::string& message) override;
    virtual void drawOverlay(SDL_Renderer* screen) override;
    virtual void processEvent(SDL_Event& event) override {
        // No specific handling to be done here, GUI handles everything
    };

private:
    gcn::Label lbl_number;
    gcn::Label lbl_name;

    gcn::Button btn_back{ "< Back" };
    gcn::Button btn_ready{ "Ready" };
    gcn::Button btn_editName{ "Edit name" };
    gcn::Button btn_editConfig{ "Edit config" };
    gcn::Button btn_teamSwitch{ "Change team" };
    gcn::ProgressBar pg_loading;
    gcn::TabbedArea tabs;
    gcn::TextField tf_message;
    gcn::TextBox tb_messages;

    bool isCurrentPlayerAdmin = false;

    void addWidgets();
};

#endif // !_H_LOBBYVIEW_

