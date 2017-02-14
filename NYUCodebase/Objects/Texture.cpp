//
//  Texture.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/9/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Texture.hpp"

namespace Graphics {
    Texture::Texture(std::string image_path) {
        imagePath = image_path;
        
        int w,h,comp;
        std::string path = std::string(RESOURCE_FOLDER) + std::string(imagePath);
        unsigned char* image = stbi_load(path.c_str(), &w, &h, &comp, STBI_rgb_alpha);
        if (image == NULL) {
            std::cout << "Unable to load image. Make sure the path is correct." << std::endl;
            SDL_assert(false);
        }
        
        // Generate texture ID
        GLuint textureID;
        glGenTextures(1, &textureID);
        
        // Set texture dimension
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        // Assign image to texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        
        // Set interpolation params
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(image);
    }
}
