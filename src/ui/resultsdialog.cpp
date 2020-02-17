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
 */
void ResultsDialog::setStats(const std::vector<PlayerStats>& matchStats) {
    stats = matchStats;
    addWidgets();
    setVisible(true);
}

void ResultsDialog::draw(gcn::Graphics* graphics) {
    // TBD
}

void ResultsDialog::action(const gcn::ActionEvent& actionEvent) {
    if (actionEvent.getId() == "ok") {
        setVisible(false);
        generateAction();
    }
}

void ResultsDialog::addWidgets() {
    add(&btn_ok, getWidth() - 10 - btn_ok.getWidth(), getHeight() - 10 - btn_ok.getHeight());
}
