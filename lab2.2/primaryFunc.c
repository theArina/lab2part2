//Часть 2, лаба 2, вариант 2.
//Фамилия И.О., номер счета, сумма на счете, дата последнего изменения.
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
*/

#include "Header.h"
#include <time.h>

int writeFile(Account *accounts, int arrSize, int id)
{
	FILE * ptrFile = fopen("accounts.txt", "a+");

	if ((accounts + id)->isEmpty == true)
		return 1;

	for (int i = 0; i < arrSize; i++)
	{
		if ((accounts + i)->id == id)
		{
			if ((accounts + i)->isEmpty == false)
			{
				fprintf(ptrFile, " %d  ", (accounts + i)->id);
				fprintf(ptrFile, "%llu\t", (accounts + i)->accNum);
				fprintf(ptrFile, "%lu\t", (accounts + i)->fundSum);

				fprintf(ptrFile, "%u.", (accounts + i)->lasEdited.day);
				fprintf(ptrFile, "%u.", (accounts + i)->lasEdited.month);
				fprintf(ptrFile, "%u\t", (accounts + i)->lasEdited.year);

				fprintf(ptrFile, "%s ", (accounts + i)->firstName);
				fprintf(ptrFile, "%s ", (accounts + i)->lastName);
				fprintf(ptrFile, "%s\n", (accounts + i)->patronymic);
			}
		}
	}	

	fclose(ptrFile);
	return 0;
}

int readFileAccs(Account *accounts, int arrSize)
{
	FILE * ptrFile = fopen("accounts.txt", "r");

	if (feof(ptrFile) != 0)
		return 1;

	char temp = ' ';
	int j = 0;

	for (int i = 0; i < arrSize; i++)
	{
		moveInFile(&ptrFile, temp);
		fscanf(ptrFile, "%llu", &(accounts + i)->accNum);

		moveInFile(&ptrFile, temp);
		fscanf(ptrFile, "%lu", &(accounts + i)->fundSum);

		moveInFile(&ptrFile, temp);
		fscanf(ptrFile, "%hu", &(accounts + i)->lasEdited.day);

		moveInFile(&ptrFile, temp);
		fscanf(ptrFile, "%hu", &(accounts + i)->lasEdited.month);

		moveInFile(&ptrFile, temp);
		fscanf(ptrFile, "%hu", &(accounts + i)->lasEdited.year);

		moveInFile(&ptrFile, temp);
		fscanf(ptrFile, "%s", &(accounts + i)->firstName);

		moveInFile(&ptrFile, temp);
		fscanf(ptrFile, "%s", &(accounts + i)->lastName);

		moveInFile(&ptrFile, temp);
		fscanf(ptrFile, "%s", &(accounts + i)->patronymic);

		(accounts + i)->lasEdited.seconds = secondsSince(accounts + i);
	}

	fclose(ptrFile);
	return 0;
}

bool printAcc(Account *accounts, int arrSize, int id)
{
	bool flag = false;
	for (int i = 0; i < arrSize; i++)
	{
		if ((accounts + i)->id == id)
		{
			if ((accounts + i)->isEmpty == false)
			{
				printf(" %d	", (accounts + i)->id);
				printf("%llu	  ", (accounts + i)->accNum);
				printf("%lu		", (accounts + i)->fundSum);

				printf("%hu.", (accounts + i)->lasEdited.day);
				printf("%hu.", (accounts + i)->lasEdited.month);
				printf("%hu\t", (accounts + i)->lasEdited.year);

				printf("%s ", (accounts + i)->firstName);
				printf("%s ", (accounts + i)->lastName);
				printf("%s		", (accounts + i)->patronymic);
				printf("\n");
				flag = true;
			}
		}
	}

	return !flag;
}

void printAccs(Account *accounts, int arrSize)
{
	printf("\n Id\tAccount number\t  Sum\t\tDate\t\tFull name\n\n");
	for (int i = 0; i < arrSize; i++)
		printAcc(accounts, arrSize, (accounts + i)->id);
	printf("\n");
}

