//
//  Texture.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/9/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp
#include "libraries.h"
#include "resources.h"
#include "Matrix.h"
#include "Drawable.hpp"

namespace Graphics {
    class Texture: Drawable {
    public:
        int w,h,comp;
        std::string imagePath;
        bool loaded;
        GLuint textureID;
        
        Texture(std::string image_path);
        
        void rotate(int radians);
    };
}

#endif /* Texture_hpp */
