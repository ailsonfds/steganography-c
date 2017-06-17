#include "steganography.h"

int power(int base, int index){
	int i, sum = base;
	for (i = 1; i < index; ++i){
		sum *= base;
	}
	return sum;
}

int bitify(char *message, int **bitcode){
	int i, size = strlen(message)*8, count = 0;
	FILE *errf = fopen("debug.txt", "w");
	*bitcode = malloc(sizeof(int)*strlen(message)*8);
	while(count < size/8){
		for(i = 0; i < 8; i++){
			(*bitcode)[count*8+i] = (message[count])%2;
			(message[count])/=2;
			fprintf(errf, "%d", (*bitcode)[count*8+i]);
		}
		count++;
	}
	return size;
}

void desbitfy(FILE *output, int *bitcode, int msgsize){
	int count = 0, sum, i;
	char decoder = 0;
	FILE *errf = fopen("debug.txt", "w");
	while(count < msgsize/8){
		sum = 0;
		for (i = 0; i < 8; i++){
			sum += bitcode[count*8+i]*(power(2,i));
		}
		if(sum != 0) sum--;
		decoder = (char)(sum);
		fprintf(output, "%c", decoder);
		count++;
		decoder = 0;
		fprintf(errf, "%c = %d | ", decoder, sum);
	}
	fclose(errf);
}

void encodify(RGBQUAD ***matriz, int height, int width, int *message, int msg_size){
	int i, j, k = 0;
	for(i = 0; i < height && k < msg_size; ++i){
		for(j = 0; j < width && k < msg_size; ++j){
			if(message[k] == 0 && k < msg_size)
				(*matriz)[i][j].rgbRed = (*matriz)[i][j].rgbRed&(~1);
			else if(message[k] == 1 && k < msg_size)
				(*matriz)[i][j].rgbRed = (*matriz)[i][j].rgbRed|1;
			k++;
			if(message[k] == 0 && k < msg_size)
				(*matriz)[i][j].rgbGreen = (*matriz)[i][j].rgbGreen&(~1);
			else if(message[k] == 1 && k < msg_size)
				(*matriz)[i][j].rgbGreen = (*matriz)[i][j].rgbGreen|1;
			k++;
			if(message[k++] == 0 && k < msg_size)
				(*matriz)[i][j].rgbBlue = (*matriz)[i][j].rgbBlue&(~1);
			else if(message[k] == 1 && k < msg_size)
				(*matriz)[i][j].rgbBlue = (*matriz)[i][j].rgbBlue|1;
			k++;
		}
	}
}

int *decodify(RGBQUAD **matriz, int height, int width, int *message, int *size){
	int i, j, k = 0;
	*size = height*width*3;
	*size += (*size)%8;
	printf("%d\n", *size);
	message = malloc((*size)*sizeof(int));
	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){
			message[k++] = (matriz[i][j].rgbRed)%2;
			message[k++] = (matriz[i][j].rgbGreen)%2;
			message[k++] = (matriz[i][j].rgbBlue)%2;
		}
	}
	return message;
}
