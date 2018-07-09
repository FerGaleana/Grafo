#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"


struct strNode{
	Type id; //Identificador unico
	Type v; //Vertice
	struct strNode *next;
};

typedef struct strNode *Node;

struct strGraph{
	int V; //Numero de vertices
	int A; //Numero de aristas
	CMP cmpFunction; //Comparador
	Clone myClone; //Clonador
	MyFree myFree;
	Node *arr; //Arreglo de vErtices
};

Graph graph_create(CMP comparator){
	Graph g= (Graph)malloc(sizeof(struct strGraph));

	if(g != NULL){
		g->A= 0; //Numero de aristas
		g->V=0; //Numero de vertices
		g->arr[0]->id= (int)0; //No hay id
		g->arr[0]->next= NULL; //No hay siguiente
		g->arr[0]->v= (int)0; //No hay vertice
		g->myClone= NULL; //Clonador
		g->myFree=NULL; //Destructor
		g->cmpFunction= comparator; //Comparador
	}

	return g;
}

void graph_destroy(Graph g){
	for(int i=0; i<g->V; i++)
		free(g->arr[i]);
	free(g);

}
