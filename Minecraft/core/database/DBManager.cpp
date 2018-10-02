//
//  DBManager.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "DBManager.hpp"

#include "DBSqlite.hpp"
#include "Utils.hpp"

DBManager::DBManager()
:db(new DBSqlite())
{}

DBManager::~DBManager()
{
    Utils::SafeDelete(db);
}

bool DBManager::loadChunk(Chunk& chunk) {
    return db->loadChunk(chunk);
}

void DBManager::save(const ChunkManager& chunk) {
    db->save(chunk);
}
