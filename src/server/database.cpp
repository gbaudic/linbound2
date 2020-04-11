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
    int result = sqlite3_open_v2(db_path.c_str(), &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);

    if (result) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Cannot open db file: %s", sqlite3_errmsg(db));
    } else {
        init();
    }
}

/**
 * Destructor
 */
Database::~Database(){
    sqlite3_close(db);
}

/**
 * \brief Create a new user
 * \param name name for the user
 * \param password password for the user
 * \return 0 if success, -1 if name already taken, -2 for other errors
 */
int Database::createUser(const std::string& name, const std::string& password) {
    sqlite3_stmt* stmt = nullptr;
    int code = -2;

    int result = sqlite3_prepare_v2(db, "insert into USERS (name, password) values (:name, :password)", -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        return -2;
    }

    // Bind values
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":name"), name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":password"), password.c_str(), -1, SQLITE_STATIC);

    // Run query
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        if (result == SQLITE_CONSTRAINT) {
            // Must be the uniqueness of name which failed
            code = -1;
        } else {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
            code = -2;
        }
    } else {
        // Success
        code = 0;
    }
    
    sqlite3_finalize(stmt);
    return code;
}

/**
 * \brief Try to connect an existing user
 * \param name name for the user
 * \param password provided password for the user, cleartext for the moment
 * \return 0 if success, 1 wrong password, 2 unknown login. Other errors are not computed here. 
 */
int Database::connectUser(const std::string& name, const std::string& password) {
    sqlite3_stmt* stmt = nullptr;
    bool found = false;
    int code = -1;

    int result = sqlite3_prepare_v2(db, "select name, password from USERS where name = :name", -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        return code;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        found = true;
        const char* pass = (const char*)sqlite3_column_text(stmt, 1);
        // Czech password
        code = password == string(pass) ? 0 : 1;
    }

    if (!found) {
        // Login not found
        code = 2;
    }
    
    sqlite3_finalize(stmt);
    return code;
}

/**
 * \brief Update user data
 * \param name name for the user
 * \param goldDelta gold to add/remove from balance
 * \param gpDelta gp to add/remove. Defaults to 0. 
 * \return 0 if success, -1 on error
 */
int Database::updateUser(const std::string& name, const int goldDelta, const int gpDelta) {
    sqlite3_stmt* stmt = nullptr;
    // Prepare statement
    int result = sqlite3_prepare_v2(db, "update USERS set gold = max(0, gold + :gold), gp = max(0, gp + :gp) where name = :name",
        -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        return -1;
    }

    // Bind values
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, ":gold"), goldDelta);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, ":gp"), gpDelta);
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":name"), name.c_str(), -1, SQLITE_STATIC);
    
    // Run query
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    // Cleanup time
    sqlite3_finalize(stmt);
    return 0;
}

/**
 * \brief Act the purchase of an item
 * \param name name for the user
 * \param itemCode index for this item
 * \param validity length of purchase
 * \return 0 if success, -1 if unsufficient funds, -2 if item already owned
 */
int Database::buyItem(const std::string& name, const int itemCode, ItemType type, ItemValidity validity) {
    sqlite3_stmt* stmt = nullptr;
    int code = -2;

    int result = sqlite3_prepare_v2(db, "insert into PURCHASES (user, item, type, end_date) values (:name, :item, :type, date('now',:delta))", -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        return -2;
    }

    // Bind values
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":name"), name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, ":item"), itemCode);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, ":type"), static_cast<int>(type));

    std::string duration = "+1";
    switch (validity) {
    case ItemValidity::ONE_DAY:
        duration += " day";
        break;
    case ItemValidity::ONE_MONTH:
        duration += " month";
        break;
    case ItemValidity::ONE_WEEK:
        duration = "+7 days";
        break;
    case ItemValidity::ONE_YEAR:
        duration += " year";
        break;
    case ItemValidity::LIMITLESS:
        duration += "00 years";
        break;
    default:
        break;
    }
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":delta"), duration.c_str(), -1, SQLITE_STATIC);

    // Run query
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        code = -2;
    } else {
        // Success
        code = 0;
    }

    sqlite3_finalize(stmt);
    return code;
}

/**
 * \brief Toggle status of an item
 * \param name name for the user
 * \param itemCode index for this item
 * \param wear true to use, false to remove
 */
int Database::wearItem(const std::string& name, const int itemCode, ItemType type, bool wear) {
    sqlite3_stmt* stmt = nullptr;
    int code = -2;

    // Create statement: first reinit all items from this type, then set chosen item
    int result = sqlite3_prepare_v2(db, "update PURCHASES set is_worn = 0 where user = :name and type = :type; " \
        "update PURCHASES set is_worn = :worn where user = :name and item = :item;", -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        return -2;
    }

    // Bind values
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":name"), name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, ":item"), itemCode);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, ":type"), static_cast<int>(type));
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, ":worn"), wear ? 1 : 0);

    // Run query
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        code = -2;
    } else {
        // Success
        code = 0;
    }

    sqlite3_finalize(stmt);
    return code;
}

/**
 * \brief Remove an item
 * \param name name for the user
 * \param itemCode index for this item
 * \return 0 if success, -1 if user does not exist, -2 if item not found for this user
 */
int Database::deleteItem(const std::string& name, const int itemCode) {
    sqlite3_stmt* stmt = nullptr;
    int code = -2;

    // Create statement: first reinit all items from this type, then set chosen item
    int result = sqlite3_prepare_v2(db, "delete PURCHASES where user = :name and item = :item", -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        return -2;
    }

    // Bind values
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, ":name"), name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, ":item"), itemCode);

    // Run query
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", sqlite3_errmsg(db));
        code = -2;
    } else {
        // Success
        code = 0;
    }

    sqlite3_finalize(stmt);
    return code;;
}

/**
 * Initialize a newly created db file by creating tables in it
 */
void Database::init() {
    char* zErrMsg = nullptr;

    // Users
    std::string sql = "CREATE TABLE IF NOT EXISTS USERS(" \
        "id integer primary key autoincrement, " \
        "name text unique not null, " \
        "password text, " \
        "gold int default 0, " \
        "cash int default 0, " \
        "gp int default 1000, " \
        "level int, " \
        "country text);";

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
        "item int not null, " \
        "type int not null, " \
        "end_date text not null, " \
        "is_worn int default 0);";

    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}


