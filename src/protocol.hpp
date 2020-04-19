/**
 *  \file protocol.hpp
 *  \author G. B.
 *  \brief Protocol defines for the LinBound game
 *  \version 0.1a
 *  \date 30/04/2012
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#ifndef _H_PROTOCOL_
#define _H_PROTOCOL_

/******* Message types *******/
const Uint8 STATUS_INTERNAL = 1; //! Used for server-side errors...
const Uint8 STATUS_OK = 0; //! Like 200 for HTTP
const Uint8 STATUS_BANNED = 2; //! User forbidden for this room or server
const Uint8 STATUS_FORBIDDEN = 3; //! Wrong password
const Uint8 STATUS_NOTFOUND = 4; //! Room or user not found on this server
const Uint8 STATUS_REPEAT = 5; //! Send again
const Uint8 STATUS_DISCONNECTED = 6; //! User not connected
const Uint8 STATUS_INVALID = 7; //! Impossible operation or unknown code
const Uint8 STATUS_PING = 8;
const Uint8 STATUS_PONG = 9;

const Uint8 LOGIN_MSG = 10; //! Server login
const Uint8 LOGOUT_REPLY = 254;
const Uint8 LOGOUT_MSG = 255;
const Uint8 PWD_MSG = 20; //! Password change
const Uint8 CREATE_MSG = 21; //! Account creation

const Uint8 ENTER_ROOM_MSG = 49; //! Try to join an existing room 
const Uint8 CREATE_ROOM_MSG = 50; //! New room
const Uint8 EXIT_ROOM_MSG = 51; //! User-triggered exit
const Uint8 UPDATE_ROOM_MSG = 52;
const Uint8 PLAYER_ROOM_MSG = 58; //! New player arriving, team changes
const Uint8 ADMIN_ROOM_MSG = 59;
const Uint8 ITEMS_ROOM_MSG = 60; //! Request item list / warn of changes from admin

const Uint8 SELL_ITEM_MSG = 80; //! Sell an existing item from inventory
const Uint8 BUY_ITEM_MSG = 81; //! Add a new item to my inventory

const Uint8 SERVER_INFO = 200; //! Basic server info
const Uint8 ROOM0_INFO = 210; //! Basic room info in channel: number, title, type, map used, status
const Uint8 ROOM5_INFO = 215; //! Full room info: size, settings...
const Uint8 USER0_INFO = 220; //! Name, guild, level 
const Uint8 FRIEND_INFO = 221; //! Location for buddies
const Uint8 USER5_INFO = 225; //! Full statistics
const Uint8 ITEM0_INFO = 230; //! The 4 or 5 items worn while playing
const Uint8 ITEM5_INFO = 235; //! Full list of items used while in the "avatar shop"
const Uint8 MOBILE_INFO = 240; //! Choice of mobile(s) for the battle

const Uint8 FRIEND_ADD = 90;
const Uint8 FRIEND_DEL = 91;
const Uint8 KICK_MSG = 95; //! Exclude a user from a room
const Uint8 MUTE_MSG = 99; //! Silence a user
const Uint8 CHAT_MSG = 100; //! Chat message (add the message type to this value to get the final packet type)
const Uint8 TEAM_CHAT_MSG = 101;
const Uint8 ROOM_CHAT_MSG = 102;
const Uint8 ALL_CHAT_MSG = 103;

const Uint8 WEATHER_MSG = 110; //! Hurricane, thunder, mirror, force
const Uint8 WIND_MSG = 111; //! Wind change
const Uint8 EVENT_MSG = 115; //! Game start, double death, sudden death type...
const Uint8 TURN_MSG = 114; //! Your turn to play
const Uint8 REWARD_MSG = 116;
const Uint8 PENALTY_MSG = 117;
const Uint8 SERVER_MSG = 118;
const Uint8 SHOT_MSG = 120; //! Shot coordinates: angle, strength, weapon and item used
const Uint8 SKIP_TURN_MSG = 121;
const Uint8 SWITCH_MOBILE_MSG = 122; //! only used in DUO mode
const Uint8 DMG_MSG = 125; //! Result of a shot: impact on players, on the map...
const Uint8 ITEMS_MSG = 135; //! Item choice when playing (for server consistency checks)
const Uint8 COORDS_MSG = 130; //! Coordinates (for players landing, at the beginning or when respawning, and objects)
const Uint8 DEATH_MSG = 140; //! Announce death of a player to all players
const Uint8 RESPAWN_MSG = 141;
const Uint8 SURPRISE_MSG = 142; //! Fall of unexpected bonuses/maluses
const Uint8 DEPARTURE_MSG = 145; //! A user has left the room 
const Uint8 RESULTS_MSG = 150; //Results of the battle : wins/loses, rewards

const Uint8 LB_PROTOCOL_VERSION = 1; //! Used to denote incompatibilities between versions
const Uint8 HELLO_MSG = 123; //! 1, 2, 3, because it's that easy

#endif /* _H_PROTOCOL_ */
