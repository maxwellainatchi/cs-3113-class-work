//
//  EventFramework.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef EventFramework_hpp
#define EventFramework_hpp

#include "libraries.h"

namespace Graphics {
    class EventFramework {
    public:
        std::map<SDL_Scancode, std::function<void()>> keyDownHandlers;
        std::map<SDL_Scancode, std::function<void()>> keyUpHandlers;
        
        void registerKeyHandler(SDL_Scancode code, std::function<void()> handler, bool keyUp  = false);
    };
}

#endif /* EventFramework_hpp */
