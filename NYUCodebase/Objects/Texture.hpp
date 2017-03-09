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
        Coordinates coords;
        std::string imagePath;
        int comp;
        
        void fullSize();
    public:
        std::string imageName;
        GLuint textureID;
        int w,h;
        bool loaded;
        
        Texture();
        
        Texture(std::string imageName);
        
        void setCoords(Coordinates newCoords);
        
        void draw(ShaderProgram* shader, Coordinates vertices);
        
        void rotate(float angle);
    };
}

#endif /* Texture_hpp */
