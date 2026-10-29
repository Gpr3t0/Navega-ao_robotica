#ifndef LISTA_H
#define LISTA_H

#define MAX_LINHA 4096

typedef struct {
    char sigla_tribunal[20];
    char procedimento[100];
    char ramo_justica[50];
    char sigla_grau[20];
    char uf_oj[10];
    char municipio_oj[100];
    char id_ultimo_oj[50];
    char nome[150];
    char mesano_cnm1[20];
    char mesano_sent[20];

    double casos_novos_2026;
    double julgados_2026;
    double prim_sent2026;
    double suspensos_2026;
    double dessobrestados_2026;
    double cumprimento_meta1;

    double distm2_a;
    double julgm2_a;
    double suspm2_a;
    double cumprimento_meta2a;

    double distm2_ant;
    double julgm2_ant;
    double suspm2_ant;
    double desom2_ant;
    double cumprimento_meta2ant;

    double distm4_a;
    double julgm4_a;
    double suspm4_a;
    double cumprimento_meta4a;

    double distm4_b;
    double julgm4_b;
    double suspm4_b;
    double cumprimento_meta4b;
} Registro;

typedef struct No {
    Registro dado;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    int tamanho;
} Lista;

/* TAD Lista */
void inicializarLista(Lista *lista);
int listaVazia(Lista *lista);
void inserirFim(Lista *lista, Registro reg);
void liberarLista(Lista *lista);

/* Auxiliares */
void removerQuebraLinha(char *str);
void converterMaiusculo(char *str);

/* Leitura */
int lerCSV(const char *nomeArquivo, Lista *lista);

/* Funcionalidades */
void concatenarArquivos(void);
void gerarResumoTribunal(Lista *lista, const char *nomeSaida);
void filtrarPorMunicipioTXT(Lista *lista, const char *municipio);

#endif