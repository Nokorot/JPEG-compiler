/*
 * writePPM.h
 *
 *  Created on: 10 Mar 2019
 *      Author: noko
 */

#ifndef WRITEPPM_H_
#define WRITEPPM_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

typedef struct
{
	int width, height;
	byte* data;
} rawImg;

rawImg loadPPM(char *filename);

#endif /* WRITEPPM_H_ */
