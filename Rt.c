#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct{
	unsigned long long retweet_id;
	unsigned long long tweet_id;
}RT;

int CompareR(Type,Type);
Type CloneR(Type);
void FreeR(Type);
void PrintR(Type);

int main(){
	FILE *pRT=fopen("RETWEETS.csv","r");
	Graph g=NULL;
	g=graph_create(CompareR,CloneR,FreeR);
	//unsigned long long temp;
	RT rt;
	char c,d;
	if(pRT==NULL){
		printf("Error al abrir el archivo.\n");
		return 0;
	}
	Bool added=false,added2=false;
	while(!feof(pRT)){
		fscanf(pRT,"%I64u",&rt.retweet_id);
		added=graph_addVertex(g,(Type)&rt.retweet_id);
		fscanf(pRT,"%c",&c);
		fscanf(pRT,"%I64u",&rt.tweet_id);
		added=graph_addVertex(g,(Type)&rt.tweet_id);
		added2=graph_addEdge(g,(Type)&rt.tweet_id,(Type)&rt.retweet_id);
		d=fgetc(pRT);
	}
	int size_a=graph_edgeCount(g);
	printf("Total de retweets: %d\n",size_a);
	int size_id=graph_vertexCount(g);
	printf("Total de IDs agregados: %d\n",size_id);
	unsigned long long tweet=957638367033872384;
	int total_rt=graph_outDegree(g,(Type)&tweet);
	printf("El tweet con el ID %I64u fue retweeteado %d veces.\n",tweet,total_rt);
	unsigned long long retweet=957762296893399041;
	Bool connected=graph_hasEdge(g,(Type)&tweet,(Type)&retweet);
	if(connected==true)
		printf("El retweet %I64u fue del tweet %I64u\n",retweet,tweet);
	else
		printf("El retweet %I64u no fue del tweet %I64u\n",retweet,tweet);
	tweet=957707010434306048;
	retweet=957731211694125056;
	connected=graph_hasEdge(g,(Type)&tweet,(Type)&retweet);
		if(connected==true)
			printf("El retweet %I64u fue del tweet %I64u\n",retweet,tweet);
		else
			printf("El retweet %I64u no fue del tweet %I64u\n",retweet,tweet);

	graph_destroy(g);
	fclose(pRT);
	return 0;
}


int CompareR(Type first,Type second){
	unsigned long long temp1=*(unsigned long long*)first;
	unsigned long long temp2=*(unsigned long long*)second;

	return temp1-temp2;

}
Type CloneR(Type data){
	RT temp=*(RT*)data;
	RT *new=(RT*)malloc(sizeof(RT));
	*new=temp;
	return new;

}
void FreeR(Type data){
	free(data);
}
void PrintR(Type data){
	unsigned long long temp=*(unsigned long long*)data;
	printf("ID: %I64u",temp);
}
