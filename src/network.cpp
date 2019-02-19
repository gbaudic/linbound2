/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This Source Code Form is “Incompatible With Secondary Licenses”,
 * as defined by the Mozilla Public License, v. 2.0.
 */

#include "network.hpp"
#include "protocol.hpp"
#include "utils.hpp"
using namespace std;

NetworkManager::NetworkManager() {
    int init = SDLNet_Init();
    
    if(init == 0) {
        clientSock = SDLNet_UDP_Open(0); // pick the pork you want
    }
}

NetworkManager::~NetworkManager() {
    SDLNet_UDP_Close(clientSock);
    
    SDLNet_Quit();
}

void NetworkManager::send(Uint8 code, const std::string & message) {
    int dataSize = message.size() + 1;
    UDPpacket *packet = SDLNet_AllocPacket(dataSize);
    
    packet->len = dataSize;
    packet->address = serverInfo;
    packet->data[0] = code;
    packet->data[1] = message.c_str();
    
    SDLNet_UDP_Send(clientSock, -1, packet);
    
    SDLNet_FreePacket(packet);
}

void NetworkManager::receive(Context* currentContext) {
    UDPpacket *packet = SDLNet_AllocPacket(1024);
    
    int nbRecv = SDLNet_UDP_Recv(clientSock, packet);
    while(nbRecv == 1) {
        if(packet->len > 1) {
            Uint8 code = packet->data[0];
            string data(packet->data[1]);
            
            // Based on the code, do something with the packet...
        }
        
        nbRecv = SDLNet_UDP_Recv(clientSock, packet);
    }
    
    SDLNet_FreePacket(packet);
}

/**
 * Save server info for future use once chosen by the user
 * \param ip server IPv4, in machine byte order
 * \param port server port, in machine byte order
 */
void NetworkManager::setServerInfo(Uint32 ip, Uint16 port) {
    SDLNet_Write32(ip, &serverInfo.host);
    SDLNet_Write16(port, &serverInfo.port);
}

/**
 * Send the broadcast message to try to find a server on the local network
 */
void NetworkManager::findServer() {
    string msg = "HELLO";
    IPaddress broadcast;
    broadcast.host = INADDR_BROADCAST;
    SDLNet_Write16(SERVER_PORT, &broadcast.port);
    
    UDPpacket *packet = SDLNet_AllocPacket(5 + 1);
    
    packet->len = 5 + 1;
    packet->address = broadcast;
    packet->data[0] = HELLO_MSG;
    packet->data[1] = msg.c_str();
    
    SDLNet_UDP_Send(clientSock, -1, packet);
    
    SDLNet_FreePacket(packet);
}
