/**
 * \file scoreboard.hpp
 * \brief UI element to show score in RoomView
 * \author G. B.
 * \version 0.1a
 * \date 25/02/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* This Source Code Form is "Incompatible With Secondary Licenses",
* as defined by the Mozilla Public License, v. 2.0.
*/

#ifndef _H_SCOREBOARD_
#define _H_SCOREBOARD_

#include <string>
#include <map>
#include <guisan.hpp>
#include "../constants.hpp"

class ScoreBoard : public gcn::Widget {
public:
    ScoreBoard();

    void draw(gcn::Graphics* graphics) override;

    void init(GameMode mode, const int nbTeamPlayers, const int nbTeams = 2);
    void addScore(const char team, const int delta);
    void removeLife(const char team);
    const int getScore(const char team);

private:
    std::map<char, int> scores;
};

#endif //! _H_SCOREBOARD_
