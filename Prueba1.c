#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int CompareInt(Type,Type);
Type CloneInt(Type);
void FreeInt(Type);
void PrintInt(Type);

int main(){
	Graph g=NULL;
	int c=0;
	printf("%p\n",g);
	g=graph_create(CompareInt,CloneInt,FreeInt);
	if(g!=NULL)
		printf("CREADO %p\n",g);
	else
		printf("NO CREADO\n");

	printf("\n");
	Bool added=false,connected=false;
	int h=83;
	added=graph_addVertex(g,(Type)&h);
			if(added==true){
				c++;
				printf("%d AÑADIDO\n",c);
			}
			else
				printf("NO AÑADIDO\n");
	h=25;
	added=graph_addVertex(g,(Type)&h);
				if(added==true){
					c++;
					printf("%d AÑADIDO\n",c);
				}
				else
					printf("NO AÑADIDO\n");
	int v[]={12,8,4,7,35,6,9,15,10,4,6};
	for(int i=0;i<11;i++){
		added=graph_addVertex(g,(Type)&v[i]);
		if(added==true){
			c++;
			printf("%d AÑADIDO\n",c);
		}
		else
			printf("NO AÑADIDO\n");
	}

	int d=24;
	printf("\n");
	connected=graph_addEdge(g,(Type)&v[0],(Type)&v[4]);//liga 8 a 35
	if(connected==true)
		printf("ARISTA AÑADIDO(%u, %u)\n",v[0],v[4]);
	else
		printf("ARISTA NO AÑADIDO\n");
	for(int j=0;j<3;j++){
		connected=graph_addEdge(g,(Type)&v[j],(Type)&v[j+4]);
			if(connected==true)
				printf("ARISTA AÑADIDO(%u, %u)\n",v[j],v[j+4]);
			else
				printf("ARISTA NO AÑADIDO(%u, %u)\n",v[j],v[j+4]);
	}
	connected=graph_addEdge(g,(Type)&v[1],(Type)&v[2]);
				if(connected==true)
					printf("ARISTA AÑADIDO(%u, %u)\n",v[1],v[2]);
				else
					printf("ARISTA NO AÑADIDO(%u, %u)\n",v[1],v[2]);
	printf("\n");
	unsigned int s_v, s_a;
	s_v=graph_vertexCount(g);
	s_a=graph_edgeCount(g);
	printf("Vértices: %u\tAristas: %u\n",s_v,s_a);
	printf("\n");
	s_v=graph_outDegree(g,(Type)&v[1]);
	printf("Aristas de 8: %u\n",s_v);
	connected=graph_hasEdge(g,(Type)&v[1],(Type)&v[4]);

	if(connected==true)
		printf("ARISTA ENCONTRADO(8,35)\n");
	else
		printf("ARISTA NO ENCONTRADO(8,35)\n");
	printf("\n");
	connected=graph_hasEdge(g,(Type)&v[1],(Type)&d);
	if(connected==true)
			printf("ARISTAS ENCONTRADO(8,24)\n");
		else
			printf("ARISTA NO ENCONTRADO(8,24)\n");

	Bool printed=false;
	printed=graph_print(g,PrintInt);
	if(printed==true)
		printf("DONE\n");
	else
		printf("NO SE PUDO IMPRIMIR\n");

	graph_destroy(g);
	return 0;
}
int CompareInt(Type d1, Type d2){
	int v1=*(int*)d1;
	int v2=*(int*)d2;
	return v1-v2;
}
Type CloneInt(Type d){
	int v=*(int*)d;
	int *new=(int*)malloc(sizeof(int));
	*new=v;

	return new;
}
void FreeInt(Type d){
	free(d);
}
void PrintInt(Type d){
	printf(" %d ",*(int *)d);
}
