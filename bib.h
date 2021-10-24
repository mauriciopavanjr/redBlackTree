#include <stdlib.h>

struct tNoLLRB{
    unsigned long chave;
    unsigned long naochave;
    struct tNoLLRB *esq;
    struct tNoLLRB *dir;
    struct tno_lista *prox;
    int bloco, indice;
    int cor;
};
typedef struct tNoLLRB tNoLLRB;

struct tno_lista{
    unsigned long chave;
    unsigned long naochave;
    struct tno_lista *prox;
    int bloco, indice;
};
typedef struct tno_lista tno_lista;

struct registro
{
    unsigned long long chave;
    unsigned long long naochave;
    unsigned char outros[1008];
};
typedef struct registro registro;

int verificaCor(tNoLLRB *no);
void trocaCor(tNoLLRB *no);
void rotacaoDir(tNoLLRB **no);
void rotacaoEsq(tNoLLRB **no);
void MoveNoEsq(tNoLLRB **no);
void MoveNoDir(tNoLLRB **no);
//void balancear(tNoLLRB **no);
void insereNo(tNoLLRB **no, unsigned long k, unsigned long naochave, int bloco, int indice, int *aux);
void insereLLRB(tNoLLRB **raiz, unsigned long k, unsigned long naochave, int bloco, int indice, int *aux);
void travessia(tNoLLRB *raiz);
tno_lista *insereInicio(tno_lista **raiz, unsigned long k,unsigned long naochave,int bloco, int indice);
void ler_lista(tno_lista *raiz);
void buscar_elemento(tNoLLRB *raiz,unsigned long naochave);