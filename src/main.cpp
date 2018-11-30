/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <iostream>

#include "main.hpp"
#include "config.hpp"
#include "settings.hpp"
#include "utils.hpp"

using namespace std;

/**
 * Minimalistic main function
 */
int main(int argc, char* argv[]) {
    if(argc > 1) {
        usage();
    }
    
	return 0;
}

void usage() {
    cout << "Linbound v" << linbound::getVersionString() << endl
         << "(C) 2007-2018 G. Baudic" << endl;
    return;
}
