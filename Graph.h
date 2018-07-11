#ifndef GRAPH_H_
#define GRAPH_H_

typedef void *Type;
typedef enum{false, true} bool;

typedef struct strNode Node;
typedef struct strGraph *Graph;

typedef int (*CMP)(Type, Type);
typedef Type(*Clone)(Type);
typedef void(*MyFree)(Type);
typedef void(*Print)(type);

//Crea un grafo. Recibe una función de comparación, una de clonación y una para liberar memoria
Graph graph_create(CMP comparator, Clone clone, MyFree mfree);
//Destruye el contenedor
void graph_destroy(Graph g);
//Añade un vértice. Recibe el grafo y el dato a añadir
Bool graph_addVertex(Graph g, Type data);
//Añade un arista. Recibe un grafo, el origen del arista y el destino
Bool graph_addEdge(Graph g, Type source, Type skin);
//Retorna el número de vértices en el grafo
unsigned int graph_vertexCount(Graph g);
//Retorna el número de aristas en el grafo
unsigned int graph_edgeCount(Graph g);
//Recibe el grafo y el id que se desea buscar, retornando el número de vértices sucesores de este
unsigned int graph_outDegree(Graph g,Type source);
//Recibe el grafo, el origen y el de destino. Rretorna True si están conectados.
Bool graph_hasEdge(Graph g,Type source,Type skin);
//Imprime todos los datos del grafo, recibiendo una función para impresión
Bool graph_print(Graph g, Print p);

#endif /* GRAPH_H_ */
