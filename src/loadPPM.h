/*
 * loadPPM.h
 *
 *  Created on: 20 Feb 2019
 *      Author: noko
 */

#ifndef LOADPPM_H_
#define LOADPPM_H_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

typedef struct
{
	int width, height;
	byte* data;
} rawImg;

rawImg loadPPM(char *filename);

#endif /* LOADPPM_H_ */
