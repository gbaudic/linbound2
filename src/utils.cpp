/**
 *  \file utils.cpp
 *  \brief Utility functions
 *  \author G. B.
 *  \date /11/2016
 *  \version 0.1a
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. 
 * If a copy of the MPL was not distributed with this file, 
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This Source Code Form is “Incompatible With Secondary Licenses”, 
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include <cstdlib>
#include <cmath>
#include <string>
#include <SDL2/SDL.h>
#include "utils.hpp"

using namespace std;

namespace linbound {

    /**
    * Makes an angle between 0 and 360 degrees
    * \param angle the angle to normalize, in degrees
    * \return a value between 0 and 359 degrees
    */
    Sint16 normalizeAngle(Sint16 angle){
        while(angle < 0)
            angle += 360;
            
        return angle % 360;
    }

    /**
    *  Implementation of Pythagorean theorem
    *  Required for damage computation
    */
    double getDistance(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2) {
        return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    }

    /**
    * Implements a conversion to get same angle notation as in GunBound
    * Required to make transition easier for players
    * \param angle the angle in degree
    * \returns a normalized value with 0 <= abs(angle) <= 90, 0 is horizontal, pointing downwards is negative
    */
    Sint16 getShotAngle(Sint16 angle) {
        angle = normalizeAngle(angle); //[0; 360)
        angle -= 180; //[-180; 180)

        if(angle > 90){
            return 90 - (angle - 90);
        } else {
            if(angle < -90) {
                return -90 - (90 + angle);
            } else {
                return angle;
            }
        }

    }

    /**
    * Determine if mirroring is needed
    * \param angle the angle in degree
    */
    bool flip(Sint16 angle){
        angle = normalizeAngle(angle) - 180;
        return abs(angle) > 90;
    }

    /**
    *  User-friendly version display
    */
    string getVersionString(){
        string result = to_string(MAJOR_VERSION);
        result += "." + to_string(MINOR_VERSION);
        result += "." + to_string(PATCH_VERSION);
        return result;
    }

    /**
    *  Version number to compare compatibilities
    */
    int getVersion(){
        return PATCH_VERSION + MINOR_VERSION*10 + MAJOR_VERSION*1000;
    }

    /**
    *  User-friendly IP address display for server choice
    *  \param address the Uint32 containing the address, using system endianness
    *  \return an IPv4 in the usual form x.y.z.a
    */
    string prettifyIP(Uint32 address){
        int ip32 = (address >> 24) & 0xff;
        int ip24 = (address >> 16) & 0xff;
        int ip16 = (address >> 8) & 0xff;
        int ip8 = address & 0xff;
        
        return to_string(ip32)+"."+to_string(ip24)+"."+to_string(ip16)+"."+to_string(ip8);
    }

	/**
	*  Helper function to insert widgets centered w.r.t. a parent
	*  \param source widget to insert
	*  \param destination parent to insert to
	*/
	void addCenteredWidget(gcn::Widget * source, gcn::Container * destination)
	{
		int x = (destination->getWidth() - source->getWidth()) / 2;
		int y = (destination->getHeight() - source->getHeight()) / 2;

		destination->add(source, x, y);
	}


}
