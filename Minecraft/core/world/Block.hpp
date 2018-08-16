//
//  Block.hpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/14/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Block_h
#define Block_h

namespace Blocks{
    enum Types {
        Air,
        Stone,
        GrassBlock,
        Dirt,
        Water,
        Sand,
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
