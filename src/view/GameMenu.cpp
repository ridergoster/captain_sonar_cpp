//
//  GameMenu.cpp
//  captain_sonar_macosx
//
//  Created by Vincent Kocupyr on 12/07/2017.
//  Copyright © 2017 oxygine. All rights reserved.
//

#include "GameMenu.h"
#include "Sprite.h"
#include "initActor.h"
#include "res.h"
#include "InputTextHandler.h"
#include "MyButton.h"
#include "ClientSocket.h"
#include "sio_message.h"
#include "GameScene.h"

spGameMenu GameMenu::instance;

GameMenu::GameMenu()
{
    // BACKGROUND
    _bg = initActor(new Sprite,
                            arg_resAnim = res::ui.getResAnim("menu"),
                            arg_attachTo = _view);

    // LOGO
    _logo = initActor(new Sprite,
                     arg_resAnim = res::ui.getResAnim("logo"),
                     arg_anchor = Vector2(0.5f, 0.5f),
                     arg_pos = _view->getSize() / 2,
                     arg_attachTo = _view);
    _logo->setY(_logo->getHeight()/2);
    
    // TEXT
    _txtUsername = initActor(new TextField(),
                            arg_name = "txtUsername",
                            arg_text = "Enter username: ",
                            arg_anchor = Vector2(0.5f, 0.5f),
                            arg_pos = _view->getSize() / 2,
                            arg_attachTo = _view);
    _txtUsername->setFontSize(20);
    _txtUsername->setX(10);
    _txtUsername->setY(_view->getHeight() - 10 - (_view->getHeight() - _bg->getHeight())/2);
    
    _txtServerID = initActor(new TextField(),
                            arg_name = "txtServerID",
                            arg_text = "Enter serverID: ",
                            arg_anchor = Vector2(0.5f, 0.5f),
                            arg_attachTo = _view);
    _txtServerID->setFontSize(20);
    _txtServerID->setX(_view->getWidth() - 300);
    _txtServerID->setY(_view->getHeight() - (_view->getHeight() - _bg->getHeight()) - 20);

    // INPUT
    _inputUsername = initActor(new InputTextHandler("lambda"),
                         arg_name = "username",
                         arg_anchor = Vector2(0.5f, 0.5f),
                         arg_attachTo = _view);
    _inputUsername->setX(170);
    _inputUsername->setY(_txtUsername->getPosition().y - 20);
    
    _inputServerID = initActor(new InputTextHandler("12345"),
                         arg_name = "serverId",
                         arg_pos = _view->getSize() / 2,
                         arg_anchor = Vector2(0.5f, 0.5f),
                         arg_size =  Vector2(100, 60),
                         arg_attachTo = _view);
    _inputServerID->setX(_view->getWidth() - 100);
    _inputServerID->setY(_view->getHeight() - (_view->getHeight() - _bg->getHeight()) - 10);
    
    //username->_current->text->getText();
    
    // BUTTON
    _btnExit = initActor(new MyButton,
                        arg_name = "exit",
                        arg_resAnim = res::ui.getResAnim("buttons")->getFrame(1, 3),
                        arg_anchor = Vector2(0.5f, 0.5f),
                        arg_attachTo = _view);
    _btnExit->setText("EXIT");
    _btnExit->setX(_view->getWidth() - _btnExit->getWidth() / 2);
    _btnExit->setY(_btnExit->getHeight() / 2);
    _btnExit->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameMenu::onEvent));
    
    _btnStart = initActor(new MyButton(),
                        arg_name = "start",
                        arg_resAnim = res::ui.getResAnim("buttons")->getFrame(0, 3),
                        arg_anchor = Vector2(0.5f, 0.5f),
                        arg_pos = _view->getSize() / 2,
                        arg_attachTo = _view);
    _btnStart->setText("Start Game");
    _btnStart->setX(_view->getWidth() - _btnStart->getWidth());
    _btnStart->setY(_view->getHeight() - (_view->getHeight() - _bg->getHeight())/2);
    _btnStart->addEventListener(TouchEvent::CLICK, CLOSURE(this, &GameMenu::onEvent));
}

void GameMenu::onEvent(Event* ev)
{
    string id = ev->currentTarget->getName();
    if (id == "exit")
    {
        //request quit
        core::requestQuit();
    }
    
    string serverID = _inputServerID->_current->text->getText();
    string username = _inputUsername->_current->text->getText();
    
    if (id == "start")
    {
        sio::message::ptr binObj = sio::object_message::create();
        binObj->get_map()["serverID"] = sio::string_message::create(serverID);
        binObj->get_map()["username"] = sio::string_message::create(username);

        ClientSocket::Instance().socket()->emit("join", binObj);

        std::cout << "START GAME with serverID: " << serverID << " and username: " << username << std::endl;

        //clicked to play button
        //change scene
        changeScene(GameScene::instance);
    }
}
