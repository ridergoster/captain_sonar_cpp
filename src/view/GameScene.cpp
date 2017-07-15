//
//  GameScene.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include <stdio.h>
#include "GameScene.h"
#include "res.h"
#include "Game.h"

spGameScene GameScene::instance;

GameScene::GameScene()
{
    //create game actor
    _game = new Game;
    _game->init();
    _game->attachTo(_view);
    
}

void GameScene::_show()
{
    //ControlScene::instance->show();
}

void GameScene::onEvent(Event* ev)
{
    if (ev->type == TouchEvent::CLICK)
    {
        //menu button clicked
        //pause game by pausing it's clock
        _game->getClock()->pause();
        
        //show GameMenu dialog
    }
}
