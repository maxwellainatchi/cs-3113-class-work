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
#define TITLE "title"
#define WIN "win"

namespace Games { namespace Platformer {
    inline int rows = 12;
    inline IntPair screenPages = {1,2};
    inline SpriteSheet platformerBlocks;
    inline SpriteSheet* font;
    inline Grid gameGrid;
    inline std::vector<std::vector<Entity*>> blocks;
    inline std::vector<int> rowHeights;
    inline bool* sawsEnabled = new bool(false);
    
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
        platformerBlocks.atlas["floor_grassy_normal"] = *blocksGrid[{16, 3}];
        platformerBlocks.atlas["floor_dirt"] = *blocksGrid[{17, 2}];
        platformerBlocks.atlas["bg_dirt"] = *blocksGrid[{26, 1}];
        platformerBlocks.atlas["player_blue_rest"] = *blocksGrid[{1, 19}];
        platformerBlocks.atlas["player_pink_rest"] = *blocksGrid[{2, 19}];
        platformerBlocks.atlas["player_blue_jumping"] = *blocksGrid[{1, 20}];
        platformerBlocks.atlas["player_pink_jumping"] = *blocksGrid[{2, 20}];
        platformerBlocks.atlas["enemy_one"] = *blocksGrid[{4, 20}];
        platformerBlocks.atlas["saw_infloor_state1"] = *blocksGrid[{11, 28}];
        platformerBlocks.atlas["saw_infloor_state2"] = *blocksGrid[{11, 29}];
        
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
    
    inline void configureSaw(Game* g, State state, Entity* block) {
        block->category = "saw";
        block->animationState = "state1";
        block->onCollide = [=](Entity* other, float elapsed) {
            guard (other->category == "player" && *sawsEnabled) else { return; }
            g->changeState(LOSE);
        };
        g->timers[state].insert(new Timer(0.3, [=]() {
            if (block->animationState == "state1") {
                block->coords = &platformerBlocks.atlas["saw_infloor_state2"];
                block->animationState = "state2";
            } else {
                block->coords = &platformerBlocks.atlas["saw_infloor_state1"];
                block->animationState = "state1";
            }
        }));
        g->registerKeyHandler(SDL_SCANCODE_0, {RUNNING}, [=]() {
            *sawsEnabled = !(*sawsEnabled);
        });
        g->frames[state].insertDynamic(block);
    }
    
//    inline void configureEnemy(Game* g, State state, Entity* block) {
//        block->category = "enemy";
//        block->onCollide = [=](Entity* other, float elapsed) {
//            guard (other->category == "player" && *sawsEnabled) else { return; }
//            g->changeState(LOSE);
//        };
//        g->willUpdate = [=](float elapsed) {
//            if () {
//                
//            }
//        };
//        g->registerKeyHandler(SDL_SCANCODE_0, {RUNNING}, [=]() {
//            *sawsEnabled = !(*sawsEnabled);
//        });
//        g->frames[state].insertDynamic(block);
//    }
    
    inline void configureEnd(Game* g, State state, Entity* block) {
        block->category = "end";
        block->onCollide = [=](Entity* other, float elapsed) {
            guard (other->category == PLAYER_INFO.category) else { return; }
            g->changeState(WIN);
        };
    }
    
    inline bool isDirtFloor(IntPair rowCol) {
        return rowHeights[rowCol.col()] > rowCol.row();
    }
    
    inline bool isGrassyFloor(IntPair rowCol) {
        return rowHeights[rowCol.col()] == rowCol.row();
    }
    
    inline bool isSaw(IntPair rowCol) {
        return rowCol.col() > 4 && rowHeights[rowCol.col()] + 1 == rowCol.row() && arc4random_uniform(UINT32_MAX) > 0.8 * UINT32_MAX;
    }
    
