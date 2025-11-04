#include<stdio.h>
#include<stdlib.h>

define MAXSIZE 100

typedef struct AMGraph{
Vertice V[MAXSIZE];
Adjvex A[MAXSIZE];
} AMGraph;

typedef struct Vertice{
char v[];
} Vertice;

typedef struct Adjvex{
int data;
Adjvex *next;
} Adjvex;

void InitVertice(AMGraph *G,int n){
for(int i=1;i<n;i++){
G->V[i].v[0]='V'；
G->V[i].v[1]='i'；
G->V[i].v[2]='\0'；
}
}

void InitAdjvex(AMGraph *G,int n){
  G->A[1].next=G->A[];
  G->A[1].data=;
  //continue
}
