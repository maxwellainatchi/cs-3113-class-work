//
//  Space Invaders.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/2/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Space Invaders.hpp"

namespace Games {
    SpaceInvaders::SpaceInvaders(): Graphics::Game("Space Invaders") {}
    
    Entities::Player* SpaceInvaders::generatePlayer() {
        var player = new Entities::Player(spriteSheet, Assets::Sprites::player, window.uv);
        // Appearance
        player->scale({0.5,0.5});
        player->setOrigin({
            window.uv.center().x,
            window.uv.bottom
        });
        
        // Movement
        player->controlScheme = ControlSchemes::ArrowKeys_LEFTRIGHT;
        player->registerMovementHandlers(this, {RUNNING});
        player->speed = 2;
        
        // Shooting
        registerKeyHandler(SDL_SCANCODE_SPACE, {RUNNING}, [&] () { generateBullet(); });
        
        frames[RUNNING].insert(player);
        return player;
    }
    
    Entities::Sprite* SpaceInvaders::generateEnemy(Position::Point origin, int enemyType) {
        var enemy = new Entities::Sprite(spriteSheet, Assets::Sprites::Enemies::base + std::to_string(enemyType));
        if (!enemy->texture.loaded) { return nullptr; }
        enemy->scale(enemyScale);
        enemy->setOrigin(origin);
        enemies.push_back(enemy);
        frames[RUNNING].insert(enemy);
        return enemy;
    }
    
    void SpaceInvaders::generateEnemyGrid(int numRows, int numCols) {
        var dummyEnemy = generateEnemy({0,0}, 1);
        var padding = window.uv.width()/numRows/2 + dummyEnemy->bounds.width()/2;
        Position::Point origin = {
            window.uv.right - padding,
            window.uv.top - dummyEnemy->bounds.height() - 0.1f
        };
        Position::Vector2D offset = {
            window.uv.width() / (numCols + 1),
            dummyEnemy->bounds.height()
        };
        
        frames[RUNNING].erase(dummyEnemy);
        for (var row = 0; row < numRows; ++row) {
            for (var col = 0; col < numCols; ++col) {
                generateEnemy(origin, (col % 2 + row % 2) % 2 + 1);
                origin.x -= offset.x;
                if (origin.x < window.uv.left) {
                    origin.x = window.uv.right - padding;
                    origin.y -= offset.y;
                }
            }
        }
    }
    
    void SpaceInvaders::generateBullet(bool fromEnemy) {
        Entities::Entity* entity;
        Position::Point origin;
        Position::Vector2D velocity = {0,0};
        if (fromEnemy) {
            entity = enemies[arc4random_uniform((uint)enemies.size())];
            origin.y = entity->bounds.bottom - bulletSize.y;
            velocity.y = -2.0f;
        } else {
            guard(playerCanFire) else { return; }
            playerCanFire = false;
            playerBulletTimer->start();
            entity = player1;
            origin.y = entity->bounds.top;
            velocity.y = 3.0f;
        }
        origin.x = entity->bounds.center().x;
        var bullet = new Entities::Bullet(Assets::Images::whiteLine, window.uv, velocity);
        bullet->setCoordinates({
            origin,
            bulletSize.x,
            bulletSize.y
        });
        bullet->onCollide = [&, bullet, fromEnemy] (Entities::Entity* otherEntity) {
            guard (otherEntity != bullet) else { return; }
            guard (!fromEnemy || fromEnemy && otherEntity == player1) else { return; }
            otherEntity->hidden = true;
            otherEntity->intangible = true;
            bullet->hidden = true;
            bullet->intangible = true;
            guard (!fromEnemy) else {
                this->state = LOSE;
                return;
            }
            --livingEnemies;
            guard (livingEnemies) else {
                    this->state = WIN;
                }
        };
        bullets.insert(bullet);
        frames[RUNNING].insert(bullet);
    }
    
    void SpaceInvaders::reset() {
        guard (player1 != nullptr) else {
            player1 = generatePlayer();
        }
        player1->hidden = false;
        player1->intangible = false;
        if (enemies.size()) {
            for (auto enemy : enemies) {
                enemy->hidden = false;
                enemy->intangible = false;
            }
        } else {
            generateEnemyGrid(numRows, numCols);
        }
        livingEnemies = numRows*numCols;
        for (var bullet : bullets) {
            frames[RUNNING].erase(bullet);
        }
        
    }
    
    void SpaceInvaders::setup() {
        pausekey = SDL_SCANCODE_P;
        registerKeyHandler(SDL_SCANCODE_SPACE, {WIN, LOSE}, [&] () {
            this->reset();
            this->state = RUNNING;
        });
        registerKeyHandler(SDL_SCANCODE_SPACE, {WIN, LOSE}, selector(this->reset));
        
        
        playerBulletTimer->action = [&] () {
            playerCanFire = true;
            this->playerBulletTimer->stop();
        };
        enemyMovementTimer->action = [&] () {
            if (enemies.size() == 0) { return; }
            auto without = enemies.back()->bounds.withoutness(window.uv);
            var offset = Position::Vector2D();
            if (without.x < 0) {
                enemyVelocity.x = -enemyVelocity.x;
                offset.y = enemyVelocity.y;
            }
            without = enemies[0]->bounds.withoutness(window.uv);
            if (without.x > 0) {
                enemyVelocity.x = -enemyVelocity.x;
                offset.y = enemyVelocity.y;
            }
            offset.x = enemyVelocity.x;
            for (auto enemy: enemies) {
                enemy->translate(offset);
            }
        };
        enemyBulletTimer->action = [&] () {
            if (arc4random_uniform(UINT32_MAX) < enemyShootChance * UINT32_MAX) {
                this->generateBullet(true);
            }
        };
        
        // Add all the timers
        timers[RUNNING].insert(playerBulletTimer);
        timers[RUNNING].insert(enemyMovementTimer);
        timers[RUNNING].insert(enemyBulletTimer);
        
        // Running frame
        spriteSheet = new Graphics::SpriteSheet(Assets::Images::spritesheet, {0.33,1}, {
            Assets::Sprites::Enemies::first,
            Assets::Sprites::Enemies::second,
            Assets::Sprites::player
        });
        reset();
        
        
        // Paused frame
        pausedText = new Entities::TitleText(Assets::Text::paused, {});
        frames[WIN].insert(new Entities::TitleText(Assets::Text::win, {}));
        frames[LOSE].insert(new Entities::TitleText(Assets::Text::lose, {}));
        frames[PAUSED].insert(pausedText);
    }
    
    void SpaceInvaders::willStart() {
        enemyMovementTimer->start();
        enemyBulletTimer->start();
        playerBulletTimer->start();
        state = RUNNING;
    }
}
