#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"


struct GstrNode{
	unsigned long id; //Identificador
	Type data; //Dato contenido
	List next; //Lista a vértices sucesores
	Bool print;
};
typedef struct strNode Node;

struct strGraph{
	int V; //Numero de vertices
	int A; //Numero de aristas
	CMP cmpFunction; //Comparador
	Clone myClone; //Clonador
	MyFree myFree;
	Node **arr; //Arreglo de vértices
};

Graph graph_create(CMP comparator,Clone clone, MyFree mfree){
	Graph g= (Graph)malloc(sizeof(struct strGraph));

	if(g != NULL){
		g->A= 0; //Numero de aristas
		g->V=0; //Numero de vertices
		g->arr[0]->id= (int)0; //No hay id
		g->arr[0]->next= NULL; //No hay siguiente
		g->arr[0]->v= (int)0; //No hay vertice
		g->myClone= clone; //Clonador
		g->myFree=mfree; //Destructor
		g->cmpFunction= comparator; //Comparador
	}

	return g;
}

void graph_destroy(Graph g){
	for(int i=0; i<g->V; i++)
		free(g->arr[i]);
	free(g);

}
