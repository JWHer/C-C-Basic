#include <stdio.h>
#include<stdlib.h>
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

void floyd(int matrix[MAX_V][MAX_V]) {
	int n = MAX_V;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = weight[i][j];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (matrix[j][k] > matrix[j][i] + matrix[i][k])
					matrix[j][k] = matrix[j][i] + matrix[i][k];
				if (matrix[j][k] > 99)
					printf("  F");
				else
					printf("%3d", matrix[j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void main() {
	int matrix[MAX_V][MAX_V];
	floyd(matrix);
}