    inline Entity* configureBlockForRowCol(Entity* block, Game* g, State state, IntPair rowCol) {
        LOG("Generating block for " + rowCol.debugDescription(), NOID);
        DEBUG_TIME(true, "Block generation at " + rowCol.debugDescription());
        if (rowCol.col() == gameGrid.cols() - 2) {
            block->configureWithSpriteSheet(platformerBlocks, "floor_grassy_normal");
        } else if (isDirtFloor(rowCol)) {
            block->configureWithSpriteSheet(platformerBlocks, "floor_dirt");
            configureFloorBlock(g, state, block);
        } else if (isGrassyFloor(rowCol)) {
            block->configureWithSpriteSheet(platformerBlocks, "floor_grassy_normal");
            configureFloorBlock(g, state, block);
        } else if (isSaw(rowCol)) {
            block->configureWithSpriteSheet(platformerBlocks, "saw_infloor_state1");
            configureSaw(g, state, block);
//        } else if  (arc4random_uniform(UINT32_MAX) > 0.9 * UINT32_MAX) {
//            block->configureWithSpriteSheet(platformerBlocks, "enemy_one");
//            configureEnemy(g, state, block);
        } else {
            block->configureWithSpriteSheet(platformerBlocks, "bg_dirt");
            //configureBackgroundBlock(g, state, block);
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
        
        repeat(i, 3) {
            rowHeights.push_back(1);
        }
        repeat(col, gameGrid.cols() - 4) {
            let lastHeight = rowHeights[rowHeights.size() - 1];
            var thisHeight = lastHeight + arc4random_uniform(3) - 1;
            thisHeight = thisHeight > 1  && thisHeight < gameGrid.rows() - 4 ? thisHeight : lastHeight;
            rowHeights.push_back(thisHeight);
        }
        
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
        
        Entity* player1 = new Entity(platformerBlocks, "player_blue_rest");
        player1->type = "player_blue";
        Generation::configurePlayer(player1, g, RUNNING, *gameGrid[{1, 1}], 6.f, EventFramework::ControlSchemes::ArrowKeys, playerCollisionDetection);
        player1->gravity = {0,-10.f};
        player1->friction = {2.f, 0.f};
        
        Entity* player2 = new Entity(platformerBlocks, "player_pink_rest");
        player2->type = "player_pink";
        Generation::configurePlayer(player2, g, RUNNING, *gameGrid[{1, 1}], 4.f, EventFramework::ControlSchemes::WASD, playerCollisionDetection);
        player2->gravity = {0,-10.f};
        player2->friction = {5.f, 0.f};
        
//        var playerUpdateTimer = new Timer(0.1, [=]() {
//            if (player1->velocity.y > SMALL_AMOUNT) {
//                player1->animationState = "jumping";
//            } else {
//                player2->animationState = "rest";
//            }
//            if (player2->velocity.y > SMALL_AMOUNT) {
//                player2->animationState = "jumping";
//            } else {
//                player2->animationState = "rest";
//            }
//            player1->coords = &platformerBlocks.atlas[player1->type + "_" + player1->animationState];
//            player2->coords = &platformerBlocks.atlas[player2->type + "_" + player2->animationState];
//        });
//        g->timers[RUNNING].insert(playerUpdateTimer);
        
        LOG("Registering key handlers", DBG);
        
        Timer* startTimer = new Timer(3, EmptyInstantAction);
//        bool* startShiftingRows = new bool(false);
//        Timer* shiftRowTimer = new Timer(gameGrid.getcellSize().x, [=]() {
//            guard (*startShiftingRows) else {
//                *startShiftingRows = true;
//                return;
//            }
//            gameGrid.addCol();
//            repeat (row, gameGrid.rows()) {
//                var block = getBlockForRowCol({row, 0});
//                configureBlockForRowCol(block, g, RUNNING, {row, gameGrid.cols() - 1});
//                block->bounds = *gameGrid[{row, -1}];
//            }
//        });
        startTimer->action = [=]() {
            g->willUpdate = [=](float elapsed) {
                guard (g->state == RUNNING) else { return; }
                LOG("Translating view", INFO);
                g->view.Translate(-elapsed, 0, 0);
                for (var wall in walls) {
                    wall->bounds += {elapsed, 0};
                }
            };
            startTimer->stop();
//            g->timers[RUNNING].insert(shiftRowTimer);
//            shiftRowTimer->start();
        };
        g->timers[RUNNING].insert(startTimer);
        
        g->createState(LOSE);
        var losingText = Generation::generateText(/* With Game: */      g,
                                                  /* For State: */      LOSE,
                                                  /* Showing Text: */   "Game Over!",
                                                  /* Given Height: */   10.f,
                                                  /* Using Font: */     font,
                                                  /* Within Bounds: */  g->window.uv);
        
        g->createState(WIN);
        var winningText = Generation::generateText(/* With Game: */      g,
                                                  /* For State: */      WIN,
                                                  /* Showing Text: */   "You Win!",
                                                  /* Given Height: */   10.f,
                                                  /* Using Font: */     font,
                                                  /* Within Bounds: */  g->window.uv);
        
        g->createState(TITLE);
//        var titleImage = new Entity();
//        titleImage->texture = new Texture("titlebg.jpg");
//        titleImage->bounds = titleImage->bounds * Vector(std::max(g->window.uv.width(), g->window.uv.height()));
//        titleImage->bounds += g->window.uv.bottomLeft();
//        g->frames[TITLE].insertBackground(titleImage);
        var startText = Generation::generateText(/* With Game: */      g,
                                                  /* For State: */      TITLE,
                                                  /* Showing Text: */   "Play Jumpy Man",
                                                  /* Given Height: */   10.f,
                                                  /* Using Font: */     font,
                                                  /* Within Bounds: */  g->window.uv);
        
        var explainText = Generation::generateText(/* With Game: */      g,
                                                    /* For State: */      TITLE,
                                                    /* Showing Text: */   "Don't hit any of the walls!",
                                                    /* Given Height: */   4.f,
                                                    /* Using Font: */     font,
                                                    /* Within Bounds: */  {g->window.uv.bottomLeft(), g->window.uv.width(), 6.f});
        
        var continueText = Generation::generateText(/* With Game: */      g,
                                                 /* For State: */      TITLE,
                                                 /* Showing Text: */   "press 1 for one player, 2 for 2 player...",
                                                 /* Given Height: */   4.f,
                                                 /* Using Font: */     font,
                                                 /* Within Bounds: */  {g->window.uv.bottomLeft(), g->window.uv.width(), 4.f});
        
        g->registerKeyHandler(SDL_SCANCODE_1, {TITLE}, [=]() {
            player2->intangible = true;
            player2->paused = true;
            player2->hidden = true;
            g->changeState(RUNNING);
        });
        
        g->registerKeyHandler(SDL_SCANCODE_2, {TITLE}, [=]() {
            g->changeState(RUNNING);
        });
        
        g->willChangeState = [=](State newState) {
            g->view.identity();
        };
        
        let musPath = RESOURCE_FOLDER"/Sound/tetris.mp3";
        Mix_Music* bg_music = Mix_LoadMUS(musPath);
        
        g->willStart = [=]() {
            Mix_PlayMusic(bg_music, -1);
        };
        
        g->willEnd = [=]() {
            Mix_FreeMusic(bg_music);
        };
        
        g->registerKeyHandler(SDL_SCANCODE_ESCAPE, {RUNNING, LOSE, WIN, TITLE}, [=]() {
            g->done = true;
        });
        
        g->changeState(TITLE);
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
