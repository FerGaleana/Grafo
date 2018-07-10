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
	unsigned int V; //Numero de vertices
	unsigned int A; //Numero de aristas
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
		g->arr=NULL; //No existe el arreglo
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
