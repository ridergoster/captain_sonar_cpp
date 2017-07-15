//
//  GameMenu.h
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 12/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "Scene.h"
#include "InputTextHandler.h"
#include "MyButton.h"

DECLARE_SMART(GameMenu, spGameMenu);
class GameMenu: public Scene
{
public:
    static spGameMenu instance;
    
    GameMenu();
    
private:
    void onEvent(Event* ev);
    
    spSprite _bg;
    spSprite _logo;
    
    spMyButton _btnExit;
    spMyButton _btnStart;
    
    spTextField _txtUsername;
    spTextField _txtServerID;
    
    spInputTextHandler _inputUsername;
    spInputTextHandler _inputServerID;
};
