//
//  res.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 12/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include "res.h"

namespace res
{
    Resources ui;
    
    void load()
    {
        ui.loadXML("xmls/ui.xml");
    }
    
    void free()
    {
        ui.free();
        
    }
}
