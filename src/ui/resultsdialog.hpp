/**
 * \file resultsdialog.hpp
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

#ifndef _H_RESULTSDIALOG_
#define _H_RESULTSDIALOG_

#include <vector>
#include <guisan.hpp>
#include "../common/commonplayer.hpp"

class ResultsDialog : public gcn::Window, public gcn::ActionListener {
public:
    ResultsDialog();
    void setStats(const std::vector<PlayerStats>& matchStats);
    virtual void draw(gcn::Graphics* graphics) override;
    void action(const gcn::ActionEvent& actionEvent) override;

private:
    std::vector<PlayerStats> stats;
    gcn::Button btn_ok{ "OK" };

    void addWidgets();
};

#endif // !_H_RESULTSDIALOG_
