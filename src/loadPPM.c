#include "loadPPM.h"

#define Empty (rawImg) {0,0,0,0};

int readInt(FILE *file) {
	int val = 0;
	char c;
	byte cmt_flag = 0;
	fread(&c, 1, 1, file);
	while (c && (cmt_flag || !('0' <= c && c <= '9'))) {
		if (c == '#') cmt_flag = 1;
		else if (c == '\n') cmt_flag = 0;
		fread(&c, 1, 1, file);
	}

	while ('0' <= c && c <= '9') {
		val = val*10 + (c - '0');
		fread(&c, 1, 1, file);
	}
	return val;
}

int log_2(int i) {
	int j = 0;
	while (i >> (++j));
	return j-1;
}

rawImg P1(int width, int height, FILE *file) { return Empty; }
rawImg P2(int width, int height, FILE *file) { return Empty; }
rawImg P3(int width, int height, int maxval, FILE *file) { return Empty; }
rawImg P4(int width, int height, int maxval, FILE *file)
{
	int w = width / 8 + (width % 8 == 0) ? 0 : 1;

	byte* data = (byte *) malloc(w*height);
	fread(data, 1, w*height, file);


	/*byte tmp;
	byte* data = (byte *) malloc(width*height);
	for (int i = 0; i < height; ++i)
	for (int j = 0; j < w; ++j) {
		fread(&tmp, 1, 1, file);
		data[i*j*width + 0] = ((tmp >> 0) & 1) *255;
		data[i*j*width + 1] = ((tmp >> 1) & 1) *255;
		data[i*j*width + 2] = ((tmp >> 2) & 1) *255;
		data[i*j*width + 3] = ((tmp >> 3) & 1) *255;
		data[i*j*width + 4] = ((tmp >> 4) & 1) *255;
		data[i*j*width + 5] = ((tmp >> 5) & 1) *255;
	}*/

	return (rawImg) {width, height, 1, data};
}

rawImg P5(int width, int height, int maxval, FILE *file)
{
	byte* data = (byte *) malloc(width*height);
	fread(data, 1, width*height, file);

	if (maxval < 255)
	for (int i = 0; i < width*height; ++i) {
		data[i] = (byte) ((float) data[i] * 255 / maxval);
	}

	return (rawImg) {width, height, 2, data};
}

rawImg P6(int width, int height, int maxval, FILE *file)
{
	byte* data = (byte *) malloc(width*height*3);
	fread(data, 1, width*height*3, file);

	if (maxval < 255)
	for (int i = 0; i < width*height*3; ++i) {
		data[i] = (byte) ((float) data[i] * 255 / maxval);
	}

	return (rawImg) {width, height, 3, data};
}


rawImg loadPPM(char *filename)
{

	long fileLength;

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
