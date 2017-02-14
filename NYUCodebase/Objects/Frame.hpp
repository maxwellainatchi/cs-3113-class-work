//
//  Frame.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/9/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Frame_hpp
#define Frame_hpp

#include <vector>
#include "Drawable.hpp"

namespace Graphics {
    class Frame {
    public:
        std::vector<Drawable> objects;
        
        void clearBG();
    };
}

#endif /* Frame_hpp */
