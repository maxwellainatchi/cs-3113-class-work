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
#define weak_assert(x) if(!(x)) { return; } 0
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
#define getOnly(type, var) type var; __getter(type, var)
#define classdef(type, var) type var; __getter(type, var); __setter(type, var)
#define __getter(type, varname) public: const type& get##varname() const { return varname; } private:
#define __setter(type, varname) public: void set##varname(const type& newValue) { self.varname = newValue; } private:
#define alias(type, old, new) const type& new() const { return old; }

#define EmptyInstantAction λ(){}
#define EmptyTimedAction λ(float elapsed){}
#define EmptyShaderAction λ(ShaderProgram* shader){}
#define EmptyCollisionAction λ(Entity* entity, float elapsed){}
#define EmptyStateAction λ(std::string state){}

#endif /* macros_h */
