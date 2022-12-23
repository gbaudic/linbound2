/**
 * \file network.cpp
 * \brief Network-related functions and initializations
 * \author G. B.
 * \version 0.1a
 * \date 19/02/2019
 */
/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is "Incompatible With Secondary Licenses",
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "network.hpp"
#include "protocol.hpp"
#include "utils.hpp"
using namespace std;

/**
 * Constructor
 * \param isServer indicate if we are on the server side
 */
NetworkManager::NetworkManager(bool isServer) {
    int init = SDLNet_Init();
    
    if (init == 0) {
        socket = SDLNet_UDP_Open(isServer ? SERVER_PORT : 0); // pick the pork you want
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "NetworkManager init error: %s", SDLNet_GetError());
    }

    serverInfo.host = INADDR_ANY;
    serverInfo.port = 0;
}

/**
 * Destructor
 */
NetworkManager::~NetworkManager() {
    // Clean up packets
    for(UDPpacket *p : packets) {
        SDLNet_FreePacket(p);
    }
    packets.clear();
    
    // Close library
    SDLNet_UDP_Close(socket);
    
    SDLNet_Quit();
}

/**
 * \brief Send a packet
 * \param code packet type
 * \param message message to send, as a string
 * \param target address to which the packet should be sent
 * \see protocol.hpp
 */
void NetworkManager::send(Uint8 code, const string & message, const IPaddress & target) {
    int dataSize = static_cast<int>(message.size()) + 1 + 1;
    UDPpacket *packet = SDLNet_AllocPacket(dataSize);
    
    packet->len = dataSize;
    packet->address = target;
    packet->data[0] = code;
    strncpy((char*)packet->data+1, message.c_str(), message.size() + 1);
    
    SDLNet_UDP_Send(socket, -1, packet);
    
    SDLNet_FreePacket(packet);
}

/**
 * \brief Convenience function to send message to server
 * \param code packet type
 * \param message message to send
 */
void NetworkManager::sendToServer(Uint8 code, const std::string& message) {
    send(code, message, serverInfo);
}

/**
 * \brief Receive all packets currently awaiting processing
 * \return an ordered list of the received packets on the client socket
 */
vector<UDPpacket*> & NetworkManager::receive() {
    // Cleanly remove the previously allocated packets, if any
    for(UDPpacket *p : packets) {
        SDLNet_FreePacket(p);
    }
    packets.clear();
    
    UDPpacket *packet = SDLNet_AllocPacket(1024);
    
    int nbRecv = SDLNet_UDP_Recv(socket, packet);
    while(nbRecv == 1) {
        packets.push_back(packet);
        
        packet = SDLNet_AllocPacket(1024);
        nbRecv = SDLNet_UDP_Recv(socket, packet);
    }
    
    SDLNet_FreePacket(packet); // the last allocated one is empty
    
    return packets;
}

/**
 * Inform the server we are leaving
 */
void NetworkManager::logout() {
    sendToServer(LOGOUT_MSG, "goodbye");
}

/**
 * Save server info for future use once chosen by the user
 * \param ip server IPv4, in machine byte order
 */
void NetworkManager::setServerInfo(Uint32 ip) {
    SDLNet_Write32(ip, &serverInfo.host);
    SDLNet_Write16(SERVER_PORT, &serverInfo.port);
}

/**
 * Extract message code from a packet
 * \param p packet to handle
 * \return code for the packet
 */
Uint8 NetworkManager::getCode(const UDPpacket *p) {
    return p->data[0];
}

/**
 * Extract payload from a packet
 * \param p packet to handle
 * \return payload
 */
string NetworkManager::getMessage(const UDPpacket *p) {
    string message(reinterpret_cast<char*>(p->data+1));
    return message;
}

/**
 * Extract address from a packet
 * Useful for server to know who to reply to
 * \param p packet to handle
 * \return address to use
 */
IPaddress NetworkManager::getAddress(const UDPpacket* p){
    return p->address;
}

/**
 * \brief Determine if a given message type should exist
 * \param code message type
 * \param location player location on server
 * \param isPlaying if in a room, is the room playing (defaults to false)
 * \return true if message should exist at this point, false otherwise
 */
bool NetworkManager::isExpected(Uint8 code, PlayerLocationType location, bool isPlaying) {
    bool result = false;

    switch (location) {
    case PlayerLocationType::DISCONNECTED:
        result = code == HELLO_MSG || code == CREATE_MSG || code == LOGIN_MSG;
        break;
    case PlayerLocationType::SERVER:
        result = code >= 200 || code == SELL_ITEM_MSG || code == BUY_ITEM_MSG || 
            code == ENTER_ROOM_MSG || code == CREATE_ROOM_MSG || code == FRIEND_ADD || code == FRIEND_DEL;
        break;
    case PlayerLocationType::ROOM:
        result = (code >= 51 && code <= 60) || (code >= 99 && code < 110);
        if (isPlaying) {
            result = result || (code >= 110 && code <= 150);
        } else {
            result = result || code == KICK_MSG;
        }
        break;
    default: 
        break;
    }
    
    return result;
}


