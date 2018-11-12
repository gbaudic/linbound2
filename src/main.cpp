#include <iostream>

#include "config.hpp"
#include "utils.hpp"

using namespace std;

/**
 * Minimalistic main function
 */
int main(int argc, char* argv[]) {
	return 0;
}

void usage() {
    cout << "Linbound v" << linbound::getVersionString() << endl
         << "(C) 2007-2018 G. Baudic" << endl;
    return;
}
