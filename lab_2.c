#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include <ctype.h>

int alpha[91];
char mas[100];
int k_mas;
int n;
int ans=0;

int count();

void all_m2()
{
	for (int i = 0; i < 91; i++)
		alpha[i] = -2;
}

void scan_mas()
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

void used_in_m1()
{
	for (int i = 0; i < k_mas; i++)
	{
		if (mas[i] > 64 && mas[i] < 91 && alpha[mas[i]] == -2)
		{
			n++;
			alpha[mas[i]] = -1;
		}
	}
}


void perebor()
{
	int stop = pow(10, n);
	int prov = 1;
	int mas_prov[10] = { 11,13,2,3,17,5,19,7,23,29 };

	int p[10];
	for (int i = 0; i < n; i++)
		p[i] = 0;
	
	while (1) {
		int not_print = 0;
		int num = 0;
		for (int i = 0; i < n; i++)
		{
			num = num + p[i] * pow(10, n - i - 1);
		}
		num++;
		
		if (num == stop) break;
		for (int i = n - 1; i >= 0; i--)
		{

			p[i] = num % 10;
			num = num / 10;
			if (prov % mas_prov[p[i]] != 0)
				prov = prov * mas_prov[p[i]];
			else
				not_print = 1;

		}

		if (not_print == 0)
		{
			
			int q = 0;
			for (int i = 65; i < 91; i++)
			{
				if (alpha[i] != -2)
				{
					alpha[i] = p[q];
					q++;
				}
			}
			
			if (count() == 1) return;
		}
		prov = 1;

	}


}

int count()
{
	int res = 0;
	int num_sum = 0;
	int q = 0;
	while (1) {
		int i = 0;
		char a[10];
		for (i; i < 10 && mas[q] != '+' && mas[q] != '='; i++, q++)
		{
			if (i == 0 && alpha[mas[q]] == 0) return 0;
			a[i] = alpha[mas[q]]+48;
		}
		a[i] = 0;
		num_sum = num_sum + atoi(a);
		if (mas[q] == '=') break;
		q++;
	}

	
	q++;
	char b[10];
	int j = 0;
	for (j; j < 10 && mas[q]!='\n' && mas[q] != 0; j++, q++)
	{
		if (j == 0 && alpha[mas[q]] == 0) return 0;
		b[j] = alpha[mas[q]]+48;
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
	scan_mas();

	for (int i = 0; i < k_mas; i++)
	{
		if (isspace(mas[i]))
		{
			printf("PLEASE. DON'T USE SPACES");
			goto STOP;
		}
	}

	all_m2();
	used_in_m1();

	printf("%s\n", mas);

	perebor();

	if (ans == 1) {
		for (int i = 0; i < k_mas; i++)
		{
			if (mas[i] == '+' || mas[i] == '=')
				printf("%c", mas[i]);
			else
				printf("%d", alpha[mas[i]]);
		}
	}
	else
		printf("THE SOLUTION IS NOT FOUND");
STOP:
	printf("\n%.3f", (clock() - start_time) / 1000.0f);
	return 0;

}