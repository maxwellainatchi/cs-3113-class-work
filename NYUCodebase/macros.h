//
//  macros.h
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/23/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef macros_h
#define macros_h

#define guard(x) if ((x)) {}
#define weak_assert(x) if(!(x)) { return; }
#define break_if(x) if((x)) { break; }
#define continue_if(x) if((x)) { continue; }
#define var auto
#define let const auto
#define in :
#define repeat(varName, x) for (int varName = 0; varName < (x); ++varName)
#define cstatic constexpr static
#define λ [&]
#define selector(x) λ() {(x)();}
#define self (*this)
#define cstr char*

#define EmptyInstantAction λ(){}
#define EmptyTimedAction λ(float elapsed){}
#define EmptyShaderAction λ(ShaderProgram* shader){}
#define EmptyCollisionAction λ(Entity* entity, float elapsed){}
#define EmptyStateAction λ(std::string state){}

#endif /* macros_h */
