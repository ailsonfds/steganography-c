#ifndef __STEGANOGRAPHY_H__
#define __STEGANOGRAPHY_H__

#include "image_manip.h"

int bitify(char *message, int **bitcode);

void desbitfy(FILE *output, int *bitcode, int msgsize);

void encodify(RGBQUAD ***matriz, int height, int width, int *message, int msg_size);

int* decodify(RGBQUAD **matriz, int height, int width, int *message, int *size);

#endif /*__STEGANOGRAPHY_H__*/