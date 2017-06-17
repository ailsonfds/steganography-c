#ifndef __IMAGE_MANIP_H__
#define __IMAGE_MANIP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagBITMAPFILEHEADER{  /* ocupa 14 bytes e é o 1° a aparecer no ficheiro */
	char bfType[3]; /* especifica o firmato BM */
	unsigned int bfSize; /* tamanho do arquivo em bytes */
	unsigned short bfReserved1;	
	unsigned short bfReserved2;	
	unsigned int bfOffBits; /* offset da matriz de pixels */
}BITMAPFILEHEADER;

typedef struct tagRGBQUAD{
	unsigned char rgbBlue, rgbGreen, rgbRed, rgbReserved; /* cores RGB da imagem */
}RGBQUAD;

typedef struct tagBITMPAINFOHEADER{ 
	unsigned int biSize; /* tamanho do cabeçalho */
	int biWidth; /* largura da imagem */
	int biHeight; /* altura da imagem */
	unsigned short biPlanes; /* quantidade de planos da imagem	*/
	unsigned short biBitCount;	/* quantidade de bits por pixel */
	unsigned int biCompression; /* compressão, se existit */
	unsigned int biSizeImage; /* tamanho da imagem em bytes */
	unsigned int biXPelsPerMeter; /* número de pixels por metro horizontalmente */
	unsigned int biYPelsPerMeter; /* número de pixels por metro verticalmente */
	unsigned int biClrUsed;	 /* quantidade de cores utilizadas na imagem */
	unsigned int biClrImportant;  /* quantidade de cores importantes */
}BITMAPINFOHEADER;

typedef struct tagBITMAPINFO{  
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD *bmiColors; 
}BITMAPINFO;

typedef struct tagPPMFILEHEADER{
	char type[3];
	unsigned int height;
	unsigned int width;
	unsigned int range;
	int offset;
}PPMFILEHEADER;

void read_header_BMP(FILE *img, BITMAPFILEHEADER *file_header, BITMAPINFOHEADER *info_header);

void write_header_BMP(FILE *img, BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header);

void read_header_PPM(FILE *img, PPMFILEHEADER *header);

void write_header_PPM(FILE *img, PPMFILEHEADER header);

void read_pixels(RGBQUAD ***matriz, int height, int width, FILE *img, int offset);

void write_pixels(RGBQUAD **matriz, int height, int width, FILE *img, int offset);

#endif /*__IMAGE_MANIP_H__*/