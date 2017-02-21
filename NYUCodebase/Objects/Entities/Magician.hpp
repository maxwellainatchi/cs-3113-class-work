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

namespace Entities {
    class Magician: public Entity {
    public:
        float apparitionTime;
        float timeSinceLastApparition;
        Graphics::Coordinates pen;
        
        Magician(std::string imageName, Graphics::Coordinates pen);
        
        // Inherited
        virtual void update(float elapsed);
    };
}

#endif /* Magician_hpp */
