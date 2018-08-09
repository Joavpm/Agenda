struct agenda{
    char nome[50];
    char endereco[50];
};

typedef struct elemento* Lista;

Lista* cria_lista();
void liberaAgenda(Lista* li);
int consultaAgendaEndereco(Lista* li, char* endereco);
int insereAgenda(Lista* li, struct agenda ag, char* nome);
int removeAgenda(Lista* li, char* nome);
int tamanhoAgenda(Lista* li);
void imprimeAgenda(Lista* li);
