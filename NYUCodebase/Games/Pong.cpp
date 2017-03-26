//
//  Pong.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Pong.hpp"

namespace Games {
    Pong::Pong(): Graphics::Game("Pong") {}
    
    void Pong::checkPaddleCollision() {
        if (player1->isCollidingWith(ball) || player2->isCollidingWith(ball)) {
            ball->velocity.x = -ball->velocity.x;
        }
    }
    
    void Pong::resetLives() {
        player1Lives.clear();
        player2Lives.clear();
        
        int numLives = 5;
        float lifePadding = 0.1f;
        float lifeMargin = 0.7f;
        float lifeSize = 0.1f;
        for (int i = 0; i < numLives; ++i) {
            Entities::Entity* life = new Entities::Entity("whiteLine.png");
            life->setCoordinates({
                {
                    workingArea.left + i*(lifeSize + lifePadding) + lifeMargin,
                    workingArea.top - lifeSize - lifePadding
                },
                {
                    workingArea.left + (i+1)*lifeSize + i*lifePadding + lifeMargin,
                    workingArea.top - lifePadding
                }
            });
            player1Lives.push_back(life);
        }
        
        for (int i = 0; i < numLives; ++i) {
            Entities::Entity* life = new Entities::Entity("whiteLine.png");
            life->setCoordinates({
                {
                    workingArea.right - i*(lifeSize + lifePadding) - lifeMargin,
                    workingArea.top - lifeSize - lifePadding
                },
                {
                    workingArea.right - (i+1)*lifeSize - i*lifePadding - lifeMargin,
                    workingArea.top - lifePadding
                }
            });
            player2Lives.push_back(life);
        }
    }
    
    void Pong::drawWalls() {
        for (int i = 0; i < 2; ++i) {
            walls.push_back(new Entities::Entity("blueLine.png"));
        }
        walls[0]->setCoordinates({window.uv.topLeft(), {
            window.uv.right,
            window.uv.top - wallSize
        }});
        walls[1]->setCoordinates({window.uv.bottomLeft(), {
            window.uv.right,
            window.uv.bottom + wallSize
        }});
        
        workingArea = Position::Rectangle({
            {window.uv.left, window.uv.bottom + wallSize},
            {window.uv.right, window.uv.top - wallSize}
        });
    }
    
    void Pong::drawCenterLine() {
        float lineLength = workingArea.height() / lineCount;
        for (int i = 0; i < lineCount; ++i) {
            Entities::Entity* segment = new Entities::Entity("blueLine.png");
            segment->setCoordinates({
                {
                    workingArea.center().x - wallSize/2.0f,
                    workingArea.top - i * lineLength - 0.5f*linePadding
                }, {
                    workingArea.center().x + wallSize/2.0f,
                    workingArea.top - (i + 1) * lineLength + 0.5f*linePadding
                }
            });
            midLine.push_back(segment);
        }
    }
    
    int Pong::didLose() {
        var without = ball->bounds.withoutness(window.uv);
        if (without.x > 0)
            return 2;
        else if (without.x < 0)
            return 1;
        else
            return 0;
    }
    
    void Pong::setup() {
        std::vector<Entities::Entity*> frame;
        drawWalls();
        drawCenterLine();
        resetLives();
        
        //MARK: Mechanics
        player1 = new Entities::Player(spriteSheet, "whiteline", workingArea);
        player2 = new Entities::Player(spriteSheet, "whiteLine", workingArea);
        ball = new Entities::Ball("whiteLine.png", workingArea);
        
        Position::Vector2D paddleSize = {0.1, 0.75};
        Position::Vector2D ballSize = {0.1, 0.1};
        Position::Vector2D padding = {0.2,0};
        
        Position::Point origin1 = {workingArea.left, workingArea.top - paddleSize.y};
        origin1 = origin1 + padding;
        
        Position::Point origin2 = {workingArea.right - paddleSize.x, workingArea.top - paddleSize.y};
        origin2 = origin2 - padding;
        
        Position::Point ballOrigin = {
            window.uv.center().x - paddleSize.x / 2,
            window.uv.center().y + paddleSize.y / 2
        };
        
        var bounds1 = Position::Rectangle(origin1, origin1 + paddleSize);
        var bounds2 = Position::Rectangle(origin2, origin2 + paddleSize);
        var ballBounds = Position::Rectangle(ballOrigin, ballOrigin + ballSize);
        
        player1->setCoordinates(bounds1);
        player2->setCoordinates(bounds2);
        ball->setCoordinates(ballBounds);
        
        player1->controlScheme = Graphics::EventFramework::ControlSchemes::ArrowKeys_UPDOWN;
        player2->controlScheme = Graphics::EventFramework::ControlSchemes::WASD_UPDOWN;
        
        player1->registerMovementHandlers(this, {RUNNING});
        player2->registerMovementHandlers(this, {RUNNING});
        
        registerKeyHandler(SDL_SCANCODE_R, {RUNNING}, [&] () {
            ball->reset(window.uv);
            if (paused) { paused = false; }
            resetLives();
        });
        
        registerKeyHandler(SDL_SCANCODE_SPACE, {RUNNING}, [&] () {
            if (player1Lives.size() > 0 && player2Lives.size() > 0) {
                if (ball->paused) {
                    ball->paused = false;
                } else {
                    paused = !paused;
                }
            } else {
                resetLives();
            }
        });
        
        player1->speed = playerSpeed;
        player2->speed = playerSpeed;
        ball->velocity = {ballSpeed, ballSpeed};
        
        //MARK: Rendering
        frame.push_back(player1);
        frame.push_back(player2);
        frame.push_back(ball);
        for (Entities::Entity* wall : walls) {
            frame.push_back(wall);
        }
        for (Entities::Entity* segment : midLine) {
            frame.push_back(segment);
        }
        
        frames[RUNNING] = std::set<Entities::Entity*>(frame.begin(), frame.end());
        
        ball->reset(window.uv);
    }
    
    void Pong::update(float elapsed) {
        checkPaddleCollision();
        int loser = didLose();
        if (!ball->paused && loser) {
            if (loser == 1) {
                player1Lives.pop_back();
            } else {
                player2Lives.pop_back();
            }
            ball->reset(workingArea);
            //TODO: TODO: Render losing text
        }
        if (!paused) {
            Graphics::Game::update(elapsed);
            // These are separate because they get removed
            for (Entities::Entity* life : player1Lives) {
                life->update(elapsed);
            }
            for (Entities::Entity* life : player2Lives) {
                life->update(elapsed);
            }
        }
    }
    
    void Pong::render() {
        Game::render();
        for (Entities::Entity* life : player1Lives) {
            life->draw(shader);
        }
        for (Entities::Entity* life : player2Lives) {
            life->draw(shader);
        }
    }
}
