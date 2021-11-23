#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>

#define MAX_SIZE 1000000
#define OPTIONS_COUNT 10

void cls();
double doubleClock(clock_t);
int randInt(int, int);
void entIntVar(int*, int, int, const char*);
void fillArr(int*, int);
void randFillArr(int*, int, int, int);
int* createIntArr(int);
void intArrCopy(int*, int*, int);
void print_arr(int[], int);
uint64_t linear_sort(int[], int);
uint64_t insert_sort(int[], int);
uint64_t bubble_sort(int[], int);
int linear_find(int[], int, int);
int barrier_find(int[], int, int);
int binary_find(int[], int, int);
int option_CreateArr();
int option_LinearSort();
int option_InsertSort();
int option_BubbleSort();
int option_LinearSearch();
int option_BarrierSearch();
int option_BinarySearch();
int option_ComparisonSortings();
int option_PrintArray();

const char *options[OPTIONS_COUNT] = {
	"�����",
	"������� ������",
	"������������� �������",
	"������������� ��������",
	"������������� ���������",
	"����� �������� �������",
	"����� �������� � ��������",
	"�������� ����� ��������",
	"��������� ����������",
	"������� ������ �� �����",
};

int size, option = 1;
int* arr, * original_arr;
int arrAdded, arrSorted; // FLAGS

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");

	while (option != 0) {
		if (arrAdded) {
			printf("[%d ��-��] - ", size);
			if (arrSorted) printf("������������");
			else printf("�� ������������");
			printf("\n");
		}
		printf("\n������ �����:\n");
		for (int i = 0; i < OPTIONS_COUNT; i++) {
			printf("%d) %s\n", i, options[i]);
		}
		entIntVar(&option, 0, OPTIONS_COUNT - 1, "��������");
		switch (option)
		{
			case 1:
				option_CreateArr();
				break;
			case 2:
				option_LinearSort();
				break;
			case 3:
				option_InsertSort();
				break;
			case 4:
				option_BubbleSort();
				break;
			case 5:
				option_LinearSearch();
				break;
			case 6:
				option_BarrierSearch();
				break;
			case 7:
				option_BinarySearch();
				break;
			case 8:
				option_ComparisonSortings();
				break;
			case 9:
				option_PrintArray();
				break;
		}
	}
	free(arr);
	free(original_arr);
	return 0;
}

int option_CreateArr() {
	if (arrAdded) {
		int cont = 0;
		printf("\n������ ��� ������\n");
		entIntVar(&cont, 0, 1, "�������: 1 - ������� ��� ������, 0 - �����");
		if (!cont) {
			cls();
			return 1;
		}
		free(arr);
		free(original_arr);
	}
	entIntVar(&size, 1, MAX_SIZE, "\n������� ������ �������");
	arr = createIntArr(size);
	original_arr = createIntArr(size);
	if (size <= 20) fillArr(arr, size);
	else {
		int randMin, randMax;
		printf("������ ������� ������ 20,\n");
		printf("������ ���������� ���������� ����������,\n");
		entIntVar(&randMin, INT_MIN, INT_MAX, "������� �������� [a, b] ��������� �����\n������� a");
		entIntVar(&randMax, INT_MIN, INT_MAX, "������� b");
		while (randMin > randMax) {
			printf("�������� [a; b] ������ ���� �����, ��� a <= b!\n");
			printf("������� ������\n");
			entIntVar(&randMin, INT_MIN, INT_MAX, "������� a");
			entIntVar(&randMax, INT_MIN, INT_MAX, "������� b");
		}
		randFillArr(arr, size, randMin, randMax);
	}
	intArrCopy(arr, original_arr, size);
	arrAdded = 1;
	arrSorted = 0;
	cls();
	printf("[������ ������ � ��������]\n");
	return 0;
}

int option_LinearSort() {
	if (!arrAdded) {
		cls();
		printf("!������ ��� �� ������!\n");
		return 1;
	}
	double sortTime;
	uint64_t operations;
	intArrCopy(original_arr, arr, size);
	clock_t TS_Sort = clock();
	printf("\n����������� �������� ����������...");
	operations = linear_sort(arr, size);
	sortTime = doubleClock(clock() - TS_Sort);
	arrSorted = 1;
	cls();
	printf("[�������� ���������� ��������� �� %.3f ������ (%u ���. ��������)]\n", sortTime, operations / 1000);
	return 0;
}

int option_InsertSort() {
	if (!arrAdded) {
		cls();
		printf("!������ ��� �� ������!\n");
		return 1;
	}
	double sortTime;
	uint64_t operations;
	intArrCopy(original_arr, arr, size);
	clock_t TS_Sort = clock();
	printf("\n����������� ���������� ��������...");
	operations = insert_sort(arr, size);
	sortTime = doubleClock(clock() - TS_Sort);
	arrSorted = 1;
	cls();
	printf("[C��������� �������� ��������� �� %.3f ������ (%u ���. ��������)]\n", sortTime, operations / 1000);
	return 0;
}

