/*
 * main.cpp
 *
 *  Created on: 20 Feb 2019
 *      Author: noko
 */

extern "C" {
#include "loadPPM.h"
}

#include <iostream>

int main(){
	rawImg img = loadPPM((char*) "res/plot1000.ppm");


}

