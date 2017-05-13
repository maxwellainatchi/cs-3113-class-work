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
    
    IntPair rowCol = {0, 0};
    
    Texture* texture;
    Rectangle* coords;
    Matrix model;
    
    InstantAction willSetup = EmptyInstantAction;
    TimedAction willUpdate = EmptyTimedAction;
    ShaderAction willRender = EmptyShaderAction;
    
    std::function<void(Entity*, float elapsed)> onCollide;
    
    Rectangle bounds;
    
    Vector velocity;
    Vector acceleration;
    Vector friction;
    Vector gravity;
    
    Vector oneOffVelocity;
    Vector oneOffAcceleration;
    Vector oneOffFriction;
    Vector oneOffGravity;
    
    Vector direction; // TODO: move this somewhere, anywhere, else
    
    bool hidden = false, intangible = false, paused = false;
    uint zOrder = 1;
    
    Entity();
    Entity(Texture* texture, Rectangle bounds);
    Entity(SpriteSheet sheet, std::string name);
    
    void configureWithSpriteSheet(SpriteSheet sheet, std::string name);
    
    bool willCollideWith(Entity* entity, float elapsed, bool yOnly);
    
    void setup();
    void update(float elapsed);
    void render(ShaderProgram* shader);
    
    // MARK: Utility
    
    std::string identifierForSimilarityLevel(SimilarityLevel level);
    Vector lerp(Vector v0, Vector v1, Vector t);
    Rectangle projectedPosition(float elapsed, bool yOnly);
    Vector projectedVelocity(float elapsed, bool yOnly);
    std::string debugDescription();
};

typedef std::function<void(Entity*, float elapsed)> CollisionAction;

#endif /* Entity_hpp */
