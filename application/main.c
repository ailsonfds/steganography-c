#include "steganography.h"

int main(int argc, char **argv){
	int decode_index = 0, format_index = 0;
	int  img_index = 0, msg_index = 0, count = 1;
	char outstr[50];
	FILE *input_img;
	FILE *output_img;
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	PPMFILEHEADER header;
	RGBQUAD **matriz;
	int _height = 0, _width = 0;
	char tmpmsg[2];
	FILE *msg;
	char message[5000];
	int *bitmsg;
	int msgsize;
	while(count < argc){
		if(strcmp(argv[count],"-i") == 0 || strcmp(argv[count],"-o") == 0) msg_index = ++count;
		if(strcmp(argv[count],"-f") == 0){
			format_index = ++count;
			img_index = ++count;
		}
		if(strcmp(argv[count],"-d") == 0 || strcmp(argv[count],"-e") == 0) decode_index = count;
		count++;
	}
	if(decode_index == 0 || format_index == 0 || img_index == 0 || msg_index == 0 || argc != 7){
		fprintf(stderr, "Leak of arguments!!\n");
		abort();
	}
	strcpy(outstr, "new_img.");
	strcat(outstr, argv[format_index]);
	printf("%s\n", outstr);

	input_img = fopen(argv[img_index], "r");
	if(input_img == NULL){
		fprintf(stderr, "File not opened!!\n");
		return 0;
	}

	if(strcmp(argv[format_index], "bmp") == 0){
		read_header_BMP(input_img, &file_header, &info_header);
		_height = info_header.biHeight;
		_width = info_header.biWidth;
		read_pixels(&matriz, info_header.biHeight, info_header.biWidth, input_img, file_header.bfOffBits);
	}else if(strcmp(argv[format_index], "ppm") == 0){
		read_header_PPM(input_img, &header);
		_height = header.height;
		_width = header.width;
		read_pixels(&matriz, header.height, header.width, input_img, header.offset);
	}
	fclose(input_img);

	output_img = fopen(outstr, "w");

	if(output_img == NULL){
		fprintf(stderr, "File not opened!!\n");
		return 0;
	}

	strcpy(message, "");	
	if(strcmp(argv[msg_index-1], "-i") == 0){
		msg = fopen(argv[msg_index], "r");
		while(fscanf(msg, "%c", &tmpmsg[0]) != EOF){
			tmpmsg[1] = '\0';
			strcat(message, tmpmsg);
		}
		msgsize = bitify(message, &bitmsg);
	}else{
		msg = fopen(argv[msg_index], "wb");
	}

	if(strcmp(argv[decode_index],"-e") == 0 && strcmp(argv[msg_index-1], "-i") == 0)
		encodify(&matriz, _height, _width, bitmsg, msgsize);
	else if(strcmp(argv[decode_index],"-d") == 0 && strcmp(argv[msg_index-1], "-o") == 0){
		bitmsg = decodify(matriz, _height, _width, bitmsg, &msgsize);
		desbitfy(msg, bitmsg, msgsize);
	}else{
		fprintf(stderr, "Invalid Options!!\n");
		abort();
	}

	if(strcmp(argv[format_index], "bmp") == 0){
		write_header_BMP(output_img, file_header, info_header);
		write_pixels(matriz, info_header.biHeight, info_header.biWidth, output_img, file_header.bfOffBits);
	}else if(strcmp(argv[format_index], "ppm") == 0){
		write_header_PPM(output_img, header);
		write_pixels(matriz, header.height, header.width, output_img, header.offset);
	}
	fclose(output_img);
	return 0;
}