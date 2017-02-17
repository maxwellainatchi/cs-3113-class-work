//
//  Texture.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Texture.hpp"

namespace Graphics {
    
    Texture::Texture() {
        loaded = false;
    }
    
    Texture::Texture(std::string imageName) {
        this->imageName = imageName;
        this->imagePath = std::string(RESOURCE_FOLDER) + imageName;
        
        // Load image
        unsigned char* image = stbi_load(imagePath.c_str(), &w, &h, &comp, STBI_rgb_alpha);
        if(image == NULL) {
            std::cout << "Unable to load image. Make sure the path is correct\n";
            loaded = false;
        } else {
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
    }
    
    void Texture::fullSize() {
        // Texture coordinates are y-inverted for some reason
        texCoords = Graphics::Coordinates({0.0,1.0},{1.0,0.0});
    }
    
    void Texture::draw(ShaderProgram* shader) {
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
        glVertexAttribPointer(shader->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.resolveCoords());
        glEnableVertexAttribArray(shader->texCoordAttribute);
        
        // Draw
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // Clean up
        glDisableVertexAttribArray(shader->positionAttribute);
        glDisableVertexAttribArray(shader->texCoordAttribute);
    }
}
