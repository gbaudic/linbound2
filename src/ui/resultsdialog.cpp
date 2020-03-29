/**
 * \file resultsdialog.cpp
 * \brief Convenience dialog to show results at the end of game
 * \author G. B.
 * \version 0.1a
 * \date 17/02/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* This Source Code Form is "Incompatible With Secondary Licenses",
* as defined by the Mozilla Public License, v. 2.0.
*/

#include <string>
#include "resultsdialog.hpp"
using namespace gcn;

/**
 * \brief Constructor
 */
ResultsDialog::ResultsDialog() : Window("Results") {

    btn_ok.setActionEventId("ok");
    btn_ok.addActionListener(this);

    setVisible(false); // will be shown in due time
}

/**
 * \brief Set the results so we can display them
 * \param matchStats results
 * \param nbTeams number of teams on this match
 */
void ResultsDialog::setStats(const std::vector<PlayerResult>& matchStats, const int nbTeams) {
    stats = matchStats;
    this->nbTeams = nbTeams;

    // We do this here instead of in the constructor 
    // because we need size info we do not have at creation
    addWidgets();
    setVisible(true);
}

/** @copydoc gcn::Widget::draw(Graphics*) */
void ResultsDialog::draw(gcn::Graphics* graphics) {
    // Draw window and button first
    Window::draw(graphics);

    int x = 10;
    int y = 30;
    for (int i = 0; i < stats.size(); i++) {
        // Prepare to fill second column if necessary
        if (i == stats.size() / 2) {
            x += 300;
            y = 30;
        }

        // Draw rectangle
        switch (stats[i].team) {
        case 'A':
            graphics->setColor(a_color);
            break;
        case 'B':
            graphics->setColor(b_color);
            break;
        case 'C':
            graphics->setColor(c_color);
            break;
        case 'D':
            graphics->setColor(d_color);
            break;
        default: break;
        }
        graphics->fillRectangle(gcn::Rectangle(x, y, 300, 50));

        // name
        graphics->setColor(text);
        graphics->drawText(stats[i].name, x + 20, y + 5);

        // gold
        graphics->drawText(std::to_string(stats[i].goldEarned) + "G", x + 100, y + 5);
        
        // xp (red if negative)
        if (stats[i].gpEarned < 0) {
            graphics->setColor(negative_xp);
        }
        graphics->drawText(std::to_string(stats[i].gpEarned) + "GP", x + 125, y + 5);

        // winner?
        if (stats[i].wins) {
            graphics->setColor(text);
            graphics->drawText("WINNER", x + 20, y + 25);
        }

        y += 50;
    }
}

/** @copydoc gcn::ActionListener::action(ActionEvent) */
void ResultsDialog::action(const gcn::ActionEvent& actionEvent) {
    if (actionEvent.getId() == "ok") {
        // Close the window and go back to room lobby
        setVisible(false);
        generateAction();
    }
}

void ResultsDialog::addWidgets() {
    add(&btn_ok, getWidth() - 10 - btn_ok.getWidth(), getHeight() - 10 - btn_ok.getHeight());
}
