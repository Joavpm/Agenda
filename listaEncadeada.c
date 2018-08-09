#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "listaEncadeada.h" //inclui os Protótipos

//Definição do tipo lista
struct elemento{
    struct agenda dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* criaAgenda(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void liberaAgenda(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consultaAgendaEndereco(Lista* li, char* endereco){
    if(li == NULL || endereco == NULL)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && endereco != no->dados.endereco){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        return 1;
    }
}

int insereAgenda(Lista* li, struct agenda ag,char* nome){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = ag;
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        while(atual != NULL && strcmp(no->dados.nome,nome) != 0){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int removeAgenda(Lista* li,char* nome){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *ant, *no = *li;
    while(no != NULL && strcmp(no->dados.nome,nome) != 0){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanhoAgenda(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

void imprimeAgenda(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("Nome: %d\n",no->dados.nome);
        printf("Endereco: %s\n",no->dados.endereco);
        no = no->prox;
    }
}

void menu(){
    int op;
    char nome[50];
    printf("Digite:\n0-Sair\n1-Criar uma agenda\n2-Alterar uma agenda");
    scanf("%d",&op);

    while(op !=0){
        switch(op){
            case 1:
                printf("Nome da agenda(sem espacos): ");
                scanf("%s",nome);
                fflush(stdin);
                criaAgenda(nome);
            break;
            case 2:
                printf("Qual agenda deseja consultar/alterar? ");
                scanf("%s",nome);
                fflush(stdin);
                Consulta(nome);

        }
    }
}

void criaAgenda_arq(char nome[]) {
    FILE *arq;
    strcpy(nome,".txt");

    arq = fopen(nome,"w");
    if(arq==NULL){
        printf("ERRO");
        exit(1);
    }

    fclose(arq);
}

void Consulta(char nome[]) {
    Lista* li;
    char nomeAgenda[30];
    char endereco[30];
    struct agenda ag;

     FILE *arq;
    strcpy(nome,".txt");

    arq = fopen(nome,"w");
    if(arq==NULL){
        printf("ERRO");
        exit(1);
    }

    li = criaAgenda(li);    

    while(fread(&ag,sizeof(agenda),1,arq)) {
        insereAgenda(li,ag,nomeAgenda);
    }
    printf("Qual endereco deseja consultar? ");
    scanf("%s",endereco);
    int consulta = consultaAgendaEndereco(li, char* endereco);

    consulta == 1 ? printf("Endereco esta na lista"); : printf("Nao esta na lista");
}
