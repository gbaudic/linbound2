/**
 * \file commonplayer.cpp
 * \brief Common definitions for a player in client and server side
 * \author G. B.
 * \version 0.1a
 * \date 14/04/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "commonplayer.hpp"

/**
 * \brief Constructor
 */
CommonPlayer::CommonPlayer() {
    
}

/**
 * \brief Inject the info from db or server into the player object
 * \param newInfo info on player
 */
void CommonPlayer::setInfo(const PlayerBasicInfo& newInfo) {
    info = newInfo;
}

/**
 * \brief Set/change the team for this player
 * \param newTeam name of the team to join, A, B, C or D
 */
void CommonPlayer::setTeam(char newTeam) {
    team = newTeam;
}

/**
 * \brief Adjust the amount of a reward/penalty according to the enabled items
 * \param baseAmount amount of the reward
 * \return actual amount to use for this player
 */
int CommonPlayer::getRewardAmount(const int baseAmount) const {
    return baseAmount * (100 + properties[0]) / 100;
}
