//
//  InputTextHandler.hpp
//
//  Created by Cody Claborn on 12/8/15.
//  Copyright © 2015 oxygine. All rights reserved.
//

#pragma once

#include "InputText.h"
#include "res.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace oxygine;
using namespace std;

DECLARE_SMART(TextWithBackground, spTextWithBackground);
class TextWithBackground: public ColorRectSprite {
public:
    
    TextWithBackground(const string& defText) {
        
        text = new TextField;
        text->setTouchEnabled(false);
        
        TextStyle style;
        style.color = Color::White;
        style.hAlign = TextStyle::HALIGN_LEFT;
        style.vAlign = TextStyle::VALIGN_MIDDLE;
        style.multiline = true;        
        text->setStyle(style);
        text->setText(defText);
        text->setFontSize(20);
		this->setColor(Color(0x00000000));
        
        addChild(text);
    }
    
    spTextField text;
    
    void sizeChanged(const Vector2& size) {
        text->setSize(size);
    }
};

// Custom event class
class HandleInputEvent : public Event {
public:
	enum {EVENT = makefourcc('H', 'a', 'I', 'n') };

	string command;
	vector<string> options;

	HandleInputEvent(string command, vector<string> options) :Event(EVENT), command(command), options(options) {}
};

DECLARE_SMART(InputTextHandler, spInputTextHandler);
class InputTextHandler : public Actor {
public:
    spInputText _input;
    spTextWithBackground _current;
    
    int rainChannel = -1;
    
    InputTextHandler(const string& defText) {
        _input = new InputText;
        _current = new TextWithBackground(defText);
        _current->setSize(getStage()->getSize().x - (40 * 2), 60);
        _current->attachTo(this);
        _current->addEventListener(TouchEvent::CLICK, CLOSURE(this, &InputTextHandler::onClick));
    }
                       
    void onClick(Event* ev) {
        if (_current) {
            _current->setColor(Color(0x00000000));
        }
                           
        _current = safeSpCast<TextWithBackground>(ev->currentTarget);
        _input->start(_current->text);
        _current->setColor(Color(0x00000000));
    }
    
    ~InputTextHandler()
    {
        
    }
                       
    void clicked(string id)
    {
        
    }
};
