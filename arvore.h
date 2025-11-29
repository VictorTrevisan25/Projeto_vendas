#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    int id;
    char cliente[51];
    char vendedor[51];
    char matricula[5];
    Data data;
    float valor;
} Venda;

typedef struct NoArvore {
    Venda info;
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArv;

typedef struct {
    NoArv *raiz;
} Arv;

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

NoArv *cria_no(Venda v) {
    NoArv *n = malloc(sizeof(NoArv));
    n->info = v;
    n->esq = n->dir = NULL;
    return n;
}

int existe_id(NoArv *pai, int id) {
    if (pai == NULL)
    {
        return 0;
    }
    if (id == pai->info.id)
    {
        return 1;
    }
    if (id < pai->info.id)
    {
        return existe_id(pai->esq, id);
    }
    return existe_id(pai->dir, id);
}

int gera_id_unico(Arv *A) {
    int id;
    do {
        id = 1000 + rand() % 9000;
    } while (existe_id(A->raiz, id));
    return id;
}

void gerar_matricula(char m[5]) {
    int x = rand() % 1000;
    sprintf(m, "V%03d", x);
}

void imprimir_data(Data d) {
    printf("%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

void imprimir_linha_completa(Venda v) {
    printf("%4d | %-15s | %-8s | %-15s | ", v.id, v.vendedor, v.matricula, v.cliente);
    imprimir_data(v.data);
    printf(" | %10.2f\n", v.valor);
}

void imprimir_cabecalho_vendedor() {
    printf("\nID   | %-15s | %-15s | %-10s\n","Cliente", "Data", "Valor(R$)");
    printf("-------------------------------------------------------------\n");
}

void imprimir_linha_vendedor(Venda v) {
    printf("%4d | %-15s | ", v.id, v.cliente);
    imprimir_data(v.data);
    printf(" | %10.2f\n", v.valor);
}


Arv *cria_arvore() {
    Arv *A = malloc(sizeof(Arv));
    A->raiz = NULL;
    return A;
}

int arv_vazia(Arv *A)
{
    if(A->raiz == NULL)
    {
        return 1;
    }
    return 0;
}


Venda ler_venda(Arv *A) {
    Venda v;

    v.id = gera_id_unico(A);
    gerar_matricula(v.matricula);

    printf("ID gerado: %d\n", v.id);
    printf("Matricula gerada: %s\n", v.matricula);

    printf("Nome do vendedor: ");
    limpar_buffer();
    scanf(" %50[^\n]", v.vendedor);

    printf("Nome do cliente: ");
    limpar_buffer();
    scanf(" %50[^\n]", v.cliente);

    printf("Dia: ");
    scanf("%d", &v.data.dia);

    printf("Mes: ");
    scanf("%d", &v.data.mes);

    printf("Ano: ");
    scanf("%d", &v.data.ano);

    printf("Valor da venda: ");
    scanf("%f", &v.valor);

    return v;
}

NoArv *aux_insere(NoArv *pai, Venda v) {

    if (pai == NULL) {
        return cria_no(v);
    }

    if (v.id < pai->info.id) {
        pai->esq = aux_insere(pai->esq, v);
    }
    else {
        pai->dir = aux_insere(pai->dir, v);
    }

    return pai;
}

void insere(Arv *A, Venda v) {
    A->raiz = aux_insere(A->raiz, v);
}

void imprimir_cabecalho_completo() {
    printf("\nID   | %-15s | %-8s | %-15s | %-15s | %-10s\n", "Vendedor", "Matric.", "Cliente", "Data", "Valor(R$)");
    printf("--------------------------------------------------------------------------\n");
}

void listar_crescente(NoArv *pai) {
    if (pai == NULL)
    {
        return;
    }
    listar_crescente(pai->esq);
    imprimir_linha_completa(pai->info);
    listar_crescente(pai->dir);
}

void listar_decrescente(NoArv *pai) {
    if (pai == NULL)
    {
        return;
    }
    listar_decrescente(pai->dir);
    imprimir_linha_completa(pai->info);
    listar_decrescente(pai->esq);
}

void buscar_por_matricula(NoArv *pai, const char *m, int *cab, int *qtd) {


    if (pai == NULL) {
        return;
    }

    buscar_por_matricula(pai->esq, m, cab, qtd);

    if (strcmp(pai->info.matricula, m) == 0) {

        if (*cab == 0) {
            printf("\nVendedor: %s\n", pai->info.vendedor);
            printf("Matricula: %s\n", pai->info.matricula);
            imprimir_cabecalho_vendedor();
            *cab = 1;
        }

        imprimir_linha_vendedor(pai->info);

        *qtd++;
    }

    buscar_por_matricula(pai->dir, m, cab, qtd);
}


void buscar_por_nome(NoArv *pai, const char *nome, int *cab, int *qtd) {
    if (pai == NULL)
    {
        return;
    }

    buscar_por_nome(pai->esq, nome, cab, qtd);

    if (strcmp(pai->info.vendedor, nome) == 0) {
        if (!*cab) {
            printf("\nVendedor: %s\n", pai->info.vendedor);
            printf("Matricula: %s\n", pai->info.matricula);
            imprimir_cabecalho_vendedor();
            *cab = 1;
        }
        imprimir_linha_vendedor(pai->info);
        (*qtd)++;
    }

    buscar_por_nome(pai->dir, nome, cab, qtd);
}


void listar_por_valor(NoArv *pai, float val, int acima, int *qtd) {
    if (pai == NULL)
    {
        return;
    }

    listar_por_valor(pai->esq, val, acima, qtd);

    if ((acima && pai->info.valor >= val) ||
        (!acima && pai->info.valor <= val)) {
        imprimir_linha_completa(pai->info);
        (*qtd)++;
    }

    listar_por_valor(pai->dir, val, acima, qtd);
}


int contar_vendas(NoArv *pai) {
    if (pai == NULL)
    {
        return 0;
    }
    return 1 + contar_vendas(pai->esq) + contar_vendas(pai->dir);
}

float somar_faturamento(NoArv *pai) {
    if (pai == NULL)
    {
        return 0;
    }
    return pai->info.valor + somar_faturamento(pai->esq) + somar_faturamento(pai->dir);
}

NoArv *remover_aux(NoArv *pai, int id) {

    if (pai == NULL) {
        return NULL;
    }

    if (id < pai->info.id) {
        pai->esq = remover_aux(pai->esq, id);
    }

    else if (id > pai->info.id) {
        pai->dir = remover_aux(pai->dir, id);
    }

    else {

        if (pai->esq == NULL && pai->dir == NULL) {
            free(pai);
            return NULL;
        }
        if (pai->esq == NULL) {
            NoArv *tmp = pai->dir;
            free(pai);
            return tmp;
        }
        if (pai->dir == NULL) {
            NoArv *tmp = pai->esq;
            free(pai);
            return tmp;
        }

        NoArv *maior = pai->esq;
        while (maior->dir != NULL) {
            maior = maior->dir;
        }
        pai->info = maior->info;

        pai->esq = remover_aux(pai->esq, maior->info.id);
    }

    return pai;
}


Arv *remover_venda(Arv *A, int id) {
    A->raiz = remover_aux(A->raiz, id);
    return A;
}

void liberar_nos(NoArv *pai) {
    if (pai == NULL)
    {
        return;
    }
    liberar_nos(pai->esq);
    liberar_nos(pai->dir);
    free(pai);
}

void liberar_arvore(Arv *A) {
    liberar_nos(A->raiz);
    free(A);
}
