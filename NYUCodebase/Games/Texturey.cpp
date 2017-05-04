//
//  Texturey.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/14/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include <stdio.h>

#include "Game.hpp"

namespace Games {
    namespace Texturey {
        Entity* animal(Game* g) {
            var animal = new Entity();
            animal->setup = λ() {
                animal->texture = Texture("picture.png");
                animal->bounds = {{
                    arc4random() * g->window.uv.width() + g->window.uv.left, arc4random() * g->window.uv.height() + g->window.uv.bottom
                },  1, 1
                };
            };
            //            animal->update = λ(float elapsed) {
            //
            //            };
            return animal;
        }
        
        Game* createGame() {
            var game = new Game("Texturey");
            game->frames[RUNNING].insert(animal(game));
            return game;
        }
        
        void play() {
            var game = createGame();
            game->start();
        }
    }
}
