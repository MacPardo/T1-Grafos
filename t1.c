#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG

typedef struct stack {
  int values[100];
  int size;
} stack;

void push(stack* s, int n) {
  s->values[s->size++] = n;
}

int* copy(int* n, int size) {
  int* r = (int*)malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    r[i] = n[i];
  }
  return r;
}

stack caminho_completo_adj(int vertice, int** grafo, int* ok, int size) {
  stack trail, fail;
  trail.size = 0;
  fail.size = -1;

  if (ok[vertice]) {
    return fail;
  }
  ok[vertice] = 1;

  int completo = 1;
  for (int i = 0; i < size; i++) {
    if (!ok[i]) completo = 0;
  }
  if (completo) {
    trail.size = 0;
    push(&trail, vertice);
    return trail;
  }

  for (int i = 0; i < size; i++) {
    if (grafo[vertice][i]) {
      trail = caminho_completo_adj(i, grafo, copy(ok, size), size);
      if (trail.size != -1) {
        push(&trail, vertice);
        return trail;
      }
    }
  }

  return fail;
}

stack caminho_completo_inc(int vertice, int** grafo, int* ok, int size, int arestas) {
  stack trail, fail;
  int vertice_destino;
  trail.size = 0;
  fail.size = -1;

  if (ok[vertice]) {
    return fail;
  }
  ok[vertice] = 1;

  int completo = 1;
  for (int i = 0; i < size; i++) {
    if (!ok[i]) completo = 0;
  }
  if (completo) {
    trail.size = 0;
    push(&trail, vertice);
    return trail;
  }

  for (int i = 0; i < arestas; i++) { //testa para todas as arestas
    if (grafo[vertice][i] > 0) { //se o vertice eh o ponto de partida

      for (int j = 0; j < size; j++) { //encontra o vertice de destino desta aresta
        if (grafo[j][i] < 0) {
          vertice_destino = j;
          break;
        }
      }

      trail = caminho_completo_adj(i, grafo, copy(ok, size), size); //chama a funcao no vertice de destino
      if (trail.size != -1) {
        push(&trail, vertice);
        return trail;
      }
    }
  }

  return fail;
}

stack caminho_adj(int vertice, int destino, int** grafo, int* ok, int size) {
  stack trail, fail;
  trail.size = 0;
  fail.size = -1;

  if (ok[vertice]) {
    return fail;
  }
  ok[vertice] = 1;

  if (vertice == destino) {
    push(&trail, vertice);
    return trail;
  }

  for (int i = 0; i < size; i++) {
    if (grafo[vertice][i]) {
      trail = caminho_adj(i, destino, grafo, copy(ok, size), size);
      if (trail.size != -1) {
        push(&trail, vertice);
        return trail;
      }
    }
  }

  return fail;
}

stack caminho_inc(int vertice, int destino, int** grafo, int* ok, int size, int arestas) {
  stack trail, fail, smallest_trail;
  int vertice_destino;
  trail.size = 0;
  fail.size = -1;

  if (ok[vertice]) {
    return fail;
  }
  ok[vertice] = 1;

  if (vertice == destino) {
    push(&trail, vertice);
    return trail;
  }

  for (int i = 0; i < arestas; i++) { //testa para todas as arestas
    if (grafo[vertice][i] > 0) { //se o vertice eh o ponto de partida

      for (int j = 0; j < size; j++) { //encontra o vertice de destino desta aresta
        if (grafo[j][i] < 0) {
          vertice_destino = j;
          break;
        }
      }

      trail = caminho_adj(i, destino, grafo, copy(ok, size), size); //chama a funcao no vertice de destino
      if (trail.size != -1 && trail.size < smallest_trail.size) {
        smallest_trail = trail;
      }
    }
  }

  if (smallest_trail.size != -1) {
    push(&smallest_trail, vertice);
    return smallest_trail;
  }

  return fail;
}

