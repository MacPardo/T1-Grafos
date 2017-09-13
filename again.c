#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1123456

int distancia;

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

  stack trail;
  trail.size = 0;

  ok[vertice] = 1;

  int menor_peso = INF, menor_vertice = -1;
  for (int i = 0; i < size; i++) {
    if (grafo[vertice][i] != 0 && grafo[vertice][i] < menor_peso && !ok[i]) {
      menor_peso = grafo[vertice][i];
      menor_vertice = i;
    }
  }

  if (menor_vertice != -1) {
    trail = caminho_completo_adj(menor_vertice, grafo, ok, size);
  }

  push(&trail, vertice);
  distancia += menor_peso < INF ? menor_peso : 0;
  return trail;
}



stack caminho_completo_inc(int vertice, int** grafo, int* ok, int size, int arestas) {
  stack trail;
  trail.size = 0;

  ok[vertice] = 1;

  int menor_peso = INF, menor_vertice = -1;
  for (int i = 0; i < arestas; i++) { //testa para todas as arestas
    if (grafo[vertice][i] > 0) { //se o vertice eh o ponto de partida
      for (int j = 0; j < size; j++) { //encontra o vertice de destino desta aresta
        if (grafo[j][i] < 0 && abs(grafo[j][i]) < menor_peso && !ok[j]) {
          menor_peso = abs(grafo[j][i]);
          menor_vertice = j;
        }
      }
    }
  }

  if (menor_vertice != -1) {
    trail = caminho_completo_inc(menor_vertice, grafo, ok, size, arestas);
  }

  push(&trail, vertice);
  distancia += menor_peso < INF ? menor_peso : 0;
  return trail;

}

stack caminho_adj(int vertice, int destino, int** grafo, int* ok, int size) {

  stack trail;
  trail.size = 0;

  ok[vertice] = 1;

  int menor_peso = INF, menor_vertice = -1;
  for (int i = 0; i < size; i++) {
    if (grafo[vertice][i] != 0 && grafo[vertice][i] < menor_peso && !ok[i]) {
      menor_peso = grafo[vertice][i];
      menor_vertice = i;
    }
  }

  if (menor_vertice != -1 && menor_vertice != destino) {
    trail = caminho_completo_adj(menor_vertice, grafo, ok, size);
  }

  push(&trail, vertice);
  distancia += menor_peso < INF ? menor_peso : 0;
  return trail;
}

stack caminho_inc(int vertice, int destino, int** grafo, int* ok, int size, int arestas) {
  stack trail;
  trail.size = 0;

  ok[vertice] = 1;

  int menor_peso = INF, menor_vertice = -1;
  for (int i = 0; i < arestas; i++) { //testa para todas as arestas
    if (grafo[vertice][i] > 0) { //se o vertice eh o ponto de partida
      for (int j = 0; j < size; j++) { //encontra o vertice de destino desta aresta
        if (grafo[j][i] < 0 && abs(grafo[j][i]) < menor_peso && !ok[j]) {
          menor_peso = abs(grafo[j][i]);
          menor_vertice = j;
        }
      }
    }
  }

  if (menor_vertice != -1 && vertice != destino) {
    trail = caminho_completo_inc(menor_vertice, grafo, ok, size, arestas);
  }

  push(&trail, vertice);
  distancia += menor_peso < INF ? menor_peso : 0;
  return trail;

}

