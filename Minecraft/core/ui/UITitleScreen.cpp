//
//  UITitleScreen.cpp
//  UITitleScreen
//
//  Created by Shun Sato on 8/3/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "UITitleScreen.hpp"

#include "FieldMode.hpp"
#include "GameContext.hpp"
#include "UIButton.hpp"


UITitleScreen::UITitleScreen()
:UIBaseView(0)
{
    className = "UITitleScreenSetup";
    setup();
}

UITitleScreen::~UITitleScreen()
{}

void UITitleScreen::setup() {
    color = Color::WHITE;
    
    const Size buttonSize(150, 50);
    UIButton* connectButton = new UIButton(buttonSize);
    connectButton->setCoordinates(vec2d(0, 100), Anchor::CENTER);
    connectButton->setTitle("Connect");
    connectButton->setBackgroundColor(Color::GREY);
    connectButton->setEvent([=] () {
    });
    
    UIButton* sendMessageButton = new UIButton(buttonSize);
    sendMessageButton->setCoordinates(vec2d(0, 0), Anchor::CENTER);
    sendMessageButton->setTitle("Send Message");
    sendMessageButton->setBackgroundColor(Color::GREY);
    sendMessageButton->setEvent([=] () {
    });
    
    UIButton* receiveButton = new UIButton(buttonSize);
    receiveButton->setCoordinates(vec2d(0, -100), Anchor::CENTER);
    receiveButton->setTitle("Receive Message");
    receiveButton->setBackgroundColor(Color::GREY);
    receiveButton->setEvent([=] () {
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

void UITitleScreen::draw() const {
    UIView::draw();
}
