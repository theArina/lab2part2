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

#define nameLen 20

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
	
	unsigned long long accNum;
	unsigned long fundSum;
	Date lasEdited;
	
	char firstName[nameLen];
	char lastName[nameLen];
	char patronymic[nameLen];

} Account;

char* generateNames(char *str, char *name)
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

unsigned long secondsSince(Account *i)
{
	int secPerDay = 24 * 60 * 60;
	return ((i->lasEdited.day * secPerDay) +
		(i->lasEdited.month * secPerDay * 30) +
		(i->lasEdited.year - 2000) * secPerDay * 365);
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

	for (int i = 0; i < arrSize; i++)
	{
		(accounts + i)->id = i;
		(accounts + i)->isEmpty = false;
		(accounts + i)->accNum = (unsigned long long)rand() % 9999 * 1000000 + rand() % 100000;
		(accounts + i)->fundSum = (unsigned long)rand() % 10000000 + 1000;

		(accounts + i)->lasEdited.day = (unsigned short)rand() % 30 + 1;
		(accounts + i)->lasEdited.month = (unsigned short)rand() % 11 + 1;
		(accounts + i)->lasEdited.year = (unsigned short)rand() % 7 + 2010;
		(accounts + i)->lasEdited.seconds = secondsSince(accounts + i);

		memcpy((accounts + i)->firstName, generateNames(fnames, name), nameLen); 
		memcpy((accounts + i)->lastName, generateNames(lnames, name), nameLen);
		memcpy((accounts + i)->patronymic, generateNames(ptrs, name), nameLen); 
	}

	free(name);
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
			{
				printf(" %d	", (accounts + i)->id);
				printf("%llu	  ", (accounts + i)->accNum);
				printf("%lu		", (accounts + i)->fundSum);

				printf("%u.", (accounts + i)->lasEdited.day);
				printf("%u.", (accounts + i)->lasEdited.month);
				printf("%u\t", (accounts + i)->lasEdited.year);

				printf("%s ", (accounts + i)->firstName);
				printf("%s ", (accounts + i)->lastName);
				printf("%s		", (accounts + i)->patronymic);
				printf("\n");
			}
		}
	}
}

void printAccs(Account *accounts, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	printf(" Id\tAccount number\t  Sum\t\tDate\t\tFull name\n\n");
	for (int i = 0; i < arrSize; i++)
		printAcc(accounts, arrSize, (accounts + i)->id);
	printf("\n");
}

