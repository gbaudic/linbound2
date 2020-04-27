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

#ifndef _H_MESSAGELOG_
#define _H_MESSAGELOG_

#include <string>
#include <list>
#include <memory>
#include <SDL2/SDL.h>
#include <guisan.hpp>
#include "../config.hpp"

/**
 * Helper class to store messages before drawing them
 */
struct Message {
    std::string message;
    Uint8 type;  // see protocol.hpp
    Uint32 arrival;  // in milliseconds
};

class MessageLog : public gcn::Widget {
public:
    explicit MessageLog();
    void addMessage(const std::string& user, const std::string &message, const Uint8 type);
    void addMessage(const std::string& message, const Uint8 type);

    virtual void draw(gcn::Graphics* graphics) override;

private:
    const int MESSAGE_LIMIT = 7; // max length
    const Uint32 DISPLAY_DELAY = 5000; // in ms
    std::list<Message> messages;

    // Predefined colors to draw the messages
    gcn::Color standard{ 0xff, 0xff, 0xff };
    gcn::Color server{ 0xff, 0xff, 0 };
    gcn::Color reward{ 0, 0xff, 0xff };
    gcn::Color penalty{ 0xff, 0, 0 };

    std::unique_ptr<gcn::Image> imgServer{ gcn::Image::load(RESOURCE_PREFIX + "/messages/server_message.png") };
    std::unique_ptr<gcn::Image> imgPenalty{ gcn::Image::load(RESOURCE_PREFIX + "/messages/penalty_message.png") };
    std::unique_ptr<gcn::Image> imgReward{ gcn::Image::load(RESOURCE_PREFIX + "/messages/gold_message.png") };
};


#endif //! _H_MESSAGELOG_
