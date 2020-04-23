/**
 * \file itembox.cpp
 * \brief UI component holding in-game items in room and lobby views
 * \author G. B.
 * \version 0.1a
 * \date 22/04/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <stdexcept>
#include "itembox.hpp"
using namespace gcn;

/**
 * Constructor
 * \param name Context in which this widget will be used, so we can adapt the behaviour
 */
ItemBox::ItemBox(ContextName name) : inGame(name == ContextName::ROOM) {
    setWidth(6 * 34);
    setHeight(34);
}

/**
 * \brief Try to add an item to the list
 * \param item the item to add
 * \return true if addition succeeded, false otherwise
 */
bool ItemBox::add(GameItemType item) {
    bool result = false;
    int size = GameItem::getSize(item);
    for (int i = 0; i < SIZE; i++) {
        if (items[i] == GameItemType::NONE_1) {
            if (size == 1) {
                items[i] = item;
                result = true;
                break;
            } else { // size == 2: we need 2 slots
                if (i < SIZE - 1 && items[i + 1] == GameItemType::NONE_1) {
                    items[i] = item;
                    items[i + 1] = item;
                    result = true;
                    break;
                }
            }
        }
    }
    return result;
}

/**
 * \brief Remove all instances of a given type 
 * Used in Lobby view when room admin disables an item
 * \param type type to remove
 */
void ItemBox::remove(GameItemType type) {
    if (!inGame) {
        int size = GameItem::getSize(type);
        int i = 0;
        while (i < SIZE) {
            if (items[i] == type) {
                items[i] = GameItemType::NONE_1;
                if (size == 2) {
                    items[i + 1] = GameItemType::NONE_1;
                }
                i += size;
            } else {
                i++;
            }
        }
    }
}

/**
 * \brief Remove an item at the specified index
 * \return true if success, false otherwise
 */
bool ItemBox::remove(const int index) {
    bool result = false;
    if (index >= 0 && index < SIZE) {
        int i = 0;
        while (i < SIZE) {
            int size = GameItem::getSize(items[i]);
            if ((index == i && size == 1) || (size == 2 && (index == i || index == i + 1))) {
                // Location found
                current = items[i];
                items[i] = GameItemType::NONE_1;
                if (size == 2) {
                    items[i + 1] = GameItemType::NONE_1;
                }
                result = current != GameItemType::NONE_1;
                break;
            }
            i += size;
        }
    }
    return result;
}

/**
 * \brief Get the currently selected item (if any)
 * Calling this method resets the selection! 
 * \return the currently selected item, or NONE_1 if none selected. 
 */
GameItemType ItemBox::getSelected() {
    GameItemType result = current;
    current = GameItemType::NONE_1;
    return result;
}

void ItemBox::draw(gcn::Graphics* graphics) {
    Color lightgray{ 0xcc, 0xcc, 0xcc };
    Color lightblue{ 0x4c, 0xa3, 0xaa };
    // Draw background
    for (int i = 0; i < SIZE; i++) {
        graphics->setColor(lightgray);
        graphics->drawRectangle(Rectangle(i * 34, 0, 32, getHeight()));
        graphics->setColor(lightblue);
        graphics->fillRectangle(Rectangle(i * 34 + 1, 1, 30, getHeight() - 2));
    }

    // Draw items
    int i = 0;
    while (i < SIZE) {
        int size = GameItem::getSize(items[i]);
        if (items[i] != GameItemType::NONE_1 && items[i] != GameItemType::NONE_2) {
            // This item should show up
            try {
                const Image* img = images.at(items[i]);
                graphics->drawImage(img, i * 34 + 2, 2);
            } catch (const std::out_of_range) {
                // Image not found in map: load it
                auto it = images.insert(std::make_pair(items[i], Image::load(GameItem::getFilename(items[i]))));
                graphics->drawImage(it.first->second, i * 34 + 2, 2);
            }
        }

        i += size;
    }
}

void ItemBox::mouseReleased(gcn::MouseEvent& mouseEvent) {
    if (mouseEvent.getButton() == MouseEvent::LEFT || mouseEvent.getButton() == MouseEvent::RIGHT) {
        if (mouseEvent.getX() >= 0 && mouseEvent.getX() <= getWidth() && mouseEvent.getY() >= 0 && mouseEvent.getY() <= getHeight()) {
            bool hasItem = remove(mouseEvent.getX() / 34);
            if (hasItem) {
                generateAction();
            }
            mouseEvent.consume();
        }
    }
}

void ItemBox::keyReleased(gcn::KeyEvent& keyEvent) {
    if (inGame) {
        const Key key = keyEvent.getKey();
        // Only F1-F6 are supported in keyboard interaction
        if (key.getValue() >= Key::F1 && key.getValue() <= Key::F6) {
            bool hasItem = remove(key.getValue() - Key::F1);
            if (hasItem) {
                generateAction();
            }
            keyEvent.consume();
        }
    }
}


