//
//  Taz.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Taz_hpp
#define Taz_hpp

#include "libraries.h"
#include "animal.hpp"

namespace Graphics {
    class Taz: public Animal {
    public:
        float angle;
        float speed;
        
        Taz(std::string imageName, Coordinates pen, float speed = 1.0);
        
        // Inherited
        virtual void move(float elapsed);
    };
}

#endif /* Taz_hpp */
