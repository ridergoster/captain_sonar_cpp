//
//  Game.h
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "oxygine-framework.h"
#include "Player.h"
#include "MoveControl.h"
#include "InfoBox.h"
#include "sio_message.h"
#include "PowerControl.h"
#include <boost/filesystem.hpp>
#include <vector>

//#include <list>
using namespace oxygine;

//DECLARE_SMART(Player, spPlayer);
//DECLARE_SMART(Joystick, spJoystick);
DECLARE_SMART(Game, spGame);

class Game: public Actor
{
public:
    Game();
    ~Game();
    void init();


protected:
    void onEvent(Event* ev);
    int onSDLEvent(Event *ev);

    void OnCreate(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnJoin(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnJoinOpponent(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnLeaveOpponent(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnReadyOpponent(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnStart(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnMove(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnRadar(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnMine(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnHit(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    void OnWin(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp);
    
    void hideOpponent();
    void checkMine(int x, int y);
    bool checkValidity(int x, int y);
    void move();
    void power();
    
    string _status;
    string _serverID;
    spSprite _sea;
    spPlayer _player;
    spPlayer _opponent;
    spMoveControl _moveControl;
    spInfoBox _infoBox;
    spPowerControl _powerControl;
    spMyButton _powerAction;
    spMyButton _moveAction;
    vector<Vector2> _listMine;
};
