//
//  Platformer.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 5/1/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef PLATFORMER_CPP
#define PLATFORMER_CPP

#include "Game.hpp"
#include "functionlibraries.h"

#define LOSE "lose"

namespace Games { namespace Platformer {
    inline int rows = 9;
    inline IntPair screenPages = {1,2};
    inline SpriteSheet platformerBlocks;
    inline SpriteSheet* font;
    inline Grid gameGrid;
    inline std::vector<std::vector<Entity*>> blocks;
    
    inline void loadResources(Game* g) {
        LOG("Loading resources");
        DEBUG_TIME(true, "Resource Load");
        
        // Font
        std::string alphabet =
        std::string(16, (char) 26) +
        std::string(16, (char) 26) +
        " !\"#$%&'()*+,-./"
        "0123456789:;<=>?"
        "@ABCDEFGHIJKLMNO"
        "PQRSTUVWXYZ[\\]^_"
        "`abcdefghijklmno"
        "pqrstuvwxyz{|}~␀";
        font = Generation::loadFont(/* Filename: */             "font1.png",
                                    /* Number of Rows: */       16,
                                    /* Number of Cols: */       16,
                                    /* Horizontal Spacing: */   0.08f,
                                    /* Using String: */         alphabet);
        
        // Platformer SpriteSheet
        let blocksGrid = Grid({30}, {1}, {1/30.f}, {0}, {0.005});
        platformerBlocks = {};
        platformerBlocks.sheet = new Texture("spritesheet_rgba.png");
        platformerBlocks.atlas["floor_grassy_normal"] = *blocksGrid[{4, 3}];
        platformerBlocks.atlas["floor_dirt"] = *blocksGrid[{5, 2}];
        platformerBlocks.atlas["bg_dirt"] = *blocksGrid[{26, 1}];
        platformerBlocks.atlas["player_blue"] = *blocksGrid[{1, 19}];
        platformerBlocks.atlas["player_pink"] = *blocksGrid[{2, 19}];
        
        // Game Grid
        let blockLength = g->window.uv.height()/rows;
        gameGrid = Grid({rows, (int) (g->window.uv.ratio() * rows)}, screenPages, {blockLength}, g->window.uv.bottomLeft());
        
        DEBUG_TIME(false, "Resource Load", INFO);
    }
    
    inline Entity* getBlockForRowCol(IntPair rowCol) {
        if (blocks.size() > rowCol.row() && blocks[rowCol.row()].size() > rowCol.col()) {
            var block = blocks[rowCol.row()][(rowCol.col() + gameGrid.startIndex.x) % gameGrid.cols()];
            if (block) { return block; }
        }
        return nullptr;
    }
    
    inline void configureBackgroundBlock(Game* g, State state, Entity* block) {
        block->category = "background";
        block->paused = true;
        block->intangible = true;
        g->frames[state].insertBackground(block);
    }
    
    inline void configureFloorBlock(Game* g, State state, Entity* block) {
        block->category = "floor block";
        block->paused = true;
        block->zOrder = 2;
        g->frames[state].insertStatic(block);
    }
    
    inline bool isDirtFloor(IntPair rowCol) {
        int periodicCol = (rowCol.col() + 3) % 10;
        if (rowCol.row() == 0) {
            return periodicCol < 3;
        } else if (rowCol.row() == 1) {
            return periodicCol == 1;
        }
        return false;
    }
    
    inline bool isGrassyFloor(IntPair rowCol) {
        int periodicCol = (rowCol.col() + 3) % 10;
        if (rowCol.row() == 0) {
            return periodicCol > 2;
        } else if (rowCol.row() == 1) {
            return periodicCol == 0 || periodicCol == 2;
        } else if (rowCol.row() == 2) {
            return periodicCol % 10 == 1;
        }
        return false;
    }
    
    inline Entity* configureBlockForRowCol(Entity* block, Game* g, State state, IntPair rowCol) {
        LOG("Generating block for " + rowCol.debugDescription(), NOID);
        DEBUG_TIME(true, "Block generation at " + rowCol.debugDescription());
        if (isDirtFloor(rowCol)) {
            block->configureWithSpriteSheet(platformerBlocks, "floor_dirt");
            configureFloorBlock(g, state, block);
        } else if (isGrassyFloor(rowCol)) {
            block->configureWithSpriteSheet(platformerBlocks, "floor_grassy_normal");
            configureFloorBlock(g, state, block);
        } else {
            block->configureWithSpriteSheet(platformerBlocks, "bg_dirt");
            configureBackgroundBlock(g, state, block);
        }
        DEBUG_TIME(false, "Block generation at " + rowCol.debugDescription(), NOID);
        return block;
    }
    
