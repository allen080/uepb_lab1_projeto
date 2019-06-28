#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "configs.h"
#include "functions.h"
#include "locale.h"

void acervo() {
	LIVROS livro;
	int op;
	
	Color("blue2");
	puts("\n\t[*] Acervo de Livros Da UEPB [*]\n");
	Color("blue1");
	puts("1) Cadastrar novo livro\n2) Editar livro\n3) Remover livro cadastrado\n4) Listar todos os livros\n5) Voltar ao menu\n");
	resetColor();
	puts("Opção:");
	
	while(1) {
		printf("-> ");
		scanf("%d",&op);
		
		if(op==5) {
			clear();
			return;
		}
		else if(op<1||op>5)
		    puts("[!] Inválido");
		else
			break;
	}

	Color("blue1");
	if(op==1) {
	    livro = cadastrarLivro();
		if(armazenarLivro(livro))
	 	    puts("\n[*] Cadastro efetuado");
		else 
	 	    puts("\n[!] Erro ao cadastrar livro");
	 	pressioneCont();
		     
	} else if(op==2) {
		editarLivro(&livro);
	} else if(op==3) {
		removerDado("livros_cadastrados.txt",-1);		 
	} else {
		clear();
		puts("\n[*] Lista de livros completa\n");
		listarArquivo("livros_cadastrados.txt");
		pressioneCont();
	}
	
	delay(1);
	acervo();
}

void alunos() {
	ALUNOS aluno;
	int op;
	
	Color("blue2");
	puts("\n\t\t  [*] Menu do Aluno [*]\n");
	Color("yellow2");
	puts("1) Cadastrar novo aluno\n2) Editar aluno\n3) Remover aluno cadastrado\n4) Listar todos os Alunos\n5) Voltar ao menu\n");
	resetColor();
	puts("Opção:");
	
	while(1) {
		printf("-> ");
		scanf("%d",&op);
		
		if(op==5) {
			clear();
			return;
		}   
		else if(op<1||op>5) {
			Color("red2");
		    puts("[!] Inválido");
		   	resetColor();
		}
		else
			break;
	}
	Color("yellow2");
	
	if(op==1) {
	    aluno = cadastrarAluno();
		if(armazenarAluno(aluno)){	  
	 	    puts("\n[*] Cadastro efetuado");
	 	    pressioneCont();
	 	}
		else 
	 	    puts("\n[!] Erro ao cadastrar aluno");
	 	    
	} else if(op==2) {
		clear();
		if(editarAluno(&aluno))
		    puts("\n[*] Edição concluida [*]");
	} else if(op==3) {
		clear();
		if(removerDado("alunos_cadastrados.txt",-1)){
		   puts("\n[*] Livro removido do acervo\n [*]");
		   pressioneCont();
        }
        
	} else if(op==4) {
		clear();
		puts("\n[*] Lista de alunos cadastrados\n");
		listarArquivo("alunos_cadastrados.txt");
		pressioneCont();
	}
	
	delay(1);
	alunos();	
	
}

void emprestimos() {
	/*EMPRESTIMOS emprest;*/
	int op;
	
	Color("blue2");
	puts("\n\t[*] Menu de Emprestimos [*]\n");
	Color("green2");
	puts("1) Novo emprestimo\n2) Confirmar devolução do livro\n3) Cancelar emprestimos\n4) Listar Emprestimos\n5) Voltar ao menu\n");
	resetColor();
	puts("Opção:");
	while(1) {
		printf("-> ");
		scanf("%d",&op);
		
		if(op==5) {
			clear();
			delay(1);
			return;
		}   
		else if(op<1||op>5){
	 		Color("red2");
		    puts("[!] Inválido");
		    Color("green2");
		}
		else break;
	}
	
	Color("green2");
	if(op==1) {
		clear();
	    novoEmprestimo();
	} else if(op==2) {
		confirmarDev();
	} else if(op==3) {
		cancelarEmpre();
		pressioneCont();
	} else if(op==4) {
		clear();
		puts("\n\t\t[*] Listar Emprestimos [*]\n\n1) Listar por livro\n2) Listar por aluno\n3) Listar todos Emprestimos\n");
		while(1) {
			printf("-> ");
			scanf("%d",&op);
			
			if(op<1||op>3) {
				puts("[!] invalido");
				continue;
			}
			else if(op==1)
		 	    listarEmpresLiv();
		 	else if(op==2)
			   listarEmpresAluno();
			else if(op==3)
				listarEmpresTodos();
				
			pressioneCont();
			break;    
		}
	}
	
	delay(1);
	emprestimos();	
}

void menu() {
	int op;
	
	/*cabeçalho do programa*/
	puts("*********************************************************\n*\t\t\t\t\t\t\t*");
 	Color("blue2");
 	printf("\t\t[*] Biblioteca UEPB [*]");
 	resetColor();
 	puts("\t\t\n*\t\t\t\t\t\t\t*");
	puts("*********************************************************");
	
	Color("yellow2");
	puts("\n1) Acervo (Livros)\n2) Alunos\n3) Emprestimos\n4) Sair\n");
	resetColor();
	puts("Opção:");
	
	while(1) {
		printf("-> ");
		scanf("%d",&op);
		
		if(op==4)
		    return;
		else if(op==1) {
			clear();
			acervo();
		} else if(op==2) {
			clear();
			alunos();
		} else if(op==3) {
			clear();
			emprestimos();
		} else {
  		    Color("red2");
		    puts("[!] Inválido");
		   	resetColor();
			continue;
		}
		break;
	}
	menu();
}

int main(void) {
	setlocale(LC_ALL,"");
	resetColor();
	menu();
	Color("blue2");
	puts("\n\t\t[*] Programa Finalizado [*]");
	resetColor();
	/*
	FAZER:
	-cores;
	-emprestimos;
	-ajeitar bugs;
	-comentar codigo;
	MEU DEUS ME AJUDA;
	*/

	
										
	/*iniciar();
	
	resetColor();

	ALUNOS al;
	
	al = cadastrarAluno();
	armazenarAluno(al);
	
	editarAluno(&al);
	*/
	return 0;
}
