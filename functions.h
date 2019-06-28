/* char* formatS(char string[],int integer)  */

#define MAX_DEV 10;

typedef struct {
	int codigo_l,quant_emprestimos;
	char nome_l[100],autor[70],area[40];
}LIVROS;

typedef struct {
	int matricula;
	char nome[120],cpf[15];
}ALUNOS;

typedef struct {
	int cod_livro,cod_aluno;
	char nome_l[100],data_emprestimo[40],data_devolucao[40];
}EMPRESTIMOS;

/*geral*/
int listarArquivo(char *f_name);
int removerDado(char *f_name,signed int id_p);
/*acervo*/
LIVROS cadastrarLivro(void);
int armazenarLivro(LIVROS l);
int editarLivro(LIVROS *l);
/*aluno*/
ALUNOS cadastrarAluno(void);
int armazenarAluno(ALUNOS aluno);
int editarAluno(ALUNOS *aluno);
/*emprestimos*/
int armazenarEmprestimos(EMPRESTIMOS emp);
int novoEmprestimo(void);
int confirmarDev(void);
int cancelarEmpre(void);
int listarEmpresTodos(void);
int listarEmpresAluno(void);
int listarEmpresLiv(void);
