//
//  Texturey.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Texturey.hpp"

namespace Games {
    Texturey::Texturey() : Graphics::Game("Texturey") {}
    
    void Texturey::setup() {
        //NOTE: Taz isn't working right now due to rotation being broken
        
        // Add Entities to frame
        frame.push_back(new Entities::Sheep("thirdpicture.png", window.uv));
        frame.push_back(new Entities::Sheep("picture.png", window.uv));
        frame.push_back(new Entities::Magician("otherpicture.png", window.uv));
        
        // Assign initial positions
        Graphics::Vector2D size = {1,1};
        frame[1]->setCoordinates({window.uv.bottomLeft, window.uv.bottomLeft + size});
        
        // Add pause
        registerKeyHandler(SDL_SCANCODE_SPACE, [&] () {
            paused = !paused;
        });
    }
    
    void Texturey::update(float elapsed) {
        if (!paused) {
            Graphics::Game::update(elapsed);
        }
    }
}
