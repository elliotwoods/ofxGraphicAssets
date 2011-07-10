#pragma once
//
//  ofxFontAsset.h
//  MapTools
//
//  Created by Elliot Woods on 12/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "ofxDirList.h"
#include <fstream>

#include "ofTrueTypeFont.h"
#include <map>
#include <algorithm>

class ofxFontAsset
{
public:
    ofxFontAsset();
    static ofTrueTypeFont& getFont(string assetName);
    static vector<string>  getFontList();
    
private:
    static void    initialise();
    
    static map<string, ofTrueTypeFont>      dictionary;
    static bool                             initialised;
    
    static ofTrueTypeFont                  blank;
};