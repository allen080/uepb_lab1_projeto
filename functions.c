#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "colors.h"
#include "configs.h"
#include "functions.h"

/* acervo de livros: */

/****funções gerais do programa****/

int listarArquivo(char *f_name) {
	FILE *f = NULL;
	char c[100];
	
	f = fopen(f_name,"r");
	if(f==NULL) return 0;
	
	while(fgets(c,sizeof(c),f)!=NULL)
	    printf("%s",c);

	fclose(f);
	return 1;
}

int removerDado(char *f_name,signed int id_p) {
	/*remove um dado de um dos arquivos.txt, se o parametro do id_p solicitado for -1, pergunta qual id que deseja inserir, senao usa o id fornecido*/
	FILE *f = NULL,*new_f = NULL;
	char line[100],r_id[20],aux[20],*str_id;
	int found = 0,achou_id = 0;

	if(strcmp(f_name,"livros_cadastrados.txt") && strcmp(f_name,"alunos_cadastrados.txt") && strcmp(f_name,"emprestimos_realizados.txt"))
	   return 0;

	if(id_p==-1) {
	    printf("\nid para remoção: ");
		cleanBuf();
		getstr(r_id,sizeof(r_id));
	} else {
		sprintf(r_id,"%d",id_p);
	}
	
	f = fopen(f_name,"r");
	new_f = fopen("novo_arq.txt","w");
	if(f==NULL || new_f==NULL) return 0; /*abre os dois arquivos e checa se foram abertos corretamente*/

	if(!strcmp("alunos_cadastrados.txt",f_name)) 
	    strcpy(aux,"numero de matricula: ");
	else if(!strcmp("livros_cadastrados.txt",f_name))
 	    strcpy(aux,"codigo do livro: ");
	else
	    strcpy(aux,"matricula do aluno: ");	
	    
	str_id = strcat(aux,r_id); /*junta o id com a string especificada */
	
	while(fgets(line,sizeof(line),f)!=NULL) {	    
	    line[strlen(line)-1]='\0'; /*remove o '\n' da linha */
		
		if(isSubstr(line,r_id)) { /*verifica se encontrou o id*/		
			found = 1;
			achou_id = 1;
		}
		
		if(achou_id==0) /*escreve a linha apenas se nao tiver encontrado*/
			fprintf(new_f,"%s\n",line);
 		else if(!strcmp(line,"") || !strcmp(line,"\n")) { /*checa se terminou os dados do ID do usuario encontrado, para continuar a escrita dos outros dados*/
			achou_id = 0;	
		}
	}
	
	if(!found) {
		puts("\n[!] Não foi possivel remover o dado [!]");
		return 0;
	}
	fclose(f);
	fclose(new_f);
	
	/*renomeia o novo arquivo para o original*/
	if(!strcmp("alunos_cadastrados.txt",f_name))
    	system("type novo_arq.txt > alunos_cadastrados.txt & del novo_arq.txt 2> nul");
	else if(!strcmp("livros_cadastrados.txt",f_name))
    	system("type novo_arq.txt > livros_cadastrados.txt & del novo_arq.txt 2> nul");
	
	return 1;
}

/**Acervo de Livros**/

LIVROS cadastrarLivro(void) {
	LIVROS livro;
	char aux_c[12];
	
	clear();
	printf("[*] Iniciando cadastro do livro\n\n");
	
	printf("Nome do livro: ");
	getstr(livro.nome_l,sizeof(livro.nome_l));
	printf("Autor principal: ");
	getstr(livro.autor,sizeof(livro.autor));
	
	while(1) {
		printf("Código do livro: ");
		scanf("%d",&livro.codigo_l);
		sprintf(aux_c,"%d",livro.codigo_l);
		
		if(inFile("livros_cadastrados.txt",aux_c,2)) {
		    Color("red2");
		    puts("[!] Codigo do livro ja cadastrado [!]");
		    Color("blue1");
		}else break;		
	}
	printf("Área de conhecimento: ");
	getstr(livro.area,sizeof(livro.area));
	
	do{
		printf("Quantidade de exemplares para emprestar: ");
		scanf("%d",&livro.quant_emprestimos);
		if(livro.quant_emprestimos<=0)
		    puts("[!] invalido");
	} while(livro.quant_emprestimos<=0);

	return livro;
}

int armazenarLivro(LIVROS l) { /*armazena o livro em livros cadastrados.txt*/
	FILE *file = NULL;
	char *info[5] = {"codigo do livro","nome do livro","nome do autor principal","area do conhecimento","exemplares para emprestimo"};
	
	file = fopen("livros_cadastrados.txt","a");
	if(file==NULL) return 0;
	
	fprintf(file,"%s: %d\n",info[0],l.codigo_l);
	fprintf(file,"%s: %s\n",info[1],l.nome_l);
    fprintf(file,"%s: %s\n",info[2],l.autor);
    fprintf(file,"%s: %s\n",info[3],l.area);
    fprintf(file,"%s: %d\n\n",info[4],l.quant_emprestimos);

	fclose(file);
	return 1;
}

