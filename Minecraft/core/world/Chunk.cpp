//
//  Chunk.cpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/14/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Chunk.hpp"

#include <iostream>
#include <sstream>

#include "ChunkManager.hpp"
#include "Mesh.hpp"
#include "Utils.hpp"


Chunk::Chunk(const vec3n& coord)
:coord(coord)
,mesh(new Mesh())
,_hasMeshCreated(false)
{
    for (auto xIt=blocks.begin(); xIt!=blocks.end(); ++xIt) {
        for (auto yIt=(*xIt).begin(); yIt!=(*xIt).end(); ++yIt) {
            for (auto zIt=(*yIt).begin(); zIt!=(*yIt).end(); ++zIt) {
                (*zIt) = Blocks::Types::Air;
            }
        }
    }
}

Chunk::~Chunk() {
    Utils::SafeDelete(mesh);
}

const std::array<std::array<std::array<Blocks::Types, NUMBER_OF_BLOCKS_IN_CHUNK_Z>, NUMBER_OF_BLOCKS_IN_CHUNK_Y>, NUMBER_OF_BLOCKS_IN_CHUNK_X>& Chunk::getBlocks() const {
    return blocks;
}

const vec3n& Chunk::getCoord() const {
    return coord;
}

bool Chunk::isBlocked(int x, int y, int z) const {
    if (!isInside(x, y, z)) {
        return false;
    }
    
//    std::cout << "Chunk::isBlocked x:" << x << " y:" << y << " z:" << z << std::endl;
    return !Blocks::isTransparent(blocks[x][y][z]);
}

bool Chunk::isInside(int x, int y, int z) const {
    if (x < 0 || NUMBER_OF_BLOCKS_IN_CHUNK_X <= x) {
        return false;
    }
    if (y < 0 || NUMBER_OF_BLOCKS_IN_CHUNK_Y <= y) {
        return false;
    }
    if (z < 0 || NUMBER_OF_BLOCKS_IN_CHUNK_Z <= z) {
        return false;
    }
    return true;
}

Blocks::Types Chunk::getBlock(int x, int y, int z) const {
    return blocks[x][y][z];
}

void Chunk::setBlock(int x, int y, int z, Blocks::Types blockType) {
    if (!isInside(x, y, z)) {
        return;
    }
    blocks[x][y][z] = blockType;
    _hasMeshCreated = false;
}

bool Chunk::hasNoised() const {
    return noised;
}

std::string Chunk::serializeBlocks() const {
    std::stringstream blockData;
    for (int x=0; x<NUMBER_OF_BLOCKS_IN_CHUNK_X; ++x) {
        for (int y=0; y<NUMBER_OF_BLOCKS_IN_CHUNK_Y; ++y) {
            for (int z=0; z<NUMBER_OF_BLOCKS_IN_CHUNK_Z; ++z) {
                if (x == 0 && y == 0 && z == 0) {
                    blockData << blocks[x][y][z];
                } else {
                    blockData << "," << blocks[x][y][z];
                }
            }
        }
    }
    return blockData.str();
}

bool Chunk::deserializeBlocks(const std::string& serializedString) {
    std::vector<std::string> splittedStrings;
    Utils::split(splittedStrings, serializedString, ",");
    
    if (splittedStrings.size() != NUMBER_OF_BLOCKS_IN_CHUNK_X * NUMBER_OF_BLOCKS_IN_CHUNK_Y * NUMBER_OF_BLOCKS_IN_CHUNK_Z) {
        return false;
    }
    
    for (int x=0; x<NUMBER_OF_BLOCKS_IN_CHUNK_X; ++x) {
        for (int y=0; y<NUMBER_OF_BLOCKS_IN_CHUNK_Y; ++y) {
            for (int z=0; z<NUMBER_OF_BLOCKS_IN_CHUNK_Z; ++z) {
                blocks[x][y][z] = static_cast<Blocks::Types>(std::stoi(splittedStrings[(x * NUMBER_OF_BLOCKS_IN_CHUNK_X + y) * NUMBER_OF_BLOCKS_IN_CHUNK_Z + z]));
            }
        }
    }
    return true;
}

void Chunk::clearAllBlocks() {
    for (int x=0; x<NUMBER_OF_BLOCKS_IN_CHUNK_X; ++x) {
        for (int y=0; y<NUMBER_OF_BLOCKS_IN_CHUNK_Y; ++y) {
            for (int z=0; z<NUMBER_OF_BLOCKS_IN_CHUNK_Z; ++z) {
                blocks[x][y][z] = Blocks::Air;
            }
        }
    }
}

