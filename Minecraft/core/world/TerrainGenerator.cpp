//
//  TerrainGenerator.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "TerrainGenerator.hpp"

#include <algorithm>
#include <iostream>
#include <random>

#include "Chunk.hpp"
#include "Constants.hpp"
#include "PerlinNoise.hpp"
#include "Utils.hpp"
#include "Time.hpp"
#include "World.hpp"

const int NUM_TERRAIN_LAYERS = 2;

TerrainGenerator::TerrainGenerator()
{
    initializeNoises();
}

TerrainGenerator::~TerrainGenerator() {
    for (auto it=noises.begin(); it!=noises.end(); ++it) {
        Utils::SafeDelete(*it);
    }
}

void TerrainGenerator::initializeNoises() {
    int seed = static_cast<int>(Time::now_ms() / 1000) % 10000;
    for (int i=0; i<NUM_TERRAIN_LAYERS; ++i) {
        noises.push_back(new PerlinNoise(seed + i));
    }
}

void TerrainGenerator::generate(World& world, const std::vector<std::vector<std::vector<Chunk*>>>& chunks) {
    auto worldHeight = NUMBER_OF_CHUNKS_IN_WORLD_Y * CHUNK_SIZE;
    
    auto worldWidth1 = NUMBER_OF_CHUNKS_IN_WORLD_X * CHUNK_SIZE;
    auto worldWidth2 = NUMBER_OF_CHUNKS_IN_WORLD_Z * CHUNK_SIZE;
    
    std::mt19937 randomGenerator(Time::now_ms());
    std::uniform_int_distribution<int> random(0, 1000);
    
    for (auto it=chunks.begin(); it!=chunks.end(); ++it) {
        for (auto it2=(*it).begin(); it2!=(*it).end(); ++it2) {
            for (auto it3=(*it2).begin(); it3!=(*it2).end(); ++it3) {
                auto chunk = *it3;
                if (chunk->hasNoised()) {
                    continue;
                }

                auto blocks = chunk->getBlocks();

                auto xSize = blocks.size();
                auto ySize = blocks.front().size();
                auto zSize = blocks.front().front().size();

                auto chunkCoord = chunk->getCoords();
                auto offsetX = CHUNK_SIZE * chunkCoord.x;
                auto offsetY = CHUNK_SIZE * chunkCoord.y;
                auto offsetZ = CHUNK_SIZE * chunkCoord.z;

                for (int x=0; x<xSize; ++x) {
                    for (int z=0; z<zSize; ++z) {
                        
                        auto perlinX = (offsetX + x) / static_cast<double>(worldWidth1) * 15 * NUMBER_OF_CHUNKS_IN_WORLD_X / 20;
                        auto perlinZ = (offsetZ + z) / static_cast<double>(worldWidth2) * 15 * NUMBER_OF_CHUNKS_IN_WORLD_Z / 20;
                        auto noiseForGrass = noises.front()->noise(perlinX, perlinZ, 0.3);
                        auto noiseForStone = noises[1]->noise(perlinX, perlinZ, 0.4);
                        
                        auto groundHeight = static_cast<int>(floor(worldHeight * noiseForGrass));
                        auto stoneHeight = static_cast<int>(floor(worldHeight * 1.0 * noiseForStone));

                        for (int y=0; y<ySize; ++y) {
                            if (chunk->getBlock(x, y, z) != Blocks::Air) {
                                continue;
                            }
                            
                            if (y + offsetY > groundHeight && y + offsetY > stoneHeight) {
//                                std::cout << "y:" << y+offsetY << " groundHeight:" << groundHeight+1 << " SEA_LEVEL:" << SEA_LEVEL << std::endl;
                                if (y + offsetY <= SEA_LEVEL) {
                                    chunk->setBlock(x, y, z, Blocks::Water);
                                    continue;
                                }
                                if (groundHeight > stoneHeight && (y + offsetY) == groundHeight+1 && random(randomGenerator) < 5){
                                    // Trunk
                                    for(int i = 0; i < 5; i++) {
                                        chunk->setBlock(x, y+i, z, Blocks::Wood);
                                    }
                                    
//                                    // Leaves
                                    for(int k = -3; k <= 3; k++) {
                                        for(int l = -3; l <= 3; l++) {
                                            for(int m = -3; m <= 3; m++) {
                                                if(k * k + l * l + m * m < 8 + (random(randomGenerator) & 1))
                                                    world.setBlock(offsetX + x + k, offsetY + y + 5 + l, offsetZ + z + m, Blocks::Leaves);
                                            }
                                        }
                                    }
                                    continue;
                                }
                                chunk->setBlock(x, y, z, Blocks::Air);
                                continue;
                            }
                            
                            if (groundHeight - 2 <= y + offsetY && y + offsetY <= SEA_LEVEL) {
                                chunk->setBlock(x, y, z, Blocks::Sand);
                                continue;
                            }
                            
                            if (y + offsetY <= stoneHeight) {
                                if (random(randomGenerator) < 50) {
                                    chunk->setBlock(x, y, z, Blocks::Coal);
                                } else {
                                    chunk->setBlock(x, y, z, Blocks::Stone);
                                }
                                continue;
                            }
                            
                            chunk->setBlock(x, y, z, Blocks::Grass);
                        }
                    }
                }
            }
        }
    }

    std::cout << "end" << std::endl;
}
