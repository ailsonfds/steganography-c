#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerImagemBMP.h"
#include "manipularMensagem.h"


void guardar_mensagem_bmp(FILE *img, FILE *arquivo_txt){

	BITMAPFILEHEADER cab1;
	BITMAPINFOHEADER cab2;

	/*Informações do arquivo .txt*/
	char nome_arquivo[25]; //nome do arquivo para abertura
	char nome_arquivobmp[25];
	int i, j;
	char mensagem[50]; //vetor que receberá a mensagem do arquivo nessa função
	int tamanhoMsg; //tamanho da mensagem do arquivo
	char cpy[2];
	

	/*Informações da imagem a ser lida*/
	//char *formato; //define o formato da imagem
	//formato = malloc(2*sizeof(char)); //aloca na memória a quantidade necessária para especificar o formato da imagem
	int k=0;
	//int altura, largura; //define a altura e largura da imagem
	//int MAX; //Quantidade de tons da imagem


	printf("Informe o nome do arquivo que deseja abrir:\n");
		scanf("%s", nome_arquivo);

	arquivo_txt = fopen(nome_arquivo, "rb");

	if(arquivo_txt == NULL){
		fprintf(stderr, "Erro na abertura do arquivo\n");
		fclose(arquivo_txt);
	}

	fread(mensagem, sizeof(char), 50, arquivo_txt);

	tamanhoMsg = strlen(mensagem);
	char str[tamanhoMsg][9];
	
	for(i=0; i<tamanhoMsg; i++){
		str[i][0] = '\0';
		for(j=0; j<8; j++){
			sprintf(cpy,"%d", mensagem[i]%2);
			strcat(str[i], cpy);
			mensagem[i]/=2;
		}
		str[i][j] = '\0';
		printf("%s ", str[i]);
	}
	printf("\n");

	printf("Informe o nome do arquivo BMP que deseja abrir:\n");
		scanf("%s", nome_arquivobmp);

	img = fopen(nome_arquivobmp, "rb+");

	if(img == NULL){
		fprintf(stderr, "ERRO AO TENTAR ABRIR O ARQUIVO\n");
		ferror(img);
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
    		if( k < (tamanhoMsg) ){
				int l = 0;
				while( l < 9 ){
					if( str[k][l++] == '0' ){
						Matriz[i][j].rgbRed = Matriz[i][j].rgbRed>>1;
						Matriz[i][j].rgbRed = Matriz[i][j].rgbRed<<1;
					}
					else{
						Matriz[i][j].rgbRed = Matriz[i][j].rgbRed | 1;
					}
					if( str[k][l++] == '0' ){
						Matriz[i][j].rgbGreen = Matriz[i][j].rgbGreen>>1;
						Matriz[i][j].rgbGreen = Matriz[i][j].rgbGreen<<1;
					}
					else{
						Matriz[i][j].rgbGreen = Matriz[i][j].rgbGreen | 1;
					}
					if( str[k][l++] == '0' ){
						Matriz[i][j].rgbBlue = Matriz[i][j].rgbBlue>>1;
						Matriz[i][j].rgbBlue = Matriz[i][j].rgbBlue<<1;
					}
					else{
						Matriz[i][j].rgbBlue = Matriz[i][j].rgbBlue | 1;
					}
					k++;
				}
			}
    	}


    }

    fclose(img);

  	img = fopen(nome_arquivobmp, "wb");

  	if(img == NULL){
  		fprintf(stderr, "ERRO NA ABERTURA DO ARQUIVO\n");
  		ferror(img);
  	}

  	fwrite(&cab1.bfType, sizeof(cab1.bfType), 1,img);
    fwrite(&cab1.bfSize, sizeof(cab1.bfSize), 1,img);
    fwrite(&cab1.bfReserved1, sizeof(cab1.bfReserved1), 1,img);
    fwrite(&cab1.bfReserved2, sizeof(cab1.bfReserved2), 1,img);
    fwrite(&cab1.bfOffBits, sizeof(cab1.bfOffBits), 1,img);
    //  JÁ QUE NÃO SE REPETIRÁ SERÁ IGUAL A UM
    fwrite(&cab2.biSize, sizeof(cab2.biSize), 1,img);
    fwrite(&cab2.biWidth, sizeof(cab2.biWidth), 1,img);
    fwrite(&cab2.biHeight, sizeof(cab2.biHeight), 1,img);
    fwrite(&cab2.MbiPlanes, sizeof(cab2.MbiPlanes), 1,img);
    fwrite(&cab2.biBitCount, sizeof(cab2.biBitCount), 1,img);
    fwrite(&cab2.biCompression, sizeof(cab2.biCompression), 1,img);
    fwrite(&cab2.biSizeImage, sizeof(cab2.biSizeImage), 1,img);
    fwrite(&cab2.biXPelsPerMeter, sizeof(cab2.biXPelsPerMeter), 1,img);
    fwrite(&cab2.biYPelsPerMeter, sizeof(cab2.biYPelsPerMeter), 1,img);
    fwrite(&cab2.biClrUsed, sizeof(cab2.biClrUsed), 1,img);
    fwrite(&cab2.biClrImportant, sizeof(cab2.biClrImportant), 1,img);

    for(i=cab2.biHeight;i>0;i--){
    	for(j=0;j<cab2.biWidth;j++){
    		fprintf(img,"%c%c%c%c",Matriz[i][j].rgbRed, Matriz[i][j].rgbGreen, Matriz[i][j].rgbBlue, Matriz[i][j].rgbReserved);
    	}
    }


	
}
