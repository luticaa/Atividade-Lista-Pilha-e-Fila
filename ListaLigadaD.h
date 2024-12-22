#ifndef LISTALIGADAD_H
#define LISTALIGADAD_H

#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct tempRegistro {
    REGISTRO reg;
    struct tempRegistro* prox,*anterior;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
} LISTA;

void inicializarLista(LISTA* l);
void exibirLista(LISTA* l);
int tamanho(LISTA* l);
int tamanhoEmBytes(LISTA* l);
PONT buscaSequencial(LISTA* l, TIPOCHAVE ch);
PONT buscaSeqOrd(LISTA* l, TIPOCHAVE ch);
PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant);
bool excluirElemLista(LISTA* l, TIPOCHAVE ch);
void reinicializarLista(LISTA* l);
bool inserirElemListaOrd(LISTA* l, REGISTRO reg);
PONT retornarPrimeiro(LISTA* l, TIPOCHAVE *ch);
PONT retornarUltimo(LISTA* l, TIPOCHAVE *ch);

#endif // LISTALIGADAD_H