int editarLivro(LIVROS *l) { /*VER ESSA FUNÇAO*/
	int op,l_id;
	char aux_id[12];
	
	clear();
	puts("\n[*] Iniciando Edição do livro\n");
	
	printf("Código do livro que sera editado: ");
	scanf("%d",&l_id);
	sprintf(aux_id,"%d",l_id);
	
	if(!inFile("livros_cadastrados.txt",aux_id,2)) {
		puts("\n[!] ID do livro não encontrado\n");
		return 0;
	}
	
	puts("\n1) Editar nome do livro\n2) Editar nome do autor\n3) Editar codigo\n4) Editar área de conhecimento\n5) Editar quantidade de exemplares\n6)Sair da edição\n\nOpção:");
	while(1) {
		printf("-> ");
		scanf("%d",&op);
		if(op<1||op>6)
			 puts("[!] Inválido");
		else break;
	}
	switch(op) {
  		case 1:
  			 printf("\nnovo nome do livro: ");
			 getstr(l->nome_l,sizeof(l->nome_l));
			 break;
        case 2:
			printf("\nnovo nome do autor: ");
			getstr(l->autor,sizeof(l->autor));
			break;
		case 3:
	    	printf("\nnovo codigo: ");
	 		scanf("%d",&l->codigo_l);
	 		break;
		case 4:
			printf("\nnova quant. de emprestimos: ");
   			scanf("%d",&l->quant_emprestimos);
	     	break;
		case 5:
  			 printf("\nnova area de conhecimento: ");
	 		 getstr(l->area,sizeof(l->area));
	 		 break;
	    case 6:
	    	delay(1);
	    	return 2;
		default:
			puts("[!] Inválido");
			break;
		}
	
	if(removerDado("livros_cadastrados.txt",l_id));
	   armazenarLivro(*l);
	
	puts("\n[*] Edição concluida\n");	
	return 1;
}


/******ALUNOS*****/

ALUNOS cadastrarAluno(void) {
	ALUNOS aluno;
	char temp_id[12];
	
	clear();
	puts("\n[*] Iniciando cadastro do aluno\n");
	
	printf("nome: ");
	getstr(aluno.nome,sizeof(aluno.nome));
	
	while(1) { /*recebe a matricula do aluno apenas se nao estiver uma igual cadastrada*/
	    printf("numero de matricula: ");
		cleanBuf();
		scanf("%d",&aluno.matricula);
	
		sprintf(temp_id,"%d",aluno.matricula);
		if(!inFile("alunos_cadastrados.txt",temp_id,2))
	 	   break;
		puts("[!] ja existe uma matricula com esse codigo, digite outro");	
	}
	
	printf("cpf: ");
	getstr(aluno.cpf,sizeof(aluno.cpf));

	return aluno;
}

int armazenarAluno(ALUNOS aluno) {
	FILE *f = NULL;
	f = fopen("alunos_cadastrados.txt","a");
	if(f==NULL) {
		puts("[!] Erro ao armazenar aluno");
		return 0;
	}
	
	fprintf(f,"numero de matricula: %d\n",aluno.matricula);
	fprintf(f,"nome do aluno: %s\n",aluno.nome);
	fprintf(f,"numero de cpf: %s\n\n",aluno.cpf);
	
	fclose(f);
	
	return 1;
}

int editarAluno(ALUNOS *aluno) {
	int id_edit,op;
	char aux[12];
	
	puts("\n[*] Editando dados do aluno\n");
	printf("Nome do aluno que sera editado: ");
	getstr(aluno->nome,sizeof(aluno->nome));
	printf("Cpf do aluno: ");
	getstr(aluno->cpf,sizeof(aluno->cpf));
	printf("Numero de matricula do aluno para edição: ");
	scanf("%d",&id_edit);
	sprintf(aux,"%d",id_edit); /*cria uma copia em string do id*/
	
	if(!inFile("alunos_cadastrados.txt",aux,2)) {
	   puts("\n[!] matricula informada não encontrada");
	   return 0;
    }
    
    puts("\n1)nome\n2)numero de matricula\n3)cpf\n4)sair da edição\n\nopção para editar:");
    while(1) {
    	printf("-> ");
    	cleanBuf();
    	scanf("%d",&op);
    	
    	if(op<1||op>4)
    	   puts("[!] invalido");
    	else break;
	}
	putchar('\n');
	
	if(op==1) {
		printf("novo nome: ");
		getstr(aluno->nome,sizeof(aluno->nome));
	} else if(op==2) {
		printf("novo numero de matricula: ");
		scanf("%d",&aluno->matricula);
	} else if(op==3) {
		printf("novo cpf: ");
		getstr(aluno->cpf,sizeof(aluno->cpf));
	} else {
		puts("\n[*] encerrando edição");
	}
	
	
	if(removerDado("alunos_cadastrados.txt",id_edit))
	   armazenarAluno(*aluno);
	 
    return 1;
}

