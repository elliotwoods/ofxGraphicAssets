//
//  ofxFontAsset.cpp
//  ofxImageAsset
//
//  Created by Elliot Woods on 12/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "ofxFontAsset.h"

bool ofxFontAsset::initialised = false;

map<string, ofTrueTypeFont> ofxFontAsset::dictionary = map<string, ofTrueTypeFont>();
ofTrueTypeFont ofxFontAsset::blank = ofTrueTypeFont();

ofxFontAsset::ofxFontAsset()
{
    initialise();
}

ofTrueTypeFont& ofxFontAsset::getFont(string assetName)
{
    initialise();
    
    if (dictionary.count(assetName) != 0)
        return dictionary[assetName];
    else
    {
        if (assetName=="default")
            return blank;
        else
            return dictionary["defualt"];
    }
}

void ofxFontAsset::initialise()
{
    if (initialised)
        return;
    
    initialised = true;
    
    ofxDirList dir;
    
    dir.allowExt("ttf");
    dir.setVerbose(false);
    
    int nFiles = dir.listDir("fonts/");
    
    string filename;
    string sizesFilePath;
    string name;
    
    vector<int>     sizes;
    int currentSize;
    
    for (int i=0; i < nFiles; i++)
    {
        //get filename/name without 3 char extension
        filename = dir.getName(i);
        name = filename.substr(0, filename.length()-4);
        
        //get absolute filename of sizes file
        sizesFilePath = dir.getPath(i);
        sizesFilePath = sizesFilePath.substr(0, sizesFilePath.length()-3) + "txt";

        ////////////////////////
        //try to read sizes file
        sizes.clear();
        try {
            ifstream file;
            file.open(sizesFilePath.c_str());
            
            while (file >> currentSize)
                sizes.push_back(currentSize); 
            
        } catch (...) {
        
        }
        
        if (sizes.size() == 0)
            sizes.push_back(10);
        ////////////////////////
        
        //we didn't throw, so let's        
        //load font/sizes
        
        //if name is 'default' then we have special
        //case of supporting only 1 text size
        if (name == "default")
        {
            dictionary["default"] = ofTrueTypeFont();
            dictionary["default"].loadFont("fonts/" + filename, sizes[0]);
        }
        
        //otherwise we add all text sizes
        //as fonts name with size, e.g.:
        //  "Helvetica_10"
        
        vector<int>::iterator it;
        string compoundName;
        //
        for (it = sizes.begin(); it != sizes.end(); it++)
        {
            compoundName = name + "_" + ofToString(*it);
            
            dictionary[compoundName] = ofTrueTypeFont();
            dictionary[compoundName].loadFont("fonts/" + filename, *it);
        }

    }
    
    //let's output what assets we have
    cout << "////////////////////////\n";
    cout << "//FONTS LOADED\n";
    cout << "////////////////////////\n";
    cout << "//\n";
    
    map<string, ofTrueTypeFont>::iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); it++)
        cout << it->first << "\n";
    
    cout << "////////////////////////\n";
    
}

vector<string> ofxFontAsset::getFontList()
{
    vector<string> retval;
    
    map<string, ofTrueTypeFont>::iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); it++)
        retval.push_back(it->first);
    
    return retval;
}