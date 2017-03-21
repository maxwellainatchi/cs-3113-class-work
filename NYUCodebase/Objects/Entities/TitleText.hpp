//
//  TitleText.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef TitleText_hpp
#define TitleText_hpp

#include "libraries.h"
#include "Entity.hpp"
#include "SpriteSheet.hpp"
#include "Sprite.hpp"

namespace Entities {
    class TitleText: public Entity {
    private:
        std::string text;
        Graphics::Coordinates bounds;
        std::vector<Sprite*> letters;
    public:
        Graphics::SpriteSheet* font;
        
        TitleText();
        TitleText(std::string text, Graphics::Coordinates bounds);
        
        void setText(std::string text);
        
        // Inherited
        virtual void draw(ShaderProgram* shader);
    };
}

#endif /* TitleText_hpp */
