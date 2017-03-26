//
//  TitleText.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "TitleText.hpp"

namespace Entities {
    TitleText::TitleText(): TitleText("", Position::Rectangle()) {}
    
    TitleText::TitleText(std::string text, Position::Rectangle bounds): bounds(bounds) {
        //if (font == nullptr) {
            std::vector<std::string> names;
            
            // For some odd reason, I need to add a character at the end of each line
            for (std::string line : {
                "=*$<>%      ~",
                "&()[]`\\/~~~+~",
                "89.,;:?!-#\"'~",
                "wxyz01234567~",
                "klmnopqrstuv~",
                "YZabcdefghij~",
                "MNOPQRSTUVWX~",
                "ABCDEFGHIJKL~"
            }) {
                for (char c : line) { // Starts from bottom left
                    if (c != '~') {
                        names.push_back(std::string(1, c));
                    } else {
                        names.push_back(std::string(1, char(13)));
                    }
                }
            }
            font = new Graphics::SpriteSheet("font.png", {1.0f/12.0f, 1.0f/8.0f}, names);
        //}
        setText(text);
    }
    
    void TitleText::setText(std::string newText) {
        text = newText;
        for (auto letter : letters) {
            delete letter;
        }
        letters.clear();
        for (char c : text) {
            letters.push_back(new Sprite(font, std::string(1, c)));
        }
        Position::Point origin = bounds.topLeft();
        Position::Vector2D size = {1.0f/6.0f, 1.0f/4.0f};
        for (Sprite* letter : letters) {
            if (letter == nullptr) { continue; }
            letter->setCoordinates({
                origin,
                size.x,
                size.y
            });
            origin.x += size.x;
            if (origin.x > bounds.right) {
                origin.x = bounds.left;
                origin.y -= size.y;
            }
        }
    }
    
    void TitleText::draw(ShaderProgram *shader) {
        for (Sprite* letter : letters) {
            letter->draw(shader);
        }
    }
}
