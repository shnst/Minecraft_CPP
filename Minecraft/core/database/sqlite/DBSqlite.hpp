//
//  DBSqlite.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef DBSqlite_hpp
#define DBSqlite_hpp

#include <string>
#include <vector>

#include "IDatabase.hpp"

class sqlite3;

typedef sqlite3** DB_HANDLE;

class DBSqlite: public IDatabase {
public:
    DBSqlite();
    ~DBSqlite();
    
    bool loadChunk(Chunk& chunk) override;
    void save(const ChunkManager& chunk) override;
private:
    void initialize();
    
    void openDatabase(DB_HANDLE handle);
    void closeDatabase(DB_HANDLE handle);
    
    std::vector<std::string> getExistingTableNames(DB_HANDLE dbh);
    
    bool createChunkTable(DB_HANDLE handle);
    bool executeQuery(DB_HANDLE handle, const std::string& query);
    
    void beginTransaction(DB_HANDLE dbh);
    void endTransaction(DB_HANDLE dbh);
    
    /** Transactionを開始したDBのリスト */
    static std::vector<DB_HANDLE> dbHandles;
    std::string databasePath;
    
};

#endif /* DBSqlite_hpp */
