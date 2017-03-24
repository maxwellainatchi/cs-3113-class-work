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
#define var auto
#define let const auto
#define in :
#define cstatic constexpr static
#define λ [&]
#define selector(x) λ() {(x)();}

#endif /* macros_h */
