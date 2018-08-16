//
//  Coordinates.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Coordinates_hpp
#define Coordinates_hpp

#include "Constants.hpp"
#include "Size.hpp"
#include "Vector2d.hpp"

/**
 * Coordinates.hpp defines functions that are related to coordinates and window size calculation.
 */

inline vec2d tileToPoint(const vec2n& tile){
    return vec2d(
                tile.x * TILE_SIZE_IN_POINT,
                tile.y * TILE_SIZE_IN_POINT);
}

inline vec2n pointToTile(const vec2d& point) {
    return vec2n(
                point.x / TILE_SIZE_IN_POINT,
                point.y / TILE_SIZE_IN_POINT);
}

inline bool isInsideBound(const vec2n& tileCoordinates) {
    return 0 <= tileCoordinates.x && tileCoordinates.x < FIELD_WIDTH
            && 0 <= tileCoordinates.y && tileCoordinates.y < FIELD_HEIGHT;
}

inline vec2d getFieldSizeInPoint() {
    return vec2d(
                FIELD_WIDTH * TILE_SIZE_IN_POINT,
                FIELD_HEIGHT * TILE_SIZE_IN_POINT);
}

inline Size getWindowSize() {
    return Size(WINDOW_WIDTH, WINDOW_HEIGHT);
}

#endif /* Coordinates_hpp */
