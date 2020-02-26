/**
 * \file scoreboard.cpp
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

#include "scoreboard.hpp"
using namespace std;
using namespace gcn;

/**
 * Constructor
 */
ScoreBoard::ScoreBoard() : Widget() {
    setWidth(100);
}

void ScoreBoard::draw(Graphics* graphics) {
    unsigned int step = getWidth() / (scores.size() * 2);
    int i = 0;

    for (map<char, int>::iterator it = scores.begin(); it != scores.end(); it++) {
        graphics->setColor(Color(0xffffff));
        graphics->drawText(string(1, it->first), step * 2 * i, 0, Graphics::LEFT);
        graphics->drawText(to_string(it->second), step * 2 * i + 1, 0, Graphics::LEFT);
        i++;
    }
}

/**
 * \brief Initialize the object
 * \param mode game mode
 * \param nbTeamPlayers number of players for each team
 * \param nbTeams number of teams (usually 2)
 */
void ScoreBoard::init(GameMode mode, const int nbTeamPlayers, const int nbTeams) {
    int startScore = mode == GameMode::POINTS ? 0 : nbTeamPlayers + 1;
    
    for (int i = 0; i < nbTeams; i++) {
        scores['A' + i] = startScore;
    }
}

/**
 * \brief Edit the score of a team
 * \param team char representing the team (A, B, C, D)
 * \param delta delta to apply to the current score
 */
void ScoreBoard::addScore(const char team, const int delta) {
    scores[team] += delta;
}

/**
 * \brief Convenience function to register a death
 * \param team char representing the team which suffered the death
 */
void ScoreBoard::removeLife(const char team) {
    addScore(team, -1);
}

/**
 * \brief Convenience function to get the current score for a team
 * \param team char representing the team
 * \return the current score for this team
 */
const int ScoreBoard::getScore(const char team) {
    return scores[team];
}
