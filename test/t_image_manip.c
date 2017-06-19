#include "image_manip.h"

int main(){
	FILE *input_img;
	FILE *output_img;
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	PPMFILEHEADER header;
	RGBQUAD **matriz;

	printf("Testando leitura de arquivo...\n");

	input_img = fopen(fname, "r");
	if(input_img == NULL){
		fprintf(stderr, "File not opened!!\n");
		return 0;
	}

	if(strcmp(format, "bmp") == 0){
		read_header_BMP(input_img, &file_header, &info_header);
		read_pixels(&matriz, info_header.biHeight, info_header.biWidth, input_img, file_header.bfOffBits);
	}else if(strcmp(format, "ppm") == 0){
		read_header_PPM(input_img, &header);
		read_pixels(&matriz, header.height, header.width, input_img, header.offset);
	}
	fclose(input_img);

	printf("Testando escrita em arquivo...\n");

	output_img = fopen(outstr, "w");

	if(output_img == NULL){
		fprintf(stderr, "File not opened!!\n");
		return 0;
	}

	if(strcmp(format, "bmp") == 0){
		write_header_BMP(output_img, file_header, info_header);
		write_pixels(matriz, info_header.biHeight, info_header.biWidth, output_img, file_header.bfOffBits);
	}else if(strcmp(format, "ppm") == 0){
		write_header_PPM(output_img, header);
		write_pixels(matriz, header.height, header.width, output_img, header.offset);
	}
	fclose(output_img);
	return 0;
}