#ifndef GRAPH_H_
#define GRAPH_H_

typedef void *Type;
typedef enum{false, true} bool;

typedef struct strNode Node;
typedef struct strGraph *Graph;

typedef int (*CMP)(Type, Type);
typedef Type(*Clone)(Type);
typedef void(*MyFree)(Type);

Graph graph_create(CMP comparator);
void graph_destroy(Graph g);

#endif /* GRAPH_H_ */
