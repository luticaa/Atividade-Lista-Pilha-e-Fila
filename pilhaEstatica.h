#ifndef PILHA_ESTATICA_H
#define PILHA_ESTATICA_H

#include <stdbool.h>

#define MAX 50
typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    int topo;
    REGISTRO A[MAX];
} PILHA;

void inicializarPilha(PILHA* p);
int tamanhoPilha(PILHA* p);
void exibirPilha(PILHA* p);
int tamanhoEmBytesPilha(PILHA* p);
int buscaTopoDaPilha(PILHA* p);
void reinicializarPilha(PILHA* p);
bool inserirElementoPilha(PILHA* p, REGISTRO reg);
bool excluirElementoPilha(PILHA* p, REGISTRO* reg);
int retornarPrimeiroPilha(PILHA* p, TIPOCHAVE* ch);
REGISTRO* excluirElementoPilha2(PILHA* p);
int buscaSequencial(PILHA* p, TIPOCHAVE ch);

#endif
    