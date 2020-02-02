/**
 *  \file messagelog.hpp
 *  \brief Log to display message in Room view
 *  \author G. B.
 *  \date 02/02/2020
 *  \version 0.1a
 */
 /* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
  * If a copy of the MPL was not distributed with this file,
  * You can obtain one at http://mozilla.org/MPL/2.0/.
  *
  * This Source Code Form is "Incompatible With Secondary Licenses",
  * as defined by the Mozilla Public License, v. 2.0.
  */

#include <SDL2/SDL.h>
#include "../protocol.hpp"
#include "../config.hpp"
#include "messagelog.hpp"
using namespace gcn;

/**
 * Constructor
 */
MessageLog::MessageLog() : Widget(), 
imgServer(Image::load(RESOURCE_PREFIX + "/server_message.png")),
imgPenalty(Image::load(RESOURCE_PREFIX + "/penalty_message.png")),
imgReward(Image::load(RESOURCE_PREFIX + "/gold_message.png"))
{
    setHeight(15 * MESSAGE_LIMIT);
    setWidth(500);
}

/**
 * \brief Add a message to the list
 * \param message full text to display
 * \param type message type as defined in protocol.hpp
 */
void MessageLog::addMessage(const std::string& message, const Uint8 type) {
    if (messages.size() >= MESSAGE_LIMIT) {
        messages.pop_front();
    }

    // Create and push message
    Message m;
    m.arrival = SDL_GetTicks();
    m.type = type;
    m.message = message;
    messages.push_back(m);
}

/**
 * Draw the widget
 */
void MessageLog::draw(gcn::Graphics* graphics) {
    // Draw messages if applicable
    int toRemove = 0;
    int y = 0;
    Uint32 currentTime = SDL_GetTicks();

    for (std::list<Message>::iterator it = messages.begin(); it != messages.end(); ++it) {
        if ((*it).arrival + DISPLAY_DELAY < currentTime) {
            toRemove++;
        } else {
            int x = 0;
            // Set color
            // Draw image if necessary
            switch ((*it).type) {
            case REWARD_MSG:
                graphics->setColor(reward);
                x = imgReward->getWidth() + 3;
                graphics->drawImage(imgReward.get(), 0, y);
                break;
            case PENALTY_MSG:
                graphics->setColor(penalty);
                x = imgPenalty->getWidth() + 3;
                graphics->drawImage(imgPenalty.get(), 0, y);
                break;
            case SERVER_MSG:
                graphics->setColor(server);
                x = imgServer->getWidth() + 3;
                graphics->drawImage(imgServer.get(), 0, y);
                break;
            default: 
                graphics->setColor(standard);
                break;
            }
            
            // Draw text
            graphics->drawText((*it).message, x, y, Graphics::LEFT);
            y += 15;
        }
    }

    // Do some cleanup in list
    while (toRemove > 0) {
        messages.pop_front();
        toRemove--;
    }
}
