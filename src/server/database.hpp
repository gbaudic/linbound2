/**
 * \file database.hpp
 * \brief Database-related functions for the server
 * \author G. B.
 * \version 0.1a
 * \date 30/03/2020
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_DATABASE_
#define _H_DATABASE_

#include <string>
#include <sqlite3.h>
#include "../common/commonitem.hpp"
#include "../common/commonplayer.hpp"

class Database {
public:
    Database();
    ~Database();
    int createUser(const std::string &name, const std::string &password);
    int connectUser(const std::string &name, const std::string &password);
    int updateUser(const std::string &name, const int goldDelta, const int gpDelta = 0);
    int buyItem(const std::string& name, const int itemCode, ItemType type, ItemValidity validity);
    int wearItem(const std::string& name, const int itemCode, ItemType type, bool wear);
    int deleteItem(const std::string& name, const int itemCode);
    PlayerBasicInfo getUserInfo(const std::string& name);

private:
    void init();

    sqlite3* db = nullptr;  // database object
};

#endif //! _H_DATABASE
