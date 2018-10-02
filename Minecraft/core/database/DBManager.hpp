//
//  DBManager.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef DBManager_hpp
#define DBManager_hpp

#include "Singleton.hpp"

class Chunk;
class ChunkManager;
class IDatabase;

class DBManager: public Singleton<DBManager> {
public:
    ~DBManager();
    
    bool loadChunk(Chunk& chunk);
    void save(const ChunkManager& chunk);
private:
    DBManager();
    friend class Singleton<DBManager>;
    
    IDatabase* db;
};

#endif /* DBManager_hpp */
