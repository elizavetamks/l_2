#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include <ctype.h>
char mas[100];
int k_mas;
int n;
int ans = 0;
int p[10];

typedef struct alphabet
{
	char symb;
	int val;
	struct alphabet* next;
}alphabet;

int count(alphabet* start);

inline void scan_mas()
{
	FILE* f = fopen("text.txt", "r");
	fgets(mas, 100, f);
	k_mas = strlen(mas);
	if (mas[k_mas - 1] == '\n')
	{
		mas[k_mas - 1] = 0;
		k_mas = k_mas - 1;
	}
}

int is_in_alph(char symbol, alphabet* el)
{
	if (el == NULL) return 0;
	else if (el->symb == symbol) return 1;
	else if (el->next == NULL) return 0;
	else return is_in_alph(symbol, el->next);
}

void create_list(char symbol, alphabet* start)
{
	alphabet* new_el = (alphabet*)malloc(sizeof(alphabet));
	new_el->next = start->next;
	start->next = new_el;
	new_el->symb = symbol;
}

void insert_num(int number, alphabet* el, int k)
{
	el->val = number;
	if (el->next != NULL)
		insert_num(p[k + 1], el->next, k + 1);
}


int what_is_num(char symbol, alphabet* el)
{
	if (symbol == el->symb) return el->val;
	else if (el->next != NULL) return what_is_num(symbol, el->next);
	else return 0;
}

void perebor(alphabet*start)
{
	int stop = 0;
	int prov = 1;


	for (int i = 0; i < n; i++)
		p[i] = 0;

	while (1) {
		int not_print = 0;
		int num = 0;

		p[n - 1]++;
		if (p[n - 1] == 10)
		{
			int w = 1;
			while (1)
			{
				if (n - w == 0)
				{
					stop = 1;
					break;
				}
				p[n - w] = 0;
				p[n - w-1]++;
				if (p[n - w - 1] != 10) break;
				else w++;
			}
		}

		if (stop) break;

		for (int i = 0; i < n-1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (p[i] == p[j]) not_print = 1;
			}
		}

		if (not_print == 0)
		{
			insert_num(p[0], start->next, 0);
			if (count(start) == 1) return;
		}
		prov = 1;
	}
}

int count(alphabet* start)
{
	int res = 0;
	int num_sum = 0;
	int q = 0;
	while (1) {
		int i = 0;
		char a[10];
		for (i; i < 10 && mas[q] != '+' && mas[q] != '='; i++, q++)
		{
			if (i == 0 && what_is_num(mas[q], start->next) == 0) return 0;
			a[i] = what_is_num(mas[q], start->next) + 48;
		}
		a[i] = 0;
		num_sum = num_sum + atoi(a);
		if (mas[q] == '=') break;
		q++;
	}

	q++;
	char b[10];
	int j = 0;
	for (j; j < 10 && mas[q] != '\n' && mas[q] != 0 ; j++, q++)
	{
		if (j == 0 && what_is_num(mas[q], start->next) == 0) return 0;
		b[j] = what_is_num(mas[q], start->next) + 48;
	}
	b[j] = 0;
	res = atoi(b);

	if (num_sum == res)
	{
		ans = 1;
		return 1;
	}
	return 0;
}

int main()
{
	unsigned int start_time = clock();
	struct alphabet start;
	start.next = NULL;
	scan_mas();

	for (int i = 0; i < k_mas; i++)
	{
		if (isspace(mas[i]))
		{
			printf("PLEASE. DON'T USE SPACES");
			goto STOP;
		}
	}

	for (int i = 0; i < k_mas; i++)
	{
		if (mas[i] > 64 && mas[i] < 91)
		{
			if (is_in_alph(mas[i],start.next) == 0)
			{
				n++;
				create_list(mas[i], &start);
			}
		}
	}

	printf("%s\n", mas);
	
	perebor(&start);

	if (ans == 1) {
		for (int i = 0; i < k_mas; i++)
		{
			if (mas[i] == '+' || mas[i] == '=')
				printf("%c", mas[i]);
			else
				printf("%d", what_is_num(mas[i], start.next));
		}
	}
	else
		printf("THE SOLUTION IS NOT FOUND");
STOP:
	printf("\n%.3f", (clock() - start_time) / 1000.0f);
	return 0;

}
