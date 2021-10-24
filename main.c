#include "bib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    clock_t ini, fim;
    tNoLLRB *llrb = NULL;
    int i = 0,n;
    int cont;
    cont = 0;
    unsigned long naochave;
    registro vet[4];
    FILE *arq  = fopen("base.bin","rb+");
    if(arq == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }
    ini = clock();
    while(!feof(arq)){
        if(fread(&vet,sizeof(registro),4,arq) == 4){
            for(n = 0;n<4;n++)
                insereLLRB(&llrb,vet[n].chave,vet[n].naochave,i,n, &cont);
                //printf("%lu\n",vet[n].naochave);
        }
    }
    fclose(arq);
    fim = clock();
    printf("tempo: %lf\n",((double)(fim - ini)/CLOCKS_PER_SEC));
    printf("colisoes: %d\n", cont);
    //travessia(avl);
    //unsigned long nk;
    //unsigned long k;
    printf("Buscar Nao Chave:");
    scanf("%lu",&naochave);
    ini = clock();
    buscar_elemento(llrb,naochave);
    fim = clock();
    /*FILE *a = fopen("colisoes.txt","r+");
    if(arq == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }
   while(!feof(arq)){
        fscanf(a,"%lu\n",&nk);
        //printf("Buscar Nao Chave:");
        //scanf("%lu",&naochave);
        buscar_elemento(avl,nk);
        sleep(2);
    }
    fclose(a);*/
    printf("tempo: %lf\n",((double)(fim - ini)/CLOCKS_PER_SEC));
    return 0;
}
