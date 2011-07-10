#pragma once
//
//  ofxImageAsset.h
//  MapTools
//
//  Created by Elliot Woods on 11/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "ofImage.h"
#include "ofxDirList.h"

class ofxImageAsset
{
    public:
        ofxImageAsset();
        ofImage& getImage(string assetName);
        vector<string> getImageList();
        
    private:
        void    initialise();
    
        static map<string, ofImage>     dictionary;
        static bool                     initialised;
    
        static ofImage                  blank;
};