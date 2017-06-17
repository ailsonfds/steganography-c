#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guardarMensagem.h"
#include "lerImagemPPM.h"

void guardar_mensagem(FILE *imagem_copia, FILE *arquivo_txt){
	/*Informações do arquivo .txt*/
	char nome_arquivo[25]; //nome do arquivo para abertura
	char nome_arquivoppm[25];
	int i, j;
	char mensagem[50]; //vetor que receberá a mensagem do arquivo nessa função
	int tamanhoMsg; //tamanho da mensagem do arquivo
	char cpy[2];

	/*Informações da imagem a ser lida*/
	PIXEL **Matriz; //Define uma matriz de PIXEL
	char *formato; //define o formato da imagem
	formato = malloc(2*sizeof(char)); //aloca na memória a quantidade necessária para especificar o formato da imagem
	int k=0;
	int altura, largura; //define a altura e largura da imagem
	int MAX; //Quantidade de tons da imagem


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

	printf("Informe o nome do arquivo PPM que deseja abrir:\n");
		scanf("%s", nome_arquivoppm);

	imagem_copia = fopen(nome_arquivoppm, "rb+");

	if(imagem_copia == NULL){
		fprintf(stderr, "ERRO AO TENTAR ABRIR O ARQUIVO\n");
		ferror(imagem_copia);
	}

	fscanf(imagem_copia, "%s", formato);

	if(strcmp(formato, "P6")!= 0){
		fprintf(stderr, "O formato da imagem não é PPM binário\n");
		fclose(imagem_copia);
	}
fscanf(imagem_copia, "%d %d %d", &altura, &largura, &MAX);

	fgetc(imagem_copia);

	Matriz = (PIXEL **) malloc(largura*sizeof(PIXEL *));
	for(i=0; i<largura; i++){
		Matriz[i] = (PIXEL *) malloc(altura*sizeof(PIXEL));
		for(j=0; j<altura; j++){
			fscanf(imagem_copia, "%c%c%c", &Matriz[i][j].r, &Matriz[i][j].g, &Matriz[i][j].b);
			if( k < (tamanhoMsg) ){
				int l = 0;
				while( l < 9 ){
					if( str[k][l++] == '0' ){
						Matriz[i][j].r = Matriz[i][j].r>>1;
						Matriz[i][j].r = Matriz[i][j].r<<1;
					}
					else{
						Matriz[i][j].r = Matriz[i][j].r | 1;
					}
					if( str[k][l++] == '0' ){
						Matriz[i][j].g = Matriz[i][j].g>>1;
						Matriz[i][j].g = Matriz[i][j].g<<1;
					}
					else{
						Matriz[i][j].g = Matriz[i][j].g | 1;
					}
					if( str[k][l++] == '0' ){
						Matriz[i][j].b = Matriz[i][j].b>>1;
						Matriz[i][j].b = Matriz[i][j].b<<1;
					}
					else{
						Matriz[i][j].b = Matriz[i][j].b | 1;
					}
					k++;
				}
			}
			//fseek(imagem_copia, sizeof(char)*(3), SEEK_CUR);
		}	
	}

	fclose(imagem_copia);
	imagem_copia = fopen(nome_arquivoppm, "wb");

	if(imagem_copia == NULL){
		fprintf(stderr, "ERRO AO TENTAR ABRIR O ARQUIVO\n");
		ferror(imagem_copia);
	}

	fprintf(imagem_copia, "%s\n", formato);

	fprintf(imagem_copia, "%d %d\n%d\n", altura, largura, MAX);

	for(i=0; i<largura; i++){
		for(j=0; j<altura; j++){
			fprintf(imagem_copia, "%c%c%c", Matriz[i][j].r, Matriz[i][j].g, Matriz[i][j].b);
		}
	}

	fclose(imagem_copia);
	fclose(arquivo_txt);
}