int main(void) {

  //CAMINHO COMPLETO COM MATRIZ DE ADJACENCIA
  int size = 5;
  int** grafo1adj = (int**)malloc(sizeof(int*) * size);
  for (int i = 0; i < size; i++) {
    grafo1adj[i] = (int*)malloc(sizeof(int) * size);
    memset(grafo1adj[i], 0, sizeof(int) * size);
  }

  grafo1adj[0][1] = 30;
  grafo1adj[0][4] = 20;
  grafo1adj[1][3] = 50;
  grafo1adj[2][0] = 15;
  grafo1adj[2][1] = 10;
  grafo1adj[2][3] = 5;
  grafo1adj[4][2] = 10;
  grafo1adj[4][3] = 30;

  printf("Grafo 1 representado por matriz de adjacencia:\n");

  printf("X\t");
  for (int i = 0; i < size; i++) {
    printf("%d\t", i + 1);
  }
  printf("\n");
  for (int i = 0; i < size; i++) {
    printf("%d\t", i + 1);
    for (int j = 0; j < size; j++) {
      printf("%d\t", grafo1adj[i][j]);
    }
    printf("\n");
  }

  int* ok = (int*)malloc(sizeof(int) * size);
  memset(ok, 0, sizeof(int) * size);
  stack eh;
  eh = caminho_completo_adj(0, grafo1adj, copy(ok, size), size);

  if (eh.size != -1) {
    printf("Caminho = ");
    for (int i = eh.size - 1; i >= 0; i--) {
      printf("%d ", eh.values[i] + 1);
    }
    printf("\n");
  }
  else {
    printf("Nao existe caminho\n");
  }

  //CAMINHO COMPLETO COM MATRIZ DE INCIDENCIA
  int arestas = 9;
  int** grafo1inc = (int**)malloc(sizeof(int*) * size);
  for (int i = 0; i < size; i++) {
    grafo1inc[i] = (int*)malloc(sizeof(int) * arestas);
    memset(grafo1inc[i], 0, sizeof(int) * arestas);
  }

  grafo1inc[0][0] = 20;
  grafo1inc[4][0] = -20;
  grafo1inc[2][1] = 15;
  grafo1inc[0][1] = -15;
  grafo1inc[0][2] = 30;
  grafo1inc[1][2] = -30;
  grafo1inc[4][3] = 10;
  grafo1inc[2][3] = -10;
  grafo1inc[2][4] = 10;
  grafo1inc[1][4] = -10;
  grafo1inc[4][5] = 30;
  grafo1inc[3][5] = -30;
  grafo1inc[2][6] = 5;
  grafo1inc[3][6] = -5;
  grafo1inc[3][7] = 50;
  grafo1inc[1][7] = -50;
  grafo1inc[1][8] = 50;
  grafo1inc[3][8] = -50;

  printf("Grafo 1 representado por matriz de incidencia:\n");
  printf("X\t");
  for (int i = 0; i < arestas; i++) {
    printf("%d\t", i + 1);
  }
  printf("\n");
  for (int i = 0; i < size; i++) {
    printf("%d\t", i + 1);
    for (int j = 0; j < arestas; j++) {
      printf("%d\t", grafo1inc[i][j]);
    }
    printf("\n");
  }

  eh = caminho_completo_adj(0, grafo1adj, copy(ok, size), size);

  if (eh.size != -1) {
    printf("Caminho = ");
    for (int i = eh.size - 1; i >= 0; i--) {
      printf("%d ", eh.values[i] + 1);
    }
    printf("\n");
  }
  else {
    printf("Nao existe caminho\n");
  }

  //CAMINHO ENTRE DOIS VERTICES COM MATRIZ DE ADJACENCIA
  size = 7;
  int** grafo2adj = (int**)malloc(sizeof(int*) * size);
  for (int i = 0; i < size; i++) {
    grafo2adj[i] = (int*)malloc(sizeof(int) * size);
    memset(grafo2adj[i], 0, sizeof(int) * size);
  }

  grafo2adj[0][1] = 2;
  grafo2adj[0][3] = 6;
  grafo2adj[0][4] = 12;
  grafo2adj[1][2] = 1;
  grafo2adj[1][5] = 5;
  grafo2adj[2][6] = 40;
  grafo2adj[3][5] = 4;
  grafo2adj[4][6] = 30;
  grafo2adj[5][6] = 8;

  printf("Grafo 2 representado por matriz de adjacencia:\n");

  printf("X\t");
  for (int i = 0; i < size; i++) {
    printf("%d\t", i + 1);
  }
  printf("\n");
  for (int i = 0; i < size; i++) {
    printf("%d\t", i + 1);
    for (int j = 0; j < size; j++) {
      printf("%d\t", grafo2adj[i][j]);
    }
    printf("\n");
  }

  ok = (int*)malloc(sizeof(int) * size);
  memset(ok, 0, sizeof(int) * size);

  eh = caminho_adj(0, 6, grafo2adj, copy(ok, size), size);

  if (eh.size != -1) {
    printf("Menor caminho = ");
    for (int i = eh.size - 1; i >= 0; i--) {
      printf("%d ", eh.values[i] + 1);
    }
    printf("\n");
  }
  else {
    printf("Nao existe caminho\n");
  }

  //CAMINHO ENTRE DOIS VERTICES COM MATRIZ DE INCIDENCIA
  arestas = 9;
  int** grafo2inc = (int**)malloc(sizeof(int*) * size);
  for (int i = 0; i < size; i++) {
    grafo2inc[i] = (int*)malloc(sizeof(int) * arestas);
    memset(grafo2inc[i], 0, sizeof(int) * arestas);
  }
  return 0;
}
