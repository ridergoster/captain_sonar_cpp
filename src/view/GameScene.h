//
//  GameScene.h
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "Scene.h"
#include "Game.h"

DECLARE_SMART(GameScene, spGameScene);
class GameScene: public Scene
{
public:
    static spGameScene instance;
    GameScene();

private:
    void _show();
    void onEvent(Event* ev);
    spGame _game;
};
