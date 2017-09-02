#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>


typedef struct TNodo{
    char nome[10];
    TNodo *esq;
    TNodo *dir;
    int altura;
}TNodo;

typedef struct TipoRegistro{
	char nome[50];
	char sexo[10];
	int ano_nasc;
	TipoRegistro *proximo;
	TipoRegistro *anterior;
}TRegistro;


typedef struct TipoListaRegistro{
	TRegistro *inicio;
	TRegistro *fim;
}TListaRegistro;

TListaRegistro registros;

int altura_arvore(TNodo *N);
int maior_altura(int a, int b);
TNodo* novoNodo(char *nome);
TNodo *rotacaoDireita(TNodo *y);
TNodo *rotacaoEsquerda(TNodo *x);
int pegar_fator_balanc(TNodo *N);
TNodo* insereNodo(TNodo* nodo, char *nome);
void gotoxy(int coluna, int linha);
void exibeNodo(TNodo *R, int linha, int coluna, int variacao);
void caminhamento_emOrdem(TNodo *R);
void caminhamento_posOrdem(TNodo *R);
void caminhamento_preOrdem(TNodo *R);


TNodo criar_arvore(TListaRegistro *registros){
	
	TNodo *raiz = NULL;
	TRegistro *registro_atual = (TRegistro *)malloc(sizeof(TRegistro));
	registro_atual = registros->inicio;
	
	while(registro_atual != NULL){
		raiz = insereNodo(raiz, registro_atual->nome);
		registro_atual = registro_atual->proximo;
	}
	
	
	return *raiz;
}

void exibe_arvore(TNodo *raiz){
	exibeNodo(raiz, 2, 40, 40);
}


void inicializa_lista_registro(TListaRegistro *registros){
	registros->inicio = NULL;
	registros->fim = NULL;
}

void inserir_registro(TListaRegistro *registros, TRegistro *novoElemento){
			
	
	if(registros->inicio == NULL){// Se lista vazia
		
		novoElemento->proximo = NULL;
		novoElemento->anterior = NULL;
	
		registros->inicio = novoElemento;
		registros->fim = novoElemento;	
		
	}else{//Se lista não vazia
		
		novoElemento->proximo = NULL;
		novoElemento->anterior = registros->fim;
	
		registros->fim->proximo = novoElemento;
		registros->fim = novoElemento;	
		
	}
	
}

void consultar_registro(TListaRegistro *registros, TRegistro *consulta){
	TRegistro *atual;
	int encontrou = 0;
	if(registros->inicio == NULL){
		printf("\nNao ha registro cadastrados");
		encontrou = 1;
	}else{
		atual = registros->inicio;
		while(atual != NULL){
			if(strcmp(atual->nome, consulta->nome) == 0){
				printf("\n\tNome:           %s", atual->nome);
				printf("\n\tAno Nascimento: %d", atual->ano_nasc);
				printf("\n\tSexo:           %s", atual->sexo);
				encontrou = 1;
			}
			atual = atual->proximo;
		}
	}
	
	if(encontrou == 0){
		printf("\nRegistro nao encontrado");
	}
}

void excluir_registro(TListaRegistro *registros, TRegistro *excluir){
	
	int excluido = 0;
	char aluno[50];
	
	TRegistro *registro_atual = (TRegistro *)malloc(sizeof(TRegistro));
	registro_atual = registros->inicio;
	

	
	while(registro_atual != NULL){
		
		if(strcmp(registro_atual->nome, excluir->nome) == 0){
			
				if(registro_atual->anterior == NULL){// Caso o curso a ser excluido seja o primeiro da lista
				
					if(registro_atual->proximo == NULL){//Unico da lista
									
						registros->inicio = NULL;
						registros->fim = NULL;
						
					}else{
						
						registros->inicio = registro_atual->proximo;
						registros->inicio->anterior = NULL;
						
					}
					
				}else if(registro_atual->proximo == NULL){// Caso o curso a ser excluido seja o ultimo da lista
					
					registros->fim = registro_atual->anterior;
									
				}else{// Caso não seja nem o primeiro e nem o ultimo		
					
					registro_atual->anterior->proximo = registro_atual->proximo;
					registro_atual->proximo->anterior = registro_atual->anterior;
										
				}
				
				free(registro_atual);
				
				excluido = 1;
				break;
			}			
			
			registro_atual = registro_atual->proximo;			
		}
		
		
		if(excluido == 1){
			printf("\n\nRegistro excluido com sucesso");
		}else{
			printf("\n\nRegistro nao encontrado");
		
	}
		
}

