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
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <algorithm>
#include "../utils.hpp"
#include "roomview.hpp"
using namespace std;

const Uint16 RoomView::MAX_POWER;

/**
 * Constructor
 */
RoomView::RoomView(const GameMode mode, GameMap *map) : Context(ContextName::ROOM),
btn_1("1"), btn_2("2"), btn_supershot("SS"),
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
	if (cursorTop > 0 && currentTime - cursorTop >= AUTOSCROLL_DELAY) {
		ydelta = -SCROLL_DELTA;
	}
	if (cursorBottom > 0 && currentTime - cursorBottom >= AUTOSCROLL_DELAY) {
		ydelta = SCROLL_DELTA;
	}
	if (cursorLeft > 0 && currentTime - cursorLeft >= AUTOSCROLL_DELAY) {
		xdelta = -SCROLL_DELTA;
	}
	if (cursorRight > 0 && currentTime - cursorRight >= AUTOSCROLL_DELAY) {
		xdelta = SCROLL_DELTA;
	}
	moveViewport(xdelta, ydelta);

	// Draw map background

	// Draw map foreground

	// Draw mobiles

}

void RoomView::drawOverlay(SDL_Renderer *screen) {
	// TODO overlays appear for sudden deaths, game start or exceptional achievements
}

void RoomView::processEvent(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		// Shooting
		if (event.key.keysym.sym == SDLK_SPACE && !tf_chat.isFocused() && currentMode == InteractionMode::TURN) {
			currentPower += POWER_INCREMENT;
			currentPower = min(currentPower, MAX_POWER);
		}
	} else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_SPACE && !tf_chat.isFocused() && currentMode == InteractionMode::TURN) {
			// Player has finished shooting
			currentMode = InteractionMode::IDLE;
		}
	} else if (event.type == SDL_MOUSEMOTION) {
		SDL_MouseMotionEvent mouseEvent = event.motion;

		if (mouseEvent.x >= 0 && mouseEvent.x <= getWidth() && mouseEvent.y >= 0 && mouseEvent.y <= getHeight() - 100) {
			// We are in the window, check if we are in an edge
			// Left edge
			updateMagicEdge(mouseEvent.x, cursorLeft);

			// Right edge
			updateMagicEdge(getWidth() - mouseEvent.x, cursorRight);

			// Top edge
			updateMagicEdge(mouseEvent.y, cursorTop);

			// Bottom edge
			updateMagicEdge(getHeight() - 100 - mouseEvent.y, cursorBottom);
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
}

/**
 * \brief Prepare the view so the player can shoot and move
 */
void RoomView::setTurn() {
	currentMode = InteractionMode::TURN;
	currentPower = 0;
	motionLeft = MOTION_LIMIT;
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
	int fgW, fgH;
	SDL_QueryTexture(currentMap->getForeground(), NULL, NULL, &fgW, &fgH);
	int bgW, bgH;
	SDL_QueryTexture(currentMap->getBackground(), NULL, NULL, &bgW, &bgH);

	fg_rect.x = max(0, min(x, fgW - getWidth() - 1));
	fg_rect.y = max(0, min(x, fgH - getHeight() - 1));

	// Now propagate the movement to the background rect
	bg_rect.x = fg_rect.x * (bgW - getWidth()) / (fgW - getWidth());
	bg_rect.y = fg_rect.y * (bgH - getHeight()) / (fgH - getHeight());
}
