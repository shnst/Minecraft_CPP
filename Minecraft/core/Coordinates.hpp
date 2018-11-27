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

inline Size getWindowSize() {
    return Size(WINDOW_WIDTH, WINDOW_HEIGHT);
}

#endif /* Coordinates_hpp */
