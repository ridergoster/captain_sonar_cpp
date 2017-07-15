//
//  InfoBox.h
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 14/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#pragma once
#include "Actor.h"
#include <vector>

using namespace oxygine;
using namespace std;

DECLARE_SMART(InfoBox, spInfoBox);
class InfoBox: public Actor
{
public:
    InfoBox(float width, float height);
    void addText(const string &info);
    void addTexts(const vector<string> &infos);
    
private:
    vector<spTextField> _infos;
};
