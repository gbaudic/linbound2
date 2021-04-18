/**
 * \file commonitem.cpp
 * \brief Common definitions for avatar items
 * \author G. B.
 * \version 0.1a
 * \date 20/01/2021
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */
 
#include "commonitem.hpp"
using namespace std;

/**
 * @brief Getter for type
 * @return the type
 * @see ItemType
*/
ItemType CommonItem::getType() const {
    return type;
}

/**
 * @brief Determine if an item can only be bought by cash
 * @return true if it is the case
*/
bool CommonItem::isCashOnly() const {
    return goldPrices[0] + goldPrices[1] + goldPrices[2] + goldPrices[3] + goldPrices[4] == -5;
}

/**
 * @brief Determine if an item can only be bought by gold
 * @return true if it is the case
*/
bool CommonItem::isGoldOnly() const {
    return cashPrices[0] + cashPrices[1] + cashPrices[2] + cashPrices[3] + cashPrices[4] == -5;
}

/**
 * @brief Getter for properties
 * @param property desired property
 * @return specified value, 0 means that the item contributes nothing
*/
int CommonItem::getProperty(ItemProperty property) const {
    int result = 0;
    
    switch(property) {
        case ItemProperty::DELAY:
            result = properties[0];
            break;
        case ItemProperty::POPULARITY:
            result = properties[1];
            break;
        case ItemProperty::ATTACK:
            result = properties[2];
            break;
        case ItemProperty::DEFENSE:
            result = properties[3];
            break;
        case ItemProperty::ENERGY:
            result = properties[4];
            break;
        case ItemProperty::SHIELD:
            result = properties[5];
            break;
        case ItemProperty::ITEMDELAY:
            result = properties[6];
            break;
        case ItemProperty::PIT:
            result = properties[7];
            break;
        default:
            break;
    }
    
    return result;
}

/**
 * @brief Getter for name
 * @return the name
*/
std::string CommonItem::getName() const {
    return name;
}

/**
 * @brief Getter for description
 * SHown in the avatar item shop only
 * @return the description
*/
std::string CommonItem::getDescription() const {
    return description;
}

