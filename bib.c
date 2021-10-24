#include "bib.h"
#include<stdio.h>
#include<stdlib.h>

#define RED 1
#define BLACK 0

//VERIFICA A COR DE UM N�
int verificaCor(tNoLLRB *no){
    if(no == NULL)
        return BLACK;
    else
        return no->cor;
}

//TROCA COR DO N� E DE SEUS FILHOS
void trocaCor(tNoLLRB *no){
    no->cor = !no->cor;
    if(no->esq != NULL)
        no->esq->cor = !no->esq->cor;
    if(no->dir != NULL)
        no->dir->cor = !no->dir->cor;
}

//ROTACAO DIREITA
void rotacaoDir(tNoLLRB **no){
    tNoLLRB *aux = (*no);
    (*no) = aux->esq;
    aux->esq = (*no)->dir;
    (*no)->dir = aux;
    (*no)->cor = (*no)->dir->cor;
    (*no)->dir->cor = RED;
}

//ROTACAO ESQUERDA
void rotacaoEsq(tNoLLRB **no){
    tNoLLRB *aux = (*no);
    (*no) = aux->dir;
    aux->dir = (*no)->esq;
    (*no)->esq = aux;
    (*no)->cor = verificaCor((*no)->esq);
    aux = (*no)->esq;
    aux->cor = RED;
}

//MOVE NO VERMELHO PARA ESQUERDA
void MoveNoEsq(tNoLLRB **no){
    trocaCor(*no);
    if(verificaCor((*no)->dir->esq) == RED){
        rotacaoDir(&(*no)->dir);
        rotacaoEsq(no);
    }
    trocaCor(*no);
}

//MOVE NO VERMELHO PARA DIREITA
void MoveNoDir(tNoLLRB **no){
    trocaCor(*no);
    if((verificaCor((*no)->esq->esq)) == RED)
        rotacaoDir(no);
    trocaCor(*no);
}

void insereNo(tNoLLRB **no, unsigned long k, unsigned long naochave, int bloco, int indice,  int *aux){
    if ((*no) == NULL){
        (*no) = (tNoLLRB *)malloc(sizeof(tNoLLRB));
        if ((*no) == NULL)
            return;
        (*no)->chave = k;
        (*no)->cor = RED;
        (*no)->naochave = naochave;
        (*no)->bloco = bloco;
        (*no)->indice = indice;
        (*no)->esq = (*no)->dir = NULL;
        (*no)->prox = NULL;
        return;
    }
    //COLISAO
    if ((*no)->naochave == naochave && (*no)->chave != k){
        insereInicio(&((*no)->prox), k, naochave, bloco, indice);
        (*aux)++;
    }
    else{
        //INSERCAO NA ESQUERDA
        if ((*no)->naochave > naochave)
            insereNo(&(*no)->esq, k, naochave, bloco, indice, aux);
        //INSERCAO NA DIREITA
        if ((*no)->naochave < naochave)
            insereNo(&(*no)->dir, k, naochave, bloco, indice, aux);
    }
    //VERIFICACAO SE FILHO DIREITO E' VERMELHO
    if ( ( verificaCor((*no)->dir) == RED )  && ( verificaCor((*no)->esq) == BLACK ))
        rotacaoEsq(no);
    //VERIFICACAO SE TEM 2 VERMELHOS CONSECUTIVOS
    if ( (verificaCor((*no)->esq) == RED ) && ( verificaCor((*no)->esq->esq) == RED ) )
        rotacaoDir(no);
    //VERIFICACAO SE OS 2 FILHOS SAO VERMELHOS
    if ( (verificaCor((*no)->esq) == RED ) && ( verificaCor((*no)->dir) == RED ) )
        trocaCor(*no);
}

//INSERCAO
void insereLLRB(tNoLLRB **raiz, unsigned long k, unsigned long naochave, int bloco, int indice, int *aux){
    insereNo(raiz, k, naochave, bloco, indice, aux);
    if ((*raiz) != NULL)
        (*raiz)->cor = BLACK;
}