int option_BubbleSort() {
	if (!arrAdded) {
		cls();
		printf("!������ ��� �� ������!\n");
		return 1;
	}
	double sortTime;
	uint64_t operations;
	intArrCopy(original_arr, arr, size);
	clock_t TS_Sort = clock();
	printf("\n����������� ���������� ���������...");
	operations = bubble_sort(arr, size);
	sortTime = doubleClock(clock() - TS_Sort);
	arrSorted = 1;
	cls();
	printf("[C��������� ��������� ��������� �� %.3f ������ (%u ���. ��������)]\n", sortTime, operations / 1000);
	return 0;
}

int option_LinearSearch() {
	if (!arrAdded) {
		cls();
		printf("!������ ��� �� ������!\n");
		return 1;
	}
	int x, index;
	double findTime;
	entIntVar(&x, INT_MIN, INT_MAX, "\n������� �������, ������� ����� �����");
	printf("����������� �������� ����� �������� %d...", x);
	clock_t TS_Find = clock();
	index = linear_find(arr, size, x);
	findTime = doubleClock(clock() - TS_Find);
	cls();
	printf("������ �������� ��������(%d) = %d (���� �������� ��� � �������: -1)\n", x, index);
	printf("[�������� ����� �������� �� %.5f ������(�)]\n", findTime);
	return 0;
}

int option_BarrierSearch() {
	if (!arrAdded) {
		cls();
		printf("!������ ��� �� ������!\n");
		return 1;
	}
	int x, index;
	double findTime;
	entIntVar(&x, INT_MIN, INT_MAX, "\n������� �������, ������� ����� �����");
	printf("����������� ����� � �������� �������� %d...", x);
	clock_t TS_Find = clock();
	index = barrier_find(arr, size, x);
	findTime = doubleClock(clock() - TS_Find);
	cls();
	printf("������ �������� ��������(%d) = %d (���� �������� ��� � �������: -1)\n", x, index);
	printf("[����� � �������� �������� �� %.5f ������(�)]\n", findTime);
	return 0;
}

int option_BinarySearch() {
	if (!arrAdded) {
		cls();
		printf("!������ ��� �� ������!\n");
		return 1;
	}
	if (!arrSorted) {
		cls();
		printf("!�������� ����� ����� ��������� ������ �� ���������������� �������!\n");
		printf("!������ ��� �� ������������!\n");
		return 1;
	}
	int x, index;
	double findTime;
	entIntVar(&x, INT_MIN, INT_MAX, "\n������� �������, ������� ����� �����");
	printf("����������� �������� ����� �������� %d...", x);
	clock_t TS_Find = clock();
	index = binary_find(arr, size, x);
	findTime = doubleClock(clock() - TS_Find);
	cls();
	printf("������ �������� ��������(%d) = %d (���� �������� ��� � �������: -1)\n", x, index);
	printf("[�������� ����� �������� �� %.5f ������(�)]\n", findTime);
	return 0;
}

int option_ComparisonSortings() {
	if (!arrAdded) {
		cls();
		printf("!������ ��� �� ������!\n");
		return 1;
	}
	double LinearSortTime, InsertSortTime, BubbleSortTime;
	uint64_t LinearSortOperations, InsertSortOperations, BubbleSortOperations;

	cls();
	// Linear
	intArrCopy(original_arr, arr, size);
	clock_t TS_linearSort = clock();
	printf("\n����������� �������� ����������...\n");
	LinearSortOperations = linear_sort(arr, size);
	LinearSortTime = doubleClock(clock() - TS_linearSort);
	printf("�������� ���������� ��������� -> %.3f ������, %u ���. ��������\n", LinearSortTime, LinearSortOperations / 1000);

	// Insert
	intArrCopy(original_arr, arr, size);
	clock_t TS_insertSort = clock();
	printf("\n����������� ���������� ��������...\n");
	InsertSortOperations = insert_sort(arr, size);
	InsertSortTime = doubleClock(clock() - TS_insertSort);
	printf("���������� ��������� -> % .3f ������, %u ���. ��������\n", InsertSortTime, InsertSortOperations / 1000);

	// Bubble
	intArrCopy(original_arr, arr, size);
	clock_t TS_bubbleSort = clock();
	printf("\n����������� ���������� ���������...\n");
	BubbleSortOperations = bubble_sort(arr, size);
	BubbleSortTime = doubleClock(clock() - TS_bubbleSort);
	printf("���������� ��������� ��������� -> %.3f ������, %u ���. ��������\n", BubbleSortTime, BubbleSortOperations / 1000);

	cls();
	printf("\t��������� ���������� (%d ��-��)\n\n", size);
	printf("%9s\t%11s\t%21s\n", "���", "�����(���)", "���-�� ��������(���)");
	printf("%9s\t%11.3f\t%21u\n", "��������", LinearSortTime, LinearSortOperations);
	printf("%9s\t%11.3f\t%21u\n", "��������", InsertSortTime, InsertSortOperations);
	printf("%9s\t%11.3f\t%21u\n", "���������", BubbleSortTime, BubbleSortOperations);

	printf("\n\n");
	arrSorted = 1;
	return 0;
}

