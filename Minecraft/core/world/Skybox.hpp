//
//  Skybox.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include "Size.hpp"
#include "Updatable.hpp"
#include "Vector3d.hpp"

class Skybox: Updatable {
public:
    Skybox(double size);
    ~Skybox();
    
    
    void update(double delta) override;
    double getSize() const;
private:
    const double size;
};

#endif /* Skybox_hpp */