void travessia(tNoLLRB *raiz){
    if(raiz == NULL)
        return;
    printf("chave:%d  cor:%d\n", raiz->chave, raiz->cor);
    travessia(raiz->esq);
    travessia(raiz->dir);
}

tno_lista * insereInicio(tno_lista **raiz, unsigned long k,unsigned long naochave,int bloco, int indice)
{
    if(*raiz == NULL){
        *raiz = (tno_lista *)malloc(sizeof(tno_lista));
        if (*raiz == NULL) return NULL;
        (*raiz)->prox = NULL;
        (*raiz)->naochave = naochave;
        (*raiz)->bloco = bloco;
        (*raiz)->indice = indice;
        (*raiz)->chave = k;
        return *raiz;
    }else
    {
        tno_lista *aux = *raiz;
        *raiz = (tno_lista *)malloc(sizeof(tno_lista));
        if (*raiz == NULL) return NULL;
        (*raiz)->prox = aux;
        (*raiz)->naochave = naochave;
        (*raiz)->bloco = bloco;
        (*raiz)->indice = indice;
        (*raiz)->chave = k;
        return *raiz;
    }
}

void ler_lista(tno_lista *raiz)
{
    while(raiz != NULL)
    {
        printf("--------------------- Colidiu ------------------------------------\n");
        printf("Lista: NaoChave:%lu Chave:%lu Bloco:%d\nIndice:%d\n",raiz->naochave,raiz->chave,raiz->bloco,raiz->indice);
        raiz = raiz->prox;
    }
    return;
}

void buscar_elemento(tNoLLRB *raiz,unsigned long naochave)
{
    if(raiz == NULL){
        printf("Nao existe valor para esse naochave\n");
        return;
    }
    if(raiz->naochave == naochave)
    {
        FILE *arq  = fopen("base.bin","rb+");
        if(arq == NULL)
        {
            printf("Erro ao abrir arquivo!\n");
            return;
        }
        registro vet[4];
        fseek(arq,sizeof(registro)*(raiz->bloco),0);
        fread(&vet,sizeof(registro),4,arq);
        printf("\nChave:%lu\nNaoChave:%lu\nOutros:%s\n",raiz->chave,raiz->naochave,vet[raiz->indice].outros);
        ler_lista(raiz->prox);
    }
    else
        if(naochave > raiz->naochave)
            buscar_elemento(raiz->dir,naochave);
        else
            buscar_elemento(raiz->esq,naochave);
}

/*void removeLLRB(tNoLLRB **raiz, int k){
    removeNo(raiz, k);
    if ((*raiz) != NULL)
        (*raiz)->cor = BLACK;
}

tNoLLRB *removeNo(tNoLLRB **raiz, int k){
    if( *raiz == NULL )
        return NULL;
    if( (*raiz)->chave > k ){
        if ( verificaCor((*raiz)->esq) == BLACK && verificaCor((*raiz)->esq->esq) == BLACK )
            MoveNoEsq(raiz);
        (*raiz)->esq = removeNo((*raiz)->esq, k);
    }
    else{
        if (verificaCor((*raiz)->esq) == RED )
            rotacaoDir(*raiz);
        if ( (*raiz)->chave == k && (*raiz)->dir == NULL ){
            free(*raiz);
            *raiz = NULL;
            return NULL;
        }
        if ( verificaCor((*raiz)->dir) == BLACK && verificaCor((*raiz)->dir->esq) == BLACK )
            MoveNoDir(raiz);
        if ( (*raiz)->chave == k ){
            tNoLLRB *no = buscaMenor((*raiz)->dir);

        }
    }
}

//BALANCEAMENTO
void balancear(tNoLLRB **no){
    if((*no)->dir->cor == RED)
        rotacaoEsq(no);
    if( (*no)->esq != NULL && (*no)->dir->cor == RED && (*no)->esq->esq->cor == RED )
        rotacaoDir(no);
    if ( (*no)->esq->cor == RED && (*no)->dir->cor == RED )
        trocaCor(*no);
}

*/
