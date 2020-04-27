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
 */
NetworkManager::NetworkManager() {
    int init = SDLNet_Init();
    
    if(init == 0) {
        clientSock = SDLNet_UDP_Open(0); // pick the pork you want
    }

	serverInfo.host = INADDR_ANY;
	serverInfo.port = 0;
}

/**
 * Destructor
 */
NetworkManager::~NetworkManager() {
    for(UDPpacket *p : packets) {
        SDLNet_FreePacket(p);
    }
    packets.clear();
    
    SDLNet_UDP_Close(clientSock);
    
    SDLNet_Quit();
}

/**
 * \brief Send a packet to the server
 * \param code packet type
 * \param message message to send, as a string
 * \see protocol.hpp
 */
void NetworkManager::send(Uint8 code, const string & message) {
    int dataSize = static_cast<int>(message.size()) + 1 + 1;
    UDPpacket *packet = SDLNet_AllocPacket(dataSize);
    
    packet->len = dataSize;
    packet->address = serverInfo;
    packet->data[0] = code;
	strncpy((char*)packet->data+1, message.c_str(), message.size() + 1);
    
    SDLNet_UDP_Send(clientSock, -1, packet);
    
    SDLNet_FreePacket(packet);
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
    
    int nbRecv = SDLNet_UDP_Recv(clientSock, packet);
    while(nbRecv == 1) {
        packets.push_back(packet);
        
        packet = SDLNet_AllocPacket(1024);
        nbRecv = SDLNet_UDP_Recv(clientSock, packet);
    }
    
    SDLNet_FreePacket(packet); // the last allocated one is empty
    
    return packets;
}

/**
 * Inform the server we are leaving
 */
void NetworkManager::logout() {
	send(LOGOUT_MSG, "goodbye");
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
