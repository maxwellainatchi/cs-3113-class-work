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
        player = new Entities::Player("otherpicture.png");
        frame.push_back(new Entities::Sheep("picture.png", Graphics::Coordinates({-2,-2},{2,2})));
        frame.push_back(player);
        frame.push_back(new Entities::Magician("thirdpicture.png", Graphics::Coordinates({-2,-2},{2,2})));
        
        frame[0]->translate({0.5, 0.0});
        frame[1]->translate({-0.5, 0.0});
        registerKeyHandler(SDL_SCANCODE_SPACE, [&] () {
            paused = !paused;
        });
        player->registerMovementHandlers(this);
    }
    
    void Texturey::update(float elapsed) {
        if (!paused) {
            Graphics::Game::update(elapsed);
        }
    }
}