/**EMPRESTIMOS**/

int armazenarEmprestimos(EMPRESTIMOS emp) {
	FILE *f = NULL;
	f = fopen("emprestimos_realizados.txt","a");
	if(f==NULL) {
		puts("[!] erro ao armazenar dados do emprestimo");
		return 0;
	}
	
	fprintf(f,"matricula do aluno: %d\n",emp.cod_aluno);
	fprintf(f,"codigo do livro: %d\n",emp.cod_livro);
	fprintf(f,"nome do livro: %s\n",emp.nome_l);
	fprintf(f,"data do emprestimo: %s\n",emp.data_emprestimo);
	fprintf(f,"data de devolução: %s\n\n",emp.data_devolucao);
	
	puts("[*] Emprestimo realizado [*]");
	fclose(f);
	
	return 1;
}

int novoEmprestimo(void) {
	EMPRESTIMOS emp;
	char aux_id[12];
	
	puts("\n\t\t[*] Realizando emprestimo [*]\n");
	puts("Lista de livros do acervo:\n");
	listarArquivo("livros_cadastrados.txt");
	
	printf("Nome do livro que sera emprestado: ");
	getstr(emp.nome_l,sizeof(emp.nome_l));
	printf("Código do livro: ");
	cleanBuf();
	scanf("%d",&emp.cod_livro);
	
	if(!inFile("livros_cadastrados.txt",emp.nome_l,2)) {
		puts("\n[!] Livro não consta no Acervo\n");
	    return 1;
	}
	
	printf("Código do aluno que emprestará o livro: ");
	scanf("%d",&emp.cod_aluno);
	sprintf(aux_id,"%d",emp.cod_aluno); /**/
	
	if(!inFile("alunos_cadastrados.txt",aux_id,2)) {
		puts("\n[!] Aluno não cadastrado\n");
	    return 0;
	}
	/*receber data atual como data do emprestimo:*/
	time_t cur_time = time(NULL);
	struct tm time_n = *localtime(&cur_time);
	
	snprintf(emp.data_emprestimo,sizeof(emp.data_emprestimo),"%d/%d/%d",time_n.tm_mday,time_n.tm_mon+1,time_n.tm_year+1900);
	
	printf("\nData de emprestimo do livro = Data Atual (%s)\n",emp.data_emprestimo);
	printf("Data de devolução do livro(MAX: 10 dias): ");
	getstr(emp.data_devolucao,sizeof(emp.data_devolucao));
	
	armazenarEmprestimos(emp);
	return 1;
}

int listarEmpresTodos(void) {
	clear();
	int ret;
	
	puts("\n[*] Listando todos os Emprestimos realizados [*]\n");
	ret = listarArquivo("emprestimos_realizados.txt");
	
	return ret; 
}

int listarEmpresLiv(void) { /*Lista os emprestimos realizados de um livro especifico*/
	FILE *file = fopen("emprestimos_realizados.txt","r");
	if(file==NULL) return 0;
	
	LIVROS l;
	char aux_str[100],line[100],matricula_bkp[100];
	int exibir=0,exibiu_mat,emp_realizado=0;
	
	printf("\nNome do livro: ");
	getstr(l.nome_l,sizeof(l.nome_l));
	printf("Codigo do livro: ");
	scanf("%d",&l.codigo_l);
	
	/*sprintf(aux_c,"%d",l.codigo_l);*/
	sprintf(aux_str,"codigo do livro: %d",l.codigo_l);
	
	/*confere se o livro esta cadastrado*/
	if(!inFile("emprestimos_realizados.txt",l.nome_l,2) || !inFile("emprestimos_realizados.txt",aux_str,2))  {
		puts("\n[!] Livro não cadastrado [!]");
		return 0;
	}
	
	printf("\n[*] Listando emprestimos do livro %s [*]\n\n",l.nome_l);
	
	while(fgets(line,sizeof(line),file)!=NULL) { /*percorre toda lista de emprestimos e exibe apenas as que forem do livro informado*/
		line[strlen(line)-1] = '\0';
		if(!strcmp(line,"")) continue;
		
		if(isSubstr(line,"matricula do aluno")) {
			strcpy(matricula_bkp,line);
			exibiu_mat = 0;
			continue;
		}

		if(!strcmp(aux_str,line)) {
			exibir = 1;
			emp_realizado++;
		}
		
		if(exibir) { 
			if(!exibiu_mat) {
				exibiu_mat = 1;
				printf("%s\n",matricula_bkp);
			}		
			printf("%s\n",line); /*mostra os dados do livro encontrado*/			
		} if(exibir && isSubstr(line,"data de devolução")) {
		    exibiu_mat = 0;
		    exibir = 0;
		}
												
	}
	fclose(file);
	
	if(emp_realizado<=0) { /*verifica se foi encontrado pelo menos um livro*/
		puts("\n[!] Não foi realizado nenhum emprestimo desse livro.\n");
	}
	
	return 1;
}

