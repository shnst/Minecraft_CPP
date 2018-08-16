//
//  World.hpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include "Drawable.hpp"

class Chunk;
class ChunkRenderer;

class World: Drawable {
public:
    World();
    ~World();
    
    void draw() const override;
    
private:
    Chunk* chunk;
    ChunkRenderer* chunkRenderer;
};

#endif /* World_hpp */
