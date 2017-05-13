//
//  GenerationFunctions.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"

struct EntityInfo {
    std::string category;
    std::string textureName;
};

inline const EntityInfo WALL_INFO = {"wall", "blueLine.png"};
inline const EntityInfo TEXT_INFO = {"text", ""};
inline const EntityInfo PLAYER_INFO = {"player", "whiteLine.png"};
inline const EntityInfo BULLET_INFO = {"bullet", "whiteLine.png"};
inline const EntityInfo ENEMY_INFO = {"enemy", "blueLine.png"};

namespace Generation {
    // MARK: - Static entities
    
    inline std::set<Entity*> generateWalls(Game* g, State state, bool hidden) {
        let visiblePortion = 0.01f;
        let wallWidth = 1.f;
        std::set<Entity*> retVal;
        std::vector<Direction> directions = {Direction::left, Direction::right, Direction::down, Direction::up};
        for (var direction in directions) {
            var wall = new Entity();
            wall->willSetup = [=](){
                switch (direction) {
                    case Direction::left:
                        wall->bounds = {
                            g->window.uv.bottomLeft() + Vector(visiblePortion, 0.f),
                            -wallWidth, g->window.uv.height()
                        };
                        g->innerBounds.left += visiblePortion;
                        break;
                    case Direction::right:
                        wall->bounds = {
                            g->window.uv.bottomRight() + Vector(-visiblePortion, 0.f),
                            wallWidth, g->window.uv.height()
                        };
                        g->innerBounds.right -= visiblePortion;
                        break;
                    case Direction::down:
                        wall->bounds = {
                            g->window.uv.bottomLeft() + Vector(0.f, visiblePortion),
                            g->window.uv.width(), -wallWidth
                        };
                        g->innerBounds.bottom += visiblePortion;
                        break;
                    case Direction::up:
                        wall->bounds = {
                            g->window.uv.topLeft() + Vector(0.f, -visiblePortion),
                            g->window.uv.width(), wallWidth
                        };
                        g->innerBounds.top -= visiblePortion;
                        break;
                    default: SDL_assert(false);
                }
                wall->texture = new Texture(WALL_INFO.textureName);
                wall->hidden = hidden;
                wall->category = WALL_INFO.category;
            };
            g->frames[state].insertStatic(wall);
            retVal.insert(wall);
        }
        return retVal;
    }
    
    inline Entity* generateLetter(Game* g, State state, char c, float height, Vector offset, SpriteSheet* font, Rectangle pen) {
        var letter = new Entity(*font, std::string(1, c));
        letter->category = TEXT_INFO.category;
        letter->type = std::string(1, c);
        letter->intangible = true;
        letter->bounds = {pen.topLeft() + offset, height, -height};
        guard(letter->bounds.bottom > pen.bottom) else { letter->hidden = true; }
        g->frames[state].insertBackground(letter);
        return letter;
    }
    
    inline std::vector<Entity*> generateText(Game* g, State state, std::string text, float size, SpriteSheet* font, Rectangle pen) {
        std::vector<Entity*> letters;
        var lines = tokenize(text, '\n');
        guard (font->atlas.size()) else { return {}; }
        var width = size * font->xSpacing;
        var height = size * g->window.uv.height()/32.f;
        Vector offset = {0, 0};
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
    
    // MARK: - Dynamic Entities
    
    inline Entity* configurePlayer(Entity* player, Game* g, State state, Rectangle area, float speed, ControlScheme scheme, std::function<CollisionAction(Entity*, Game*)> collision) {
        player->category = PLAYER_INFO.category;
        player->bounds = area;
        for (var control in scheme) {
            g->registerContinuousKeyHandler(control.second, {state}, [=]() {
                if (control.first == Direction::up && player->velocity.y > SMALL_AMOUNT) { return; }
                let newDir = Vector(control.first);
                if (newDir.x) { player->velocity.x = newDir.x * speed; }
                if (newDir.y) { player->velocity.y = newDir.y * speed; }
            });
        }
        player->onCollide = collision(player, g);
        g->frames[state].insertDynamic(player);
        return player;
    }
    
    // For backwards compatibility
    inline Entity* generatePlayer(Game* g, State state, Rectangle area, float speed, ControlScheme scheme, std::function<CollisionAction(Entity*, Game*)> collision) {
        Entity* player = new Entity();
        player->texture = new Texture(PLAYER_INFO.textureName);
        return configurePlayer(player, g, state, area, speed, scheme, collision);
    }
    
    inline Entity* configureAndInsertBullet(Game* g, State state, Entity* bullet, Entity* from, SimilarityLevel level, Direction d, float speed, std::function<CollisionAction(Entity*, Game*)> collision) {
        bullet->category = BULLET_INFO.category;
        bullet->texture = new Texture(BULLET_INFO.textureName);
        bullet->velocity = Vector(d) * speed;
        bullet->bounds = {
            {from->bounds.center().x, from->bounds.top + SMALL_AMOUNT},
            0.05f,
            0.25f
        };
        bullet->onCollide = [=](Entity* other, float elapsed) {
            guard (other->category != WALL_INFO.category) else {
                bullet->hidden = true;
                bullet->intangible = true;
                bullet->paused = true;
                return;
            }
            guard ( other->identifierForSimilarityLevel(level) != from->identifierForSimilarityLevel(level)) else { return; }
            collision(bullet, g)(other, elapsed);
        };
        g->frames[RUNNING].insertDynamic(bullet);
        return bullet;
    }
    
    // MARK: - Helper functions
    
    inline SpriteSheet* loadFont(std::string fontName, int rows, int cols, float xSpacing, std::string alphabet) {
        var font = new SpriteSheet();
        font->sheet = new Texture(fontName);
        font->xSpacing = xSpacing;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                let index = row * cols + col;
                guard (index < alphabet.length()) else { return font; }
                font->atlas.insert({
                    std::string(1, alphabet[index]),
                    {{1.f/16 * col, 1.f/16 * row}, 1.f/cols, 1.f/rows}
                });
            }
        }
        return font;
    }
}
