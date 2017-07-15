//
//  Game.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <vector>
#include "Game.h"
#include "res.h"
#include "sio_message.h"
#include "ClientSocket.h"

Game::Game()
{
    _status = "waiting";
    _listMine.clear();
    
    ClientSocket::Instance().socket()->on("create", std::bind(&Game::OnCreate,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("join-prepare", std::bind(&Game::OnJoin,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("join-opponent", std::bind(&Game::OnJoinOpponent,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("leave-opponent", std::bind(&Game::OnLeaveOpponent,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("ready-opponent", std::bind(&Game::OnReadyOpponent,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("start", std::bind(&Game::OnStart,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("move", std::bind(&Game::OnMove,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("radar", std::bind(&Game::OnRadar,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("mine", std::bind(&Game::OnMine,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("hit", std::bind(&Game::OnHit,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    ClientSocket::Instance().socket()->on("win", std::bind(&Game::OnWin,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4));
    
    core::getDispatcher()->addEventListener(core::EVENT_SYSTEM, CLOSURE(this, &Game::onSDLEvent));

}


Game::~Game()
{
    
}

void Game::init()
{
    //scene layer would have size of display
    setSize(getStage()->getSize());
    
    //create background
    _sea = new Sprite;
    _sea->setName("sea");
    _sea->setResAnim(res::ui.getResAnim("map"));
    _sea->attachTo(this);
    _sea->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Game::onEvent));
    
    _moveControl = new MoveControl(_sea->getWidth(), getStage()->getHeight() - _sea->getHeight());
    _moveControl->attachTo(this);
    _moveControl->setX(0);
    _moveControl->setY(getStage()->getHeight() - _moveControl->getHeight()/2);
    
    
    _infoBox = new InfoBox(getStage()->getWidth() - _sea->getWidth(), 300);
    _infoBox->attachTo(this);
    _infoBox->setX(_sea->getWidth());
    _infoBox->setY(0);
    
    _powerControl = new PowerControl(getStage()->getWidth() - _sea->getWidth(), getStage()->getHeight() - _moveControl->getHeight() - _infoBox->getHeight());
    _powerControl->attachTo(this);
    _powerControl->setX(_sea->getWidth());
    _powerControl->setY(_infoBox->getHeight());
    
    _powerAction = initActor(new MyButton,
                             arg_name="power",
                             arg_resAnim= res::ui.getResAnim("buttons")->getFrame(0, 3),
                             arg_attachTo=this);
    _powerAction->setX(_moveControl->getWidth() + 10);
    _powerAction->setY(getStage()->getHeight() - _moveControl->getHeight() + 10);
    _powerAction->setText("POWER");
    _powerAction->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Game::onEvent));

    _moveAction = initActor(new MyButton,
                             arg_name="move",
                             arg_resAnim= res::ui.getResAnim("buttons")->getFrame(0, 3),
                             arg_attachTo=this);
    _moveAction->setX(_moveControl->getWidth() + 20 + _moveAction->getWidth());
    _moveAction->setY(getStage()->getHeight() - _moveControl->getHeight() + 10);
    _moveAction->setText("MOVE");
    _moveAction->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Game::onEvent));

    _player = new Player(_sea->getWidth()/15, _sea->getHeight()/15);
    _player->attachTo(this);
    
    _opponent = new Player(_sea->getWidth()/15, _sea->getHeight()/15);
    _opponent->attachTo(this);
}

void Game::onEvent(Event* ev)
{
    string name = ev->target->getName();
    std::cout << "name click; " << name << endl;
    if (ev->type == TouchEvent::CLICK)
    {
        if (name.compare("sea") == 0) {
            Vector2 pos = ((TouchEvent*)ev)->position;
            int x = pos.x / _sea->getWidth() * 15;
            int y = pos.y / _sea->getHeight() * 15;
            std::cout << "pos x: " << x << " y: " << y << std::endl;
            
            _infoBox->addText("pos x: " + std::to_string(x)  + " y: " + std::to_string(y));
            
            if (_status.compare("prepare") == 0 && checkValidity(x,y) == true) {
                _player->setX((x + 0.5) * _sea->getWidth() / 15);
                _player->setY((y + 0.5) * _sea->getHeight() / 15);
                _player->show();
                _status = "ready";
                
                sio::message::ptr binObj = sio::object_message::create();
                binObj->get_map()["x"] = sio::int_message::create(x);
                binObj->get_map()["y"] = sio::int_message::create(y);
                ClientSocket::Instance().socket()->emit("ready", binObj);
            }
        }
        else if (name.compare("move") == 0) {
            move();
        }
        else if (name.compare("power") == 0) {
            power();
        }
        
    }
}

bool Game::checkValidity(int x, int y) {
    return true;
}

void Game::move() {
    std::cout << "here" << endl;
    if (_status.compare("move") == 0 && _powerControl->isValid() && _moveControl->isValid()) {
        string powerUp = _powerControl->getLastClicked();
        string moveDirection = _moveControl->getLastClicked();
        
        int y = _player->getY()/ _sea->getHeight() * 15;
        int x = _player->getX()/ _sea->getWidth() * 15;
        int newX, newY;
        
        
        std::cout << powerUp << " WPOER" << endl;
        sio::message::ptr binObj = sio::string_message::create(moveDirection);

        if (moveDirection.compare("UP") == 0 && y > 0) {
            newY = (y - 1 + 0.5) * _sea->getHeight() / 15;
            newX = (x + 0.5) * _sea->getWidth() / 15;
            _player->move(newX, newY, "UP");
            _powerControl->addValue(powerUp);
            ClientSocket::Instance().socket()->emit("move", binObj);
            checkMine(x, y-1);
        }
        else if (moveDirection.compare("DOWN") == 0 && y < 14) {
            
            newY = (y + 1 + 0.5) * _sea->getHeight() / 15;
            newX = (x + 0.5) * _sea->getWidth() / 15;
            _player->move(newX, newY, "DOWN");
            _powerControl->addValue(powerUp);
            ClientSocket::Instance().socket()->emit("move", binObj);
            checkMine(x, y+1);
        }
        else if (moveDirection.compare("LEFT") == 0 && x > 0) {
            
            newY = (y + 0.5) * _sea->getHeight() / 15;
            newX = (x - 1 + 0.5) * _sea->getWidth() / 15;
            _player->move(newX, newY, "LEFT");
            _powerControl->addValue(powerUp);
            ClientSocket::Instance().socket()->emit("move", binObj);
            checkMine(x-1, y);
        }
        else if (moveDirection.compare("RIGHT") == 0 && x < 14) {
            
            newY = (y + 0.5) * _sea->getHeight() / 15;
            newX = (x + 1 + 0.5) * _sea->getWidth() / 15;
            _player->move(newX, newY, "RIGHT");
            _powerControl->addValue(powerUp);
            ClientSocket::Instance().socket()->emit("move", binObj);
            checkMine(x+1, y);
        }
    }
}

void Game::power() {
    string power = _powerControl->getLastClicked();
    if(_powerControl->isValid() && _powerControl->usePower(power)) {
        if (power.compare("RADAR") == 0) {
            _opponent->show();
            //boost::thread thr(boost::bind(, this));
            boost::thread* thr = new boost::thread(&Game::hideOpponent, this);
            ClientSocket::Instance().socket()->emit("radar");
        }
        if (power.compare("MINE") == 0) {
            int y = _player->getY()/ _sea->getHeight() * 15;
            int x = _player->getX()/ _sea->getWidth() * 15;
            sio::message::ptr binObj = sio::object_message::create();
            binObj->get_map()["x"] = sio::int_message::create(x);
            binObj->get_map()["y"] = sio::int_message::create(y);
            ClientSocket::Instance().socket()->emit("mine", binObj);
        }
    }
}

void Game::hideOpponent() {
    SDL_Delay(5000);
    _opponent->hide();
}

void Game::checkMine(int x, int y) {
    int res = -1;
    int idx = -1;
    for(Vector2 vec : _listMine) {
        idx++;
        if(vec.x == x && vec.y == y) {
            res = idx;
            _player->looseLife(1);
            int life = _player->getLife();
            if(life > 0) {
                _infoBox->addText("YOU HIT A MINE ! Life: " + std::to_string(life));
                ClientSocket::Instance().socket()->emit("hit");
            }
            if(_player->getLife() == 0) {
                _infoBox->addText("Game Over... you Loose");
                ClientSocket::Instance().socket()->emit("die");
                _status="waiting";
            }
            break;
        }
    }
    if(res > -1) {
        _listMine.erase(_listMine.begin() + res);
    }
}


void Game::OnCreate(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
{
    string user = data->get_map()["username"]->get_string();
    string server = data->get_map()["serverID"]->get_string();
    
    _player->setName(user);
    _serverID = server;
    
    _infoBox->addTexts({
        "server [" + _serverID + "] created by: " + _player->getName(),
        "waiting for opponent..."
    });
}

void Game::OnJoin(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
{
    string user = data->get_map()["username"]->get_string();
    string opponent = data->get_map()["opponent"]->get_string();
    string server = data->get_map()["serverID"]->get_string();
    
    _player->setName(user);
    _serverID = server;
    _opponent->setName(opponent);
    _status = "prepare";
    _infoBox->addTexts({
        "user: " + _player->getName() + " join server [" + _serverID + "] created by: " + _opponent->getName(),
        "POSITION YOUR SHIP"
    });
}

void Game::OnJoinOpponent(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
{
    string opponent = data->get_map()["opponent"]->get_string();
    _opponent->setName(opponent);
    _status = "prepare";
    
    _infoBox->addTexts({
        "opponent: " + _opponent->getName() + " join server [ " + _serverID + "] !",
        "POSITION YOUR SHIP"
    });
}

void Game::OnLeaveOpponent(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
{
    string opponent = data->get_map()["opponent"]->get_string();

    _infoBox->addTexts({
        "opponent: " + _opponent->getName() + " leave the server...",
        "waiting for opponent..."
    });
    _status = "ready";
}

void Game::OnReadyOpponent(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
{
    int x = int(data->get_map()["x"]->get_int());
    int y = int(data->get_map()["y"]->get_int());
    _opponent->setPosition((x + 0.5) * _sea->getWidth() / 15, (y + 0.5) * _sea->getHeight() / 15);
    
    std:: cout << "position opponent : " + std::to_string(x) + " - " + std::to_string(y) << endl;

    _infoBox->addText("opponent: " + _opponent->getName() + " READY !");
}

void Game::OnStart(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
{
    _status = "move";
    
    _infoBox->addText("GAME START");
}

void Game::OnMove(string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp)
{

    string direction = data->get_string();
    int y = _opponent->getY()/ _sea->getHeight() * 15;
    int x = _opponent->getX()/ _sea->getWidth() * 15;
    int newX, newY;
    if (direction.compare("UP") == 0) {
        newY = (y - 1 + 0.5) * _sea->getHeight() / 15;
        newX = (x + 0.5) * _sea->getWidth() / 15;
        _opponent->move(newX, newY, "UP");
    }
    else if (direction.compare("DOWN") == 0) {
        newY = (y + 1 + 0.5) * _sea->getHeight() / 15;
        newX = (x + 0.5) * _sea->getWidth() / 15;
        _opponent->move(newX, newY, "DOWN");
    }
    else if (direction.compare("LEFT") == 0) {
        newY = (y + 0.5) * _sea->getHeight() / 15;
        newX = (x - 1 + 0.5) * _sea->getWidth() / 15;
        _opponent->move(newX, newY, "LEFT");
    }
    else if (direction.compare("RIGHT") == 0) {
        newY = (y + 0.5) * _sea->getHeight() / 15;
        newX = (x + 1 + 0.5) * _sea->getWidth() / 15;
        _opponent->move(newX, newY, "RIGHT");
    }
    
    _infoBox->addText(_opponent->getName() + " move: " + direction);
}

void Game::OnRadar(const string &name, const sio::message::ptr &data, bool isAck, sio::message::list &ack_resp) {
    _infoBox->addText("POWER: " + _opponent->getName() + " use RADAR");
}

void Game::OnMine(const string &name, const sio::message::ptr &data, bool isAck, sio::message::list &ack_resp) {
    _infoBox->addText("POWER: " + _opponent->getName() + " use MINE");
    int x = int(data->get_map()["x"]->get_int());
    int y = int(data->get_map()["y"]->get_int());
    _listMine.push_back(Vector2(x,y));
}

void Game::OnHit(const string &name, const sio::message::ptr &data, bool isAck, sio::message::list &ack_resp) {
    _infoBox->addText("HIT: " + _opponent->getName() + " get dammage !");
}

void Game::OnWin(const string &name, const sio::message::ptr &data, bool isAck, sio::message::list &ack_resp) {
    _infoBox->addText(_opponent->getName() + "is dead. YOU WIN !");
}


int Game::onSDLEvent(Event* ev)
{
    SDL_Event *event = (SDL_Event*)ev->userData;

    switch(event->type)
    {
        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_LEFT)
                _moveControl->setDirection("LEFT");
            else if(event->key.keysym.sym == SDLK_RIGHT)
                _moveControl->setDirection("RIGHT");
            else if(event->key.keysym.sym == SDLK_UP)
                _moveControl->setDirection("UP");
            else if(event->key.keysym.sym == SDLK_DOWN)
                _moveControl->setDirection("DOWN");
            else if(event->key.keysym.sym == SDLK_m)
                _powerControl->setPower("MINE");
            else if(event->key.keysym.sym == SDLK_r)
                _powerControl->setPower("RADAR");
            else if(event->key.keysym.sym == SDLK_s)
                _powerControl->setPower("SILENCE");
            else if(event->key.keysym.sym == SDLK_SPACE)
                move();
            else if(event->key.keysym.sym == SDLK_p)
                power();
            break;
        default:
            break;
    }
    return 0;
}
