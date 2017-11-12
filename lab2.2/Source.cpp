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
	int test;
} Account;

void fillAcc(Account *accounts, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
		(accounts + i)->test = 1+rand()%100;
}

void printArrayTest(Account *accounts, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
		printf("%d ", (accounts + i)->test);
	printf("\n\n");
}

void scanAcc(Account *accounts, int id)
{
	printf("please type a number:\n");
	scanf("%d", &(accounts + id)->test);
}

void printAcc(Account *accounts, int id)
{
	if ((accounts + id)->test != 0)
		printf("%d \n", (accounts + id)->test);
	else
		printf("account with this id doesent exist\n");
}

void clearingAcc(Account *accounts, int id, int arrSize)
{
	if (id < arrSize)
		(accounts + id)->test = 0;
}

void searchFreePlace(Account *accounts, int arrSize, int *acc)
{
	int i;
	for (i = 0; i < arrSize && (accounts + i)->test != 0; i++); 
	if ((accounts + i)->test == 0)
		(accounts + i)->test = *acc;
	else
		printf("there is no free places\n");
	
}

void searchAcc(Account *accounts, int arrSize, int *acc)
{
	int i;
	for (i = 0; i < arrSize && (accounts + i)->test != *acc; i++);
	i < arrSize? printf("%d\n", *(accounts + i)): printf("no matches\n");
}

void sortAcc(Account *accounts, int arrsize)
{
	bool isSwap;
	do {
		isSwap = false;
		int lastSwap = 0;
		for (int i = 0; i < arrsize - 1; i++)
		{
			if ((accounts + i)->test >(accounts + i +1)->test)
			{
				int t = (accounts + i)->test;
				(accounts + i)->test = (accounts + i+1)->test;
				(accounts + i+1)->test = t;
				isSwap = true;
				lastSwap = i + 1;
			}
		}
		arrsize = lastSwap;
	} while (isSwap);
}

void main()
{
	int arrSize = 20;
	int id = 0;
	int acc = 42;
	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	/*printf("enter id: \n");
	scanf("%d", &id);*/

	fillAcc(accounts, arrSize);
	printArrayTest(accounts, arrSize);
	searchAcc(accounts, arrSize, &acc);

	free(accounts);
}