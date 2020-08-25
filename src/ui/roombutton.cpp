/**
 * \file roombutton.hpp
 * \brief Button overload for rooms in serverview
 * \author G. B.
 * \version 0.1a
 * \date 02/11/2016
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include "../config.hpp"
#include "roombutton.hpp"
using namespace std;

/**
 * Constructor
 * \param nb room number
 * \param name room name
 * \param mode current game mode (SOLO, DUO, etc.)
 */
LB_RoomButton::LB_RoomButton(const Uint16 nb, const std::string &name, const GameMode mode) : gcn::ImageButton(RESOURCE_PREFIX + "room_button.png"), 
number(nb), roomName(name), gameMode(mode) {
    // TODO room status
}

/**
 * Destructor
 */
LB_RoomButton::~LB_RoomButton() {

}

/** 
 * \copydoc gcn::Widget::draw(Graphics*)
 */
void LB_RoomButton::draw(gcn::Graphics* graphics) {
	//TODO

	gcn::Color faceColor = getBaseColor();
	gcn::Color highlightColor;
	gcn::Color shadowColor;
	int alpha = getBaseColor().a;

	if (isPressed()) {
		faceColor = faceColor - 0x303030;
		faceColor.a = alpha;
		highlightColor = faceColor - 0x303030;
		highlightColor.a = alpha;
		shadowColor = faceColor + 0x303030;
		shadowColor.a = alpha;
	} else {
		highlightColor = faceColor + 0x303030;
		highlightColor.a = alpha;
		shadowColor = faceColor - 0x303030;
		shadowColor.a = alpha;
	}

	graphics->setColor(faceColor);
	graphics->fillRectangle(gcn::Rectangle(1, 1, getDimension().width-1, getHeight() - 1));

	graphics->setColor(highlightColor);
	graphics->drawLine(0, 0, getWidth() - 1, 0);
	graphics->drawLine(0, 1, 0, getHeight() - 1);

	graphics->setColor(shadowColor);
	graphics->drawLine(getWidth() - 1, 1, getWidth() - 1, getHeight() - 1);
	graphics->drawLine(1, getHeight() - 1, getWidth() - 1, getHeight() - 1);

	graphics->setColor(getForegroundColor());

	if(isPressed()) {
		graphics->drawImage(mImage, 0 + 1, 0 + 1);
		graphics->drawText(to_string(number), 2 + 1, 2 + 1, gcn::Graphics::LEFT);
		graphics->drawText(roomName, 20 + 1, 2 + 1, gcn::Graphics::LEFT);
		//Draw room image
		//Draw status image
	} else {
		graphics->drawImage(mImage, 0, 0);
		graphics->drawText(to_string(number), 2, 2, gcn::Graphics::LEFT);
		graphics->drawText(roomName, 20, 2, gcn::Graphics::LEFT);

		if (isFocused()) {
			graphics->drawRectangle(gcn::Rectangle(2, 2, getWidth() - 4, getHeight() - 4));
		}
	}

}

/**
 *  May be necessary for GUI interaction
 *  \return the number for the room represented by this button on the GUI
 */
Uint16 LB_RoomButton::getNumber() {
	return number; 
}
