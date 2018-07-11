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
	unsigned int v=g->n_v;
	
	for(int i=0; i<v; i++){
		
		if(g->arr[i]->next != NULL) //Si el next de mi arreglo tiene un dato
			list_destroy(g->arr[i]->next); //Se destruye 
		
		g->myFree(g->arr[i]->data); //Se libera el dato
		free(g->arr[i]); //Se libera el arreglo
	}
	
	free(g); //Se libera memoria del grafo

}

//Funciones para arreglo dinámico
//Crea el primer apuntador dentro del arreglo vértices (se manda a llamar si es el primer vértice) e inicializa los datos
GNode* add_array(Type data, unsigned int id){
	
	GNode* newVertex= (GNode*)malloc(sizeof(struct GstrNode)); //Se crea memoria para un nuevo vértice
	if(newVertex != NULL){  //Se inicializan datos
		newVertex->data= data; 
		newVertex->id= id;
		newVertex->next= NULL;
		newVertex->print= false;
		return newVertex;
	}
	else
		return NULL;
}

//Agrega un nuevo vértice de acuerdo al id del nuevo y de los ya existentes
Bool graph_addVertex(Graph g, Type data){
	
	GNode **arreglo= g->arr; //Se crea un nuevo arreglo
	unsigned int i= g->n_v; //i se inicializa en el número de vértices del grafo
	Bool found= false; 
	if(i==0 && arreglo==NULL){ //Si no se tiene ningun vértice en el arreglo
		arreglo= (GNode**)malloc(sizeof(GNode*)); //Crea un nuevo arreglo de apuntadores
		if(arreglo == NULL)
			return false;
		else
		g->arr= arreglo; //El arreglo del grafo se iguala al arreglo nuevo
	}
	else{
		int j=0;
		//Busca que no exista el dato
		while(found==false && j<i){ //Mientras que el dato no exista y j< número de vértices
			if(g->cmpFunction(data,(arreglo[j]->data)) == 0){
				found= true; //Se encontró el dato
				return false; //No se agregó el nuevo dato porque ya existe
			}
			j++; //Se va recorriendo el arreglo en busca de datos
		}
	}
	if(found==false && arreglo != NULL){ //Si no existe el dato pero el arreglo ya contiene datos
		if(i>0){ //Si tiene por lo menos un vértice
			GNode** arregloTemp= (GNode**)realloc(arreglo,sizeof(GNode*)*(g->n_v+1)); //Se hace un nuevo arreglo temporal
			if(arregloTemp != NULL) //Si tiene datos
				arreglo= arregloTemp; //Arreglo se iguala al temporal
		}
		
		arreglo[i]= add_array(g->myClone(data),i+1); //Crea el apuntador para el próximo vértice
		
		if(arreglo[i] == NULL) 
			return false; 
		g->arr= arreglo; //Se copia el arreglo de la función al del grafo
		g->n_v++; //Incrementa el número de vértices
	}
	else
		return false;
	return true;
}

//Buscar vértice
GNode* searchVertex(Graph g, Type source){
	Bool found= false;
	int i= 0;
	GNode *current= g->arr[i]; //Current toma los datos del arreglo desde el inicio
	if(g != NULL){ //Si el grafo recibido contiene datos
		while(found==false && i<g->n_v){ //Si no se ha encontrado el dato y el contador es menor al número de vértices
			if(g->cmpFunction(source,current->data) == 0) //Se compara el ingresado con cada uno del arreglo
				found= true; //Si se encontró 
			else{
				i++; //Incrementa el contador 
				current= g->arr[i]; //Se recorre el nodo current
			}
		}
	}
	if(found == false) //Si no se encontró el dato
		return NULL;
	return current;
}
//Retorna True si el vértice del dato que contiene source, contiene a skin.
Bool graph_hasEdge(Graph g,Type source,Type skin){
	GNode *source_node= searchVertex(g,source);
	GNode *skin_node= searchVertex(g,skin);
	GNode *current;
	Bool found= false;
	int size= list_size(source_node->next);
	int i= 0;
	if(source_node!=NULL && skin_node!=NULL){
		while(found==false && i<size){
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
Bool graph_addEdge(Graph g, Type source, Type skin){
	GNode *source_node= searchVertex(g,source);
	GNode *skin_node= searchVertex(g,skin);
	//List l;
	//unsigned int i=g->A;
	if(source_node!=NULL && skin_node!=NULL && source_node!=skin_node){
		if(source_node->next == NULL){
			source_node->next= list_create();
		}
		if(graph_hasEdge(g,source,skin) == false){
			list_add(source_node->next,(struct strNode*)skin_node);
			g->A++;
			return true;
		}
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
	GNode *current= searchVertex(g,source);
	int size= 0;
	if(current != NULL){
		size=list_size(current->next);
	}
	return size;
}

void edge_print(GNode *edge, Print p, int esp){
	GNode *temp;
	for(int j=0;j<list_size(edge->next);j++){
		temp=(GNode*)list_get(edge->next,j);
		if(temp->print==false){
		for(int i=0;i<esp;i++)
			printf("->");
		p(temp->data);
		temp->print=true;
		if(temp->next!=NULL){
			esp++;
			printf("\n");
			edge_print(temp,p,esp);
			esp--;
		}
		printf("\n");
	}
	}
}

Bool graph_print(Graph g, Print p){
	GNode *edge;
	GNode *temp;
	int i;
	if(g!=NULL){
		for(i=0;i<g->n_v;i++){
			edge= g->arr[i];
			if(edge->print == false){
			p(edge->data);
			if(edge->next != NULL){
				printf("\n");
				edge_print(edge,p,1);
			}
			printf("\n");
			}
		}
		return true;
	}
	return false;
}

