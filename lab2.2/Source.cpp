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
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <ctime>

#define nameLen 10
#define DIFF(x, y) ((x) > (y) ? (x - y) : (y - x))

typedef struct
{
	unsigned short day;
	unsigned short month;
	unsigned short year;
	unsigned long seconds;

} Date;

typedef struct
{
	bool isEmpty;
	int id;
	unsigned int test;
	
	unsigned long long accNum;
	unsigned long fundSum;
	Date lasEdited;
	
	char firstName[nameLen];
	char lastName[nameLen];
	char patronymic[nameLen];

} Account;

char *generateNames(char *str, char *name)
{
	int n = rand() % 10;
	int i;

	for (i = 0; i <= n; str++)
		if (*str == '/')
			i++;

	for (i = 0; *str != '/'; str++, i++)
		name[i] = *str;
	name[i] = '\0';
	
	return name;
}

void fillAccs(Account *accounts, int arrSize)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

	srand(time(NULL));

	char fnames[] = "/Tom/Miles/Sam/Jenni/Morty/Emma/Elizabeth/Jack/Luna/Eve/";
	char lnames[] = "/Jonas/Drake/Urie/Lerman/Toro/Way/Iero/Watson/Colby/Smith/";
	char ptrs[] = "/ /Third/Second/ / /Fifth/Fourth/ /Second/ /";

	char *name = (char*)malloc(sizeof(char) * nameLen);
	int secPerDay = 24 * 60 * 60;

	for (int i = 0; i < arrSize; i++)
	{
		(accounts + i)->id = i;
		(accounts + i)->isEmpty = false;
		(accounts + i)->accNum = (unsigned long long)rand() % 999*1000000 + rand() % 100000;
		(accounts + i)->fundSum = (unsigned long)rand() % 10000000 + 1000;

		(accounts + i)->lasEdited.day = (unsigned short)rand() % 30 + 1;
		(accounts + i)->lasEdited.month = (unsigned short)rand() % 11 + 1;
		(accounts + i)->lasEdited.year = (unsigned short)rand() % 7 + 2010;
		(accounts + i)->lasEdited.seconds = ((accounts + i)->lasEdited.day * secPerDay) +
			((accounts + i)->lasEdited.month * secPerDay * 30) + 
			((accounts + i)->lasEdited.year-2000) * secPerDay * 365;

		memcpy((accounts + i)->firstName, generateNames(fnames, name), nameLen);
		memcpy((accounts + i)->lastName, generateNames(lnames, name), nameLen);
		memcpy((accounts + i)->patronymic, generateNames(ptrs, name), nameLen);

	}

	free(name);
}

void printAccs(Account *accounts, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	printf("Id\tNum\t\t  Sum\t\tDate\t\tFull Name\n\n");
	for (int i = 0; i < arrSize; i++)
	{
		printf("%d	", (accounts + i)->id);
		printf("%llu	  ", (accounts + i)->accNum);
		printf("%lu		", (accounts + i)->fundSum);

		printf("%u.", (accounts + i)->lasEdited.day);
		printf("%u.", (accounts + i)->lasEdited.month);
		printf("%u\t", (accounts + i)->lasEdited.year);
		//printf("%lu\t", (accounts + i)->lasEdited.seconds);

		printf("%s ", (accounts + i)->firstName);
		printf("%s ", (accounts + i)->lastName);
		printf("%s		", (accounts + i)->patronymic);
		printf("\n");
	}
	printf("\n");
}

Account *scanAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	for (int i = 0; i < arrSize; i++)
	{
		if ((accounts + i)->id == id)
		{
			printf("please enter a number:\n");
			scanf("%d", &((accounts + i)->test));
			return accounts + i;
		}
	}

	return NULL;
}

void printAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	for (int i = 0; i < arrSize; i++)
	{
		if ((accounts + i)->id == id)
		{
			if ((accounts + i)->isEmpty == false)
				printf("%d \n", (accounts + i)->test);
		}
	}

	printf("account with this id doesent exist\n");
}

void clearAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0); 

	for (int i = 0; i < arrSize; i++)
	{
		if ((accounts + i)->id == id)
		{
			(accounts + id)->test = 0;
		}
	}
}

Account *searchEmptyAcc(Account **accounts, int *arrSize)
{
	int i;
	Account *mAccounts = *accounts;

	for (i = 0; i < *arrSize && (mAccounts + i)->isEmpty == false; i++);

	if (i >= *arrSize)
	{
		mAccounts = (Account *)realloc(mAccounts, (*arrSize + 1) * sizeof(Account));
		if (mAccounts)
		{
			(mAccounts + *arrSize)->id = *arrSize;                                                                 
			++*arrSize;                                                                                      
			*accounts = mAccounts;
			return (*accounts + i);
		}
		else
			return NULL;
	}
	else
		return (*accounts + i);
}

