//
//  TitleText.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef TitleText_hpp
#define TitleText_hpp

#include "libraries.h"
#include "Entity.hpp"

//TODO: Figure out how to render text lol
namespace Entities {
    class TitleText: public Entity {
    public:
        // Inherited
        void update(float elapsed);
    };
}

#endif /* TitleText_hpp */
