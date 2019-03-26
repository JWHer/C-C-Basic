#include <stdio.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_V 7
#define INF 1000
int weight[MAX_V][MAX_V] = {
{0,7,INF,INF,3,10,INF},
{7,0,4,10,2,6,INF},
{INF,4,0,2,INF,INF,INF},
{INF,10,2,0,11,9,4},
{3,2,INF,11,0,INF,5},
{10,6,INF,9,INF,0,INF},
{INF,INF,INF,4,5,INF,0}
};

int distance[MAX_V];
int found[MAX_V];

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0;i<n;i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void shortest_path(int start, int n) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		distance[i] = weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE;
	for (i = 0; i < n; i++) {
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++)
			if (!found[w])
				if (distance[u] + weight[u][w] < distance[w])
					distance[w] = distance[u] + weight[u][w];
	}
}

void main() {
	shortest_path(0, MAX_V);
	for (int i = 0; i < MAX_V; i++)
		printf("%2d ", distance[i]);
	printf("\n");
}