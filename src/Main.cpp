//
//  Main.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 12/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include <stdio.h>
#include "Main.h"
#include "res.h"
#include "GameMenu.h"
#include "GameScene.h"
#include "ClientSocket.h"

void Main_preinit()
{
    // preninit ??
}

//called from main.cpp
void Main_init()
{
    ClientSocket::Instance();
    //load xml file with resources definition
    res::load();
    
    //create all scenes
    GameScene::instance = new GameScene;
    GameMenu::instance = new GameMenu;
    //GameScene::instance = new GameScene;
    
    //show main menu
    GameMenu::instance->show();
}

//called each frame from main.cpp
void Main_update()
{
    // update main app
}

//called each frame from main.cpp
void Main_destroy()
{
    //free previously loaded resources
}
