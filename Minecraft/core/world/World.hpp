//
//  World.hpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <list>

#include "Drawable.hpp"

class Chunk;
class ChunkRenderer;

class World: Drawable {
public:
    World();
    ~World();
    
    void draw() const override;
private:
    void generateChunks();
    
    std::list<Chunk*> chunks;
    ChunkRenderer* chunkRenderer;
};

#endif /* World_hpp */
