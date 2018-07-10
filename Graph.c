#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"


struct GstrNode{
	unsigned long id; //Identificador
	Type data; //Dato contenido
	List next; //Lista a vértices sucesores
	bool print;
};
typedef struct GstrNode Node;

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
	
	Node aux, next;
	int i;
	
	for(i=0; i<g->V; i++){ //Va a ir recorriendo hasta el total de vertices
		
		if(g->arr[i] != NULL){ //Mientras que se sigan encontrando vertices
			aux= g->arr[i]; //Mi auxiliar toma el valor de ese vertice
			
			while (aux!= NULL){ //Si sigue tomando valores
				next= aux->next; //Se irA recorriendo
				
				if(g->myFree != NULL){ //Funcion myFree
					g->myFree(aux->id); //Se libera el id de mi auxiliar
					g->myFree(aux->data); //Se libera el dato de mi auxiliar
				}
				
				free(aux); //Se libera mi auxiliar
				aux=next; //Mi auxiliar se recorre
			}//fin while
			
			free(g->arr[i]); //Se libera la memoria de mi arreglo[i]
		}//fin if
	}//fin for
	free(g->arr); //Se libera la memoria de mi arreglo por completo
	free(g); //Se libera la memoria de mi grafo
}