int listarEmpresAluno(void) { /*Lista os emprestimos realizados de um aluno informado*/
	FILE *file = fopen("emprestimos_realizados.txt","r");
	if(file==NULL) return 0;
	
	ALUNOS al;
	char aux_str[100],line[100];
	int exibir=0,emp_realizado=0;
	
	printf("\nNome do aluno: ");
	getstr(al.nome,sizeof(al.nome));
	printf("Número de matricula do aluno: ");
	scanf("%d",&al.matricula);
	sprintf(aux_str,"numero de matricula: %d",al.matricula);
	
	/*confere se o aluno esta cadastrado*/
	if(!inFile("alunos_cadastrados.txt",aux_str,2) && !inFile("alunos_cadastrados.txt",al.nome,2) )  {
		puts("\n[!] Aluno não cadastrado [!]");
		return 0;
	}
	
	printf("\n[*] Listando emprestimos do aluno %s [*]\n\n",al.nome);
	
	while(fgets(line,sizeof(line),file)!=NULL) { /*percorre toda lista de emprestimos e exibe apenas as que forem do livro informado*/
		line[strlen(line)-1] = '\0';
		if(!strcmp(line,"")) continue;

		if(!strcmp(aux_str,line)) {
			exibir = 1;
			emp_realizado++;
		}
		
		if(exibir) { 	
			printf("%s\n",line); /*mostra os dados do livro encontrado*/			
		} if(exibir && isSubstr(line,"data de devolução")) {
		    exibir = 0;
		}
												
	}
	fclose(file);
	
	if(emp_realizado<=0) {
		puts("\n[!] Não foi realizado nenhum emprestimo desse aluno.\n");
	}
	
	return 1;
}
int confirmarDev(void) {
	FILE *file = fopen("emprestimos_realizados.txt","r");
	if(file==NULL) return 0;
	
	ALUNOS al;
	char aux_str[100],line[100];
	int exibir=0,emp_realizado=0;
	
	printf("\nNome do aluno: ");
	getstr(al.nome,sizeof(al.nome));
	printf("Número de matricula do aluno: ");
	scanf("%d",&al.matricula);
	sprintf(aux_str,"numero de matricula: %d",al.matricula);
	
	/*confere se o aluno esta cadastrado*/
	if(!inFile("alunos_cadastrados.txt",aux_str,2) && !inFile("alunos_cadastrados.txt",al.nome,2) )  {
		puts("\n[!] Aluno não cadastrado [!]");
		return 0;
	}
	
	printf("\n[*] Listando emprestimos do aluno %s [*]\n\n",al.nome);
	
	while(fgets(line,sizeof(line),file)!=NULL) { /*percorre toda lista de emprestimos e exibe apenas as que forem do livro informado*/
		line[strlen(line)-1] = '\0';
		if(!strcmp(line,"")) continue;

		if(!strcmp(aux_str,line)) {
			exibir = 1;
			emp_realizado++;
		}
		
		if(exibir) { 	
			printf("%s\n",line); /*mostra os dados do livro encontrado*/			
		} if(exibir && isSubstr(line,"data de devolução")) {
		    exibir = 0;
		}							
	}
	fclose(file);
	
	return 1;
}
int cancelarEmpre(void) {
	FILE *file = fopen("emprestimos_realizados.txt","r");
	if(file==NULL) return 0;
	EMPRESTIMOS emp;
	char aux_str[50];
			
	printf("\nNúmero da matricula do aluno: ");
	scanf("%d",&emp.cod_aluno);
	sprintf(aux_str,"%d",emp.cod_aluno);
	printf("Codigo do livro: ");
	scanf("%d",&emp.cod_livro);
	
	if(!inFile("emprestimos_realizados.txt",aux_str,2)) {
		puts("\n[!] Emprestimo não encontrado [!]\n");
		return 0;
	}
	
	if(removerDado("emprestimos_realizados.txt",emp.cod_aluno)) {
		puts("\n[*] Emprestimo Cancelado [*]\n");
	}
	return 1;
}
