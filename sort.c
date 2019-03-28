#include <stdio.h>
#include <time.h>
#include<stdlib.h>

#define MAX_V 60000
#define RANGE 100

//arry utillity
void show(int ary[]) {
	for (int i = 0; i < MAX_V; i++)
		printf("%2d ", ary[i]);
	printf("\n");
}
void copy(int ary[], int cpy[]) {
	for (int i = 0; i < MAX_V; i++)
		cpy[i] = ary[i];
}
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
//queue for radix
typedef struct Node {
	int data;
	struct Node *next;
}Node;
typedef struct Queue {
	Node* rear;
	Node* front;
}Queue;
void initQue(Queue *q) {
	q->front = q->rear = NULL;
}
int isEmpty(Queue *q) {
	return (q->front == NULL);
}
void insertQue(Queue *q, int data) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	if (isEmpty(q)) {
		q->rear = q->front = newNode;
	}
	else {
		q->rear->next = newNode;
		q->rear = newNode;
	}
}
int deQue(Queue *q) {
	if (isEmpty(q)) { printf("Queue is Empty!\n"); return -1; }
	Node* del = q->front;
	int data = del->data;
	q->front = q->front->next;
	if (q->front == NULL) q->rear == NULL;
	free(del);
	return data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//선택정렬
void selectionSort(int ary[]) {
	int least;
	for (int i = 0; i < MAX_V; i++) {
		least = i;
		for (int j = i + 1; j < MAX_V; j++) {
			if (ary[j] < ary[least]) least = j;
		}
		if (i != least) swap(&ary[i], &ary[least]);
		//show(ary);
	}
}
//삽입정렬
void insertionSort(int ary[]) {
	int key, j, i;
	for (i = 1; i < MAX_V; i++) {
		key = ary[i];
		for (j = i - 1; j >= 0 && ary[j] > key; j--) {
			ary[j + 1] = ary[j];
		}
		ary[j + 1] = key;
		//show(ary);
	}
}
//버블정렬
void bubbleSort(int ary[]) {
	for (int i = 0; i < MAX_V; i++) {
		for (int j = 0; j < MAX_V - 1; j++)
			if (ary[j] > ary[j + 1]) swap(&ary[j], &ary[j + 1]);
		//show(ary);
	}
			
}
//쉘  정렬
void shellSort(int ary[]) {
	int gap, key, k;
	for (gap = MAX_V / 2; gap > 0; gap /= 2) {
		if (gap % 2 == 0) gap++;
		for (int i = 0; i < gap; i++) {
			for (int j = i + gap; j < MAX_V; j += gap) {
				key = ary[j];
				for (k = j - gap; k >= i && ary[k] > key; k -= gap) {
					ary[k + gap] = ary[k];
				}
				ary[k + gap] = key;
			}
		}
		//show(ary);
	}
}
//합병정렬
int sorted[MAX_V];
void merge(int ary[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		if (ary[i] <= ary[j])
			sorted[k++] = ary[i++];
		else
			sorted[k++] = ary[j++];
	}//작은것부터 담음 //한쪽이 먼저 비면 //한번에 다 담음
	if (i > mid)
		for (int l = j; l <= right; l++)
			sorted[k++] = ary[l];
	else
		for (int l = i; l <= mid; l++)
			sorted[k++] = ary[l];
	for (int l = left; l <= right; l++)
		ary[l] = sorted[l];
}
void mergeSort(int ary[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSort(ary, left, mid);
		mergeSort(ary, mid + 1, right);
		merge(ary, left, mid, right);
		//show(sorted);
	}
}
//퀵  정렬
int partition(int ary[], int left, int right) {
	int low = left, high = right + 1, pivot = ary[left];
	//show(ary);
	do {
		do low++;
		while (low <= right && ary[low] < pivot);
		do high--;
		while (high >= left && ary[high] > pivot);
		if (low<high) swap(&ary[low], &ary[high]);
	} while (low < high);
	swap(&ary[left], &ary[high]);
	return high;
}
void quickSort(int ary[], int left, int right) {
	if (left < right) {
		int q = partition(ary, left, right);
		quickSort(ary, left, q - 1);
		quickSort(ary, q + 1, right);
	}
}
//기수정렬
void radixSort(int ary[]) {
	int buckets = 10, digits = 1, factor = 1;
	int range = RANGE-1;
	while ((range/= buckets) != 0)  digits++;
	Queue* que = (Queue*)malloc(sizeof(Queue)*buckets);
	for (int i = 0; i < buckets; i++) initQue(que + i);

	for (int d = 0; d < digits; d++) {
		for (int i = 0; i < MAX_V; i++)
			insertQue(que + ((ary[i] / factor) % buckets), ary[i]);
		for (int b = 0, i = 0; b < buckets; b++)
			while (!isEmpty(que + b))
				ary[i++] = deQue(que + b);
		factor *= buckets;
		//show(ary);
	}
	free(que);
}

void main() {
	srand((unsigned)time(NULL));
	clock_t start, end;

	int ary[MAX_V];// = { 53,71,49,92,55,38,82,72 };
	int cpy[MAX_V];
	for (int i = 0; i < MAX_V; i++)
		ary[i] = rand() % RANGE;
	//show(ary);
	copy(ary, cpy);

	start = clock();
	selectionSort(ary);
	end = clock();
	//show(ary);
	printf("선택정렬 걸린시간 : %lf\n", (double)(end - start) / 1000);
	copy(cpy, ary);

	start = clock();
	insertionSort(ary);
	end = clock();
	//show(ary);
	printf("삽입정렬 걸린시간 : %lf\n", (double)(end - start) / 1000);
	copy(cpy, ary);

	start = clock();
	bubbleSort(ary);
	end = clock();
	//show(ary);
	printf("버블정렬 걸린시간 : %lf\n", (double)(end - start) / 1000);
	copy(cpy, ary);

	start = clock();
	shellSort(ary);
	end = clock();
	//show(ary);
	printf("쉘  정렬 걸린시간 : %lf\n", (double)(end - start) / 1000);
	copy(cpy, ary);

	start = clock();
	mergeSort(ary, 0, MAX_V - 1);
	end = clock();
	//show(ary);
	printf("합병정렬 걸린시간 : %lf\n", (double)(end - start) / 1000);
	copy(cpy, ary);

	start = clock();
	quickSort(ary, 0, MAX_V - 1);
	end = clock();
	//show(ary);
	printf("퀵  정렬 걸린시간 : %lf\n", (double)(end - start) / 1000);
	copy(cpy, ary);

	start = clock();
	radixSort(ary);
	end = clock();
	//show(ary);
	printf("기수정렬 걸린시간 : %lf\n", (double)(end - start) / 1000);
	copy(cpy, ary);
}