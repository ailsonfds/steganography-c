#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerImagemBMP.h"
#include "lerImagemPPM.h"

/*Função que irá ler a imagem bitmap, recebe
dois ponteiros do tipo FILE para leitura e
escrita*/
void ler_imagem_bmp(FILE *img, FILE *img_nova){

	BITMAPFILEHEADER cab1;
	BITMAPINFOHEADER cab2;
	int i, j;

			       /*Lendo a imagem*/
	
	img=fopen("imd.bmp", "rb");  //Abertura do arquivo binário para leitura

	if(img == NULL){
		fprintf(stderr, "Erro na abertura\n");
		fclose(img);
	}
		
	/*Lê cada campo da estrutura cabeçalho*/	
    fread(&cab1.bfType, sizeof(cab1.bfType), 1,img);
    fread(&cab1.bfSize, sizeof(cab1.bfSize), 1,img);
    fread(&cab1.bfReserved1, sizeof(cab1.bfReserved1), 1,img);
    fread(&cab1.bfReserved2, sizeof(cab1.bfReserved2), 1,img);
    fread(&cab1.bfOffBits, sizeof(cab1.bfOffBits), 1,img);
    //  JÁ QUE NÃO SE REPETIRÁ SERÁ IGUAL A UM
    fread(&cab2.biSize, sizeof(cab2.biSize), 1,img);
    fread(&cab2.biWidth, sizeof(cab2.biWidth), 1,img);
    fread(&cab2.biHeight, sizeof(cab2.biHeight), 1,img);
    fread(&cab2.MbiPlanes, sizeof(cab2.MbiPlanes), 1,img);
    fread(&cab2.biBitCount, sizeof(cab2.biBitCount), 1,img);
    fread(&cab2.biCompression, sizeof(cab2.biCompression), 1,img);
    fread(&cab2.biSizeImage, sizeof(cab2.biSizeImage), 1,img);
    fread(&cab2.biXPelsPerMeter, sizeof(cab2.biXPelsPerMeter), 1,img);
    fread(&cab2.biYPelsPerMeter, sizeof(cab2.biYPelsPerMeter), 1,img);
    fread(&cab2.biClrUsed, sizeof(cab2.biClrUsed), 1,img);
    fread(&cab2.biClrImportant, sizeof(cab2.biClrImportant), 1,img);

    RGBQUAD **Matriz;
    Matriz=(RGBQUAD**)malloc(cab2.biHeight*sizeof(RGBQUAD*));
    for(i=cab2.biHeight;i>0;i--){
    	Matriz[i]=(RGBQUAD*)malloc(cab2.biWidth*sizeof(RGBQUAD));
    	for(j=0;j<cab2.biWidth;j++){
    		fscanf(img,"%c%c%c%c",&Matriz[i][j].rgbRed, &Matriz[i][j].rgbGreen, &Matriz[i][j].rgbBlue, &Matriz[i][j].rgbReserved);
//    		printf("%c%c%c%c",Matriz[i][j].rgbRed, Matriz[i][j].rgbGreen, Matriz[i][j].rgbBlue, Matriz[i][j].rgbReserved);
    	}
    }

            /* Escrevendo na nova imagem(cópia) */

	img_nova=fopen("imd_copia.bmp","wb"); //Abertura do arquivo binário para escrita

	if(img_nova == NULL){
		fprintf(stderr,"Erro na abertura\n");
		fclose(img_nova);	
	}
	
    fwrite(&cab1.bfType, sizeof(cab1.bfType), 1,img_nova);
    fwrite(&cab1.bfSize, sizeof(cab1.bfSize), 1,img_nova);
    fwrite(&cab1.bfReserved1, sizeof(cab1.bfReserved1), 1,img_nova);
    fwrite(&cab1.bfReserved2, sizeof(cab1.bfReserved2), 1,img_nova);
    fwrite(&cab1.bfOffBits, sizeof(cab1.bfOffBits), 1,img_nova);
    //  JÁ QUE NÃO SE REPETIRÁ SERÁ IGUAL A UM
    fwrite(&cab2.biSize, sizeof(cab2.biSize), 1,img_nova);
    fwrite(&cab2.biWidth, sizeof(cab2.biWidth), 1,img_nova);
    fwrite(&cab2.biHeight, sizeof(cab2.biHeight), 1,img_nova);
    fwrite(&cab2.MbiPlanes, sizeof(cab2.MbiPlanes), 1,img_nova);
    fwrite(&cab2.biBitCount, sizeof(cab2.biBitCount), 1,img_nova);
    fwrite(&cab2.biCompression, sizeof(cab2.biCompression), 1,img_nova);
    fwrite(&cab2.biSizeImage, sizeof(cab2.biSizeImage), 1,img_nova);
    fwrite(&cab2.biXPelsPerMeter, sizeof(cab2.biXPelsPerMeter), 1,img_nova);
    fwrite(&cab2.biYPelsPerMeter, sizeof(cab2.biYPelsPerMeter), 1,img_nova);
    fwrite(&cab2.biClrUsed, sizeof(cab2.biClrUsed), 1,img_nova);
    fwrite(&cab2.biClrImportant, sizeof(cab2.biClrImportant), 1,img_nova);

    for(i=cab2.biHeight;i>0;i--){
    	for(j=0;j<cab2.biWidth;j++){
    		fprintf(img_nova,"%c%c%c%c",Matriz[i][j].rgbRed, Matriz[i][j].rgbGreen, Matriz[i][j].rgbBlue, Matriz[i][j].rgbReserved);
    	}
    }

    

	fclose (img_nova);
	fclose(img);
}