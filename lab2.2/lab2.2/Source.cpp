/*Лаба 2, часть 2, вариант 2. 
Фамилия И.О., номер счета, сумма на счете, дата последнего изменения.*/
/*
1 - ввод элементов(полей) структуры +
2 - вывод +
3 - «очистка» структурированных переменных
4 - поиск свободной структурированной переменной
5 - поиск в массиве структуры и минимальным значением заданного поля
6 - поиск в массиве структур элемента с заданным значением поля или с наиболее близким к нему по значению
7 - удаление заданного элемента
8 - изменение(редактирование) заданного элемента
9 - сортировка массива структур в порядке возрастания заданного поля
	(при сортировке можно использовать тот факт, что в Си++ разрешается присваивание структурированных переменных)
10 - вычисление с проверкой и использованием всех элементов массива по заданному условию и формуле
	(например, общая сумма на всех счетах) - дается индивидуально 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <windows.h>

//struct Date
//{
//	unsigned short day;
//	unsigned short month;
//	unsigned short year;
//};
//struct Name
//{
//	char first_name[80];
//	char last_name[80];
//	char *patronymic[80];
//};
//void time()
//{
//	SYSTEMTIME SystemTime;
//
//	GetSystemTime(&SystemTime);
//	printf("hours : %d\n", SystemTime.wHour);
//
//}
//int id;
//bool is_empty;
//unsigned long long account_id;
//long fund_sum;
//long last_edited;
//Date date;
//Name name;
//SYTEMTIME last_modified;
//void menu(Account *accounts, int *id)
//{
//	printf("\t please, write a number to select an option\n\n");
//	printf("\t 1. create new account\n\t 2. show account\n\n");
//	int in = 0;
//	printf("\t ");
//	scanf("%d\n", &in);
//
//	switch (in)
//	{
//	case 1:
//		scanData(accounts, id);
//		break;
//	case 2:
//		printData(accounts, id);
//		break;
//	}
//}
typedef struct Account 
{
	int test;
	
} Account;

void fillAccounts(Account *accounts, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
		(accounts + i)->test = i;
}

void scanAccounts(Account *accounts, int id)
{
	printf("please type a number:\n");
	scanf("%d", &(accounts+id)->test);
}

void printAccounts(Account *accounts, int id, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		printf("  %d", &(accounts + i)->test);
	}
	printf("\n");	
}

void main()
{
	int arraySize = 100;
	int id = 0;
	Account *accounts = (Account *)malloc(arraySize * sizeof(Account));

	printAccounts(accounts, id, arraySize);

	free(accounts);
}
