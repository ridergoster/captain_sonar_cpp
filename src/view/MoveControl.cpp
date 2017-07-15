//
//  MoveControl.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include <iostream>
#include "MoveControl.h"
#include "res.h"

MoveControl::MoveControl(float width, float height)
{
    
    this->setSize(width, height);

    _buttonL = initActor(new Sprite,
                                arg_name = "LEFT",
                                arg_resAnim = res::ui.getResAnim("move_left"),
                                arg_anchor = Vector2(0.5f, 0.5f),
                                arg_attachTo = this);
    _buttonL->setX(this->getWidth()/4 - _buttonL->getWidth()*2);
    _buttonL->setY(this->getHeight()/2 - _buttonL->getHeight());
    _buttonL->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MoveControl::onEvent));
    
    
    _buttonR = initActor(new Sprite,
                                arg_name = "RIGHT",
                                arg_resAnim = res::ui.getResAnim("move_right"),
                                arg_anchor = Vector2(0.5f, 0.5f),
                                arg_attachTo = this);
    _buttonR->setX(this->getWidth()/2 - _buttonR->getWidth()*2);
    _buttonR->setY(this->getHeight()/2 - _buttonR->getHeight());
    _buttonR->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MoveControl::onEvent));
    
    
    _buttonU = initActor(new Sprite,
                                 arg_name = "UP",
                                 arg_resAnim = res::ui.getResAnim("move_up"),
                                 arg_anchor = Vector2(0.5f, 0.5f),
                                 arg_attachTo = this);
    _buttonU->setX(this->getWidth()*3/4 - _buttonU->getWidth()*2);
    _buttonU->setY(this->getHeight()/2 - _buttonU->getHeight());
    _buttonU->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MoveControl::onEvent));
    
    _buttonD = initActor(new Sprite,
                                 arg_name = "DOWN",
                                 arg_resAnim = res::ui.getResAnim("move_down"),
                                 arg_anchor = Vector2(0.5f, 0.5f),
                                 arg_attachTo = this);
    _buttonD->setX(this->getWidth() - _buttonD->getWidth()*2);
    _buttonD->setY(this->getHeight()/2 - _buttonD->getHeight());
    _buttonD->addEventListener(TouchEvent::CLICK, CLOSURE(this, &MoveControl::onEvent));
    
    updateFrame();
}

bool MoveControl::isValid() {
    if (_lastClicked.compare("UP") == 0 ||
        _lastClicked.compare("DOWN") == 0 ||
        _lastClicked.compare("LEFT") == 0 ||
        _lastClicked.compare("RIGHT") == 0) {
        return true;
    }
    return false;
}

void MoveControl::updateFrame() {
    
    _buttonU->addTween(Sprite::TweenAnim(res::ui.getResAnim("move_up")), 10);
    _buttonD->addTween(Sprite::TweenAnim(res::ui.getResAnim("move_down")), 10);
    _buttonL->addTween(Sprite::TweenAnim(res::ui.getResAnim("move_left")), 10);
    _buttonR->addTween(Sprite::TweenAnim(res::ui.getResAnim("move_right")), 10);
    
    if (_lastClicked.compare("UP") == 0) {
        _buttonU->addTween(Sprite::TweenAnim(res::ui.getResAnim("move_up_select")), 10);
    }
    else if (_lastClicked.compare("DOWN") == 0) {
        _buttonD->addTween(Sprite::TweenAnim(res::ui.getResAnim("move_down_select")), 10);
    }
    else if (_lastClicked.compare("LEFT") == 0) {
        _buttonL->addTween(Sprite::TweenAnim(res::ui.getResAnim("move_left_select")), 10);
    }
    else if (_lastClicked.compare("RIGHT") == 0) {
        _buttonR->addTween(Sprite::TweenAnim(res::ui.getResAnim("move_right_select")), 10);
    }
}

void MoveControl::onEvent(Event* ev)
{
    //button clicked
    //remember it's name. It would asked later from GameScene.cpp
    _lastClicked = ev->currentTarget->getName();
    updateFrame();
}

void MoveControl::setDirection(const string &direction)
{
    _lastClicked = direction;
    updateFrame();
}
