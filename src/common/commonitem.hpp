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

#ifndef _H_COMMONITEM_
#define _H_COMMONITEM_

#include <string>
#include <SDL2/SDL.h>

/**
 * \enum ItemValidity
 * \brief tells for how long the user will keep an item in inventory
 * Note that this is only used at the time of purchase; internally, this data gets converted to a date
 * and we only retrieve the items currently available when the player connects
 */
enum class ItemValidity {
    ONE_DAY, //!< 24 hours
    ONE_WEEK, //!< 7 days
    ONE_MONTH, //!< 30 days
    ONE_YEAR, //!< 365 days
    LIMITLESS //!< 100 years
};

/**
 * \enum ItemProperty
 * \brief convenience enum to tell the various categories apart
 */
enum class ItemProperty {
    DELAY, //!< delay when shooting
    POPULARITY, //!< amount of money bonuses give you
    ATTACK, //!< shot power
    DEFENSE, //!< damage inflicted by others
    ENERGY, //!< reloading of life bar
    SHIELD, //!< ??? 
    ITEMDELAY, //!< delay increased when using a weapon
    PIT //!< land destruction
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

/**
 * Shared class for an avatar item worn by the player which confers extra abilities
 */
class CommonItem {
public:
    ItemType getType() const;
    bool isGoldOnly();
    bool isCashOnly();
    int getProperty(ItemProperty property);
    std::string getName() const;
    std::string getDescription() const;

private:
    Uint32 code;
    std::string name;
    std::string description;
    ItemType type;
    int properties[8]{0, 0, 0, 0, 0, 0, 0, 0};
    unsigned int goldPrices[5]{ 0, 0, 0, 0, 0 };
    unsigned int cashPrices[5]{ 0, 0, 0, 0, 0 };
};

#endif //! _H_COMMONITEM_