    inline void setupGame(Game* g) {
        LOG("Entering Setup", INFO);
        DEBUG_TIME(true, "Configuration");
        g->createState(RUNNING);
        LOG("Setting up running frame", DBG);
        LOG("Generating blocks", DBG);
        DEBUG_TIME(true, "Block Generation");
        repeat (row, gameGrid.rows()) {
            blocks.push_back(std::vector<Entity*>());
            repeat (col, gameGrid.cols()) {
                LOG("Generating block", NOID);
                IntPair rowCol = {row, col};
                var block = new Entity();
                configureBlockForRowCol(block, g, RUNNING, rowCol);
                guard (block) else { continue; }
                block->bounds = *gameGrid[rowCol];
                block->rowCol = rowCol;
                block->name = rowCol.debugDescription();
                blocks[row].push_back(block);
            }
        }
        DEBUG_TIME(false, "Block Generation", DBG);
        
        LOG("Generating Player", DBG);
        var playerCollisionDetection = [](Entity* entity, Game* g) -> CollisionAction {
            return [=](Entity* other, float elapsed) {
                guard (other->category != PLAYER_INFO.category) else { return; }
                Collisions::penCheck(entity, g, Collisions::uncollide, Collisions::stopDead)(other, elapsed);
            };
        };
        
        var walls = Generation::generateWalls(g, RUNNING, false);
        for (var wall in walls) {
            wall->onCollide = [=](Entity* other, float elapsed) {
                guard (other->category == PLAYER_INFO.category) else { return; }
                g->changeState(LOSE);
            };
        }
        
        Entity* player1 = new Entity(platformerBlocks, "player_blue");
        Generation::configurePlayer(player1, g, RUNNING, *gameGrid[{1, 1}], 4.f, EventFramework::ControlSchemes::ArrowKeys, playerCollisionDetection);
        player1->gravity = {0,-5.f};
        player1->friction = {2.f, 0.f};
        
//        Entity* player2 = new Entity(platformerBlocks, "player_pink");
//        Generation::configurePlayer(player2, g, RUNNING, *gameGrid[{1, 1}], 4.f, EventFramework::ControlSchemes::WASD, playerCollisionDetection);
//        player2->gravity = {0,-5.f};
//        player2->friction = {2.f, 0.f};
        
        LOG("Registering key handlers", DBG);
        
        Timer* startTimer = new Timer(3, EmptyInstantAction);
        bool* startShiftingRows = new bool(false);
        Timer* shiftRowTimer = new Timer(gameGrid.getcellSize().x, [=]() {
            guard (*startShiftingRows) else {
                *startShiftingRows = true;
                return;
            }
            gameGrid.addCol();
            repeat (row, gameGrid.rows()) {
                var block = getBlockForRowCol({row, 0});
                configureBlockForRowCol(block, g, RUNNING, {row, gameGrid.cols() - 1 + gameGrid.startIndex.x});
                block->bounds = *gameGrid[{row, -1}];
            }
            DEBUG_TIME(false, "View Translation", NOID);
        });
        startTimer->action = [=]() {
            g->willUpdate = [=](float elapsed) {
                guard (g->state == RUNNING) else { return; }
                LOG("Translating view", INFO);
                DEBUG_TIME(true, "View Translation");
                g->view.Translate(-elapsed, 0, 0);
                for (var wall in walls) {
                    if (wall->bounds.height() > 1.f) { // Left or Right wall
                        wall->bounds += {elapsed, 0};
                    }
                }
            };
            startTimer->stop();
            g->timers[RUNNING].insert(shiftRowTimer);
            shiftRowTimer->start();
        };
        g->timers[RUNNING].insert(startTimer);
        
        g->createState(LOSE);
        var losingText = Generation::generateText(/* With Game: */      g,
                                                  /* For State: */      LOSE,
                                                  /* Showing Text: */   "Game Over!",
                                                  /* Given Height: */   10.f,
                                                  /* Using Font: */     font,
                                                  /* Within Bounds: */  g->window.uv);
        
        g->willChangeState = [=](State newState) {
            g->view.identity();
        };
        
        g->changeState(RUNNING);
        DEBUG_TIME(false, "Configuration", INFO);
    }
    
    inline void play() {
        var game = new Game("Platformer");
        loadResources(game);
        setupGame(game);
        game->start();
    }
}}

#endif
