//
//  Player.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include <iostream>
#include "Player.h"
#include "res.h"

using namespace std;

Player::Player(float width, float height)
{
    this->setSize(width, height);
    
    _ship = new Sprite;
    _ship->setResAnim(res::ui.getResAnim("sub_right"));
    _ship->attachTo(this);
    _ship->setAnchor(Vector2(0.5f, 0.5f));
    
    _life = 3;
    this->hide();
}

void Player::hide() {
    this->addTween(Actor::TweenAlpha(0), 100);
}

void Player::show() {
    this->addTween(Actor::TweenAlpha(255), 100);
}

void Player::move(float x, float y, const string &direction) {
    if (direction.compare("UP") == 0) {
        _ship->addTween(Sprite::TweenAnim(res::ui.getResAnim("sub_up")),50);
    }
    else if (direction.compare("DOWN") == 0) {
        _ship->addTween(Sprite::TweenAnim(res::ui.getResAnim("sub_down")),50);
    }
    else if (direction.compare("LEFT") == 0) {
        _ship->addTween(Sprite::TweenAnim(res::ui.getResAnim("sub_left")),50);
    }
    else if (direction.compare("RIGHT") == 0) {
        _ship->addTween(Sprite::TweenAnim(res::ui.getResAnim("sub_right")),50);
    }
    this->addTween(Actor::TweenPosition(x, y), 100);
}