char* myItoa(char *temp, int n)
{
	int j = 0;
	do {
		temp[j++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	temp[j] = '\0';

	return temp;
}

char* reverse(char *temp)
{
	for (int y = 0, c = 0, j = strlen(temp) - 1; y < j; y++, j--)
	{
		c = temp[y];
		temp[y] = temp[j];
		temp[j] = c;
	}

	return temp;
}

int compareStr(char *temp, char *acc)
{
	for (int p = 0; temp[p] != '\0'; p++)
	{
		int j = 0;
		for (; acc[j] != '\0' && temp[j + p] != '\0' && temp[j + p] == acc[j]; j++);
		if (acc[j] == '\0')
			return 0;
	}
	return 1;
}

void searchAcc(Account *accounts, int arrSize)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

	char acc[50] = "To";
	printf("enter data: ");
	scanf("%s", &acc);

	char *temp = (char*)malloc(sizeof(char) * 50);

	for (int i = 0; i < arrSize; i++)
	{
		if (!(accounts + i)->isEmpty)
		{
			int id = (accounts + i)->id;
			if (compareStr(reverse(myItoa(temp, id)), acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			unsigned long long num = (accounts + i)->accNum;
			if (compareStr(reverse(myItoa(temp, num)), acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			unsigned long sum = (accounts + i)->fundSum;
			if (compareStr(reverse(myItoa(temp, sum)), acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			unsigned short date = (accounts + i)->lasEdited.day;
			if (compareStr(reverse(myItoa(temp, date)), acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			date = (accounts + i)->lasEdited.month;
			if (compareStr(reverse(myItoa(temp, date)), acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			date = (accounts + i)->lasEdited.year;
			if (compareStr(reverse(myItoa(temp, date)), acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			if (compareStr((accounts + i)->firstName, acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			if (compareStr((accounts + i)->lastName, acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			if (compareStr((accounts + i)->patronymic, acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
		}
	}
	free(temp);
}

Account* searchEmptyAcc(Account **accounts, int *arrSize)
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
	{
		return (*accounts + i);
	}
}

Account* searchMinValue(Account *accounts, int arrSize)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

	int field = 0;
	scanf("%d", &field);

	int index = 0;
	unsigned long long min = ULLONG_MAX;
	unsigned long min2 = ULONG_MAX;
	unsigned long min3 = ULONG_MAX;

	for (int i = 0; i < arrSize; i++)
	{
		switch (field)
		{
		case 1:

			if (min > (accounts + i)->accNum)
			{
				min = (accounts + i)->accNum;
				index = i;
			}
			break;

		case 2:

			if (min2 > (accounts + i)->fundSum)
			{
				min2 = (accounts + i)->fundSum;
				index = i;
			}
			break;
		case 3:

			if (min3 > (accounts + i)->lasEdited.seconds)
			{
				min3 = (accounts + i)->lasEdited.seconds;
				index = i;
			}
			break;
		}
	}
	return (accounts + index);
}

void scanAcc(Account *acc)
{
	printf("enter account number: ");
	scanf("%llu", &acc->accNum);
	printf("enter sum of fund: ");
	scanf("%lu", &acc->fundSum);

	printf("enter day: ");
	scanf("%hu", &acc->lasEdited.day);
	printf("enter month: ");
	scanf("%hu", &acc->lasEdited.month);
	printf("enter year: ");
	scanf("%hu", &acc->lasEdited.year);
	acc->lasEdited.seconds = secondsSince(acc);

	printf("enter name: ");
	scanf("%s", &acc->firstName);
	printf("enter surname: ");
	scanf("%s", &acc->lastName);
	printf("enter patronymic: ");
	scanf("%s", &acc->patronymic);
	printf("\n");
}

void addAcc(Account *accounts, int *arrSize)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

	Account *acc = searchEmptyAcc(&accounts, arrSize);

	acc->isEmpty = false;

	scanAcc(acc);
}

void clearAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

	for (int i = 0; i < arrSize; i++)
	{
		if ((accounts + i)->id == id)
		{
			(accounts + id)->accNum = 0;
			(accounts + id)->fundSum = 0;
			(accounts + id)->lasEdited.day = 0;
			(accounts + id)->lasEdited.month = 0;
			(accounts + id)->lasEdited.year = 0;
			(accounts + id)->lasEdited.seconds = 0;
			memcpy((accounts + id)->firstName, "0", 1);
			memcpy((accounts + id)->lastName, "0", 1);
			memcpy((accounts + id)->patronymic, "0", 1);
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

void updateAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	for (int i = 0; i < arrSize; i++)
		if ((accounts + i)->id == id)
			scanAcc(accounts + i);	
}

void sortAccsBy(Account *accounts, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);   

	int field = 0;
	scanf("%d", &field);

	for (int i = 0; i < arrSize - 1; i++)
	{
		for (int j = 0; j < arrSize - 1 - i; j++)
		{
			bool needSwap = false;
			switch (field)
			{
			case 0:

				if ((accounts + j)->id > (accounts + j + 1)->id)
					needSwap = true;
				break;
			case 1:

				if ((accounts + j)->accNum > (accounts + j + 1)->accNum)
					needSwap = true;
				break;
			case 2:

				if ((accounts + j)->fundSum > (accounts + j + 1)->fundSum)
					needSwap = true;
				break;
			case 3:

				if ((accounts + j)->lasEdited.seconds > (accounts + j + 1)->lasEdited.seconds)
					needSwap = true;
				break;
			default:
				break;
			}

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

void menu(Account *accounts, int *arrSize)
{
	printf("\t please, write a number to select an option\n\n");
	printf("\t 1. show all accounts\n");
	printf("\t 2. show account\n"); 
	printf("\t 3. create new account\n");
	printf("\t 4. edit account\n");
	printf("\t 5. erase all account data\n");
	printf("\t 6. close an account\n");
	printf("\t 7. sort accounts\n");
	printf("\t 8. find the minimum value\n");
	printf("\t 9. search account\n");
	printf("\t 0. exit\n\n");

	int in = 0;
	printf("\t ");
	scanf("%d", &in);
	int id = 0;
	system("cls");

	switch (in)
	{
	case 1:
		printAccs(accounts, *arrSize);
		break;

	case 2:
		printf("\t ");
		scanf("%d", &id);
		printAcc(accounts, *arrSize, id);
		break;

	case 3:
		addAcc(accounts, arrSize);
		break;

	case 4:
		printf("\t ");
		scanf("%d", &id);
		updateAcc(accounts, *arrSize, id);
		break;

	case 5:
		printf("\t ");
		scanf("%d", &id);
		clearAcc(accounts, *arrSize, id);
		break;

	case 6:
		printf("\t ");
		scanf("%d", &id);
		removeAcc(accounts, *arrSize, id);
		break;

	case 7:
		sortAccsBy(accounts, *arrSize);
		break;

	case 8:
		searchMinValue(accounts, *arrSize);
		break;

	case 9:
		searchAcc(accounts, *arrSize);
		break;

	case 0:
		break;
	}
	
	printf("\t 1. back to menu\n");
	printf("\t 0. exit\n\n");

	int in2 = 0;
	printf("\t ");
	scanf("%d", &in2);
	system("cls");

	switch (in2)
	{
	case 1:
		menu(accounts, arrSize);

	case 0:
		break;
	}
}

int main(int argc, char **argv)
{
	int arrSize = 10;
	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	printf("Filling accounts ... ");
	fillAccs(accounts, arrSize);
	printf("Ok\n\n");
	printAccs(accounts, arrSize);
	searchAcc(accounts, arrSize);
	//menu(accounts, &arrSize);
	
	free(accounts);
	return 0;
}