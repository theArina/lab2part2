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

#define nameLen 80
#define DIFF(x, y) ((x) > (y) ? (x - y) : (y - x))

typedef struct
{
	bool isEmpty;
	int id;
	int test;
	
	unsigned long long accNum;
	unsigned long fundSum;
	SYSTEMTIME lasEdited;
	
	char firstName[nameLen];
	char lastName[nameLen];
	char patronymic[nameLen];

} Account;

char *generateNames(char *str, char *name)
{
	//char name[nameLen];
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
	srand(8);

	char fnames[] = "/Tom/Miles/Sam/Jennifer/Morty/Emma/Elizabeth/Jack/Luna/Eve/";
	char lnames[] = "/Jonas/Drake/Urie/Lerman/Toro/Way/Iero/Watson/Colby/Smith/";
	char ptrs[] = "/ /Third/Second/ / /Fifth/Fourth/ /Second/ /";
	char name[nameLen];

	for (int i = 0; i < arrSize; i++)
	{
		(accounts + i)->id = i;
		(accounts + i)->isEmpty = false;
		(accounts + i)->test = 1 + rand() % 100;
		(accounts + i)->accNum = rand() % 999*1000000 + rand() % 100000; //(1 + rand() % 1000)*(1 + rand() % 1000000)*101;
		(accounts + i)->fundSum = rand() % 10000000 + 1000;

		(accounts + i)->firstName = generateNames(fnames, name);
		//(accounts + i)->lastName = generateNames(lnames);
		//(accounts + i)->patronymic = generateNames(ptrs);
		//printf("%s\n", generateNames(lnames, name));
	}
}

void printAccs(Account *accounts, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	printf("id	test      Num		  Sum\n\n");
	for (int i = 0; i < arrSize; i++)
	{
		printf("%d	", (accounts + i)->id);
		printf("%d	", (accounts + i)->test);
		printf("%d	  ", (accounts + i)->accNum);
		printf("%d	", (accounts + i)->fundSum);
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

Account *searchMinValue(Account *accounts, int fieldShift, int fieldSize, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0); 

	int index = 0;
	byte buffer[256];
	memset(buffer, 0xff, 256);
	void *min = buffer;
	
	for (int i = 0, ret = 0; i < arrSize; i++)
	{
		ret = memcmp((byte*)(accounts + i) + fieldShift, min, fieldSize);
		if (ret < 0)
		{
			memcpy(min, (byte*)(accounts + i) + fieldShift, fieldSize);
			index = i;
		}
	}
	return (accounts + index);
}

Account *searchAccBy(Account *accounts, char *acc, int fieldShift, int fieldSize, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0); 

	for (int i = 0, ret; i < arrSize; i++)
	{
		if (!(accounts + i)->isEmpty)
		{
			ret = memcmp(&(accounts + i)->isEmpty + fieldShift, &acc, fieldSize);
			if (ret == 0)
				return accounts + i;
		}
	}

	long long a = atoll(acc);
	
	long long minDiff = LLONG_MAX;
	int index = 0, diff = 0;

	for (int i = 0; i < arrSize; i++)
	{
		if (!(accounts + i)->isEmpty)
		{
			diff = DIFF(a, *(byte*)(accounts + i) + fieldShift);		//тут
			if (diff < minDiff)
			{
				minDiff = diff;
				index = i;
			}
		}
	}
	return accounts + index;
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

void sortAccs(Account *accounts, int fieldShift, int fieldSize, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);   

	for (int i = 0; i < arrSize - 1; i++)      
	{
		for (int j = 0, ret = 0; j < arrSize - 1 - i; j++)
		{
			bool needSwap = false;
			ret = memcmp(&(accounts + j)->isEmpty + fieldShift, &(accounts + j + 1)->isEmpty + fieldShift, fieldSize);
			if (ret > 0)
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

	//printf("%d\n", searchMinValue(accounts, sizeof(bool) + sizeof(int), sizeof(int), arrSize)->id);
	//printf("%d\n", searchAccBy(accounts, acc, sizeof(bool) + sizeof(int), sizeof(int), arrSize)->id);
	printf("%d\n", *((int*)(accounts + 2) + sizeof(bool) + sizeof(int)));

	free(accounts);
}