void inicializarMenu(){
	
	int continuar=1;

    do{
        printf("\n=========| MENU |=========\n\n");
        printf("1. Inserir registro\n");
        printf("2. Consultar registro\n");
        printf("3. Excluir registro\n");
        printf("4. Exibir arvore AVL\n");
        printf("5. Caminhamento na avore\n");

		
		printf("\n\n0. Sair\n\n");

        scanf("%d", &continuar);
        system("cls");
        
        if(continuar == 1){
        	
			TRegistro *novoElemento = (TRegistro *)malloc(sizeof(TRegistro));
				        	
           	printf("\nInforme o nome: ");
           	scanf("%s",novoElemento->nome);
           	
           	printf("\nInforme o sexo: ");
           	scanf("%s",novoElemento->sexo);
           	
           	printf("\nInforme o ano de nascimento: ");
           	scanf("%d",&novoElemento->ano_nasc);
           	
           	inserir_registro(&registros, novoElemento);
              
            printf("\nRegistro cadastrado.\n\nAperte 1 para voltar ao menu: ");
            scanf("%d",&continuar);
           
            system("cls");
        	
        	
		}else if(continuar == 2){
			
			TRegistro *novoElemento = (TRegistro *)malloc(sizeof(TRegistro));
				        	
           	printf("\nInforme o nome: ");
           	scanf("%s",novoElemento->nome);
           	
           	consultar_registro(&registros, novoElemento);  
           	
      		printf("\n\nAperte 1 para voltar ao menu: ");
            scanf("%d",&continuar);
                
            system("cls");
			
		}else if(continuar == 3){
			
			TRegistro *novoElemento = (TRegistro *)malloc(sizeof(TRegistro));
				        	
           	printf("\nInforme o nome: ");
           	scanf("%s",novoElemento->nome);
           	
           	excluir_registro(&registros, novoElemento);
           	
      		printf("\n\nAperte 1 para voltar ao menu: ");
            scanf("%d",&continuar);
                
            system("cls");
			
		}else if(continuar == 4){
			
			TNodo raiz = criar_arvore(&registros);
			exibe_arvore(&raiz);
        		
      		printf("\n\nAperte 1 para voltar ao menu: ");
            scanf("%d",&continuar);
                
            system("cls");
			
		}else if(continuar == 5){
			
			TNodo raiz = criar_arvore(&registros);
			
			printf("\n\n\tARVORE BINARIA\n\tCAMINHAMENTO EM ORDEM\n\n");
    		caminhamento_emOrdem(&raiz);
    
    		printf("\n\n\tARVORE BINARIA\n\tCAMINHAMENTO POS ORDEM\n\n");
    		caminhamento_posOrdem(&raiz);
    
    		printf("\n\n\tARVORE BINARIA\n\tCAMINHAMENTO PRE ORDEM\n\n");
    		caminhamento_preOrdem(&raiz);	

        		
      		printf("\n\nAperte 1 para voltar ao menu: ");
            scanf("%d",&continuar);
                
            system("cls");
			
		}
						
	} while(continuar);
	
}

	
	

int main(){
	
	inicializa_lista_registro(&registros);
	inicializarMenu();
		
	system("pause");
	return 0;
	
}


//Função para pegar altura da árvore
int altura_arvore(TNodo *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}
 
// Função que retorna a maior altura
int maior_altura(int a, int b)
{
	if(a>b){
		return a;
	}else{
		return b;
	}
}
 
 
TNodo* novoNodo(char *nome)
{
    TNodo* nodo = (TNodo*) malloc(sizeof(TNodo));
    strcpy(nodo->nome,nome);
    nodo->esq = NULL;
    nodo->dir = NULL;
    nodo->altura = 1; 
    return(nodo);
}
 

