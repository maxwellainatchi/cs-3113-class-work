//
//  Magician.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Magician.hpp"

namespace Entities {
    Magician::Magician(std::string imageName, Position::Rectangle pen):
    Entities::Entity(imageName), pen(pen), t(2.0) {
        t.action = λ() {
            this->translate({
                arc4random_uniform(pen.width()) - pen.left,
                arc4random_uniform(pen.height()) - pen.bottom
            });
        };
    }
}
