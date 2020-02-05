/**
 *  \file roomview.cpp
 *  \brief Main game view showing the arena
 *  \author G. B.
 *  \date 26/12/2019
 *  \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <algorithm>
#include "../utils.hpp"
#include "../sound.hpp"
#include "roomview.hpp"
using namespace std;

const Uint16 RoomView::MAX_POWER;

/**
 * Constructor
 * @param mode game mode to play among the four implemented
 * @param map an already partly loaded object representing the game map
 */
RoomView::RoomView(const GameMode mode, GameMap *map) : Context(ContextName::ROOM),
btn_1("1"), btn_2("2"), btn_supershot("SS"),
pb_power(0, MAX_POWER, 0), pb_motion(0, MOTION_LIMIT, MOTION_LIMIT),
currentMode(InteractionMode::IDLE), gameMode(mode),
currentMap(map) {

	fg_rect.w = getWidth();
	fg_rect.h = getHeight();
	bg_rect.w = getWidth();
	bg_rect.h = getHeight();

	btn_supershot.setEnabled(false); // disabled when we start
	btn_supershot.adjustSize();
	btn_1.adjustSize();
	btn_2.adjustSize();
	btn_1.setWidth(btn_supershot.getWidth());
	btn_2.setWidth(btn_supershot.getWidth());

	tf_chat.setBackgroundColor(gcn::Color(0xff, 0xff, 0xff, 0)); // transparent
	tf_chat.setForegroundColor(gcn::Color(0xff, 0xff, 0xff)); // white text and caret
	tf_chat.setBorderSize(0);
	tf_chat.setWidth(400);
	tf_chat.setTabInEnabled(false);
	tf_chat.setTabOutEnabled(false);
	tf_chat.setActionEventId("text");
	tf_chat.addActionListener(this);

	pb_motion.setHeight(15);
	pb_motion.setForegroundColor(gcn::Color(0x0, 0x77, 0x73));
	pb_motion.setVisible(false); // only shows up when moving
	pb_motion.setWidth(getWidth() / 2);
	pb_power.setHeight(20);
	pb_power.setForegroundColor(gcn::Color(0xff, 0, 0));
	pb_power.setWidth(getWidth() - 100 - 10);

	currentMap->load();

}

RoomView::~RoomView() {
}

void RoomView::action(const gcn::ActionEvent &actionEvent) {
	if(actionEvent.getId() == "text") {
		// TODO send the message to the correct scope
	}
}

void RoomView::drawBackground(SDL_Renderer *screen) {
	// Check if we should move
	const Uint32 currentTime = SDL_GetTicks();
	Sint16 xdelta = 0;
	Sint16 ydelta = 0;
	if (cursors[0] > 0 && currentTime - cursors[0] >= AUTOSCROLL_DELAY) {
		ydelta = -SCROLL_DELTA;
	}
	if (cursors[2] > 0 && currentTime - cursors[2] >= AUTOSCROLL_DELAY) {
		ydelta = SCROLL_DELTA;
	}
	if (cursors[3] > 0 && currentTime - cursors[3] >= AUTOSCROLL_DELAY) {
		xdelta = -SCROLL_DELTA;
	}
	if (cursors[1] > 0 && currentTime - cursors[1] >= AUTOSCROLL_DELAY) {
		xdelta = SCROLL_DELTA;
	}
	moveViewport(xdelta, ydelta);
	
	SDL_Rect fullScreen;
	fullScreen.x = 0;
	fullScreen.y = 0;
	fullScreen.w = getWidth();
	fullScreen.h = getHeight();

	SDL_RenderSetClipRect(screen, &fullScreen);
	// Draw top indicators if applicable
	
	// Draw map background
	SDL_RenderCopy(screen, currentMap->getBackground(), &bg_rect, &fullScreen);
	// Draw weather effects if any
	
	// Draw map foreground
	SDL_RenderCopy(screen, currentMap->getForeground(), &fg_rect, &fullScreen);
	// Draw mobiles

	// Draw flying weapons if any

	SDL_RenderSetClipRect(screen, NULL);
}

void RoomView::drawOverlay(SDL_Renderer *screen) {
	// TODO overlays appear for sudden deaths, game start or exceptional achievements
}

