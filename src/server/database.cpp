/**
 * \file database.cpp
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

#include <SDL2/SDL.h>
#include "database.hpp"
#include "../config.hpp"
using namespace std;

/**
 * Constructor
 */
Database::Database() {
    string db_path = DB_PREFIX + "linbound.db";
    int result = sqlite3_open(db_path.c_str(), &db);

    if (result) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot open db file: %s", sqlite3_errmsg(db));
    }
}

/**
 * Destructor
 */
Database::~Database(){
    sqlite3_close(db);
}

int Database::createUser(const std::string& name, const std::string& password) {
    // TBD
    return 0;
}

int Database::connectUser(const std::string& name, const std::string& password) {
    // TBD
    return 0;
}

int Database::updateUser(const std::string& name, const std::string& field, const int value) {
    // TBD
    return 0;
}

int Database::buyItem(const std::string& name, const int itemCode, ItemValidity validity) {
    // TBD
    return 0;
}

/**
 * Initialize a newly created db file by creating tables in it
 */
void Database::init() {
    char* zErrMsg = nullptr;

    // Users
    std::string sql = "CREATE TABLE IF NOT EXISTS USERS(" \
        "id integer primary key autoincrement, " \
        "name text not null, " \
        "password text, " \
        "gold int, " \
        "cash int, " \
        "gp int);";

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // Item purchases
    sql = "CREATE TABLE IF NOT EXISTS PURCHASES(" \
        "id integer primary key autoincrement, " \
        "user text not null, " \
        "item int not null," \
        "end_date text not null);";

    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}


