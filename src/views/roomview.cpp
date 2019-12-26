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

#include "../utils.hpp"
#include "roomview.hpp"
using namespace std;

/**
 * Constructor
 */
RoomView::RoomView(const GameMode mode, GameMap *map) : Context(ContextName::ROOM), cursorLeft(0),
cursorRight(0), cursorTop(0), turnCount(0),
btn_1("1"), btn_2("2"), btn_supershot("SS"),
currentMode(InteractionMode::IDLE), gameMode(mode),
currentMap(map),
currentPower(0), motionLeft(0) {

	fg_rect.w = getWidth();
	fg_rect.h = getHeight();
	bg_rect.w = getWidth();
	bg_rect.h = getHeight();

	btn_supershot.setEnabled(false); // disabled when we start
	btn_supershot.adjustSize();
	btn_1.adjustSize();
	btn_2.adjustSize();


	tf_chat.setBackgroundColor(gcn::Color(0xff, 0xff, 0xff, 0)); // transparent
	tf_chat.setForegroundColor(gcn::Color(0xff, 0xff, 0xff)); // white text and caret
	tf_chat.setBorderSize(0);
	tf_chat.setTabInEnabled(false);
	tf_chat.setTabOutEnabled(false);
	tf_chat.setActionEventId("text");
	tf_chat.addActionListener(this);

}

RoomView::~RoomView() {
	// TODO Auto-generated destructor stub
}

void RoomView::action(const gcn::ActionEvent &actionEvent) {

}

void RoomView::drawBackground(SDL_Renderer *screen) {

}

void RoomView::drawOverlay(SDL_Renderer *screen) {

}

void RoomView::processEvent(SDL_Event &event) {

}

void RoomView::addWidgets() {

}

void RoomView::setTurn() {
	currentMode = InteractionMode::TURN;
	currentPower = 0;
	motionLeft = MOTION_LIMIT;
}
