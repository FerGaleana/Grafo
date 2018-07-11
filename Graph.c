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
		if(g->arr[i]->next!=NULL)
			list_destroy(g->arr[i]->next);
		g->myFree(g->arr[i]->data);
		free(g->arr[i]);
	}
	free(g);

}

//Funciones para arreglo dinámico
//Crea el primer apuntador dentro del arreglo vértices (se manda a llamar si es el primer vértice) e inicializa los datos
GNode* add_array(Type data, unsigned int id){
	GNode* newVertex=(GNode*)malloc(sizeof(struct GstrNode));
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
	GNode **arreglo=g->arr;
	unsigned int i=g->n_v;
	Bool found=false;
	if(i==0&&arreglo==NULL){
		arreglo=(GNode**)malloc(sizeof(GNode*)); //Crea un nuevo arreglo de apuntadores
		if(arreglo==NULL){
			return false;
		}
		else
		g->arr=arreglo;
	}
	else{
		int j=0;
		//Busca que no exista el dato
		while(found==false&&j<i){
			if(g->cmpFunction(data,(arreglo[j]->data))==0){
				found=true;
				return false;
			}
			j++;
		}
	}
	if(found==false&&arreglo!=NULL){
		if(i>0){
			GNode** arregloTemp=(GNode**)realloc(arreglo,sizeof(GNode*)*(g->n_v+1));
			if(arregloTemp!=NULL)
				arreglo=arregloTemp;
		}
		arreglo[i]=add_array(g->myClone(data),i+1);
		if(arreglo[i]==NULL){
					return false;
		}
		g->arr=arreglo;
		g->n_v++;
	}
	else
		return false;
	return true;
}

//Buscar vértice
GNode* searchVertex(Graph g,Type source){
	Bool found=false;
	int i=0;
	GNode *current=g->arr[i];
	if(g!=NULL){
	while(found==false&&i<g->n_v){
		if(g->cmpFunction(source,current->data)==0)
			found=true;
		else{
			i++;
			current=g->arr[i];
		}
	}
	}
	if(found==false)
		return NULL;
	return current;
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
Bool graph_addEdge(Graph g, Type source, Type skin){
	GNode *source_node=searchVertex(g,source);
	GNode *skin_node=searchVertex(g,skin);
	//List l;
	//unsigned int i=g->A;
	if(source_node!=NULL&&skin_node!=NULL&&source_node!=skin_node){
		if(source_node->next==NULL){
			source_node->next=list_create();
		}
		if(graph_hasEdge(g,source,skin)==false){
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
	GNode *current=searchVertex(g,source);
	int size=0;
	if(current!=NULL){
		size=list_size(current->next);
	}
	return size;
}


Bool graph_print(Graph g, Print p){
	GNode **edge=g->arr;
	GNode *temp;
	int i;
	if(g!=NULL){
		printf("Vértices: ");
		for(i=0;i<g->n_v;i++){
			printf("\nID: %u  ",edge[i]->id);
			p(edge[i]->data);
			if(edge[i]->next!=NULL){
				printf("\tAristas: ");
			for(int j=0;j<list_size(edge[i]->next);j++){
				temp=(GNode*)list_get(edge[i]->next,j);
				p(temp->data);
			}
			}

		}
		return true;
	}
	return false;
}

//PARTE DE LUIS//
/*
bool graph_addEdge(Graph g, Type source, Type skin){
    if(graph_existNode(g,source)==true && true==graph_existNode(g,skin)){
        Node* temp=(*Node)source;
        Node* temp2=(*Node)skin;
        list_add(temp->next,temp2->id);
        g->V++;
        return true;
    }
    return false;
}

bool graph_existNode(Graph g, Type vertex){
    unsigned int counter;
    CMP comparacion;
    comparacion = g->cmpFunction;
    for (counter=0; counter<g->V; counter++){
        if(1==comparacion(vertex))
            return true;
    }
    return false;
}
*/
