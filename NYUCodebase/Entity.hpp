//
//  Entity.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "libraries.h"
#include "Rectangle.hpp"
#include "Texture.hpp"
#include "Matrix.h"

enum SimilarityLevel { category, type, name };

class Entity {
public:
    std::string category;
    std::string type;
    std::string name;
    
    Texture* texture;
    Matrix model;
    
    InstantAction willSetup = EmptyInstantAction;
    TimedAction willUpdate = EmptyTimedAction;
    ShaderAction willRender = EmptyShaderAction;
    
    std::function<void(Entity*, float elapsed)> onCollide;
    
    Rectangle bounds;
    
    Vec2 velocity;
    Vec2 acceleration;
    Vec2 friction;
    Vec2 gravity;
    
    bool hidden = false, intangible = false, paused = false;
    
    Entity();
    Entity(Texture* texture, Rectangle bounds);
    
    bool willCollideWith(Entity* entity, float elapsed, bool yOnly);
    
    void setup();
    void update(float elapsed);
    void render(ShaderProgram* shader);
    
    // MARK: Utility
    
    std::string identifierForSimilarityLevel(SimilarityLevel level);
    Vec2 lerp(Vec2 v0, Vec2 v1, Vec2 t);
    Rectangle projectedPosition(float elapsed, bool yOnly);
    Vec2 projectedVelocity(float elapsed, bool yOnly);
};

typedef std::function<void(Entity*, float elapsed)> CollisionAction;

struct SpriteSheet {
    std::string sheetName;
    std::map<std::string, Rectangle> atlas;
    float xSpacing;
};

#endif /* Entity_hpp */
