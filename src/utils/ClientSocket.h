//
//  ClientSocket.h

//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "sio_client.h"

class ClientSocket
{
public:
    static sio::client& Instance();

private:
    static sio::client m_instance;
    static bool connected;
    ClientSocket();
    ~ClientSocket();
};
