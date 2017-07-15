//
//  Player.h
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "Actor.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(Player, spPlayer);
class Player: public Actor
{
public:
    Player(float width, float height);
    void setName(const string &name) {_name = name;}
    void setDive(const bool &dive) {_dive = dive;}
    void looseLife(const int &value) {_life = value > _life ? 0 : _life - value;}
    void move(float x, float y, const string &direction);
    
    string getName() {return _name;}
    bool isDiving() {return _dive;}
    int getLife() {return _life;}
    int getZone(float sW, float sH);
    void hide();
    void show();
    
protected:
    void _init();
    spSprite _ship;
    string _name;
    bool _dive;
    int _life;
};
