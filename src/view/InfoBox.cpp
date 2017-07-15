//
//  InfoBox.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 14/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include "InfoBox.h"
#include "Game.h"
#include "res.h"
#include "oxygine-framework.h"

InfoBox::InfoBox(float width, float height)
{
    this->setSize(width, height);
    _infos.clear();
    spColorRectSprite colorbg = new ColorRectSprite;
    colorbg->attachTo(this);
    colorbg->setSize(this->getSize());
    colorbg->setColor(Color::White);
}


void InfoBox::addText(const string &info)
{
    spTextField newTextField = initActor(new TextField,
                                         arg_text=info,
                                         arg_fontSize=15,
                                         arg_color=Color::Black,
                                         arg_attachTo=this);
    newTextField->setX(newTextField->getWidth()/2);
    newTextField->setY(newTextField->getHeight()/2);

    if(_infos.size() > 19) {
        _infos[0]->detach();
        _infos.erase(_infos.begin());
    }
    for(spTextField &oldText : _infos)
    {
        oldText->addTween(Actor::TweenPosition(oldText->getX(),oldText->getY()+ newTextField->getHeight()+15), 10);
    }
    _infos.push_back(newTextField);    
}

void InfoBox::addTexts(const vector<string> &infos) {
    for(const string &txt : infos) {
        addText(txt);
        SDL_Delay(200);
    }
}
