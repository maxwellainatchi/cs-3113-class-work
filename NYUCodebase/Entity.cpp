//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Entity.hpp"

Entity::Entity(): coords(nullptr) {}
Entity::Entity(Texture* texture, Rectangle bounds): texture(texture), bounds(bounds), coords(nullptr) {}
Entity::Entity(SpriteSheet sheet, std::string name): texture(sheet.sheet), coords(new Rectangle(sheet.atlas[name])), type(name) {}

void Entity::configureWithSpriteSheet(SpriteSheet sheet, std::string name) {
    self.texture = sheet.sheet;
    self.coords = new Rectangle(sheet.atlas[name]);
}

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
    oneOffVelocity = 0;
    oneOffAcceleration = 0;
    oneOffGravity = 0;
    oneOffFriction = 0;
    direction = {0};
}

void Entity::render(ShaderProgram* shader) {
    weak_assert(texture && texture->loaded && !hidden);
    willRender(shader);
    shader->setModelMatrix(model);
    if (coords) { texture->coords = *coords; }
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

Vector Entity::lerp(Vector v0, Vector v1, Vector t) {
    return {
        // I hate this syntax but I have no choice
        ::lerp(v0.x, v1.x, t.x),
        ::lerp(v0.y, v1.y, t.y)
    };
}

Rectangle Entity::projectedPosition(float elapsed, bool yOnly) {
    return bounds + projectedVelocity(elapsed, yOnly) * elapsed;
}

Vector Entity::projectedVelocity(float elapsed, bool yOnly) {
    var projVel = lerp(velocity + oneOffVelocity, {0, 0}, (friction + oneOffFriction) * elapsed) + (acceleration + oneOffAcceleration + gravity + oneOffGravity) * elapsed;
    if (yOnly) { projVel.x = 0; }
    return projVel;
}

std::string Entity::debugDescription() {
    return
    "Entity " + category + ", " + type + ", " + name + "\n\t" +
    "Is within " + bounds.debugDescription() + "\n\t" +
    "Velocity: " + velocity.debugDescription() +
    ", Acceleration: " + acceleration.debugDescription() +
    "\n\tHidden: " + std::to_string(hidden) +
    ", Intangible: " + std::to_string(intangible) +
    ", Paused: " + std::to_string(paused) + "\n";
    
}

