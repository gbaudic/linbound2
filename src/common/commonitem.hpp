/**
 * \file commonitem.hpp
 * \brief Common definitions for avatar items
 * \author G. B.
 * \version 0.1a
 * \date 30/03/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <string>

/**
 * \enum ItemValidity
 * \brief tells for how long the user will keep an item in inventory
 */
enum class ItemValidity {
    ONE_DAY, //!< 24 hours
    ONE_WEEK, //!< 7 days
    ONE_MONTH, //!< 30 days
    ONE_YEAR, //!< 365 days
    LIMITLESS //!< maximum date we can put in db
};

/**
 * \enum ItemType
 */
enum class ItemType {
    HEAD,
    BODY,
    GLASSES,
    FLAG,
    BACKGROUND, //!< fancy background, only visible in lobby
    EXTRA
};

class CommonItem {

private:
    std::string name;
    std::string description;
    ItemType type;
    int properties[8];
};
