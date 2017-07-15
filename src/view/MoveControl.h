//
//  MoveControl.h
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "Actor.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(MoveControl, spMoveControl);
class MoveControl: public Actor
{
public:
    MoveControl(float width, float height);
    const string& getLastClicked() const {return _lastClicked;}
    void setDirection(const string &direction);
    bool isValid();
private:
    void onEvent(Event* ev);
    void updateFrame();
    string _lastClicked;
    spSprite _buttonL;
    spSprite _buttonR;
    spSprite _buttonU;
    spSprite _buttonD;
};
