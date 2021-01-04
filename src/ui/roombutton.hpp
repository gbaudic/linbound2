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
 
#ifndef _H_ROOMBUTTON_
#define _H_ROOMBUTTON_

#include <string>
#include <guisan.hpp>
#include "../constants.hpp"
#include "../common/commonroom.hpp"

/**
 * @brief An improved button to represent a room
 */
class LB_RoomButton : public gcn::ImageButton {
public:
    LB_RoomButton(const Uint16 nb, const std::string &name, const GameMode mode);
    virtual ~LB_RoomButton();
    void draw(gcn::Graphics* graphics) override;
    Uint16 getNumber() const;

private:
    // TODO use RoomBasicInfo instead if applicable
    Uint16 number; //! room number as created by server
    std::string roomName; //! room name
    GameMode gameMode;
    gcn::Image* mStatusImages;
};

#endif //! _H_ROOMBUTTON_
