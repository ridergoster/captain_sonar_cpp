//
//  PowerControl.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 14/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include "PowerControl.h"
#include "MyButton.h"
#include <iostream>
#include "res.h"

PowerControl::PowerControl(float width, float height)
{
    this->setSize(width, height);
    
    _mineValue = 0;
    _radarValue = 0;
    _silenceValue = 0;
    
    _buttonMine = initActor(new MyButton,
                         arg_name = "MINE",
                         arg_resAnim = res::ui.getResAnim("buttons")->getFrame(0, 4),
                         arg_anchor = Vector2(0.5f, 0.5f),
                         arg_attachTo = this);
    _buttonMine->setText("MINE");
    _buttonMine->setX(_buttonMine->getWidth()/2 + 10);
    _buttonMine->setY(this->getHeight()/3 - _buttonMine->getHeight()/2);
    _buttonMine->addEventListener(TouchEvent::CLICK, CLOSURE(this, &PowerControl::onEvent));
    
    _spriteMine = initActor(new Sprite,
                            arg_name="mine_jauge",
                            arg_resAnim=res::ui.getResAnim("power_0"),
                            arg_attachTo=this);
    _spriteMine->setX(_buttonMine->getWidth() + 40);
    _spriteMine->setY(_buttonMine->getY() - _spriteMine->getHeight()/2);
    

    _buttonRadar = initActor(new MyButton,
                            arg_name = "RADAR",
                            arg_resAnim = res::ui.getResAnim("buttons")->getFrame(0, 4),
                            arg_anchor = Vector2(0.5f, 0.5f),
                            arg_attachTo = this);
    _buttonRadar->setText("RADAR");
    _buttonRadar->setX(_buttonRadar->getWidth()/2 + 10);
    _buttonRadar->setY(this->getHeight()*2/3 - _buttonRadar->getHeight()/2);
    _buttonRadar->addEventListener(TouchEvent::CLICK, CLOSURE(this, &PowerControl::onEvent));
    
    _spriteRadar = initActor(new Sprite,
                            arg_name="radar_jauge",
                            arg_resAnim=res::ui.getResAnim("power_0"),
                            arg_attachTo=this);
    _spriteRadar->setX(_buttonRadar->getWidth() + 40);
    _spriteRadar->setY(_buttonRadar->getY() - _spriteRadar->getHeight()/2);
    
    _buttonSilence = initActor(new MyButton,
                            arg_name = "SILENCE",
                            arg_resAnim = res::ui.getResAnim("buttons")->getFrame(0, 4),
                            arg_anchor = Vector2(0.5f, 0.5f),
                            arg_attachTo = this);
    _buttonSilence->setText("SILENCE");
    _buttonSilence->setX(_buttonSilence->getWidth() / 2 + 10);
    _buttonSilence->setY(this->getHeight() - _buttonSilence->getHeight()/2);
    _buttonSilence->addEventListener(TouchEvent::CLICK, CLOSURE(this, &PowerControl::onEvent));
    
    _spriteSilence = initActor(new Sprite,
                             arg_name="silence_jauge",
                             arg_resAnim=res::ui.getResAnim("power_0"),
                             arg_attachTo=this);
    _spriteSilence->setX(_buttonSilence->getWidth() + 40);
    _spriteSilence->setY(_buttonSilence->getY() - _spriteSilence->getHeight()/2);
}

void PowerControl::updateFrame() {
    
    _buttonMine->setAnimFrame(res::ui.getResAnim("buttons")->getFrame(0, 4));
    _buttonRadar->setAnimFrame(res::ui.getResAnim("buttons")->getFrame(0, 4));
    _buttonSilence->setAnimFrame(res::ui.getResAnim("buttons")->getFrame(0, 4));
    
    if (_lastClicked.compare("MINE") == 0) {
        _buttonMine->setAnimFrame(res::ui.getResAnim("buttons")->getFrame(0, 0));
    }
    else if (_lastClicked.compare("RADAR") == 0) {
        _buttonRadar->setAnimFrame(res::ui.getResAnim("buttons")->getFrame(0, 0));
    }
    else if (_lastClicked.compare("SILENCE") == 0) {
        _buttonSilence->setAnimFrame(res::ui.getResAnim("buttons")->getFrame(0, 0));
    }
}

