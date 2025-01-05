/******************************************************************************
//     filaDinamica.c
// Este programa gerencia filas lineares ligadas (implementacao dinamica).
// As filas gerenciadas podem ter um numero arbitrario de elementos.
// Não usaremos sentinela ou cabeça nesta estrutura.
******************************************************************************/
#include <stdio.h>
#include <malloc.h>
#define ERRO -1
#define true 1
#define false 0
typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;

typedef struct aux {
  REGISTRO reg;
  struct aux* prox;
} ELEMENTO, *PONT;;

typedef struct {
  PONT inicio;
  PONT fim;
  PONT noCabeca;
} FILA;

/* Inicialização da fila ligada (a fila jah esta criada e eh apontada 
pelo endereco em f) */
void inicializarFila(FILA* f){
  f->noCabeca = (PONT)(malloc(sizeof(ELEMENTO)));
  f->inicio = f->noCabeca;
  f->noCabeca->prox = f->noCabeca;
  //f->noCabeca.reg.chave = -1;
  f->fim = f->noCabeca;
  
} /* inicializarFila */

/* Retornar o tamanho da fila (numero de elementos) */
int tamanho(FILA* f) {
  PONT end = f->inicio;
  int tam = 0;
  while (end != NULL){
    tam++;
    end = end->prox;
  }
  return tam;
} /* tamanho */

/* Retornar o tamanho em bytes da fila. Neste caso, isto depende do numero
   de elementos que estao sendo usados.   */
int tamanhoEmBytes(FILA* f) {
  return (tamanho(f)*sizeof(ELEMENTO)) + sizeof(FILA);
} /* tamanhoEmBytes */

/* Destruição da fila 
   libera a memoria de todos os elementos da fila*/
void destruirFila(FILA* f) {
  PONT end = f->inicio;
  while (end != NULL){
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  f->inicio = NULL;
  f->fim = NULL;
} /* destruirFila */


/* retornarPrimeiro - retorna o endereco do primeiro elemento da fila e (caso
   a fila nao esteja vazia) retorna a chave desse elemento na memoria 
   apontada pelo ponteiro ch */
PONT retornarPrimeiro(FILA* f, TIPOCHAVE *ch){
  if (f->inicio != NULL) *ch = f->inicio->reg.chave;
  return f->inicio;
} /* retornarPrimeiro */

/* retornarUltimo - retorna o endereco do ultimo elemento da fila e (caso
   a fila nao esteja vazia) retorna a chave desse elemento na memoria 
   apontada pelo ponteiro ch */
PONT retornarUltimo(FILA* f, TIPOCHAVE* ch){
  if (f->inicio == NULL) return NULL;
  *ch = f->fim->reg.chave;
  return f->fim;
} /* retornarUltimo */


/* Inserção no fim da fila */
bool inserirNaFila(FILA* f,REGISTRO reg) {
  PONT novo = (PONT) malloc(sizeof(ELEMENTO)); //cria o elemento sendo inserido
  novo->reg = reg;//salva o registro na estrutura
  novo->prox = NULL;//como inserido no fim nao há proximo;

  if (f->inicio==f->noCabeca){
     f->inicio = novo; //se a lista é vazia o novo é o principio
     f->noCabeca->prox = novo;/*nó cabeça precisa apontar para o primeiro 
     (para que faça sentido ele ser o cabeça da lista) isso so ocorre com lista vazia*/
  }else{
     f->fim->prox = novo;//nao sendo vazia faz o prox do ultimo atual apontar para o novo.
  }//tipo o ultimo aponta pro novo e o novo agora é ultimo...
  f->fim = novo;//o novo agora é apontado por fim
  return true;
} /* inserir */

/* Excluir  */
bool excluirDaFila(FILA* f, REGISTRO* reg) {
  if (f->inicio==f->noCabeca){//se a lista estiver vazia nao ha exclusao
    return false;                     
  }
  *reg = f->inicio->reg; //copia registro/salva
  PONT apagar = f->inicio; //guarda o que será excluido
  f->inicio = f->inicio->prox; // o inicio passa a ser o proximo
  f->noCabeca->prox = f->inicio;//apos agora o no cabeça aponta para o novo primeiro elemento
  free(apagar);//apaga o elemento
  if (f->inicio == f->noCabeca){//caso so restar o no cabeça apos exclusão  o fim tb é o nócabeça
    f->fim = f->noCabeca;
  }
  return true;
}


/* Exibição da fila sequencial */
void exibirFila(FILA* f){
  PONT end = f->inicio;
  printf("Fila: \" ");
  while (end != NULL){
    printf("%d ", end->reg.chave); // soh lembrando TIPOCHAVE = int
    end = end->prox;
  }
  printf("\"\n");
} /* exibirFila */ 

/* Busca sequencial */
PONT buscaSeq(FILA* f,TIPOCHAVE ch){
  PONT pos = f->inicio;
  while (pos != NULL){
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
} /* buscaSeq */

/* Busca sequencial com sentinela alocado dinamicamente */
PONT buscaSeqSent1(FILA* f,TIPOCHAVE ch){
  if (!f->inicio) return NULL;
  PONT sentinela = malloc(sizeof(ELEMENTO));
  sentinela->reg.chave = ch;
  f->fim->prox = sentinela;
  PONT pos = f->inicio;
  while (pos->reg.chave != ch) pos = pos->prox;
  free(sentinela);
  f->fim->prox = NULL;
  if (pos!=sentinela) return pos;
  return NULL;
} /* buscaSeqSent1 */

/* Busca sequencial com sentinela como variavel local */
PONT buscaSeqSent2(FILA* f,TIPOCHAVE ch){
  if (!f->inicio) return NULL;
  ELEMENTO sentinela;
  sentinela.reg.chave = ch;
  f->fim->prox = &sentinela;
  PONT pos = f->inicio;
  while (pos->reg.chave != ch) pos = pos->prox;
  f->fim->prox = NULL;
  if (pos!=&sentinela) return pos;
  return NULL;
} /* buscaSeqSent1 */