int main(void) {

  //CAMINHO COMPLETO COM MATRIZ DE ADJACENCIA
  int size = 5;
  int** grafo1adj = (int**)malloc(sizeof(int*) * size);
  for (int i = 0; i < size; i++) {
    grafo1adj[i] = (int*)malloc(sizeof(int) * size);
    memset(grafo1adj[i], 0, sizeof(int) * size);
  }

  grafo1adj[1 - 1][2 - 1] = 30;
  grafo1adj[1 - 1][5 - 1] = 20;
  grafo1adj[2 - 1][4 - 1] = 50;
  grafo1adj[3 - 1][1 - 1] = 15;
  grafo1adj[3 - 1][2 - 1] = 10;
  grafo1adj[3 - 1][4 - 1] = 5;
  grafo1adj[4 - 1][2 - 1] = 50;
  grafo1adj[5 - 1][3 - 1] = 10;
  grafo1adj[5 - 1][4 - 1] = 30;

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
  distancia = 0;
  eh = caminho_completo_adj(0, grafo1adj, copy(ok, size), size);
  if (eh.size != -1) {
    printf("Caminho = ");
    for (int i = eh.size - 1; i >= 0; i--) {
      printf("%d ", eh.values[i] + 1);
    }
    printf("\n");
    printf("Distancia = %d\n", distancia);
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

  grafo1inc[1 - 1][1 - 1] = 20;
  grafo1inc[5 - 1][1 - 1] = -20;
  grafo1inc[3 - 1][2 - 1] = 15;
  grafo1inc[1 - 1][2 - 1] = -15;
  grafo1inc[1 - 1][3 - 1] = 30;
  grafo1inc[2 - 1][3 - 1] = -30;
  grafo1inc[5 - 1][4 - 1] = 10;
  grafo1inc[3 - 1][4 - 1] = -10;
  grafo1inc[3 - 1][5 - 1] = 10;
  grafo1inc[2 - 1][5 - 1] = -10;
  grafo1inc[5 - 1][6 - 1] = 30;
  grafo1inc[4 - 1][6 - 1] = -30;
  grafo1inc[3 - 1][7 - 1] = 5;
  grafo1inc[4 - 1][7 - 1] = -5;
  grafo1inc[4 - 1][8 - 1] = 50;
  grafo1inc[2 - 1][8 - 1] = -50;
  grafo1inc[2 - 1][9 - 1] = 50;
  grafo1inc[4 - 1][9 - 1] = -50;

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

  distancia = 0;

  eh = caminho_completo_inc(0, grafo1inc, copy(ok, size), size, arestas);

  if (eh.size != -1) {
    printf("Caminho = ");
    for (int i = eh.size - 1; i >= 0; i--) {
      printf("%d ", eh.values[i] + 1);
    }
    printf("\n");
    printf("Distancia = %d\n", distancia);
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

  distancia = 0;
  eh = caminho_adj(0, 6, grafo2adj, copy(ok, size), size);

  if (eh.size != -1) {
    printf("Menor caminho = ");
    for (int i = eh.size - 1; i >= 0; i--) {
      printf("%d ", eh.values[i] + 1);
    }
    printf("\n");
    printf("Distancia = %d\n", distancia);
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

  grafo2inc[1 - 1][1 - 1] = 2;
  grafo2inc[2 - 1][1 - 1] = -2;
  grafo2inc[1 - 1][2 - 1] = 6;
  grafo2inc[4 - 1][2 - 1] = -6;
  grafo2inc[1 - 1][3 - 1] = 12;
  grafo2inc[5 - 1][3 - 1] = -12;
  grafo2inc[2 - 1][4 - 1] = 1;
  grafo2inc[3 - 1][4 - 1] = -1;
  grafo2inc[2 - 1][5 - 1] = 5;
  grafo2inc[6 - 1][5 - 1] = -5;
  grafo2inc[4 - 1][6 - 1] = 4;
  grafo2inc[6 - 1][6 - 1] = -4;
  grafo2inc[5 - 1][7 - 1] = 30;
  grafo2inc[7 - 1][7 - 1] = -30;
  grafo2inc[3 - 1][8 - 1] = 40;
  grafo2inc[7 - 1][8 - 1] = -40;
  grafo2inc[6 - 1][9 - 1] = 8;
  grafo2inc[7 - 1][9 - 1] = -8;

  printf("Grafo 2 representado por matriz de incidencia:\n");
  printf("X\t");
  for (int i = 0; i < arestas; i++) {
    printf("%d\t", i + 1);
  }
  printf("\n");
  for (int i = 0; i < size; i++) {
    printf("%d\t", i + 1);
    for (int j = 0; j < arestas; j++) {
      printf("%d\t", grafo2inc[i][j]);
    }
    printf("\n");
  }

  distancia = 0;

  eh = caminho_inc(0, 7, grafo2inc, copy(ok, size), size, arestas);

  if (eh.size != -1) {
    printf("Caminho = ");
    for (int i = eh.size - 1; i >= 0; i--) {
      printf("%d ", eh.values[i] + 1);
    }
    printf("\n");
    printf("Distancia = %d\n", distancia);
  }
  else {
    printf("Nao existe caminho\n");
  }
  return 0;
}
