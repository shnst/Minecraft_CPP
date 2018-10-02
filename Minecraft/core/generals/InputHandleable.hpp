//
//  InputHandleable.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/18/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef InputHandleable_hpp
#define InputHandleable_hpp

#include "Keyboard.hpp"
#include "MouseButton.hpp"

namespace Input {
    struct MouseMoveEvent {
        MouseMoveEvent(double x, double y)
        :x(x)
        ,y(y)
        {}
        double x;
        double y;
    };
    
    struct MouseButtonEvent {
        MouseButtonEvent(MouseButton::Types button)
        :button(button)
        {}
        MouseButton::Types button;
    };
    
    struct KeyboardEvent {
        KeyboardEvent(Keyboard::Types key)
        :key(key)
        {}
        Keyboard::Types key;
    };
    
    struct Data {
        ~Data();
    
        void addMouseMoveEvent(double x, double y);
        void addKeyboardEvent(Keyboard::Types key);
        void addMouseButtonEvent(MouseButton::Types button);
        
        MouseMoveEvent* mouseMoveEvent;
        MouseButtonEvent* mouseButtonEvent;
        KeyboardEvent* keyboardEvent;
    };
}

class InputHandleable {
public:
    
    virtual void handleInput(const Input::Data& data) = 0;
};

#endif /* InputHandleable_hpp */
