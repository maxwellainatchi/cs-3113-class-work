//
//  GenerationFunctions.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"

inline var WALL_IDENTIFIER = "wall";
inline var TEXT_IDENTIFIER = "text";

namespace Generation {
    inline std::set<Entity*> generateWalls(Game* g, State state, bool hidden) {
        let wallWidth = 0.01f;
        std::set<Entity*> retVal;
        for (var i = 0; i < 4; ++i) {
            var wall = new Entity();
            wall->willSetup = [=](){
                switch (static_cast<Vec2::Direction>(i + 1)) {
                    case Vec2::left:
                        wall->bounds = {
                            g->window.uv.bottomLeft(),
                            wallWidth, g->window.uv.height()
                        };
                        break;
                    case Vec2::right:
                        wall->bounds = {
                            g->window.uv.bottomRight(),
                            -wallWidth, g->window.uv.height()
                        };
                        break;
                    case Vec2::down:
                        wall->bounds = {
                            g->window.uv.bottomLeft(),
                            g->window.uv.width(), wallWidth
                        };
                        break;
                    case Vec2::up:
                        wall->bounds = {
                            g->window.uv.topLeft(),
                            g->window.uv.width(), -wallWidth
                        };
                        break;
                    default: SDL_assert(false);
                }
                wall->texture = new Texture("blueLine.png");
                wall->hidden = hidden;
                wall->identifier = WALL_IDENTIFIER;
            };
            g->frames[state].insert(wall);
            retVal.insert(wall);
        }
        return retVal;
    }
    
    inline Entity* generateLetter(Game* g, State state, char c, float height, Vec2 offset, SpriteSheet* font, Rectangle pen) {
        var letter = new Entity();
        letter->willSetup = [=]() {
            letter->texture = new Texture(font->sheetName);
            letter->identifier = TEXT_IDENTIFIER;
            letter->intangible = true;
            var coords = font->atlas.find(std::string(1,c));
            guard (coords != font->atlas.end()) else { letter->texture->loaded = false; return; }
            letter->texture->coords = coords->second;
            letter->bounds = {pen.topLeft() + offset, height, -height};
            guard(letter->bounds.bottom > pen.bottom) else { letter->hidden = true; }
        };
        g->frames[state].insert(letter);
        return letter;
    }
    
    inline std::vector<Entity*> generateText(Game* g, State state, std::string text, float size, SpriteSheet* font, Rectangle pen) {
        std::vector<Entity*> letters;
        var lines = tokenize(text, '\n');
        guard (font->atlas.size()) else { return {}; }
        var width = size * font->xSpacing;
        var height = size * g->window.uv.height()/32.f;
        Vec2 offset = {0, 0};
        for (var line in lines) {
            var words = tokenize(line, ' ');
            for (var word in words) {
                if (offset.x != 0 && offset.x + width * word.size() > pen.width()) {
                    offset.x = 0;
                    offset.y -= height;
                }
                for (var c in (word + ' ')) {
                    var letter = generateLetter(g, state, c, height, offset, font, pen);
                    offset.x += width;
                    if (offset.x + width > pen.width()) {
                        offset.x = 0;
                        offset.y -= height;
                    }
                    letters.push_back(letter);
                }
            }
            offset.x = 0;
            offset.y -= height;
        }
        return letters;
    }
}
