
#define STB_IMAGE_IMPLEMENTATION

#include "libraries.h"
#include "objects.h"
#include "resources.h"

using namespace std;

int main(int argc, char *argv[])
{
    Graphics::Config prog = Graphics::Config();
    //float angle = 0.0f;
    Graphics::Texture emojiTexture = Graphics::Texture("emoji.png");
    
    prog.loop = [&] () {
        //angle += prog.elapsed();
        
        prog.m.model.identity();
        //prog.m.model.Rotate(angle);
        
        glBindTexture(GL_TEXTURE_2D, emojiTexture.textureID);
        
        float vertices[] = {-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5};
        glVertexAttribPointer(prog.shader->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(prog.shader->positionAttribute);
        
        float texCoords[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0};
        glVertexAttribPointer(prog.shader->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
        glEnableVertexAttribArray(prog.shader->texCoordAttribute);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glDisableVertexAttribArray(prog.shader->positionAttribute);
        glDisableVertexAttribArray(prog.shader->texCoordAttribute);
    };
    prog.start();
    return 0;
}
