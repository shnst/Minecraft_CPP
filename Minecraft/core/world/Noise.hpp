//
//  Noise.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Noise_hpp
#define Noise_hpp

class Noise {
public:
    double noise(int x, int y, int x1, int y1, int width, int height, int seed);
private:
    double noise2d(double x, double y, int seed, int octaves, double persistence);
};

#endif /* Noise_hpp */
