#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_SIZE 1000000
#define OPTIONS_COUNT 8

void cls();
double double_clock(clock_t);
int randInt(int, int);
void entIntVar(int*, int, int, const char*);
void fillArr(int*, int);
void randFillArr(int*, int, int, int);
int* createIntArr(int);
void intArrCopy(int*, int*, int);
void print_arr(int[], int);
void insert_sort(int[], int);
int barrier_find(int[], int, int);
int binary_find(int[], int, int);
int option_CreateArr();
int option_LinearSort();
int option_InsertSort();
int option_BubbleSort();
int option_LinearSearch();
int option_BarrierSearch();
int option_BinarySearch();

const char *options[OPTIONS_COUNT] = {
	"�����",
	"������� ������",
	"������������� �������",
	"������������� ��������",
	"������������� ���������",
	"����� �������� �������",
	"����� �������� � ��������",
	"�������� ����� ��������",
};

int size, option = 1;
int* arr, * original_arr;
int arrAdded, arrSorted; // FLAGS

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");

	while (option != 0) {
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
		}
	}
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
int option_LinearSort() { return 0; }
int option_InsertSort() { return 0; }
int option_BubbleSort() { return 0; }
int option_LinearSearch() { return 0; }
int option_BarrierSearch() { return 0; }
int option_BinarySearch() { return 0; }

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
	printf("[ ");
	for (int i = 0; i < size; printf("%d ", arr[i++]));
	printf("]");
}

void insert_sort(int arr[], int size) {
	int x, rem;
	for (int i = 1; i < size; i++) {
		x = arr[i];
		rem = i - 1;
		while (rem >= 0 && arr[rem] > x) {
			arr[rem + 1] = arr[rem];
			rem--;
		}
		arr[rem + 1] = x;
	}
}

int barrier_find(int arr[], int size, int x) {
	arr[size] = x;
	int i = 0;
	while (arr[i] != x) i++;
	if (i == size) i = -1;
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