//
//  Magician.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Magician_hpp
#define Magician_hpp

#include "libraries.h"
#include "Entity.hpp"
#include "Timer.hpp"

namespace Entities {
    class Magician: public Entity {
    public:
        Position::Rectangle pen;
        Graphics::Timer t;
        
        Magician(std::string imageName, Position::Rectangle pen);
    };
}

#endif /* Magician_hpp */