bool searchAcc(Account *accounts, int arrSize)
{
	char acc[50];
	printf("\n\t ");
	scanf("%s", &acc);
	printf("\n");

	bool flag = false;
	char *temp = (char*)malloc(sizeof(char) * 50);
	char *tempName = (char*)malloc(sizeof(char) * nameLen * 3);

	for (int i = 0; i < arrSize; i++)
	{
		if (!(accounts + i)->isEmpty)
		{
			int id = (accounts + i)->id;
			if (strstr(reverse(_ultoa(id, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			unsigned long long num = (accounts + i)->accNum;
			if (strstr(reverse(_ultoa(num, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			unsigned long sum = (accounts + i)->fundSum;
			if (strstr(reverse(_ultoa(sum, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			unsigned short date = (accounts + i)->lasEdited.day;
			if (strstr(reverse(_ultoa(date, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			date = (accounts + i)->lasEdited.month;
			if (strstr(reverse(_ultoa(date, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			date = (accounts + i)->lasEdited.year;
			if (strstr(reverse(_ultoa(date, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}

			if (strstr(combineStr(tempName, (accounts + i)->firstName,
				(accounts + i)->lastName, (accounts + i)->patronymic, 0), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
		}
	}
	free(temp);
	free(tempName);

	return !flag;
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
		return (*accounts + i);
}

Account* searchMinValue(Account *accounts, int arrSize)
{
	printf("\n\t ");
	int field = 0;
	scanf("%d", &field);
	printf("\n");

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
	printf("\n\t enter account number: ");
	scanf("%llu", &acc->accNum);
	printf("\t enter sum of fund: ");
	scanf("%lu", &acc->fundSum);

	printf("\t enter day: ");
	scanf("%hu", &acc->lasEdited.day);
	printf("\t enter month: ");
	scanf("%hu", &acc->lasEdited.month);
	printf("\t enter year: ");
	scanf("%hu", &acc->lasEdited.year);
	acc->lasEdited.seconds = secondsSince(acc);

	printf("\t enter name: ");
	scanf("%s", &acc->firstName);
	printf("\t enter surname: ");
	scanf("%s", &acc->lastName);
	printf("\t enter patronymic: ");
	scanf("%s", &acc->patronymic);
	printf("\n");
}

void addAcc(Account *accounts, int *arrSize)
{
	Account *acc = searchEmptyAcc(&accounts, arrSize);

	acc->isEmpty = false;

	scanAcc(acc);
}

bool clearAcc(Account *accounts, int arrSize, int id)
{
	bool flag = false;
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

			memcpy((accounts + id)->firstName, "\0", 1);
			memcpy((accounts + id)->lastName, "\0", 1);
			memcpy((accounts + id)->patronymic, "\0", 1);
			flag = true;
		}
	}

	return !flag;
}

bool removeAcc(Account *accounts, int arrSize, int id)
{
	bool flag = false;
	for (int i = 0; i < arrSize; i++)
		if ((accounts + i)->id == id)
		{
			(accounts + i)->isEmpty = true;
			flag = true;
		}

	return !flag;
}

bool updateAcc(Account *accounts, int arrSize, int id)
{
	bool flag = false;
	for (int i = 0; i < arrSize; i++)
		if ((accounts + i)->id == id)
		{
			scanAcc(accounts + i);
			flag = true;
		}

	return !flag;
}

void sortAccsBy(Account *accounts, int arrSize)
{
	printf("\n\t "); 
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
			case 4:

				if(compareStrs((accounts + j)->firstName, (accounts + j + 1)->firstName) == 0)
					needSwap = true;
				break;
			case 5:

				if (compareStrs((accounts + j)->lastName, (accounts + j + 1)->lastName) == 0)
					needSwap = true;
				break; 
			case 6:

					if (compareStrs((accounts + j)->patronymic, (accounts + j + 1)->patronymic) == 0)
						needSwap = true;
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