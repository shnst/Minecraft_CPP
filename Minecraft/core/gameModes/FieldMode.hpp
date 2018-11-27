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
#include "UDP.hpp"

class World;

class FieldMode: public GameMode, UDP::UDPReceiveListener {
public:
    FieldMode();
    ~FieldMode();
    
    void start() override;
    void pause(bool isPaused) override;
    void quit() override;
    void handleInput(const Input::Data& inputData) override;
    
    void notify(const std::string& message) override;
private:
    void setupUDP();
    
    World* world;
};

#endif /* FieldMode_hpp */
