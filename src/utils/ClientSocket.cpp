//
//  ClientSocket.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include "ClientSocket.h"
#include "sio_client.h"

using namespace sio;

client ClientSocket::m_instance;
bool ClientSocket::connected=false;

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
    m_instance.close();
    connected = false;
}

sio::client& ClientSocket::Instance()
{
    if (!connected) {
        m_instance.connect("http://127.0.0.1:3000");
        connected = true;
    }
    return m_instance;
}

