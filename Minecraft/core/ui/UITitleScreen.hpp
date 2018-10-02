//
//  UITitleScreen.hpp
//  UITitleScreen
//
//  Created by Shun Sato on 8/3/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UITitleScreen_hpp
#define UITitleScreen_hpp

#include "UIBaseView.hpp"

class UDPConnection;

/**
 * Title screen.
 */
class UITitleScreen: public UIBaseView {
public:
    UITitleScreen();
    ~UITitleScreen();
    
    void draw() const override;
private:
    void setup();
    
    UDPConnection* udpConnection;
};

#endif /* UITitleScreen_hpp */
