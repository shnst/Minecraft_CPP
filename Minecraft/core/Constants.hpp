//
//  Constants.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Constants_hpp
#define Constants_hpp

//#define MAPPING_MODE

/**
 * Constants.hpp defines constant global variables.
 */

constexpr double TILE_SIZE_IN_POINT = 1.0;

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 960;


#ifdef MAPPING_MODE
constexpr int NUMBER_OF_BLOCKS_IN_CHUNK_X = 50;
constexpr int NUMBER_OF_BLOCKS_IN_CHUNK_Y = 50;
constexpr int NUMBER_OF_BLOCKS_IN_CHUNK_Z = 50;

constexpr int HORIZONTAL_CHUNK_LOAD_DISTANCE = 20;
constexpr int WORLD_HEIGHT = 5;
#else
constexpr int NUMBER_OF_BLOCKS_IN_CHUNK_X = 5;
constexpr int NUMBER_OF_BLOCKS_IN_CHUNK_Y = 5;
constexpr int NUMBER_OF_BLOCKS_IN_CHUNK_Z = 5;

constexpr int HORIZONTAL_CHUNK_LOAD_DISTANCE = 40;
constexpr int WORLD_HEIGHT = 5;
#endif

constexpr int SEA_LEVEL = WORLD_HEIGHT * NUMBER_OF_BLOCKS_IN_CHUNK_Y / 2 ;


#endif /* Constants_hpp */
