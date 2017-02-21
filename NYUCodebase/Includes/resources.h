//
//  resources.h
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef resources_h
    #define resources_h

    #ifdef _WINDOWS
        #define RESOURCE_FOLDER ""
    #else
        #define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
    #endif

    #define IMAGE_FOLDER RESOURCE_FOLDER"Images/"

#endif /* resources_h */
