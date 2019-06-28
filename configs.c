#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configs.h"
#include "colors.h"

void cleanBuf() {
	/*limpa o buffer de saida*/
	setbuf(stdin,NULL);
}

void getstr(char *str,int size) {
	/*funcao para pegar string dinamicamente*/
    char *c = NULL;
	int cont = 0;
	c = (char*)malloc(sizeof(char));
	
	cleanBuf();
	while((*c = getchar())!='\n' && cont<size) {
		*(str+cont++) = *c;
	}
	*(str+cont) = '\0';
	
	cleanBuf();
	free(c);
}

void redimensionarTela(int x,int y) {
	char code[20];
	
	if( x<15||x>1000 || y<1||y>1000 ) {
        puts("erro: posicao invalida");
	    return;
	}

	snprintf(code,sizeof(code),"mode %d,%d > nul",x,y);
	system(code);
}
void clear(void) {
	if(system("cls 2> nul")) /*windows*/
	    system("clear 2> /dev/null"); /* linux/mac/openbsd */
}

void delay(int t) {
	char comando[40];
	snprintf(comando,40,"timeout %d >nul 2>nul",t);
	system(comando);
}

void pressioneCont(void) {
	resetColor();
 	puts("\n-> Pressione alguma tecla para voltar <-");
 	system("pause >nul");
 	clear();	
}

void iniciar(void) {
	system("color 8f & cls");
	resetColor();
	system("title Biblioteca UEPB");
	redimensionarTela(60,37);
	
	clear();
	puts("\n[*] Bem vindo a biblioteca da UEPB");
}

int isSubstr(char string[150],char subStr[150]) { /*checa se uma substring esta contida na string principal*/
	char *p;
	
	if(strlen(subStr)>strlen(string)) return 0; /*confere se a segunda string é menor que a principal*/
	p = strstr(string,subStr); /*retorna um ponteiro se for substring*/
	if(p) 
	   return 1;
    return 0;
}

int inFile(char *f_name,char string[100],int part) {
	FILE *f = fopen(f_name,"r");
	if(f==NULL || part<1 || part>2) return 0;
	
	int found=0;
	char line[100],str1[100],*str2=NULL;
	
	while(fgets(line,sizeof(line),f)!=NULL) {
		line[strlen(line)-1] = '\0';
		if(!strcmp(line,"")) continue;
		
		strcpy(str1,line);
		strtok_r(str1,":",&str2);
		str2++;
		
		if(part==1) {
			if(!strcmp(string,str1)) {
				found = 1;
				break;
			}
		} else {
			if(!strcmp(string,str2)) {
			   found = 1;
			   break;
            }
		}	
	}
	fclose(f);
	return found;
}

DATE convertData(char dt[50]) {
	DATE f_data;
	if(strlen(dt)<=1) return f_data;
	int i,c,cont_bar=0;
	char aux[5];
	
	for(i=0;i<strlen(dt);i++) {
		if(dt[i]=='/') {
			if(cont_bar==0) {
				f_data.dd = atoi(aux);
			} else if(cont_bar==1) {
				f_data.mm = atoi(aux);
			}
			    
			  			    
		}
		   cont_bar++;
		
		if(cont_bar==0)
		   aux[c++] = dt[i];
		   
	}
	return f_data;
}

int checkValidData(DATE date1,DATE date2) {
	DATE dif_date;
  
    if(date2.dd>=date1.dd)
  	    dif_date.dd = date2.dd-date1.dd;
    else {
 	    date2.dd+=30;
      	date2.mm-=1;
      	dif_date.dd = date2.dd-date1.dd;
	}

	if(date2.mm>=date1.mm)
 	    dif_date.mm = date2.mm-date1.mm;
	else {
 	    date2.mm+=12;
      	date2.yy-=1;
      	dif_date.mm = date2.dd-date1.mm;
	}
   	dif_date.yy = date2.yy-date1.yy;
   
   	if(dif_date.dd>10 || dif_date.mm>0 || dif_date.yy>0) {
   	   return 0;
    }
   	return 1;
}
