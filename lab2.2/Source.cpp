//Часть 2, лаба 2, вариант 2.
//Фамилия И.О., номер счета, сумма на счете, дата последнего изменения.
/*
1 - ввод элементов(полей) структуры +
2 - вывод +
3 - «очистка» структурированных переменных +
4 - поиск свободной структурированной переменной +
5 - поиск в массиве структуры и минимальным значением заданного поля
6 - поиск в массиве структур элемента с заданным значением поля или с наиболее близким к нему по значению +-
7 - удаление заданного элемента
8 - изменение(редактирование) заданного элемента
9 - сортировка массива структур в порядке возрастания заданного поля +
	(при сортировке можно использовать тот факт, что в Си++ разрешается присваивание структурированных переменных)
10 - вычисление с проверкой и использованием всех элементов массива по заданному условию и формуле
	(например, общая сумма на всех счетах) - дается индивидуально
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <ctime>

typedef struct
{
	bool isEmpty;
	int id;
	int test;

	/*char firstName[80];
	char lastName[80];
	char *patronymic[80];

	unsigned long long accNum;
	unsigned long fundSum;
	SYSTEMTIME lasEdited;
*/
} Account;

void fillAccs(Account *accounts, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		(accounts + i)->id = i;
		(accounts + i)->isEmpty = false;
		(accounts + i)->test = 1 + rand() % 100;
	}
}

void printAccs(Account *accounts, int arrSize)
{
	printf("id	test\n\n");
	for (int i = 0; i < arrSize; i++)
	{
		printf("%d	", (accounts + i)->id);
		printf("%d	", (accounts + i)->test);
		printf("\n");
	}
	printf("\n");
}

void scanAcc(Account *accounts, int id)
{
	printf("please enter a number:\n");
	scanf("%d", &(accounts + id)->test);
}

void printAcc(Account *accounts, int id)
{
	if ((accounts + id)->isEmpty == false)
		printf("%d \n", (accounts + id)->test);
	else
		printf("account with this id doesent exist\n");
}

void clearingAcc(Account *accounts, int id)
{
		(accounts + id)->isEmpty = true;
		(accounts + id)->test = 0;
}

Account* searchEmptyAcc(Account *accounts, int *arrSize)
{
	int i;
	for (i = 0; i < *arrSize && (accounts + i)->isEmpty == false; i++);
	if ((accounts + i)->isEmpty == true)
		return (accounts + i);
	else
	{
		accounts = (Account *)realloc((accounts), (*arrSize + 1) * sizeof(Account));
		(accounts + *arrSize)->id = *arrSize;
		*arrSize++;
		return (accounts + i);
	}
}

Account* searchMinValue(Account *accounts, int arrSize)
{
	int min = accounts[0].test;
	int m = 0;
	for (int i = 0; i < arrSize; i++)
	{
		if (min > (accounts + i)->test)
		{
			min = (accounts + i)->test;
			m = i;
		}
	}
	return (accounts + m);
}

Account* searchAcc(Account *accounts, Account *acc, int arrSize)
{
	int i;
	for (i = 0; i < arrSize && (accounts + i)->test != acc->test; i++);
	if (i < arrSize && (accounts + i)->isEmpty == false)
		return (accounts + i);
	else
	{
		int minDiff = abs(acc->test - (accounts + 0)->test);
		int m = 0;
		for (i = 0; i < arrSize; i++)
		{
			if (abs(acc->test - (accounts + i)->test) < minDiff)
			{
				minDiff = abs(acc->test - (accounts + i)->test);
				m = i;
			}
		}
		return (accounts + m);
	}
}

void removeAcc(Account *accounts, int id)
{
	(accounts + id)->isEmpty = true;
}

void editAcc(Account *accounts, int id)
{
	
}

void sortAccs(Account *accounts, int arrsize)
{
	bool isSwap;
	do {
		isSwap = false;
		int lastSwap = 0;
		for (int i = 0; i < arrsize - 1; i++)
		{
			if ((accounts + i)->test > (accounts + i + 1)->test)
			{
				Account t = *(accounts + i);
				*(accounts + i) = *(accounts + i + 1);
				*(accounts + i + 1) = t;
				isSwap = true;
				lastSwap = i + 1;
			}
		}
		arrsize = lastSwap;
	} while (isSwap);
}

void main()
{
	int arrSize = 10;

	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	Account acc;
	acc.test = 100;

	fillAccs(accounts, arrSize);
	printAccs(accounts, arrSize);

	searchEmptyAcc(accounts, &arrSize)->test = 999;
	printAccs(accounts, arrSize);

	free(accounts);
}
