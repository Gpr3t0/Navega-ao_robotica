#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main(void) {
    Lista lista;
    int opcao;
    char nomeArquivo[200];
    char municipio[100];

    inicializarLista(&lista);

    do {
        printf("\n========================================\n");
        printf("   SISTEMA DE MANIPULACAO DE CSV - C\n");
        printf("========================================\n");
        printf("1 - Carregar arquivo CSV para a lista\n");
        printf("2 - Concatenar varios arquivos CSV\n");
        printf("3 - Gerar resumo por sigla_tribunal\n");
        printf("4 - Filtrar por municipio e gerar CSV\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o caminho do arquivo CSV: ");
                fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
                removerQuebraLinha(nomeArquivo);

                liberarLista(&lista);
                inicializarLista(&lista);

                if (lerCSV(nomeArquivo, &lista)) {
                    printf("Arquivo carregado com sucesso! Total de registros: %d\n", lista.tamanho);
                } else {
                    printf("Falha ao carregar o arquivo.\n");
                }
                break;

            case 2:
                concatenarArquivos();
                break;

            case 3:
                gerarResumoTribunal(&lista, "resumo_tribunais.csv");
                break;

            case 4:
                printf("Digite o nome do municipio: ");
                fgets(municipio, sizeof(municipio), stdin);
                removerQuebraLinha(municipio);

                filtrarPorMunicipioTXT(&lista, municipio);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarLista(&lista);
    return 0;
}