TNodo *rotacaoDireita(TNodo *y)
{
    TNodo *x = y->esq;
    TNodo *z = x->dir;
 
    // Rodar
    x->dir = y;
    y->esq = z;
 
    // Atualizar alturas
    y->altura = maior_altura(altura_arvore(y->esq), altura_arvore(y->dir))+1;
    x->altura = maior_altura(altura_arvore(x->esq), altura_arvore(x->dir))+1;
    
 
    // Retornar a nova raiz
    return x;
}
 

TNodo *rotacaoEsquerda(TNodo *x)
{
    TNodo *y = x->dir;
    TNodo *z = y->esq;
 
    // Rodar
    y->esq = x;
    x->dir = z;
 
    //  Atualizar alturas
    x->altura = maior_altura(altura_arvore(x->esq), altura_arvore(x->dir))+1;
    y->altura = maior_altura(altura_arvore(y->esq), altura_arvore(y->dir))+1;
 
    // Retornar a nova raiz
    return y;
}
 

int pegar_fator_balanc(TNodo *N)
{
    if (N == NULL)
        return 0;
    return altura_arvore(N->esq) - altura_arvore(N->dir);
}
 
TNodo* insereNodo(TNodo* nodo, char *nome)
{
    
    if (nodo == NULL)
        return(novoNodo(nome));
 
    if (strcmp(nome,nodo->nome)<0)
        nodo->esq  = insereNodo(nodo->esq, nome);
    else
        nodo->dir = insereNodo(nodo->dir, nome);
 
    
    nodo->altura = maior_altura(altura_arvore(nodo->esq), altura_arvore(nodo->dir)) + 1;
 
    int fator_balanc = pegar_fator_balanc(nodo);
 
    
	// Se estiver desbalanceado: 
    
    if (fator_balanc > 1 && strcmp(nome,nodo->esq->nome)<0)
        return rotacaoDireita(nodo);
 
   
    if (fator_balanc < -1 && strcmp(nome,nodo->dir->nome)>0)
        return rotacaoEsquerda(nodo);
 
  
    if (fator_balanc > 1 && strcmp(nome,nodo->esq->nome)>0)
    {
        nodo->esq =  rotacaoEsquerda(nodo->esq);
        return rotacaoDireita(nodo);
    }
 
   
    if (fator_balanc < -1 && strcmp(nome,nodo->dir->nome)<0)
    {
        nodo->dir = rotacaoDireita(nodo->dir);
        return rotacaoEsquerda(nodo);
    }
 
    
    return nodo;
}
 

void gotoxy(int coluna, int linha) 
{ 
        COORD point; 
        point.X = coluna; point.Y = linha; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point); 
}



void exibeNodo(TNodo *R, int linha, int coluna, int variacao)
{
    char txt[5];

    
	if (R != NULL){
		if((linha < 25) && (coluna < 80) && (coluna > 0)){
           gotoxy(coluna,linha);
           
            strncpy(txt,R->nome,5);
           
           printf("<%s>",txt);
           variacao = variacao /2;
           
           exibeNodo(R->esq,linha+2,coluna-variacao, variacao);
           exibeNodo(R->dir, linha+2,coluna+variacao, variacao);      

		}
	}
}


void caminhamento_emOrdem(TNodo *R){
	if (R != NULL){
		caminhamento_emOrdem(R->esq);
		printf("\t\t%s\n",R->nome);
		caminhamento_emOrdem(R->dir);
	}
}

void caminhamento_posOrdem(TNodo *R){
	if (R != NULL){
		caminhamento_posOrdem(R->esq);
		caminhamento_posOrdem(R->dir);
		printf("\t\t%s\n",R->nome);
	}
}

void caminhamento_preOrdem(TNodo *R){
	if (R != NULL){
		printf("\t\t%s\n",R->nome);
		caminhamento_posOrdem(R->esq);
		caminhamento_posOrdem(R->dir);
	}
}

 
 
