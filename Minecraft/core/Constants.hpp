//
//  Constants.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Constants_hpp
#define Constants_hpp

/**
 * Constants.hpp defines constant global variables.
 */

// X(meter) * METER_TO_POINT_RATIO = Y(screen point)
const double METER_TO_POINT_RATIO = 52.0;
const double TILE_SIZE_IN_POINT = 5.2;

const double CAMERA_DEFAULT_WIDTH_IN_POINT = METER_TO_POINT_RATIO * 10;
const double CAMERA_DEFAULT_HEIGHT_IN_POINT = METER_TO_POINT_RATIO * 10;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int FIELD_WIDTH = 200;
const int FIELD_HEIGHT = 200;

const float PI_OVER_180 = 0.0174532925;

const int CHUNK_SIZE = 10;

const int NUMBER_OF_CHUNKS_IN_WORLD_X = 10;
const int NUMBER_OF_CHUNKS_IN_WORLD_Y = 3;
const int NUMBER_OF_CHUNKS_IN_WORLD_Z = 10;

const int SEA_LEVEL = CHUNK_SIZE * NUMBER_OF_CHUNKS_IN_WORLD_Y / 2 - 2;


#endif /* Constants_hpp */
