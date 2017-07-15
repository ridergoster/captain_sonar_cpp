//
//  MyButton.h
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 13/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "oxygine-framework.h"
using namespace oxygine;
using namespace std;

DECLARE_SMART(MyButton, spMyButton);
class MyButton: public Sprite
{
public:
    MyButton();
    
    void setText(const string& txt);
    
private:
    void onEvent(Event*);
    
    spTextField _text;
};