int option_PrintArray() {
	if (!arrAdded) {
		cls();
		printf("!������ ��� �� ������!\n");
		return 1;
	}
	cls();
	printf("���� ����� ������� ������ 20, ��������� ������ 20\n");
	printf("������������ ������:\n");
	print_arr(original_arr, size);
	printf("\n\n�������� ������:\n");
	print_arr(arr, size);
	printf("\n\n");

	return 0;
}

void entIntVar(int* var, int min, int max, const char* str) {
	int ch = 0, a = 0;
	do {
		a = 0;
		if (max == INT_MAX && min == INT_MIN) {
			printf("%s: ", str);
		} else if (max == INT_MAX) {
			printf("%s(��� %d): ", str, min);
		} else if (min == INT_MIN) {
			printf("%s(���� %d): ", str, max);
		} else printf("%s(��� %d, ���� %d): ", str, min, max);
		a = scanf_s("%d", var);
		if (a < 1) printf("����� ������� ������ �����!\n");
		while (ch = getchar() != '\n');
	} while (a < 1 || ( * var < min || *var > max));
}

void cls() { system("cls"); }

double doubleClock(clock_t t) {
	return (double)t / CLOCKS_PER_SEC;
}

int randInt(int min, int max) {
	return min + rand() % (max - min + 1);
}

void fillArr(int *arr, int size) {
	printf("��������� ������\n");
	for (int i = 0; i < size; i++) {
		entIntVar(&arr[i], INT_MIN, INT_MAX, "������� �������");
	}
}

void randFillArr(int* arr, int size, int min, int max) {
	for (int i = 0; i < size; arr[i++] = randInt(min, max));
}

int* createIntArr(int size) {
	return (int*)malloc((size) * sizeof(int));
}

void intArrCopy(int* from, int* to, int size) {
	for (int i = 0; i < size; i++) to[i] = from[i];
}

void print_arr(int arr[], int size) {
	int n = size > 20 ? 20 : size;
	printf("[ ");
	for (int i = 0; i < n; i++) {
		if (i % 4 == 0 && i != 0) printf("\n  ");
		printf("%d ", arr[i]);
	}
	if (size > 20) printf("...(%d) ", size - 20);
	printf("]");
}

uint64_t linear_sort(int arr[], int size) {
	uint64_t _operations = 0;
	int min, index, temp;
	for (int i = 0; i < size; i++) {
		min = arr[i];
		index = i;
		for (int j = i + 1; j < size; j++) {
			if (min > arr[j]) {
				min = arr[j];
				index = j;
				_operations += 2;
			}
			_operations += 2;
		}
		temp = arr[i];
		arr[i] = min;
		arr[index] = temp;
		_operations += 6;
	}
	return _operations;
}

uint64_t insert_sort(int arr[], int size) {
	uint64_t _operations = 0;
	int x, rem;
	for (int i = 1; i < size; i++) {
		x = arr[i];
		rem = i - 1;
		while (rem >= 0 && arr[rem] > x) {
			arr[rem + 1] = arr[rem];
			rem--;
			_operations += 4;
		}
		arr[rem + 1] = x;
		_operations += 4;
	}
	return _operations;
}

uint64_t bubble_sort(int arr[], int len) {
	uint64_t _operations = 0;
	int tmp;
	int end = len, swap = 0;
	while (end > 0) {
		swap = 0;
		for (int i = 1; i < end; i++) {
			if (arr[i] < arr[i - 1]) {
				swap = 1;
				tmp = arr[i - 1];
				arr[i - 1] = arr[i];
				arr[i] = tmp;
				_operations += 4;
			}
			_operations += 2;
		}
		if (!swap) {
			end = 0;
			_operations += 1;
		}
		end--;
		_operations += 4;
	}
	return _operations;
}

int linear_find(int arr[], int size, int x) {
	int result = -1;
	for (int i = 0; i < size; i++) {
		if (arr[i] == x) {
			result = i;
			break;
		}
	}
	return result;
}

int barrier_find(int arr[], int size, int x) {
	int last = arr[size - 1];
	arr[size - 1] = x;
	int i = 0;
	while (arr[i] != x) i++;
	if (i == size - 1) i = -1;
	if (last == x) i = size - 1;
	arr[size - 1] = last;
	return i;
}

int binary_find(int arr[], int size, int x) {
	int middle, found = 0, position = -1;
	int start = 0, end = size;
	while (!found && start <= end) {
		middle = (start + end) / 2;
		if (arr[middle] == x) {
			found = 1;
			position = middle;
			break;
		}
		if (x < arr[middle]) {
			end = middle - 1;
		}
		else {
			start = middle + 1;
		}
	}
	return position;
}