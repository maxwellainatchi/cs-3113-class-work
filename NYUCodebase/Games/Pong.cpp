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
        
        var numLives = 5;
        var padding = 0.1f;
        var size = 0.1f;
        Position::Point margin = {0.7f, -0.1f - size};
        var origin = workingArea.topLeft() + margin;
        for (var i = 0; i < numLives; ++i) {
            Entities::Sprite* life = new Entities::Sprite(spriteSheet, WHITE_LINE);
            life->setCoordinates({origin, size, size});
            player1Lives.push_back(life);
            origin += {size + padding, 0};
        }
        
        margin.x = -margin.x;
        origin = workingArea.topRight() + margin;
        for (var i = 0; i < numLives; ++i) {
            Entities::Sprite* life = new Entities::Sprite(spriteSheet, WHITE_LINE);
            life->setCoordinates({origin, size, size});
            player1Lives.push_back(life);
            origin -= {size + padding, 0};
        }
    }
    
    void Pong::drawWalls() {
        for (int i = 0; i < 2; ++i) {
            walls.push_back(new Entities::Entity("blueLine.png"));
        }
        walls[0]->setCoordinates({window.uv.topLeft(), window.uv.width(), -wallSize});
        walls[1]->setCoordinates({window.uv.bottomLeft(), window.uv.width(), wallSize});
        
        workingArea = Position::Rectangle({
            {window.uv.left, window.uv.bottom + wallSize},
            {window.uv.right, window.uv.top - wallSize}
        });
    }
    
    void Pong::drawCenterLine() {
        var lineLength = workingArea.height() / lineCount;
        Position::Point origin = {
            window.uv.center().x,
            window.uv.top
        };
        for (var i = 0; i < lineCount; ++i) {
            Entities::Entity* segment = new Entities::Entity("blueLine.png");
            segment->setCoordinates({
                origin,
                lineLength,
                wallSize
            });
            midLine.push_back(segment);
            origin += {0, lineLength + linePadding};
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
        std::set<Entities::Entity*> frame;
        drawWalls();
        drawCenterLine();
        resetLives();
        
        //MARK: Mechanics
        player1 = new Entities::Player(spriteSheet, WHITE_LINE, workingArea);
        player2 = new Entities::Player(spriteSheet, WHITE_LINE, workingArea);
        ball = new Entities::Ball("whiteLine.png", workingArea);
        
        Position::Vector2D paddleSize = {0.1, 0.75};
        Position::Vector2D ballSize = {0.1, 0.1};
        Position::Vector2D padding = {0.2,0};
        
//        Position::Point origin1 = {
//            workingArea.right - paddleSize.x,
//            workingArea.top - paddleSize.y
//        };
        Position::Point origin1 = {workingArea.left, workingArea.top - paddleSize.y};
        origin1 += padding;
        
        Position::Point origin2 = {workingArea.right - paddleSize.x, workingArea.top - paddleSize.y};
        origin2 -= padding;
        
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
        frame.insert(player1);
        frame.insert(player2);
        frame.insert(ball);
        for (Entities::Entity* wall : walls) {
            frame.insert(wall);
        }
        for (Entities::Entity* segment : midLine) {
            frame.insert(segment);
        }
        
        frames[RUNNING] = frame;
        
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
