typedef struct {
	int dd,mm,yy; 
}DATE; /*struct data: dia/mes/ano*/

void redimensionarTela(int x,int y);
void clear(void);
void iniciar(void);
void cleanBuf(void);
void delay(int t);
void pressioneCont(void);
void getstr(char *str,int size);
int isSubstr(char string[150],char subStr[150]);
int inFile(char *f_name,char string[100],int part);
/*
char* splitData(char str_split[100],int p);
int inFile(char *f_name,char *data_check,int part);
*/
