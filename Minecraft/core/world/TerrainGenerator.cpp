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
#include "ChunkManager.hpp"
#include "Constants.hpp"
#include "PerlinNoise.hpp"
#include "Utils.hpp"
#include "Time.hpp"

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

void TerrainGenerator::generate(ChunkManager& chunkManager, Chunk& chunk) {
    auto worldHeight = WORLD_HEIGHT * NUMBER_OF_BLOCKS_IN_CHUNK_Y;
    
    std::mt19937 randomGenerator(Time::now_ms());
    std::uniform_int_distribution<int> random(0, 1000);
    
    auto blocks = chunk.getBlocks();
    
    auto xSize = blocks.size();
    auto ySize = blocks.front().size();
    auto zSize = blocks.front().front().size();
    
    auto chunkCoord = chunk.getCoord();
    auto offsetX = NUMBER_OF_BLOCKS_IN_CHUNK_X * chunkCoord.x;
    auto offsetY = NUMBER_OF_BLOCKS_IN_CHUNK_Y * chunkCoord.y;
    auto offsetZ = NUMBER_OF_BLOCKS_IN_CHUNK_Z * chunkCoord.z;
    
    for (int x=0; x<xSize; ++x) {
        for (int z=0; z<zSize; ++z) {
            double perlinX = (x + offsetX) / 10.0;
            double perlinZ = (z + offsetZ) / 10.0;
            
//            std::cout << "Perlin x:" << perlinX << " z:" << perlinZ << std::endl;
            
            auto noiseForGrass = noises.front()->noise(perlinX, perlinZ, 0.3);
            auto noiseForStone = noises[1]->noise(perlinX, perlinZ, 0.4);
            
            auto groundHeight = static_cast<int>(floor(worldHeight * noiseForGrass));
            auto stoneHeight = static_cast<int>(floor(worldHeight * 0.9 * noiseForStone));
            
            for (int y=0; y<ySize; ++y) {
                if (chunk.getBlock(x, y, z) != Blocks::Air) {
                    continue;
                }
                
                if (y + offsetY > groundHeight && y + offsetY > stoneHeight) {
                    //                                std::cout << "y:" << y+offsetY << " groundHeight:" << groundHeight+1 << " SEA_LEVEL:" << SEA_LEVEL << std::endl;
                    if (y + offsetY <= SEA_LEVEL) {
                        chunk.setBlock(x, y, z, Blocks::Water);
                        continue;
                    }
                    if (groundHeight > stoneHeight && (y + offsetY) == groundHeight+1 && random(randomGenerator) < 1){
                        // Trunk
                        for(int i = 0; i < 5; i++) {
                            chunk.setBlock(x, y+i, z, Blocks::Wood);
                        }
                        
                        // Leaves
                        for(int k = -3; k <= 3; k++) {
                            for(int l = -3; l <= 3; l++) {
                                for(int m = -3; m <= 3; m++) {
                                    if(k * k + l * l + m * m < 8 + (random(randomGenerator) & 1))
                                        chunkManager.setBlock(offsetX + x + k, offsetY + y + 5 + l, offsetZ + z + m, Blocks::Leaves);
                                }
                            }
                        }
                        continue;
                    }
                    chunk.setBlock(x, y, z, Blocks::Air);
                    continue;
                }
                
                if (groundHeight - 2 <= y + offsetY && y + offsetY <= SEA_LEVEL) {
                    chunk.setBlock(x, y, z, Blocks::Sand);
                    continue;
                }
                
                if (y + offsetY <= stoneHeight) {
                    if (random(randomGenerator) < 50) {
                        chunk.setBlock(x, y, z, Blocks::Coal);
                    } else {
                        chunk.setBlock(x, y, z, Blocks::Stone);
                    }
                    continue;
                }
                
                chunk.setBlock(x, y, z, Blocks::Grass);
            }
        }
    }
}
