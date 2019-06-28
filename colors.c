#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

int checkBash(void) {
	/* checa se o bash esta instalado */
	return system("bash --help > nul 2> nul");
}

void Color(char *cor) {
	/* aplica uma cor especifica usando o Bash */
	char *cod,code[100];

	if(checkBash()!=0) {
		/*puts("erro: bash nao encontrado");*/
		return;
	}

	if(!strcmp(cor,"white1")) 
	    cod = "0;37";
	else if(!strcmp(cor,"white2"))
		cod = "1;37";					
	else if(!strcmp(cor,"red1"))
		cod = "1;31";
	else if(!strcmp(cor,"green1"))
		cod = "0;32";
	else if(!strcmp(cor,"green2"))
		cod = "1;32";
	else if(!strcmp(cor,"blue1")) cod = "1;34";
	else if(!strcmp(cor,"blue2")) cod = "1;36";
	else if(!strcmp(cor,"blue3")) cod = "4;36";
	else if(!strcmp(cor,"yellow2")) cod = "1;33";
	else if(!strcmp(cor,"purple1")) cod = "1;35";
	else if(!strcmp(cor,"red2")) cod = "0;31";
	else {
		puts("erro: cor invalida");
		return;
	}
	
	snprintf(code,sizeof(code),"bash -c \"printf '\033[%sm'\" 2>nul",cod);
	system(code);
}
void resetColor(void) {
	/* reseta a cor para cor branca do Prompt */
	Color("white2");
}


