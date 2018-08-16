//
//  Utils.hpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

/**
 * Utils.hpp defines utility functions that are used from entire project.
 */
#include <cmath>

namespace Utils {
    /**
     * Delete pointers. Use this function instead of delete to avoid deleting same pointers twice.
     */
    template<class T>
    static inline void SafeDelete( T*& p ){
        delete (p);
        (p) = nullptr;
    }

    // This function converts decimal degrees to radians
    static inline double degreeToRadian(double deg) {
        return (deg * M_PI / 180);
    }

    //  This function converts radians to decimal degrees
    static inline double radianToDegree(double rad) {
        return (rad * 180 / M_PI);
    }
}

#endif /* Utils_hpp */
