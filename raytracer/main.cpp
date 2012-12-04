//
//  main.cpp
//  raytracer
//
//  Created by John Yang-Sammataro on 12/1/12.
//  Copyright (c) 2012 John Yang-Sammataro. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <stgl.h>
#include <stglut.h>
#include <string>

#include "Scene.h"

using namespace std;

int main(int argc, const char * argv[])
{
    cout << "Starting program" << endl;
   
    //Create a scene
    Scene scene = Scene(argv[1]);
    //Render the scene and save the image
    STImage renderedScene = scene.render();
    
    //Display scene
    
    cout << "Program finished" << endl;
    
    return 0;
}

