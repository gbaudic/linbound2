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
#include "../gamemap.hpp"

class RoomView: public Context, public gcn::ActionListener {
public:
	/**
	 * Define the interaction the player can do
	 */
	enum class InteractionMode {
		IDLE, //! player is alive, waiting for its turn
		TURN, //! player has to play: can move and/or shoot
		DEAD  //! player is dead or waiting to respawn
	};

	explicit RoomView(const GameMode mode, GameMap* map);
	virtual ~RoomView();

	void action(const gcn::ActionEvent &actionEvent) override;

	void drawBackground(SDL_Renderer *screen) override;
	void drawOverlay(SDL_Renderer *screen) override;

	void processEvent(SDL_Event &event) override;

	void setTurn();

private:
	// Viewport definitions
	SDL_Rect fg_rect;
	SDL_Rect bg_rect;

	Uint32 cursorLeft;
	Uint32 cursorRight;
	Uint32 cursorTop;

	// Widgets
	gcn::TextField tf_chat;
	gcn::Button btn_1;
	gcn::Button btn_2;
	gcn::Button btn_supershot;
	gcn::Label lbl_lastAngle;
	gcn::Label lbl_currentAngle;
	gcn::Label lbl_wind;

	Uint16 turnCount;
	InteractionMode currentMode;
	GameMode gameMode;
	GameMap *currentMap;

	Uint16 currentPower;
	Uint16 motionLeft;

	static const Uint32 AUTOSCROLL_DELAY = 2000; // in ms
	static const Uint16 SCROLL_DELTA = 4; // in pixels, for the foreground
	static const Uint16 POWER_INCREMENT = 5; // for power bar, per frame
	static const Uint16 MOTION_LIMIT = 50;
	static const Uint16 MAGIC_EDGE_WIDTH = 20; // in pixels

	void addWidgets();
};

#endif /* _H_ROOMVIEW_ */
