//
//  IDatabase.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef IDatabase_hpp
#define IDatabase_hpp

class ChunkManager;
class Chunk;

class IDatabase {
public:
    virtual bool loadChunk(Chunk& chunk) = 0;
    virtual void save(const ChunkManager& chunk) = 0;
};

#endif /* IDatabase_h */
