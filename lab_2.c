#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include <ctype.h>

int k_mas=0;
int n;
int ans = 0;
int p[10];
int num_sum = 0;
char a[10];
char b[10];
typedef struct alphabet
{
	char symb;
	int val;
	struct alphabet* next;
}alphabet;

typedef struct quest
{
	char symb;
	struct quest* next;
	struct alphabet* alph;
}quest;

int count(alphabet* start, quest* mas_start);

inline void scan_mas(quest* mas_start)
{
	int k_m;
	char c;
	FILE* f = fopen("text.txt", "r");
	char mas[100];
	fgets(mas, 100, f);
	k_m = strlen(mas);
	if (mas[k_m - 1] == '\n')
	{
		mas[k_m - 1] = 0;
		k_m = k_m - 1;
	}

	for (int i = k_m - 1; i >= 0; i--)
	{
		
		c = mas[i];
		if (isspace(c) == 0) {
			quest* new_el = (quest*)malloc(sizeof(quest));
			new_el->symb = c;
			new_el->next = mas_start->next;
			mas_start->next = new_el;
			new_el->alph = NULL;
			k_mas++;
		}
		

	}
	
	
	
}

alphabet* is_in_alph(char symbol, alphabet* el)
{
	if (el == NULL) return 0;
	else if (el->symb == symbol) return el;
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


void perebor(alphabet* start, quest* mas_start)
{
	int stop = 0;
	int prov = 1;


	for (int i = 0; i < n; i++)
		p[i] = i;

	while (1) {
		
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
			Q:
				p[n - w - 1]++;
				if (p[n - w - 1] != 10)
				{
					if ((n - w - 2 >= 0 && p[n - w - 1] == p[n - w - 2]) || (n - w - 3 >= 0 && p[n - w - 1] == p[n - w - 3]) || (n - w - 4 >= 0 && p[n - w - 1] == p[n - w - 4]))
					{
						goto Q;
					}


					break;
				}
				else w++;
			}
		}

		if (stop) break;
	pro:
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (p[i] == p[j])
				{
					if (p[j] != 9)
					{
						p[j]++;
						goto pro;
					}
					else goto br;
				}

			}
		}


		if (start->next != NULL) insert_num(p[0], start->next, 0);
		if (count(start, mas_start) == 1) return;

	br:

		prov = 1;
	}
}


int count(alphabet* start, quest * mas_start)
{
	
	int num_sum = 0;
	int q = 0;
	
	quest* tmp=mas_start->next;
	while (1) {
		int i = 0;
		char a[10];


		for (i;tmp!=NULL && tmp->symb != '+' && tmp->symb != '='; i++)
		{
			
			if (i == 0 && tmp->alph->val == 0) return 0;
			a[i] = tmp->alph->val + 48;
			tmp = tmp->next;
		}
		
		a[i] = 0;
		num_sum += atoi(a);
	
		if (tmp->symb == '=') break;
		tmp = tmp->next;
	}


	tmp = tmp->next;
	char b[10];
	int j = 0;
	for (j; tmp != NULL; j++)
	{
		
		if (j == 0 && tmp->alph->val == 0) return 0;
		b[j] = tmp->alph->val + 48;

		tmp = tmp->next;
	}
	b[j] = 0;
	

	if (num_sum == atoi(b))
	{
		ans = 1;
		return 1;
	}
	return 0;
}

void raspredelenie(quest * mas_el, alphabet* start)
{
	if (mas_el->symb != '+' && mas_el->symb != '=')
	{
		if (is_in_alph(mas_el->symb, start->next) == 0)
		{
			n++;
			create_list(mas_el->symb, start);
			mas_el->alph = start->next;
		}
		else
			mas_el->alph = is_in_alph(mas_el->symb, start->next);
	}
	if (mas_el->next != NULL) raspredelenie(mas_el->next, start);
}

void print_mas(quest* mas_el)
{
	
	printf("%c", mas_el->symb);
	
	if (mas_el->next != NULL)
		print_mas(mas_el->next);
	return;
}

void print_ans(quest* mas_el)
{
	
	if (mas_el->symb == '+' || mas_el->symb == '=')
		printf("%c", mas_el->symb);
	else
		printf("%d", mas_el->alph->val);
	if (mas_el->next != NULL) print_ans(mas_el->next);
	return;
}

int main()
{
	
	unsigned int start_time = clock();
	struct alphabet start;
	start.next = NULL;
	struct quest mas_start;
	mas_start.next = NULL;
	mas_start.alph = NULL;
	scan_mas(&mas_start);
	
	
	raspredelenie(mas_start.next, &start);
	
	print_mas(mas_start.next);
	printf("\n");
	perebor(&start, &mas_start);

	if (ans == 1) {
		
		if (mas_start.next != NULL) print_ans(mas_start.next);
	}
	else
		printf("THE SOLUTION IS NOT FOUND");

	printf("\n%.3f", (clock() - start_time) / 1000.0f);
	return 0;

}


