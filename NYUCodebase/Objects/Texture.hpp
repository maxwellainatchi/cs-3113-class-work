//
//  Texture.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "libraries.h"
#include "resources.h"
#include "Coordinates.hpp"
#include <string>

namespace Graphics {
    class Texture {
    private:
        std::string imagePath;
        int comp;
        Coordinates texCoords;
        bool loaded;
        
        void fullSize();
    public:
        std::string imageName;
        GLuint textureID;
        Coordinates vertices;
        int w,h;
        
        Texture();
        
        Texture(std::string imageName);
        
        void draw(ShaderProgram* shader);
        
        void rotate(float angle);
    };
}

#endif /* Texture_hpp */
