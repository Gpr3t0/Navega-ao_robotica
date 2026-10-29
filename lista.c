#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "lista.h"

/* =========================
   TAD LISTA
   ========================= */

void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

int listaVazia(Lista *lista) {
    return lista->inicio == NULL;
}

void inserirFim(Lista *lista, Registro reg) {
    No *novo = (No *) malloc(sizeof(No));
    No *aux;

    if (novo == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }

    novo->dado = reg;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        aux = lista->inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    lista->tamanho++;
}

void liberarLista(Lista *lista) {
    No *aux = lista->inicio;
    No *temp;

    while (aux != NULL) {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    lista->inicio = NULL;
    lista->tamanho = 0;
}

/* =========================
   FUNÇÕES AUXILIARES
   ========================= */

void removerQuebraLinha(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

void converterMaiusculo(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = (char) toupper((unsigned char) str[i]);
    }
}

double strParaDouble(const char *str) {
    char copia[50];
    int i;

    if (str == NULL || strlen(str) == 0) {
        return 0.0;
    }

    strncpy(copia, str, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';

    for (i = 0; copia[i] != '\0'; i++) {
        if (copia[i] == ',') {
            copia[i] = '.';
        }
    }

    return atof(copia);
}

/* =========================
   LEITURA DE CSV
   ========================= */

int lerCSV(const char *nomeArquivo, Lista *lista) {
    FILE *arq;
    char linha[MAX_LINHA];
    char *token;
    int primeiraLinha = 1;

    arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo: %s\n", nomeArquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        Registro reg;

        if (primeiraLinha) {
            primeiraLinha = 0;
            continue;
        }

        removerQuebraLinha(linha);

        if (strlen(linha) == 0) {
            continue;
        }

        memset(&reg, 0, sizeof(Registro));

        token = strtok(linha, ";");
        if (token != NULL) snprintf(reg.sigla_tribunal, sizeof(reg.sigla_tribunal), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.procedimento, sizeof(reg.procedimento), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.ramo_justica, sizeof(reg.ramo_justica), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.sigla_grau, sizeof(reg.sigla_grau), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.uf_oj, sizeof(reg.uf_oj), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.municipio_oj, sizeof(reg.municipio_oj), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.id_ultimo_oj, sizeof(reg.id_ultimo_oj), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.nome, sizeof(reg.nome), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.mesano_cnm1, sizeof(reg.mesano_cnm1), "%s", token);

        token = strtok(NULL, ";");
        if (token != NULL) snprintf(reg.mesano_sent, sizeof(reg.mesano_sent), "%s", token);

        token = strtok(NULL, ";");
        reg.casos_novos_2026 = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.julgados_2026 = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.prim_sent2026 = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.suspensos_2026 = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.dessobrestados_2026 = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.cumprimento_meta1 = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.distm2_a = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.julgm2_a = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.suspm2_a = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.cumprimento_meta2a = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.distm2_ant = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.julgm2_ant = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.suspm2_ant = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.desom2_ant = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.cumprimento_meta2ant = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.distm4_a = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.julgm4_a = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.suspm4_a = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.cumprimento_meta4a = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.distm4_b = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.julgm4_b = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.suspm4_b = strParaDouble(token);

        token = strtok(NULL, ";");
        reg.cumprimento_meta4b = strParaDouble(token);

        inserirFim(lista, reg);
    }

    fclose(arq);
    return 1;
}

/* =========================
   ITEM 1 - CONCATENAR
   ========================= */

void concatenarArquivos(void) {
    FILE *saida;
    FILE *entrada;
    char pasta[300];
    char padrao[350];
    char caminhoArquivo[400];
    char linha[MAX_LINHA];
    int cabecalhoEscrito = 0;
    int totalArquivos = 0;
    int len;
    WIN32_FIND_DATA fd;
    HANDLE hFind;

    saida = fopen("concatenado.csv", "w");
    if (saida == NULL) {
        printf("Erro ao criar concatenado.csv\n");
        return;
    }

    printf("Digite o caminho da pasta com os arquivos CSV: ");
    fgets(pasta, sizeof(pasta), stdin);
    removerQuebraLinha(pasta);

    /* Remove barra final, se houver */
    len = (int)strlen(pasta);
    if (len > 0 && (pasta[len - 1] == '\\' || pasta[len - 1] == '/')) {
        pasta[len - 1] = '\0';
    }

    sprintf(padrao, "%s\\*.csv", pasta);

    hFind = FindFirstFile(padrao, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Nenhum arquivo CSV encontrado em: %s\n", pasta);
        fclose(saida);
        return;
    }

    do {
        int primeiraLinha = 1;

        sprintf(caminhoArquivo, "%s\\%s", pasta, fd.cFileName);

        entrada = fopen(caminhoArquivo, "r");
        if (entrada == NULL) {
            printf("Erro ao abrir: %s\n", caminhoArquivo);
            continue;
        }

        printf("Processando: %s\n", fd.cFileName);
        totalArquivos++;

        while (fgets(linha, sizeof(linha), entrada) != NULL) {
            if (primeiraLinha) {
                if (!cabecalhoEscrito) {
                    fputs(linha, saida);
                    cabecalhoEscrito = 1;
                }
                primeiraLinha = 0;
            } else {
                fputs(linha, saida);
            }
        }

        fclose(entrada);

    } while (FindNextFile(hFind, &fd));

    FindClose(hFind);
    fclose(saida);
    printf("\n%d arquivo(s) processado(s).\n", totalArquivos);
    printf("Arquivo concatenado gerado com sucesso: concatenado.csv\n");
}

/* =========================
   ITEM 2 - RESUMO
   ========================= */

typedef struct {
    char sigla_tribunal[20];

    double soma_julgados_2026;
    double soma_casos_novos_2026;
    double soma_dessobrestados_2026;
    double soma_suspensos_2026;

    double soma_distm2_a;
    double soma_julgm2_a;
    double soma_suspm2_a;

    double soma_distm2_ant;
    double soma_julgm2_ant;
    double soma_suspm2_ant;
    double soma_desom2_ant;

    double soma_distm4_a;
    double soma_julgm4_a;
    double soma_suspm4_a;

    double soma_distm4_b;
    double soma_julgm4_b;
    double soma_suspm4_b;
} Resumo;

void gerarResumoTribunal(Lista *lista, const char *nomeSaida) {
    Resumo resumos[500];
    int qtdResumos = 0;
    No *aux;
    FILE *saida;
    int i;

    if (listaVazia(lista)) {
        printf("A lista esta vazia.\n");
        return;
    }

    memset(resumos, 0, sizeof(resumos));

    aux = lista->inicio;

    while (aux != NULL) {
        int indice = -1;

        for (i = 0; i < qtdResumos; i++) {
            if (strcmp(resumos[i].sigla_tribunal, aux->dado.sigla_tribunal) == 0) {
                indice = i;
                break;
            }
        }

        if (indice == -1) {
            indice = qtdResumos;
            strcpy(resumos[qtdResumos].sigla_tribunal, aux->dado.sigla_tribunal);
            qtdResumos++;
        }

        resumos[indice].soma_julgados_2026 += aux->dado.julgados_2026;
        resumos[indice].soma_casos_novos_2026 += aux->dado.casos_novos_2026;
        resumos[indice].soma_dessobrestados_2026 += aux->dado.dessobrestados_2026;
        resumos[indice].soma_suspensos_2026 += aux->dado.suspensos_2026;

        resumos[indice].soma_distm2_a += aux->dado.distm2_a;
        resumos[indice].soma_julgm2_a += aux->dado.julgm2_a;
        resumos[indice].soma_suspm2_a += aux->dado.suspm2_a;

        resumos[indice].soma_distm2_ant += aux->dado.distm2_ant;
        resumos[indice].soma_julgm2_ant += aux->dado.julgm2_ant;
        resumos[indice].soma_suspm2_ant += aux->dado.suspm2_ant;
        resumos[indice].soma_desom2_ant += aux->dado.desom2_ant;

        resumos[indice].soma_distm4_a += aux->dado.distm4_a;
        resumos[indice].soma_julgm4_a += aux->dado.julgm4_a;
        resumos[indice].soma_suspm4_a += aux->dado.suspm4_a;

        resumos[indice].soma_distm4_b += aux->dado.distm4_b;
        resumos[indice].soma_julgm4_b += aux->dado.julgm4_b;
        resumos[indice].soma_suspm4_b += aux->dado.suspm4_b;

        aux = aux->prox;
    }

    saida = fopen(nomeSaida, "w");
    if (saida == NULL) {
        printf("Erro ao criar %s\n", nomeSaida);
        return;
    }

    fprintf(saida, "sigla_tribunal;total_julgados_2026;Meta1;Meta2A;Meta2Ant;Meta4A;Meta4B\n");

    for (i = 0; i < qtdResumos; i++) {
        double meta1 = 0.0;
        double meta2A = 0.0;
        double meta2Ant = 0.0;
        double meta4A = 0.0;
        double meta4B = 0.0;

        double denMeta1 = resumos[i].soma_casos_novos_2026 +
                          resumos[i].soma_dessobrestados_2026 -
                          resumos[i].soma_suspensos_2026;

        double denMeta2A = resumos[i].soma_distm2_a -
                           resumos[i].soma_suspm2_a;

        double denMeta2Ant = resumos[i].soma_distm2_ant -
                             resumos[i].soma_suspm2_ant -
                             resumos[i].soma_desom2_ant;

        double denMeta4A = resumos[i].soma_distm4_a -
                           resumos[i].soma_suspm4_a;

        double denMeta4B = resumos[i].soma_distm4_b -
                           resumos[i].soma_suspm4_b;

        if (denMeta1 != 0) {
            meta1 = (resumos[i].soma_julgados_2026 / denMeta1) * 100.0;
        }

        if (denMeta2A != 0) {
            meta2A = (resumos[i].soma_julgm2_a / denMeta2A) * (1000.0 / 7.0);
        }

        if (denMeta2Ant != 0) {
            meta2Ant = (resumos[i].soma_julgm2_ant / denMeta2Ant) * 100.0;
        }

        if (denMeta4A != 0) {
            meta4A = (resumos[i].soma_julgm4_a / denMeta4A) * 100.0;
        }

        if (denMeta4B != 0) {
            meta4B = (resumos[i].soma_julgm4_b / denMeta4B) * 100.0;
        }

        fprintf(saida, "%s;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n",
                resumos[i].sigla_tribunal,
                resumos[i].soma_julgados_2026,
                meta1,
                meta2A,
                meta2Ant,
                meta4A,
                meta4B);
    }

    fclose(saida);
    printf("Resumo gerado com sucesso em %s\n", nomeSaida);
}

/* =========================
   ITEM 3 - FILTRO POR MUNICIPIO
   ========================= */

void filtrarPorMunicipioTXT(Lista *lista, const char *municipio) {
    FILE *saida;
    No *aux;
    char municipioBusca[100];
    char municipioRegistro[100];
    char nomeSaida[120];
    int encontrou = 0;

    if (listaVazia(lista)) {
        printf("A lista esta vazia.\n");
        return;
    }

    strcpy(municipioBusca, municipio);
    converterMaiusculo(municipioBusca);

    sprintf(nomeSaida, "%s.csv", municipioBusca);

    saida = fopen(nomeSaida, "w");
    if (saida == NULL) {
        printf("Erro ao criar arquivo %s\n", nomeSaida);
        return;
    }

    fprintf(saida, "sigla_tribunal;procedimento;ramo_justica;sigla_grau;uf_oj;municipio_oj;id_ultimo_oj;nome;mesano_cnm1;mesano_sent;casos_novos_2026;julgados_2026;prim_sent2026;suspensos_2026;dessobrestados_2026;cumprimento_meta1;distm2_a;julgm2_a;suspm2_a;cumprimento_meta2a;distm2_ant;julgm2_ant;suspm2_ant;desom2_ant;cumprimento_meta2ant;distm4_a;julgm4_a;suspm4_a;cumprimento_meta4a;distm4_b;julgm4_b;suspm4_b;cumprimento_meta4b\n");

    aux = lista->inicio;

    while (aux != NULL) {
        strcpy(municipioRegistro, aux->dado.municipio_oj);
        converterMaiusculo(municipioRegistro);

        if (strcmp(municipioRegistro, municipioBusca) == 0) {
            encontrou = 1;

            fprintf(saida,
                    "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n",
                    aux->dado.sigla_tribunal,
                    aux->dado.procedimento,
                    aux->dado.ramo_justica,
                    aux->dado.sigla_grau,
                    aux->dado.uf_oj,
                    aux->dado.municipio_oj,
                    aux->dado.id_ultimo_oj,
                    aux->dado.nome,
                    aux->dado.mesano_cnm1,
                    aux->dado.mesano_sent,
                    aux->dado.casos_novos_2026,
                    aux->dado.julgados_2026,
                    aux->dado.prim_sent2026,
                    aux->dado.suspensos_2026,
                    aux->dado.dessobrestados_2026,
                    aux->dado.cumprimento_meta1,
                    aux->dado.distm2_a,
                    aux->dado.julgm2_a,
                    aux->dado.suspm2_a,
                    aux->dado.cumprimento_meta2a,
                    aux->dado.distm2_ant,
                    aux->dado.julgm2_ant,
                    aux->dado.suspm2_ant,
                    aux->dado.desom2_ant,
                    aux->dado.cumprimento_meta2ant,
                    aux->dado.distm4_a,
                    aux->dado.julgm4_a,
                    aux->dado.suspm4_a,
                    aux->dado.cumprimento_meta4a,
                    aux->dado.distm4_b,
                    aux->dado.julgm4_b,
                    aux->dado.suspm4_b,
                    aux->dado.cumprimento_meta4b);
        }

        aux = aux->prox;
    }

    fclose(saida);

    if (encontrou) {
        printf("Arquivo CSV gerado com sucesso: %s\n", nomeSaida);
    } else {
        printf("Nenhum registro encontrado para %s\n", municipioBusca);
        printf("Arquivo criado apenas com cabecalho: %s\n", nomeSaida);
    }
}