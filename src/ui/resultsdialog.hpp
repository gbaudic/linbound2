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
    void setStats(const std::vector<PlayerResult>& matchStats, const int nbTeams);
    virtual void draw(gcn::Graphics* graphics) override;
    void action(const gcn::ActionEvent& actionEvent) override;

private:
    std::vector<PlayerResult> stats;
    int nbTeams = 2;
    gcn::Button btn_ok{ "OK" };

    // Predefined colors for convenience
    gcn::Color text{ 0xff, 0xff, 0xff };
    gcn::Color xp{ 0xff, 0xff, 0 };
    gcn::Color negative_xp{ 0xff, 0, 0 };

    gcn::Color a_color{ 0xb5, 0x3d, 0x3d }; // red
    gcn::Color b_color{ 0x3d, 0x75, 0xb5 }; // blue
    gcn::Color c_color{ 0x3d, 0xb5, 0x41 }; // green
    gcn::Color d_color{ 0xb5, 0xb3, 0x3d }; // yellow

    void addWidgets();
};

#endif // !_H_RESULTSDIALOG_
