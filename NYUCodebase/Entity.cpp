//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Entity.hpp"
    
bool Entity::willCollideWith(Entity* entity, float elapsed) {
    guard (entity != self && !intangible && !entity->intangible) else { return false; }
    return projectedPosition(elapsed).isWithin(entity->projectedPosition(elapsed), false);
}

void Entity::setup() {
    willSetup();
}

void Entity::update(float elapsed) {
    weak_assert(!paused);
    willUpdate(elapsed);
    velocity = projectedVelocity(elapsed);
    bounds = projectedPosition(elapsed);
}

void Entity::render(ShaderProgram* shader) {
    weak_assert(texture && texture->loaded && !hidden);
    willRender(shader);
    shader->setModelMatrix(model);
    texture->draw(shader, bounds);
}

Vec2 Entity::lerp(Vec2 v0, Vec2 v1, Vec2 t) {
    return {
        // I hate this syntax but I have no choice
        ::lerp(v0.x, v1.x, t.x),
        ::lerp(v0.y, v1.y, t.y)
    };
}

Rectangle Entity::projectedPosition(float elapsed) {
    return bounds + projectedVelocity(elapsed) * elapsed;
}

Vec2 Entity::projectedVelocity(float elapsed) {
    return lerp(velocity, {0, 0}, friction * elapsed) + (acceleration + gravity) * elapsed;
}

