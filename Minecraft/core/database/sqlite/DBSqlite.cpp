//
//  DBSqlite.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/30/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "DBSqlite.hpp"

#include <iostream>
#include <sstream>

#include "sqlite3.h"

#include "Chunk.hpp"
#include "ChunkManager.hpp"

/**
 * NULLポインタの場合は空文字列を返す(std::stringにnullのchar*などをコンストラクタ引数として渡すと落ちるため)
 */
static inline const char* getSafeString(const char* str){
    return (str ? str : "");
}
static inline const char* getSafeString(const unsigned char* str){
    return (str ? reinterpret_cast<const char*>(str) : "");
}

DBSqlite::DBSqlite()
:databasePath("test")
{
    // multithread
    sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
    
    initialize();
}

DBSqlite::~DBSqlite()
{
    
}

void DBSqlite::initialize() {
    sqlite3* db = nullptr;
    
    openDatabase(&db);
    
    beginTransaction(&db);
    auto existingTables = getExistingTableNames(&db);
    endTransaction(&db);
    
    for (auto it=existingTables.begin(); it!=existingTables.end(); ++it) {
        std::cout << "DBSqlite::initialize table:" << *it << std::endl;
    }
    
    if (std::find(existingTables.begin(), existingTables.end(), "chunk") == existingTables.end()) {
        createChunkTable(&db);
    }
    
    closeDatabase(&db);
}

bool DBSqlite::loadChunk(Chunk& chunk) {
    bool isSuccessful = false;
    
    auto chunkCoord = chunk.getCoord();
    
    // ステートメント
    sqlite3_stmt *stmt = NULL;
    
    sqlite3* db = nullptr;
    
    openDatabase(&db);
    
    beginTransaction(&db);
    
    std::ostringstream queryStream;
    queryStream << "select width, height, length, data from chunk where x=" << chunkCoord.x << " and y=" << chunkCoord.y << " and z=" << chunkCoord.z << ";";
    std::string query = queryStream.str();

    // ステートメント作成
    int error = sqlite3_prepare_v2(db, query.c_str(), query.size(), &stmt, NULL);
    
    if (error != SQLITE_OK) {
//        LOGE("DBManager::ReadCampaignMap SQL error: %d", error);
        std::cout << "DBSqlite::loadChunk query error:" << error << std::endl;
    } else {
        // データの抽出
        while (SQLITE_ROW == (error = sqlite3_step(stmt))) {
            // 建物レベル
            int width = sqlite3_column_int(stmt, 0);
            // x座標
            int height = sqlite3_column_int(stmt, 1);
            // y座標
            int length = sqlite3_column_int(stmt, 2);
            // モード
            std::string data = getSafeString(sqlite3_column_text(stmt, 3));
            
            isSuccessful = chunk.deserializeBlocks(data);
        }
        if (error != SQLITE_DONE) {
            // ちゃんと完了しなかった場合
            std::cout << "DBSqlite::getChunk query execution error:" << error << std::endl;
        }
    }
    // ステートメントの解放
    sqlite3_finalize(stmt);
    
    endTransaction(&db);
    closeDatabase(&db);
    
    return isSuccessful;
}

void DBSqlite::save(const ChunkManager& chunkManager) {
    auto chunks = chunkManager.getChunks();
    
    sqlite3* db = nullptr;
    
    openDatabase(&db);
    
    beginTransaction(&db);
    
    
    for (const auto& chunk : chunks) {
        auto chunkCoord = chunk.second->getCoord();
        
        auto blocks = chunk.second->getBlocks();
        
        std::ostringstream query;
        query << "insert or replace into chunk (x, y, z, width, height, length, data) values("
        << chunkCoord.x << ", "
        << chunkCoord.y << ", "
        << chunkCoord.z << ", "
        << NUMBER_OF_BLOCKS_IN_CHUNK_X << ", "
        << NUMBER_OF_BLOCKS_IN_CHUNK_Y << ", "
        << NUMBER_OF_BLOCKS_IN_CHUNK_Z << ", "
        << "\"" << chunk.second->serializeBlocks() << "\""
        << ");";
        
        std::cout << "DBSqlite::save" << query.str() << std::endl;
        
        // TODO : Error handling.
        executeQuery(&db, query.str());
    }
    
    endTransaction(&db);
    closeDatabase(&db);
}

void DBSqlite::openDatabase(DB_HANDLE handle) {
    int ret = sqlite3_open(databasePath.c_str(), handle);
    if (ret != SQLITE_OK) {
        std::cout << "DBSqlite::openDatabase failed to open error:" << ret << std::endl;
        return;
    }
}

void DBSqlite::closeDatabase(DB_HANDLE handle) {
    sqlite3_close(*handle);
}

bool DBSqlite::createChunkTable(DB_HANDLE handle) {
    std::ostringstream query;
    query << "create table chunk (x integer, y integer, z integer, width integer, height integer, length integer, data text, primary key(x, y, z));";
    
    return executeQuery(handle, query.str());
}

bool DBSqlite::executeQuery(DB_HANDLE handle, const std::string& query) {
    int error = sqlite3_exec(*handle, query.c_str(), NULL, NULL, NULL);
    if (error != SQLITE_OK) {
        std::cout << "DBSqlite::executeQuery query execution error:" << error << std::endl;
        return false;
    }
    return true;
}

/**
 * 存在するテーブル名の一覧を取得
 */
std::vector<std::string> DBSqlite::getExistingTableNames(DB_HANDLE dbh) {
    // ステートメント
    sqlite3_stmt *stmt = NULL;
    // クエリ
    const char *query = "select name from sqlite_master where type='table';";
    
    std::vector<std::string> tables;
    
    // ステートメント作成
    int error = sqlite3_prepare_v2(*dbh, query, strlen(query), &stmt, NULL);
    if (error != SQLITE_OK) {
        std::cout << "DBSqlite::getExistingTableNames query error:" << error << std::endl;
    } else {
        std::ostringstream stringStream;
        while (SQLITE_ROW == (error = sqlite3_step(stmt))) {
            tables.push_back(getSafeString(sqlite3_column_text(stmt, 0)));
        }
        if (error != SQLITE_DONE) {
            std::cout << "DBSqlite::getExistingTableNames query execution error:" << error << std::endl;
        }
    }
    
    // ステートメントの解放
    sqlite3_finalize(stmt);
    return tables;
}

/**
 * トランザクション開始
 * 大量にSQLを実行する場合は、BeginTransaction()とEndTransaction()の間で処理を行うことで高速化できる
 */
void DBSqlite::beginTransaction(DB_HANDLE dbh) {
    // start sqlite transaction block
    int ret = sqlite3_exec(*dbh, "BEGIN", 0, 0, 0);
    if (ret != SQLITE_OK) {
        std::cout << "DBSqlite::beginTransaction failed to begin transaction error:" << ret << std::endl;
        return;
    }
}

/**
 * トランザクション終了
 */
void DBSqlite::endTransaction(DB_HANDLE dbh) {
    // end sqlite transaction block
    int ret = SQLITE_OK;
    do {
        ret = sqlite3_exec(*dbh, "COMMIT", 0, 0, 0);
        if (ret != SQLITE_OK) {
            std::cout << "DBSqlite::endTransaction failed to end transaction error:" << ret << std::endl;
            return;
        }
    } while (ret != SQLITE_OK);
}