void Chunk::createMesh(const ChunkManager& chunkManager) {
    mesh->vertices.clear();
    mesh->textureCoords.clear();
    
    auto xSize = blocks.size();
    auto ySize = blocks[0].size();
    auto zSize = blocks[0][0].size();
    
    auto chunkCoord = coord;
    
    //    std::cout << "ChunkRenderer::createMesh chunkX:" << offsetX << " chunkY:" << offsetY << " chunkZ:" << offsetZ << std::endl;
    
//    std::cout << "Chunk::createMesh coordX:" << coord.x << " y:" << coord.y << " z:" << coord.z << std::endl;
    
    for (int x=0; x<xSize; ++x) {
        for (int y=0; y<ySize; ++y) {
            for (int z=0; z<zSize; ++z) {
                auto blockType = blocks[x][y][z];
                if (blockType == Blocks::Air) {
                    continue;
                }
                
                int offsetX = chunkCoord.x * NUMBER_OF_BLOCKS_IN_CHUNK_X;
                int offsetY = chunkCoord.y * NUMBER_OF_BLOCKS_IN_CHUNK_Y;
                int offsetZ = chunkCoord.z * NUMBER_OF_BLOCKS_IN_CHUNK_Z;
                
                auto texture = Blocks::blockTextures[blockType];
                
//                std::cout << "Chunk::createMesh offsetX:" << offsetX + x << " y:" << offsetY + y + 1 << " z:" << offsetZ + z << std::endl;
//                std::cout << "Chunk::createMesh blockX:" << x << " y:" << y << " z:" << z << std::endl;
                
                // top
                if (!chunkManager.isBlocked(offsetX + x, offsetY + y+1, offsetZ + z)) {
//                if (isBlocked(x, y+1, z)) {
                    mesh->addFace(
                                  offsetX + x, offsetY + y+1, offsetZ + z,
                                  offsetX + x+1, offsetY + y+1, offsetZ + z,
                                  offsetX + x, offsetY + y+1, offsetZ + z+1,
                                  offsetX + x+1, offsetY + y+1, offsetZ + z+1,
                                  texture.top[0], texture.top[1], texture.top[2], texture.top[3]);
                }
                
                // bottom
                if (!chunkManager.isBlocked(offsetX + x, offsetY + y-1, offsetZ + z)) {
//                    chunkManager.isBlocked(offsetX + x, offsetY + y-1, offsetZ + z);
                    mesh->addFace(
                                  offsetX + x, offsetY + y, offsetZ + z,
                                  offsetX + x+1, offsetY + y, offsetZ + z,
                                  offsetX + x, offsetY + y, offsetZ + z+1,
                                  offsetX + x+1, offsetY + y, offsetZ + z+1,
                                  texture.bottom[0], texture.bottom[1], texture.bottom[2], texture.bottom[3]);
                }
                
                // side1
                if (!chunkManager.isBlocked(offsetX + x-1, offsetY + y, offsetZ + z)) {
                    mesh->addFace(
                                  offsetX + x, offsetY + y+1, offsetZ + z+1,
                                  offsetX + x, offsetY + y+1, offsetZ + z,
                                  offsetX + x, offsetY + y, offsetZ + z+1,
                                  offsetX + x, offsetY + y, offsetZ + z,
                                  texture.side[0], texture.side[1], texture.side[2], texture.side[3]);
                }
                
                // side2
                if (!chunkManager.isBlocked(offsetX + x+1, offsetY + y, offsetZ + z)) {
                    mesh->addFace(
                                  offsetX + x+1, offsetY + y+1, offsetZ + z,
                                  offsetX + x+1, offsetY + y+1, offsetZ + z+1,
                                  offsetX + x+1, offsetY + y, offsetZ + z,
                                  offsetX + x+1, offsetY + y, offsetZ + z+1,
                                  texture.side[0], texture.side[1], texture.side[2], texture.side[3]);
                }
                
                // side3
                if (!chunkManager.isBlocked(offsetX + x, offsetY + y, offsetZ + z-1)) {
                    mesh->addFace(
                                  offsetX + x, offsetY + y+1, offsetZ + z,
                                  offsetX + x+1, offsetY + y+1, offsetZ + z,
                                  offsetX + x, offsetY + y, offsetZ + z,
                                  offsetX + x+1, offsetY + y, offsetZ + z,
                                  texture.side[0], texture.side[1], texture.side[2], texture.side[3]);
                }
                
                // side4
                if (!chunkManager.isBlocked(offsetX + x, offsetY + y, offsetZ + z+1)) {
                    mesh->addFace(
                                  offsetX + x+1, offsetY + y+1, offsetZ + z+1,
                                  offsetX + x, offsetY + y+1, offsetZ + z+1,
                                  offsetX + x+1, offsetY + y, offsetZ + z+1,
                                  offsetX + x, offsetY + y, offsetZ + z+1,
                                  texture.side[0], texture.side[1], texture.side[2], texture.side[3]);
                }
            }
        }
    }
    _hasMeshCreated = true;
}

const Mesh& Chunk::getMesh() const {
    return *mesh;
}

bool Chunk::hasMeshCreated() const {
    return _hasMeshCreated;
}
