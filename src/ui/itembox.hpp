/**
 * \file itembox.hpp
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

#ifndef _H_ITEMBOX_
#define _H_ITEMBOX_

#include <string>
#include <map>
#include <guisan.hpp>
#include "../common/commongameitem.hpp"
#include "../context.hpp" // for ContextName

class ItemBox : public gcn::Widget, public gcn::MouseListener, public gcn::KeyListener {
public:
    explicit ItemBox(ContextName name);
    bool add(GameItemType item);
    void remove(GameItemType type);
    bool remove(const int index);
    GameItemType getSelected();
    void draw(gcn::Graphics* graphics) override;
    void mouseReleased(gcn::MouseEvent& mouseEvent) override;
    void keyReleased(gcn::KeyEvent& keyEvent) override;

private:
    static const int SIZE = 6; //!< number of slots available
    bool inGame;
    GameItemType items[SIZE]{GameItemType::NONE_1, GameItemType::NONE_1, GameItemType::NONE_1, GameItemType::NONE_1, GameItemType::NONE_1, GameItemType::NONE_1};
    GameItemType current{ GameItemType::NONE_1 };
    std::map<GameItemType, gcn::Image*> images;
};

#endif // !_H_ITEMBOX_

