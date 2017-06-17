#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manipularMensagem.h"
#include "lerImagemPPM.h"

/*Sub-rotina que irá criar
um arquivo de texto e escrever uma mensagem nele*/
void criar_mensagem(FILE *arquivo_txt){

	int tamanhoMsg;
	char *nome, *mensagem;
	nome = malloc(25*sizeof(char)); //alocando memória para o nome do arquivo
	mensagem = malloc(80*sizeof(char)); //alocando memória para a mensagem

	printf("Entre com o nome do arquivo:\n");
	scanf("%s", nome);

	arquivo_txt = fopen(nome, "wb"); //abre o arquivo texto para escrita
	
	if(arquivo_txt == NULL){ //verifica se há memória suficiente e se o arquivo existe
		fprintf(stderr, "ERRO AO TENTAR CRIAR O ARQUIVO!\n");
		fclose(arquivo_txt);
	}
	else{
		fgetc(stdin); //limpando o buffer
		fgets(mensagem, 80, stdin); //lê uma string da entrada padrão
	}

	tamanhoMsg = strlen(mensagem);

		//fprintf(arquivo_txt, "%s\n", mensagem); //armazena a string no arquivo "texto"
		fwrite(mensagem, sizeof(char), tamanhoMsg, arquivo_txt);

	fclose(arquivo_txt);	

}