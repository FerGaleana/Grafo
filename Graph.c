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
	unsigned int n_v; //Numero de vertices
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
		g->n_v=0; //Numero de vertices
		g->arr=NULL; //No existe el arreglo
		g->myClone= clone; //Clonador
		g->myFree=mfree; //Destructor
		g->cmpFunction= comparator; //Comparador
	}

	return g;
}

void graph_destroy(Graph g){
	unsigned int v= g->n_v;
	for(int i=0; i<v; i++){
		if(g->arr[i]->next!=NULL)
			list_destroy(g->arr[i]->next);
		g->myFree(g->arr[i]->data);
		free(g->arr[i]);
	}
	free(g);

}

//Agrega un apuntador al arreglo vértices e inicializa los datos
GNode* add_array(Type data, unsigned int id){
	GNode* newVertex= (GNode*)malloc(sizeof(struct GstrNode));
	if(newVertex!=NULL){
		newVertex->data=data;
		newVertex->id=id;
		newVertex->next=NULL;
		newVertex->print=false;
		return newVertex;
	}
	else
		return NULL;
}

Bool graph_addVertex(Graph g, Type data){
	GNode **arreglo= g->arr;
	unsigned int i= g->n_v;
	Bool found= false;
	if(i==0 && arreglo==NULL){
		arreglo= (GNode**)malloc(sizeof(GNode*)); //Crea un nuevo arreglo de apuntadores
		if(arreglo == NULL)
			return false;
		else
		g->arr=arreglo;
	}
	else{
		int j=0;
		//Busca que no exista el dato
		while(found==false && j<i){
			if(g->cmpFunction(data,(arreglo[j]->data)) == 0){
				found=true;
				return false;
			}
			j++;
		}
	}
	if(found==false && arreglo!=NULL){
		if(i>0){
			GNode** arregloTemp= (GNode**)realloc(arreglo,sizeof(GNode*)*(g->n_v+1));
				if(arregloTemp != NULL)
					arreglo= arregloTemp;
		}
		
		arreglo[i]=add_array(g->myClone(data),i+1);
		if(arreglo[i] == NULL)
			return false;
		
		g->arr=arreglo;
		g->n_v++;
	}
	else
		return false;

	return true;
}
Bool graph_hasEdge(Graph g,Type source,Type skin){
	GNode *source_node=searchVertex(g,source);
	GNode *skin_node=searchVertex(g,skin);
	GNode *current;
	Bool found=false;
	int size=list_size(source_node->next);
	int i=0;
	if(source_node!=NULL&&skin_node!=NULL){
		while(found==false&&i<size){
			current=(GNode*)list_get(source_node->next,i);
			if(current==skin_node)
				found=true;
			else
				i++;
		}
		if(found==true)
			return true;
	}
	return false;
}
unsigned int graph_vertexCount(Graph g){
	return g->n_v;
}

unsigned int graph_edgeCount(Graph g){
	return g->A;
}

unsigned int graph_outDegree(Graph g,Type source){
	GNode *current=searchVertex(g,source);
	int size=0;
	if(current!=NULL){
		size=list_size(current->next);
	}
	return size;
}
