//
//  ofxImageAsset.cpp
//  MapTools
//
//  Created by Elliot Woods on 11/02/2011.
//  Copyright 2011 Kimchi and Chips. All rights reserved.
//

#include "ofxImageAsset.h"

bool ofxImageAsset::initialised = false;

map<string, ofImage> ofxImageAsset::dictionary = map<string, ofImage>();
ofImage ofxImageAsset::blank = ofImage();

ofxImageAsset::ofxImageAsset()
{
    initialise();
}

ofImage& ofxImageAsset::getImage(string assetName)
{
    initialise();
    
    if (dictionary.count(assetName) != 0)
        return dictionary[assetName];
    else
    {
        ofLog(OF_LOG_ERROR, "ofxImageAsset: Asset " + assetName + " not found, returning blank image");
        return blank;
    }
}

void ofxImageAsset::initialise()
{
    if (initialised)
        return;
    
    initialised = true;
    
    ofxDirList dir;
    
    dir.allowExt("png");
    dir.setVerbose(false);
    
    int nFiles = dir.listDir("images/");
    
    string filename;
    string name;
    for (int i=0; i < nFiles; i++)
    {
        //get filename/name without 3 char extension
        filename = dir.getName(i);
        name = filename.substr(0, filename.length()-4);
        
        //insert into map
        dictionary [name] =  ofImage();
        
        //load image
        dictionary [name].loadImage("images/" + filename);
    }
    
    //setup blank image
    unsigned char blankpix[32*32];
    memset(blankpix, 100, 32*32);
    //
    blank.setFromPixels(blankpix, 32,32, OF_IMAGE_GRAYSCALE);
    //
    
    //let's output what assets we have
    cout << "////////////////////////\n";
    cout << "//IMAGES LOADED\n";
    cout << "////////////////////////\n";
    cout << "//\n";
    
    map<string, ofImage>::iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); it++)
        cout << it->first << "\n";
    
    cout << "////////////////////////\n";
}

vector<string> ofxImageAsset::getImageList()
{
    vector<string> retval;
    
    map<string, ofImage>::iterator it;
    for (it = dictionary.begin(); it != dictionary.end(); it++)
        retval.push_back(it->first);
    
    return retval;
}
