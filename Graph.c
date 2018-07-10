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
 	for(int i=0; i<g->V; i++)
 		free(g->arr[i]);
 	free(g);

 } 
//Crea el primer apuntador dentro del arreglo vértices (se manda a llamar si es el primer vértice) e inicializa los datos
GNode* create_array(Type data){
	GNode* newVertex=(GNode*)malloc(sizeof(struct GstrNode));
	if(newVertex!=NULL){
		newVertex->data=data;
		newVertex->id=1;
		newVertex->next=NULL;
		newVertex->print=false;
		return newVertex;
	}
	else
		return NULL;
}
//Añade un elemento al arreglo, aumentando el tamaño de este e inicializa los datos
GNode* add_array(GNode *prev,unsigned int id, Type data){
	GNode *newVertex=(GNode*)realloc(prev,sizeof(struct GstrNode));
	if(newVertex!=NULL){
		newVertex->id=id;
		newVertex->data=data;
		newVertex->next=NULL;
		newVertex->print=false;
		return newVertex;
	}
	else
		return NULL;
}
Bool graph_addVertex(Graph g, Type data){
	GNode **arreglo=g->arr;
	unsigned int i=g->V;
	Bool found=false;
	if(i==0&&arreglo==NULL){
		arreglo=(GNode**)malloc(sizeof(GNode*)); //Crea un nuevo arreglo de apuntadores
		if(arreglo==NULL)
			return false;
		arreglo[i]=create_array(g->myClone(data));
		if(arreglo[i]==NULL)
			return false;
		g->arr=arreglo;
		g->arr[i]=arreglo[i];
		g->V++;
		return true;
	}
	else{
		int j=0;
		//Busca que no exista el dato
		while(found==false&&j<i){
			if(g->cmpFunction(data,(arreglo[j]->data))==0){
				found=true;
			}
			j++;
		}
		if(found==false){
			arreglo[i]=add_array(arreglo[i-1],i,g->myClone(data));
			if(arreglo[i]==NULL)
				return false;
			g->arr[i]=arreglo[i];
			g->V++;
		}
	}
	return true;
}
