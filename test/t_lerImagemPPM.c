#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lerImagemPPM.h"

void ler_imagem_ppm(FILE *img, FILE *img_nova) { //Função responsável pela leitura e escrita da imagem criada
	
	char *nomeArquivo; //representa o nome do arquivo a ser lido
	char *nomeArquivoCopia;
	nomeArquivo = malloc(25*sizeof(char)); //aloca um vetor de char com capacidade para 25 caracteres
	nomeArquivoCopia = malloc(25*sizeof(char)); //aloca um vetor de char com capacidade para 25 caracteres
	PIXEL **Matriz; //Define uma matriz de PIXEL

	/*Verifica se o vetor de char foi alocado corretamente*/
	if(nomeArquivo == NULL){
		printf("Não foi possível alocar o vetor de char\n", stderr);
	}

	/*Verifica se o outro vetor de char foi alocado corretamente*/
	if(nomeArquivoCopia == NULL){
		printf("Não foi possível alocar o vetor de char\n", stderr);
	}

	printf("Informe o nome do arquivo a ser lido:\n");
		scanf("%s", nomeArquivo);

	img = fopen(nomeArquivo, "rb"); //abre o arquivo img que vai ler a imagem


	if(img == NULL){
		fprintf(stderr, "ERRO, NÃO FOI POSSÍVEL ABRIR O ARQUIVO\n");
	}


	char *formato; //define o formato da imagem
	formato = malloc(2*sizeof(char)); //aloca na memória a quantidade necessária para especificar o formato da imagem
	int i, j;
	int altura, largura; //define a altura e largura da imagem
	int MAX; //Quantidade de tons da imagem

	fscanf(img, "%s", formato); //lê o formato da imagem

		if(strcmp(formato,"P6") != 0){ //verifica se o formato é PPM
			fprintf(stderr, "O FORMATO DA IMAGEM NÃO É PPM BINÁRIO\n");
			fclose(img);
		}


	fscanf(img, "%d %d %d", &largura, &altura, &MAX); //lê os componentes altura, largura e tonalidade da imagem	

	Matriz = (PIXEL**) malloc(largura * sizeof(PIXEL*)); //aloca dinamicamente a largura da imagem e realiza um cast com (PIXEL**)
	for(i=0; i<largura; i++){
		Matriz[i] = (PIXEL*) malloc(altura * sizeof(PIXEL)); //aloca dinamicamente a altura da imagem
		for(j=0; j<altura; j++){	
			fscanf(img, "%c%c%c", &Matriz[i][j].r, &Matriz[i][j].g, &Matriz[i][j].b); //lê cada pixel da imagem, com cada pixel contendo o RGB
		}
	}

	printf("Informe o nome do arquivo a ser criado:\n");
		scanf("%s", nomeArquivoCopia);

	img_nova = fopen(nomeArquivoCopia, "wb"); //abre o arquivo "img_nova" para escrever para escrever nele os pixels lidos na imagem original

	fprintf(img_nova, "%s\n%d %d\n%d", formato, largura, altura, MAX); //Escreve no arquivo as especificações da imagem
	for(i=0; i<largura; i++){
		for(j=0; j<altura; j++){
			fprintf(img_nova, "%c%c%c", Matriz[i][j].r, Matriz[i][j].g, Matriz[i][j].b);//Escreve no novo arquivo (img_nova) os pixels da imagem lida
		}
	}


	fclose(img_nova); //fecha o arquivo
	fclose(img); //fecha o outro arquivo
}