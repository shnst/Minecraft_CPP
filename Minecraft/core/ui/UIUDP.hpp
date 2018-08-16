//
//  UIUDP.hpp
//  UIUDP
//
//  Created by Shun Sato on 8/3/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef UIUDP_hpp
#define UIUDP_hpp

#include "UIBaseView.hpp"

class UDPConnection;

/**
 * Title screen.
 */
class UIUDP: public UIBaseView {
public:
    UIUDP();
    ~UIUDP();
    
    void draw() const override;
private:
    void setup();
    
    UDPConnection* udpConnection;
};

#endif /* UIUDP_hpp */
