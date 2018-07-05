#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

struct strNode{
	int *v; //A que vErtice pertenece
	int *p; //A que vErtice va
	struct strNode *next;
};

struct strGraph{
	int V,A;
	Node *n;
	CMP comparator;
};

Graph graph_create(CMP comparator){
	Graph g= (Graph)malloc(sizeof(struct strGraph));
	if(g != NULL){
		g->A= 0;
		g->V= 0;
		g->n->v= NULL;
		g->n->p= NULL;
		g->n->next=NULL;
		g->comparator= comparator;
		//Agregar lo del arreglo dinAmico
	}
	return g;
}

void graph_destroy(Graph g){
	free(g);
}
