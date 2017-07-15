//
//  PowerControl.h
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 14/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "MyButton.h"
using namespace oxygine;
using namespace std;

DECLARE_SMART(PowerControl, spPowerControl);
class PowerControl: public Actor
{
public:
    PowerControl(float width, float height);
    const string& getLastClicked() const {return _lastClicked;}
    void setPower(const string &power);
    int getValue(const string &power);
    void addValue(const string &power);
    bool usePower(const string &power);
    bool isValid();
private:
    void onEvent(Event* ev);
    void updateFrame();
    string _lastClicked;

    spMyButton _buttonMine;
    spSprite _spriteMine;
    int _mineValue;
    spMyButton _buttonRadar;
    spSprite _spriteRadar;
    int _radarValue;
    spMyButton _buttonSilence;
    spSprite _spriteSilence;
    int _silenceValue;
};
