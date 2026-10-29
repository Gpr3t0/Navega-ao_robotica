# TP01 - Manipulando arquivos

Trabalho prático de Estrutura de Dados (UCB, 2026/1). O programa lê arquivos CSV da Justiça Eleitoral, guarda tudo numa lista encadeada e oferece três operações: concatenar todos os arquivos, gerar um resumo por tribunal com cálculo das metas, e filtrar registros por município.

Feito em C puro, compilado no Windows com MinGW.

---

## Como rodar

```bash
gcc -o trabalho.exe main.c lista.c -Wall
./trabalho.exe
```

---

## O que cada opção faz

**Opção 1 — Carregar CSV**
Lê um arquivo e popula a lista. Precisa fazer isso antes de usar as opções 3 e 4.

**Opção 2 — Concatenar**
Você informa o caminho de uma pasta. O programa pega todos os `.csv` de lá e gera um `concatenado.csv` com cabeçalho único. Aponta para a pasta `Base de Dados/Base de Dados`, não pra pasta do código.

**Opção 3 — Resumo por tribunal**
Agrupa os dados por `sigla_tribunal` e calcula as metas 1, 2A, 2Ant, 4A e 4B. Resultado vai pro `resumo_tribunais.csv`. As fórmulas seguem o enunciado à risca — cada denominador subtrai os suspensos/dessobrestados, não soma.

**Opção 4 — Filtrar por município**
Digite o nome do município (maiúsculo ou não, tanto faz). O programa gera um `MUNICIPIO.csv` com todas as linhas correspondentes.

---

## Estrutura

Três arquivos, como pedido:

- `lista.h` — define a struct `Registro`, o TAD Lista e os protótipos
- `lista.c` — implementa tudo: o TAD, a leitura do CSV e as três funções principais
- `main.c` — só o menu

---

## Testando

Para testar o resumo com dados de todos os tribunais, use a opção 2 primeiro pra concatenar tudo, depois carregue o `concatenado.csv` e rode a opção 3.

---

## Integrantes

- Arthur Tavares Silva
- Higor Samuel Ferreira Silva
- Igor Vendramini Perini
- João Gabriel da Cruz Viana
- João Lucas Claver de Oliveira
