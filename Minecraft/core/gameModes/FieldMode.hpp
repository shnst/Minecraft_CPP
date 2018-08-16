//
//  FieldMode.hpp
//  tetris
//
//  Created by Shun Sato on 8/4/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef FieldMode_hpp
#define FieldMode_hpp

#include <string>

#include "GameMode.hpp"

class World;

class FieldMode: public GameMode {
public:
    FieldMode();
    ~FieldMode();
    
    void start() override;
    void pause(bool isPaused) override;
    void quit() override;
    void handleKeyboardInput(Keyboard::Types key) override;
private:
    World* world;
};

#endif /* FieldMode_hpp */
