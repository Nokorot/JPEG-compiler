/*
 * writePPM.c
 *
 *  Created on: 10 Mar 2019
 *      Author: noko
 */

void P6(rawImg img, FILE *file)
{
	byte* data = (byte *) malloc(width*height*3);
	fread(data, 1, width*height*3, file);

	if (maxval < 255)
	for (int i = 0; i < width*height*3; ++i) {
		data[i] = (byte) ((float) data[i] * 255 / maxval);
	}
}


void writePPM(char *filename)
{
	//Open file
	FILE *file = fopen(filename, "rb");
	if (!file) {
		fprintf(stderr, "Unable to open file \"%s\"", filename);
		return Empty;
	}

	char magic[2];
	fread(magic, 1, 2, file);

	if (magic[0] != 'P' || magic[1] < '1' || magic[1] > '6') {
		fprintf(stderr, "Unknown file format \"%s\"", magic);
		return Empty;
	}

	int width = readInt(file);
	int height = readInt(file);

	printf("m: %s, w: %d, h: %d \n", magic, width, height);

	int maxval;
	if ((magic[1]-'0')/2 > 1) {
		maxval = readInt(file);
		if (maxval > 255) {
			fprintf(stderr, "Current implementation of the PPM decompiled does not support bit extensions, this file is %d-bit", log_2(maxval+1));
			return Empty;
		}
		if (maxval <= 0) {
			fprintf(stderr, "The maximum value parameter is not positive '%d'", maxval);
			return Empty;
		}
	}
	switch (magic[1]) {
	case 1: return P1(width, height, file);
	case 2: return P2(width, height, file);
	case 3: return P3(width, height, maxval, file);
	case 4: return P4(width, height, maxval, file);
	case 5: return P5(width, height, maxval, file);
	case 6: return P6(width, height, maxval, file);
	}

	return Empty;
}
