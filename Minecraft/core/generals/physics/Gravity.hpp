//
//  Gravity.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/20/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Gravity_hpp
#define Gravity_hpp

#include "Vector3d.hpp"

namespace Gravity {
    struct Data {
        Data(const vec3d& initialPosition, const vec3d& initialVelocity)
        :time(0)
        ,initialPosition(initialPosition)
        ,initialVelocity(initialVelocity)
        {}
        
        void update(double deltaTime) {
            time += deltaTime;
        }
        
        vec3d currentPosition() const {
            return initialPosition * time + vec3d(0, -9.80665, 0) * time * time / 2;
        }
        
        double time;
        const vec3d initialPosition;
        vec3d initialVelocity;
    };
}

#endif /* Gravity_hpp */