Account *searchMinValue(Account *accounts, short enter, int arrSize)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

	int index = 0;
	unsigned long long min = ULLONG_MAX;
	unsigned long min2 = ULONG_MAX;
	unsigned long min3 = ULONG_MAX;

	switch(enter)
	{
		case 1:
			
			for (int i = 0; i < arrSize; i++)
			{
				if (min >(accounts + i)->accNum)
				{
					min = (accounts + i)->accNum;
					index = i;
				}
			}
			return (accounts + index);

		case 2:
			
			for (int i = 0; i < arrSize; i++)
			{
				if (min2 >(accounts + i)->fundSum)
				{
					min2 = (accounts + i)->fundSum;
					index = i;
				}
			}
			return (accounts + index);

		case 3:

			for (int i = 0; i < arrSize; i++)
			{
				if (min3 >(accounts + i)->lasEdited.seconds)
				{
					min3 = (accounts + i)->lasEdited.seconds;
					index = i;
				}
			}
			return (accounts + index);
	}

}

Account *searchAccBy(Account *accounts, char *acc, short enter, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0); 

	long long a = atoll(acc);
	int index = 0;
	int diff = 0;

	long long minDiff = LLONG_MAX;
	long minDiff2 = LONG_MAX;

	switch (enter)
	{

	case 1:

		for (int i = 0; i < arrSize; i++)
		{
			if (!(accounts + i)->isEmpty)
			{
				if ((accounts + i)->accNum == a)
					return accounts + i;
			}
		}
		
		for (int i = 0; i < arrSize; i++)
		{
			if (!(accounts + i)->isEmpty)
			{
				diff = DIFF(a, (accounts + i)->accNum);
				if (diff < minDiff)
				{
					minDiff = diff;
					index = i;
				}
			}
		}
		return accounts + index;

	case 2:

		for (int i = 0; i < arrSize; i++)
		{
			if (!(accounts + i)->isEmpty)
			{
				if ((accounts + i)->fundSum == a)
					return accounts + i;
			}
		}

		for (int i = 0; i < arrSize; i++)
		{
			if (!(accounts + i)->isEmpty)
			{
				diff = DIFF(a, (accounts + i)->fundSum);
				if (diff < minDiff2)
				{
					minDiff2 = diff;
					index = i;
				}
			}
		}
		return accounts + index;

	case 3:

		for (int i = 0; i < arrSize; i++)
		{
			if (!(accounts + i)->isEmpty)
			{
				if ((accounts + i)->firstName == acc)
					return accounts + i;
			}
		}

	case 4:

		for (int i = 0; i < arrSize; i++)
		{
			if (!(accounts + i)->isEmpty)
			{
				if ((accounts + i)->lastName == acc)
					return accounts + i;
			}
		}

	case 5:

		for (int i = 0; i < arrSize; i++)
		{
			if (!(accounts + i)->isEmpty)
			{
				if ((accounts + i)->patronymic == acc)
					return accounts + i;
			}
		}
	}
}

void removeAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	for (int i = 0; i < arrSize; i++)
		if ((accounts + i)->id == id)
			(accounts + i)->isEmpty = true;
}

void updateAcc(Account *accounts, int arrSize, Account *acc)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	for (int i = 0; i < arrSize; i++)
		if ((accounts + i)->id == acc->id)
			memcpy(accounts + i, acc, sizeof(Account));
}

void sortAccs(Account *accounts, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);   

	for (int i = 0; i < arrSize - 1; i++)      
	{
		for (int j = 0, ret = 0; j < arrSize - 1 - i; j++)
		{
			bool needSwap = false;
			if ((accounts + j)->test > (accounts + j + 1)->test)
				needSwap = true;

			if (needSwap)
			{
				Account temp;
				memcpy(&temp, accounts + j + 1, sizeof(Account));
				memcpy(accounts + j + 1, accounts + j, sizeof(Account));
				memcpy(accounts + j, &temp, sizeof(Account));
			}
		}
	}
}

int main(int argc, char **argv)
{
	int arrSize = 10;

	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));
	
	char *acc;
	acc = "10";

	printf("Filling accounts ... ");
	fillAccs(accounts, arrSize);
	printf("Ok\n\n");
	printAccs(accounts, arrSize);

	short enter = 3;
	printf("%d \n", searchMinValue(accounts, enter, arrSize)->id);

	free(accounts);
}