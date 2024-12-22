#include "pilhaEstatica.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarPilha(PILHA* p) {
    p->topo = -1;
}

int tamanhoPilha(PILHA* p) {
    return p->topo + 1;
}

void exibirPilha(PILHA* p) {
    printf("Pilha: \" ");
    for (int i = p->topo; i >= 0; i--) {
        printf("%i ", p->A[i].chave);
    }
    printf("\"\n");
}
void exibirPilhaInvertida(PILHA* p) {
printf("Pilha (da base para o topo): \" ");
/* COMPLETE A FUNCAO */
for (int i = 0; i <= p->topo; i++) {
        printf("%i ", p->A[i].chave);
    }
printf("\"\n");
}

int tamanhoEmBytesPilha(PILHA* p) {
    return sizeof(PILHA);
}

int buscaTopoDaPilha(PILHA* p) {
    return p->topo;
}

void reinicializarPilha(PILHA* p) {
    p->topo = -1;
}

bool inserirElementoPilha(PILHA* p, REGISTRO reg) {
    if (p->topo + 1 >= MAX) return false;
    p->A[++p->topo] = reg;
    return true;
}

bool excluirElementoPilha(PILHA* p, REGISTRO* reg) {
    if (p->topo == -1) return false;
    *reg = p->A[p->topo--];
    return true;
}

int retornarPrimeiroPilha(PILHA* p, TIPOCHAVE* ch) {
    if (p->topo == -1) return -1;
    *ch = p->A[p->topo].chave;
    return p->topo;
}

REGISTRO* excluirElementoPilha2(PILHA* p) {
    if (p->topo == -1) return NULL;
    REGISTRO* res = (REGISTRO*)malloc(sizeof(REGISTRO));
    *res = p->A[p->topo--];
    return res;
}

int buscaSequencial(PILHA* p, TIPOCHAVE ch) {
    for (int i = p->topo; i >= 0; i--) {
        if (p->A[i].chave == ch) return i;
    }
    return -1;
}
