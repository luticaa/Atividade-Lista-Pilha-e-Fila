#include "listaLigadaD.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarLista(LISTA* l) {
  l->inicio = NULL;
}

void exibirLista(LISTA* l) {
  PONT end = l->inicio;
  printf("Lista: \" ");
  while (end != NULL) {
    printf("%d ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

int tamanho(LISTA* l) {
  PONT end = l->inicio;
  int tam = 0;
  while (end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

int tamanhoEmBytes(LISTA* l) {
  return (tamanho(l) * sizeof(ELEMENTO)) + sizeof(LISTA);
}

PONT buscaSequencial(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->inicio;
  while (pos != NULL) {
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
}

PONT buscaSeqOrd(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->inicio;
  while (pos != NULL && pos->reg.chave < ch) pos = pos->prox;
  if (pos != NULL && pos->reg.chave == ch) return pos;
  return NULL;
}

PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant) {
  *ant = NULL;
  PONT atual = l->inicio;
  while (atual != NULL && atual->reg.chave < ch) {
    *ant = atual;
    atual = atual->prox;
  }
  if (atual != NULL && atual->reg.chave == ch) return atual;
  return NULL;
}

bool excluirElemLista(LISTA* l, TIPOCHAVE ch) {
  PONT ant, i;
  i = buscaSeqExc(l, ch, &ant);
  if (i == NULL) return false;//se nao encontrar o elemento buscado retorne false;
  if (ant == NULL){
    l->inicio = i->prox;
  if (l->inicio != NULL) 
  // Atualiza o anterior do novo início, se nao for null (no caso da lista vazia)
    l->inicio->anterior = NULL; //elemento inicial nao tem anterior;
  } 
  /*ant so sera null se a lista for vazia ou se a chave do elemento existente
   for maior que ch, neste caso inserção ocorre na primeira posição*/
  else {ant->prox = i->prox;
    if (i->prox != NULL){ 
      //Atualiza o anterior do próximo, se nao for null se nao for o ultimo
      i->prox->anterior = ant;
      }
  //se nao significa que está apos um outro elemento, entao nao mexemos no inicial.
  }
  free(i);
  return true;
}

void reinicializarLista(LISTA* l) {
  PONT end = l->inicio;
  while (end != NULL) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->inicio = NULL;
}

bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
  TIPOCHAVE ch = reg.chave;
  PONT ant, i;
  i = buscaSeqExc(l, ch, &ant);
  /*I SERA = o elemento ATUAL NO CASO DE SER IGUAL A CHAVE E null para os demais 
  casos (lista vazia e com elementos que possuam chaves diferentes da buscada) */

  if (i != NULL) return false;
  //entende que o elemento já existe retorna falso nao é possivel duplicar
  i = (PONT)malloc(sizeof(ELEMENTO));
  if (i == NULL) return false; //falha na alocação dinamica
//QUANDO ANT = NULL OU LISTA VAZIA OU ELEMENTO NA LISTA TEM CHAVE MAIOR QUE CH
  i->reg = reg;//copia registro na nova posição
  //nao achou i = ponteiro para atual posicação de inserção
  if (ant == NULL) {
//isso aqui é o mesmo que lista vazia nao tem anterior OU REG CHAVE É MAIOR QUE CH
//A INSERÇÃO OCORRENDO NA PRIMEIRA POSIÇÃO NOTE QUE I ASSUME POSICÃO INICIAL
    i->prox = l->inicio; //o novo elemento agora é o primeiro
    i->anterior = NULL;//lista nao circular primeiro elemento nao tem anterior
    l->inicio = i;//novo elemento se torna inicio da lista

    if(i->prox != NULL)//checagem pra ver se tem mais elementos na lista;
    //aqui atualizamos o anterior do elemento que foi deslocado pra frente
      i->prox->anterior = i;
    
  } else {
    /*AQUI existem elemento/s com ch menor que o elemento a inserir a esquerda 
    então inserção ocorre entre dois elementos ou na ultima posição*/
    i->prox = ant->prox;//elemento a ser inserido irá apontar para o proximo da posição
    i->anterior = ant;//a nova posição aponta para a anteior 
    if (ant->prox != NULL)
      ant->prox->anterior = i; //a posição pos inserção passa apontar para o novo elemento
    ant->prox = i;//a posição vigente aponta para a nova 
  }
  return true;
}

PONT retornarPrimeiro(LISTA* l, TIPOCHAVE *ch) {
  if (l->inicio != NULL) *ch = l->inicio->reg.chave;
  return l->inicio;
}

PONT retornarUltimo(LISTA* l, TIPOCHAVE *ch) {
  PONT ultimo = l->inicio;
  if (l->inicio == NULL) return NULL;
  while (ultimo->prox != NULL) ultimo = ultimo->prox;
  *ch = ultimo->reg.chave;
  return ultimo;
}
