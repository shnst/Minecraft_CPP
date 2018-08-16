//
//  UIUDP.cpp
//  UIUDP
//
//  Created by Shun Sato on 8/3/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UIUDP.hpp"

#include "FieldMode.hpp"
#include "GameContext.hpp"
#include "UIButton.hpp"


UIUDP::UIUDP()
:UIBaseView(0)
{
    className = "UIUDPSetup";
    setup();
}

UIUDP::~UIUDP()
{}

void UIUDP::setup() {
    color = Color::WHITE;
    
    const Size buttonSize(150, 50);
    UIButton* connectButton = new UIButton(buttonSize);
    connectButton->setCoordinates(vec2d(0, 100), Anchor::CENTER);
    connectButton->setTitle("Connect");
    connectButton->setBackgroundColor(Color::GREY);
    connectButton->setEvent([=] () {
//        UDPConnection::get().connect("192.168.1.26", 8889, "192.168.1.25", 7555);
    });
    
    UIButton* sendMessageButton = new UIButton(buttonSize);
    sendMessageButton->setCoordinates(vec2d(0, 0), Anchor::CENTER);
    sendMessageButton->setTitle("Send Message");
    sendMessageButton->setBackgroundColor(Color::GREY);
    sendMessageButton->setEvent([=] () {
//        UDPConnection::get().send("Hello");
    });
    
    UIButton* receiveButton = new UIButton(buttonSize);
    receiveButton->setCoordinates(vec2d(0, -100), Anchor::CENTER);
    receiveButton->setTitle("Receive Message");
    receiveButton->setBackgroundColor(Color::GREY);
    receiveButton->setEvent([=] () {
//        UDPConnection::get().receive();
    });
    
    UIButton* openFieldModeButton = new UIButton(buttonSize);
    openFieldModeButton->setCoordinates(vec2d(0, -200), Anchor::CENTER);
    openFieldModeButton->setTitle("Open Field View");
    openFieldModeButton->setBackgroundColor(Color::GREY);
    openFieldModeButton->setEvent([=] () {
        close();
        GameContext::get().startGame(new FieldMode());
    });
    
    addChild(connectButton);
    addChild(sendMessageButton);
    addChild(receiveButton);
    addChild(openFieldModeButton);
}

void UIUDP::draw() const {
    UIView::draw();
}
