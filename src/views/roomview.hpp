/**
 *  \file roomview.hpp
 *  \brief Main game view showing the arena
 *  \author G. B.
 *  \date 26/12/2019
 *  \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_ROOMVIEW_
#define _H_ROOMVIEW_

#include "../context.hpp"
#include "../constants.hpp"
#include "../config.hpp"
#include "../gamemap.hpp"
#include "../ui/messagelog.hpp"
#include "../ui/chatballoon.hpp"
#include "../ui/resultsdialog.hpp"
#include "../ui/scoreboard.hpp"
#include "../ui/itembox.hpp"
#include "../common/commonplayer.hpp" // temporary, use clientplayer
#include "../common/messages.hpp" // for WeaponType
#include "lobbyview.hpp"

/**
 * \brief An extended version of a Label for current gains
 * supporting basic animation of the value
 */
class GoldDisplay : public gcn::Label {
public:
    GoldDisplay();
    void draw(gcn::Graphics* graphics) override;
    void updateValue(const Sint16 delta);

private:
    Uint32 animationStartTime = 0;
    static const Uint32 FRAME_DURATION = 100; // milliseconds
    Sint16 targetValue = 0;
    Sint16 currentValue = 0;
};

class RoomView: public Context, public gcn::ActionListener {
public:
    /**
     * Define the interaction the player can do
     */
    enum class InteractionMode {
        IDLE, //! player is alive, waiting for its turn
        TURN, //! player has to play: can move and/or shoot
        DEAD,  //! player is dead or waiting to respawn
        RESULTS //! match is over
    };

    explicit RoomView(const LobbyView *view);
    virtual ~RoomView();

    void action(const gcn::ActionEvent &actionEvent) override;

    void drawBackground(SDL_Renderer *screen) override;
    void drawOverlay(SDL_Renderer *screen) override;

    void processEvent(SDL_Event &event) override;

    void addMessage(const std::string& sender, const std::string& message, const Uint8 type);

    void setTurn();

    LobbyView* getLobby();

private:
    // Viewport definitions
    SDL_Rect fg_rect;
    SDL_Rect bg_rect;

    Uint32 cursors[4] = { 0, 0, 0, 0 }; // top, right, bottom, left

    // Widgets
    gcn::TextField tf_chat;
    gcn::Button btn_1{ "1" };
    gcn::Button btn_2{ "2" };
    gcn::Button btn_supershot{ "SS" };
    gcn::Label lbl_lastAngle;
    gcn::Label lbl_currentAngle;
    gcn::Label lbl_wind;
    gcn::ProgressBar pb_power{ 0, MAX_POWER, 0 };
    gcn::ProgressBar pb_motion{ 0, MOTION_LIMIT, MOTION_LIMIT };
    MessageLog msgLog;
    ResultsDialog results;
    ScoreBoard scoreBoard;
    GoldDisplay goldDisplay;
    ItemBox itemBox{ ContextName::ROOM };

    Uint16 turnCount = 0;
    InteractionMode currentMode = InteractionMode::IDLE;
    GameMode gameMode;
    GameMap *currentMap;

    LobbyView* origin = nullptr;

    Uint8 windPower = 0;
    Uint16 windAngle = 0;

    static const Uint32 AUTOSCROLL_DELAY = 2000; // in ms
    static const Uint16 SCROLL_DELTA = 4; // in pixels, for the foreground
    static const Uint16 MAX_POWER = 1000;
    static const Uint16 POWER_INCREMENT = 5; // for power bar, per frame
    static const Uint16 MOTION_LIMIT = 50;
    static const Uint16 MAGIC_EDGE_WIDTH = 20; // in pixels

    void addWidgets();
    void setWind(Uint8 newPower, Uint16 newAngle);
    void updateMagicEdge(const int coordinate, Uint32 &target);
    void moveViewport(const int xDelta, const int yDelta);
    void moveViewportTo(const int x, const int y);
    WeaponType getSelectedType();
};

#endif /* _H_ROOMVIEW_ */