int PowerControl::getValue(const string &power) {
    if (power.compare("RADAR") == 0) {
        return _radarValue;
    }
    else if (power.compare("MINE") == 0) {
        return _mineValue;
    }
    else if (power.compare("SILENCE") == 0) {
        return _silenceValue;
    }
    return 0;
}


void PowerControl::addValue(const string &power) {
    if (power.compare("RADAR") == 0 && _radarValue < 4) {
        _radarValue++;
        switch (_radarValue) {
            case 1:
                _spriteRadar->addTween(Sprite::TweenAnim(res::ui.getResAnim("radar_1")),10);
                break;
            case 2:
                _spriteRadar->addTween(Sprite::TweenAnim(res::ui.getResAnim("radar_2")),10);
                break;
            case 3:
                _spriteRadar->addTween(Sprite::TweenAnim(res::ui.getResAnim("radar_3")),10);
                break;
            case 4:
                _spriteRadar->addTween(Sprite::TweenAnim(res::ui.getResAnim("radar_4")),10);
                break;
            default:
                break;
        }
    }
    else if (power.compare("MINE") == 0 && _mineValue < 4) {
        _mineValue++;
        switch (_mineValue) {
            case 1:
                _spriteMine->addTween(Sprite::TweenAnim(res::ui.getResAnim("mine_1")),10);
                break;
            case 2:
                _spriteMine->addTween(Sprite::TweenAnim(res::ui.getResAnim("mine_2")),10);
                break;
            case 3:
                _spriteMine->addTween(Sprite::TweenAnim(res::ui.getResAnim("mine_3")),10);
                break;
            case 4:
                _spriteMine->addTween(Sprite::TweenAnim(res::ui.getResAnim("mine_4")),10);
                break;
            default:
                break;
        }
    }
    else if (power.compare("SILENCE") == 0 && _silenceValue < 4) {
        _silenceValue++;
        switch (_silenceValue) {
            case 1:
                _spriteSilence->addTween(Sprite::TweenAnim(res::ui.getResAnim("silence_1")),10);
                break;
            case 2:
                _spriteSilence->addTween(Sprite::TweenAnim(res::ui.getResAnim("silence_2")),10);
                break;
            case 3:
                _spriteSilence->addTween(Sprite::TweenAnim(res::ui.getResAnim("silence_3")),10);
                break;
            case 4:
                _spriteSilence->addTween(Sprite::TweenAnim(res::ui.getResAnim("silence_4")),10);
                break;
            default:
                break;
        }
    }
}

bool PowerControl::isValid() {
    if (_lastClicked.compare("MINE") == 0 ||
        _lastClicked.compare("RADAR") == 0||
        _lastClicked.compare("SILENCE") == 0) {
        return true;
    }
    return false;
}

bool PowerControl::usePower (const string &power) {
    if (power.compare("RADAR") == 0 && _radarValue == 4) {
        _spriteRadar->addTween(Sprite::TweenAnim(res::ui.getResAnim("power_0")),10);
        _radarValue = 0;
        return true;
    }
    else if (power.compare("MINE") == 0 && _mineValue == 4) {
        _spriteMine->addTween(Sprite::TweenAnim(res::ui.getResAnim("power_0")),10);
        _mineValue = 0;
        return true;
    }
    else if (power.compare("SILENCE") == 0 && _silenceValue == 4) {
        _spriteSilence->addTween(Sprite::TweenAnim(res::ui.getResAnim("power_0")),10);
        _silenceValue = 0;
        return true;
    }
    return false;
}

void PowerControl::onEvent(Event* ev)
{
    //button clicked
    //remember it's name. It would asked later from GameScene.cpp
    _lastClicked = ev->currentTarget->getName();
    updateFrame();
}

void PowerControl::setPower(const string &power)
{
    _lastClicked = power;
    updateFrame();
}
