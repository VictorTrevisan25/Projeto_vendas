#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore.h"   // biblioteca única

int main() {
    Arv *arvore = cria_arvore();
    int opcao;
    srand((unsigned) time(NULL));

    do {
        printf("\n=========================================\n");
        printf("  SISTEMA DE VENDAS - ABB\n");
        printf("=========================================\n");
        printf("1 - Inserir nova venda\n");
        printf("2 - Listar todas as vendas\n");
        printf("3 - Buscar vendas por vendedor\n");
        printf("4 - Listar vendas por valor\n");
        printf("5 - Estatisticas\n");
        printf("6 - Remover venda por ID\n");
        printf("7 - Finalizar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: {
            Venda v = ler_venda(arvore);
            insere(arvore, v);
            printf("\nVenda inserida!\n");
            system("pause");
            system("cls");
            break;
        }

        case 2: {
            if (arvore->raiz == NULL) {
                printf("\nNenhuma venda cadastrada.\n");
            } else {
                int tipo;
                printf("\n1 - Crescente\n2 - Decrescente\nEscolha: ");
                scanf("%d", &tipo);

                imprimir_cabecalho_completo();
                if (tipo == 1)
                    listar_crescente(arvore->raiz);
                else
                    listar_decrescente(arvore->raiz);
            }
            system("pause");
            system("cls");
            break;
        }

        case 3: {
            int opc;
            printf("\n1 - Buscar por matrícula\n2 - Buscar por nome\nEscolha: ");
            scanf("%d", &opc);

            int cab = 0, qtd = 0;

            if (opc == 1) {
                char mat[5];
                printf("Matricula: ");
                limpar_buffer();
                scanf(" %4[^\n]", mat);
                buscar_por_matricula(arvore->raiz, mat, &cab, &qtd);
            } else {
                char nome[51];
                printf("Nome do vendedor: ");
                limpar_buffer();
                scanf(" %50[^\n]", nome);
                buscar_por_nome(arvore->raiz, nome, &cab, &qtd);
            }

            if (qtd == 0)
                printf("\nNenhuma venda encontrada.\n");

            system("pause");
            system("cls");
            break;
        }

        case 4: {
            float valor;
            int modo;
            printf("\nValor: ");
            scanf("%f", &valor);
            printf("\n1 - Acima/igual\n2 - Abaixo/igual\nEscolha: ");
            scanf("%d", &modo);

            int qtd = 0;
            imprimir_cabecalho_completo();
            listar_por_valor(arvore->raiz, valor, modo == 1, &qtd);

            if (qtd == 0)
                printf("\nNenhuma venda encontrada.\n");

            system("pause");
            system("cls");
            break;
        }

        case 5: {
            int total = contar_vendas(arvore->raiz);
            float fat = somar_faturamento(arvore->raiz);
            float media = total == 0 ? 0 : fat / total;

            printf("\nTotal de vendas: %d\n", total);
            printf("Faturamento: R$ %.2f\n", fat);
            printf("Ticket médio: R$ %.2f\n", media);

            system("pause");
            system("cls");
            break;
        }

        case 6: {
            int id;
            printf("ID da venda: ");
            scanf("%d", &id);
            arvore = remover_venda(arvore, id);
            printf("\nRemovido (se existia).\n");
            system("pause");
            system("cls");
            break;
        }

        case 7:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
            system("pause");
            system("cls");
        }

    } while (opcao != 7);

    liberar_arvore(arvore);
    return 0;
}
