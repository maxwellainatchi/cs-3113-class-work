//
//  EventFramework.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "EventFramework.hpp"

namespace Graphics {
    void EventFramework::registerKeyHandler(SDL_Scancode code, std::function<void()> handler, bool keyUp) {
        if (keyUp) keyUpHandlers[code] = handler;
        else keyDownHandlers[code] = handler;
    }
}
