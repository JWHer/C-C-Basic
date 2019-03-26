#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
	int vn;
	int **matrix;
	int weight;
}Graph;

Graph *NewGraph(int max_vertex) {
	int i = 0;
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	graph->vn = max_vertex;
	graph->matrix = (int **)malloc(sizeof(int *)*max_vertex);
	for (i = 0; i < max_vertex; i++) {
		graph->matrix[i] = (int *)malloc(sizeof(int)*max_vertex);
		memset(graph->matrix[i], 0, sizeof(int)*max_vertex);
	}
	return graph;
}

void AddEdge(Graph *graph, int start, int goal) {
	graph->matrix[start][goal] = 1;
	graph->matrix[goal][start] = 1;
}

Graph *MakeGraph() {
	Graph *graph;
	graph = NewGraph(9);
	AddEdge(graph, 0, 1);
	AddEdge(graph, 0, 2);
	AddEdge(graph, 6, 8);
	return graph;
}

void ViewNeighbor(Graph *g, int vt){
	int i;
for (i = 0; i < g->vn; i++) {
	if (g->matrix[vt][i]) {
		printf("%d ", i);
	}
}
}

void ViewNeighbors(Graph *g) {
	int i;
	printf("==ÀÌ¿ô Á¤Á¡==\n");
	for (i = 0; i < g->vn; i++) {
		printf("%dÀÇ ÀÌ¿ô: ", i);
		ViewNeighbor(g, i);
		printf("\n");
	}
}

int main() {
	Graph *g = MakeGraph();
	ViewNeighbors(g);
}