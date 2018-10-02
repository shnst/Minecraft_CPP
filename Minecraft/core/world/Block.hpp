//
//  Block.hpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/14/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Block_h
#define Block_h

#include <array>
#include <string>
#include <vector>

namespace Blocks{
    enum Types {
        Air,
        Grass,
        Leaves,
        Stone,
        Sand,
        Water,
        Glass,
        Brick,
        Coal,
        Wood,
        
    };
    
    static bool isTransparent(Types type) {
        switch (type) {
            case Air:
            case Glass:
            case Water:
                return true;
            default:
                return false;
        }
    }
    
    static bool isPassable(Types type) {
        switch (type) {
            case Air:
            case Water:
                return true;
            default:
                return false;
        }
    }
    
    struct BlockTexture {
        BlockTexture(const std::string& textureName, const std::array<double, 4>& top, const std::array<double, 4>& side, const std::array<double, 4>& bottom)
        :textureName(textureName)
        ,top(top)
        ,side(side)
        ,bottom(bottom)
        {}
        
        const std::string textureName;
        const std::array<double, 4> top;
        const std::array<double, 4> side;
        const std::array<double, 4> bottom;
    };
    
    static const std::vector<BlockTexture> blockTextures = {
        BlockTexture(
                     "blocks.dds",
                     {0, 0, 16.0/256.0, 16.0/16.0},
                     {0, 0, 16.0/256.0, 16.0/16.0},
                     {0, 0, 16.0/256.0, 16.0/16.0}), // Air
        BlockTexture(
                     "blocks.dds",
                     {48.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {32.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {16.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Grass
        BlockTexture(
                     "blocks.dds",
                     {64.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {64.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {64.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Leaves
        BlockTexture(
                     "blocks.dds",
                     {96.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {96.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {96.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Stone
        BlockTexture(
                     "blocks.dds",
                     {112.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {112.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {112.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Sand
        BlockTexture(
                     "blocks.dds",
                     {128.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {128.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {128.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Water
        BlockTexture(
                     "blocks.dds",
                     {144.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {144.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {144.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Glass
        BlockTexture(
                     "blocks.dds",
                     {160.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {160.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {160.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Brick
        BlockTexture(
                     "blocks.dds",
                     {176.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {176.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {176.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Coal
        BlockTexture(
                     "blocks.dds",
                     {192.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {80.0/256.0, 0, 16.0/256.0, 16.0/16.0},
                     {192.0/256.0, 0, 16.0/256.0, 16.0/16.0}), // Wood
    };
}

namespace BlockFace {
    enum Types {
        Top,
        Bottom,
        Side1,
        Side2,
        Side3,
        Side4,
    };
};

#endif /* Block_h */
