//
//  Texture.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Texture.hpp"

Texture::Texture() {
    loaded = false;
}

Texture::Texture(std::string imageName) {
    self.imageName = imageName;
    self.imagePath = std::string(IMAGE_FOLDER) + imageName;
    
    // Load image
    unsigned char* image = stbi_load(imagePath.c_str(), &w, &h, &comp, STBI_rgb_alpha);
    guard (image) else {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        loaded = false;
        return;
    }
    loaded = true;
    // Generate texture ID
    glGenTextures(1, &textureID);
    
    // Bind texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set texture params
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    // Set interpolation to linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Free memory
    stbi_image_free(image);
    
    // Assign texture coordinates
    fullSize();
}

Texture::Texture(std::string imageName, Rectangle coords): Texture(imageName) {
    self.coords = coords;
}

void Texture::fullSize() {
    coords = Rectangle({{0.0f, 0.0f}, 1.0f, 1.0f});
}

void Texture::draw(ShaderProgram* shader, Rectangle vertices) {
    if (!loaded) {
        std::cout << "Tried to draw an unloaded texture!" << std::endl;
        SDL_assert(false);
    }
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set position coordinates
    glVertexAttribPointer(shader->positionAttribute, 2, GL_FLOAT, false, 0, vertices.resolveCoords());
    glEnableVertexAttribArray(shader->positionAttribute);
    
    // Set texture coordinates
    glVertexAttribPointer(shader->texCoordAttribute, 2, GL_FLOAT, false, 0, coords.resolveCoords(true));
    glEnableVertexAttribArray(shader->texCoordAttribute);
    
    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    // Clean up
    glDisableVertexAttribArray(shader->positionAttribute);
    glDisableVertexAttribArray(shader->texCoordAttribute);
}
