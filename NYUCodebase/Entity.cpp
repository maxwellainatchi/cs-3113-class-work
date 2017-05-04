//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity() {}
Entity::Entity(Texture* texture, Rectangle bounds): texture(texture), bounds(bounds) {}
    
bool Entity::willCollideWith(Entity* entity, float elapsed, bool yOnly) {
    guard (entity != this && !intangible && !entity->intangible) else { return false; }
    return projectedPosition(elapsed, yOnly).isWithin(entity->projectedPosition(elapsed, yOnly), false);
}

void Entity::setup() {
    willSetup();
}

void Entity::update(float elapsed) {
    weak_assert(!paused);
    willUpdate(elapsed);
    velocity = projectedVelocity(elapsed, false);
    bounds = projectedPosition(elapsed, false);
}

void Entity::render(ShaderProgram* shader) {
    weak_assert(texture && texture->loaded && !hidden);
    willRender(shader);
    shader->setModelMatrix(model);
    texture->draw(shader, bounds);
}

std::string Entity::identifierForSimilarityLevel(SimilarityLevel level) {
    switch (level) {
        case ::category:
            return self.category;
        case ::type:
            return self.type;
        case ::name:
            return self.name;
    }
}

Vec2 Entity::lerp(Vec2 v0, Vec2 v1, Vec2 t) {
    return {
        // I hate this syntax but I have no choice
        ::lerp(v0.x, v1.x, t.x),
        ::lerp(v0.y, v1.y, t.y)
    };
}

Rectangle Entity::projectedPosition(float elapsed, bool yOnly) {
    return bounds + projectedVelocity(elapsed, yOnly) * elapsed;
}

Vec2 Entity::projectedVelocity(float elapsed, bool yOnly) {
    var projVel = lerp(velocity, {0, 0}, friction * elapsed) + (acceleration + gravity) * elapsed;
    if (yOnly) { projVel.x = 0; }
    return projVel;
}

