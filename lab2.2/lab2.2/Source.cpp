/*Лаба 2, часть 2, вариант 2. 
Фамилия И.О., номер счета, сумма на счете, дата последнего изменения.*/
/*
1 - ввод элементов(полей) структуры
2 - вывод
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
typedef struct Account {
	int test;
	//int id;
	//bool is_empty;
	//unsigned long long account_id;
	//long fund_sum;
	//long last_edited;
	//Date date;
	//Name name;
} Account;

void scanData(Account *acc)
{
	printf("please type a number:\n");
	scanf("%d", &acc->test);
}

void printData(Account *acc)
{
	printf("your number: %d\n", acc->test);
}

void menu(Account *t)
{
	printf("\t please, write a number to select an option\n\n");
	printf("\t 1. create new account\n\t 2. show account\n\n");
	int in = 0;
	printf("\t ");
	scanf("%d\n", in);

	switch (in)
	{
	case 1:
		scanData(t);
		break;
	case '2':
		printData(t);
		break;
	}
}

void main()
{
	Account *t = (Account *)malloc(sizeof(Account));

	menu(t);

	free(t);
}
