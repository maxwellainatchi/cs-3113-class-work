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
        
        std::set<Entities::Entity*> frame;
        
        // Add Entities to frame
        frame.insert(new Entities::Sheep("thirdpicture.png", window.uv));
        auto sheep = new Entities::Sheep("picture.png", window.uv);
        frame.insert(sheep);
        frame.insert(new Entities::Magician("otherpicture.png", window.uv));
        
        // Assign initial positions
        Position::Vector2D size = {1,1};
        sheep->setCoordinates({window.uv.bottomLeft(), size.x, size.y});
        
        frames[RUNNING] = frame;
    }
    
    void Texturey::update(float elapsed) {
        Game::update(elapsed);
    }
}