void RoomView::processEvent(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		// Shooting
		if (event.key.keysym.sym == SDLK_SPACE && !tf_chat.isFocused() && currentMode == InteractionMode::TURN) {
			int currentPower = pb_power.getValue() + POWER_INCREMENT;
			currentPower = min(currentPower, static_cast<int>(MAX_POWER));
			pb_power.setValue(currentPower);
		}
	} else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_SPACE && !tf_chat.isFocused() && currentMode == InteractionMode::TURN) {
			// Player has finished shooting
			currentMode = InteractionMode::IDLE;
		}
		// Support here arrow up/down (angle), left/right (motion), F7 (mobile), F8 (pass turn), F1-6 (item use)...
	} else if (event.type == SDL_MOUSEMOTION) {
		SDL_MouseMotionEvent mouseEvent = event.motion;

		if (mouseEvent.x >= 0 && mouseEvent.x <= getWidth() && mouseEvent.y >= 0 && mouseEvent.y <= getHeight() - 100) {
			// We are in the window, check if we are in an edge
			// Left edge
			updateMagicEdge(mouseEvent.x, cursors[3]);

			// Right edge
			updateMagicEdge(getWidth() - mouseEvent.x, cursors[1]);

			// Top edge
			updateMagicEdge(mouseEvent.y, cursors[0]);

			// Bottom edge
			updateMagicEdge(getHeight() - 100 - mouseEvent.y, cursors[2]);
		}
	}
}

/**
 * Set timings for auto scrolling feature
 * @param coordinate coordinate to test
 * @param target time variable to update
 */
void RoomView::updateMagicEdge(const int coordinate, Uint32 &target) {
	if (coordinate <= MAGIC_EDGE_WIDTH) {
		if (target == 0) {
			target = SDL_GetTicks();
		}
	} else {
		target = 0;
	}
}

/**
 * \brief Add the widgets to the container
 */
void RoomView::addWidgets() {
	addWidget(&tf_chat, 50, getHeight() - 100);
	addWidget(&btn_supershot, 40, getHeight() - 5 - btn_supershot.getHeight());
	addWidget(&btn_2, 40, btn_supershot.getY() - 5 - btn_2.getHeight());
	addWidget(&btn_1, 40, btn_2.getY() - 5 - btn_1.getHeight());
	addWidget(&lbl_wind, 20, getHeight() - 20);

	addWidget(&pb_power, 70, getHeight() - pb_power.getHeight() - 10);
	addWidget(&pb_motion, 70, pb_power.getY() - 20);
}

/**
 * \brief React on wind update
 * \param newPower new power value (0-25)
 * \param newAngle new angle value (0-360), in degrees
 */
void RoomView::setWind(Uint8 newPower, Uint16 newAngle) {
	windPower = newPower;
	windAngle = newAngle;
	lbl_wind.setCaption(to_string(windPower));
	SoundManager::getInstance()->playSound("wind1");
}

/**
 * \brief Prepare the view so the player can shoot and move
 */
void RoomView::setTurn() {
	currentMode = InteractionMode::TURN;
	pb_power.setValue(0);
	pb_motion.setValue(MOTION_LIMIT);
	// TODO play a sound once to wake up player
}

/**
 * Move the viewport from a given offset
 * @param xDelta x offset
 * @param yDelta y offset
 */
void RoomView::moveViewport(const int xDelta, const int yDelta) {
	moveViewportTo(fg_rect.x + xDelta, fg_rect.y + yDelta);
}

/**
 * Move the viewport to a specified point
 * This method will ensure the final coordinates are not off-limits
 * TODO: implement a limit so we do not move too harshly
 * @param x new x coordinate
 * @param y new y coordinate
 */
void RoomView::moveViewportTo(const int x, const int y) {
	// Get some data about the map file
	int fgW;
	int fgH;
	SDL_QueryTexture(currentMap->getForeground(), NULL, NULL, &fgW, &fgH);
	int bgW;
	int bgH;
	SDL_QueryTexture(currentMap->getBackground(), NULL, NULL, &bgW, &bgH);

	fg_rect.x = max(0, min(x, fgW - getWidth() - 1));
	fg_rect.y = max(0, min(y, fgH - getHeight() - 1));

	// Now propagate the movement to the background rect
	// Note that the parallax effect is achieved here only if the background is smaller than the foreground
	bg_rect.x = fg_rect.x * (bgW - getWidth()) / (fgW - getWidth());
	bg_rect.y = fg_rect.y * (bgH - getHeight()) / (fgH - getHeight());
}
