//
//  Noise.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Noise.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

double Noise::noise2d(double x, double y, int seed, int octaves, double persistence) {
    double sum = 0;
    double strength = 1.0;
    float scale = 1.0;
    
    for(int i = 0; i < octaves; i++) {
        sum += strength * glm::simplex(glm::vec2(x, y) * scale);
        scale *= 2.0;
        strength *= persistence;
    }
    
    return sum;
}

double Noise::noise(int x, int y, int x1, int y1, int width, int height, int seed) {
    return noise2d((x + x1 * width) / 256.0, (y + y1 * height) / 256.0, seed, 5, 0.8) * 4;
}
