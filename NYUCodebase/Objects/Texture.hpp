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
#include "Rectangle.hpp"
#include <string>

namespace Graphics {
    class Texture {
    private:
        std::string imagePath;
        int comp;
        
        void fullSize();
    public:
        std::string imageName;
        GLuint textureID;
        Position::Rectangle coords;
        int w,h;
        bool loaded;
        
        Texture();
        
        Texture(std::string imageName);

        
        void draw(ShaderProgram* shader, Position::Rectangle vertices);
        
        void rotate(float angle);
    };
}

#endif /* Texture_hpp */
