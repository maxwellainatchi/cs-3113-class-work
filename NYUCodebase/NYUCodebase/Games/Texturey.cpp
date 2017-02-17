//
//  Texturey.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Texturey.hpp"

namespace Games {
    void Texturey::setup() {
        frame.push_back(new Graphics::Sheep("picture.png", Graphics::Coordinates({-2,-2},{2,2})));
        frame.push_back(new Graphics::Taz("otherpicture.png", Graphics::Coordinates({-2,-2},{2,2})));
        frame.push_back(new Graphics::Magician("thirdpicture.png", Graphics::Coordinates({-2,-2},{2,2})));
        
        frame[0]->translate({0.5, 0.0});
        frame[1]->translate({-0.5, 0.0});
    }
    
    void Texturey::update(float elapsed) {
        Graphics::Game::update(elapsed);
    }
}
