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
				printf("%d	", (accounts + i)->id);
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

	printf("Id\tNum\t\t  Sum\t\tDate\t\tFull Name\n\n");
	for (int i = 0; i < arrSize; i++)
		printAcc(accounts, arrSize, (accounts + i)->id);
	printf("\n");
}

void reverse(char *temp)
{
	for (int y = 0, c = 0, j = strlen(temp) - 1; y < j; y++, j--)
	{
		c = temp[y];
		temp[y] = temp[j];
		temp[j] = c;
	}
}

int compareStr(char *temp, char *acc)
{
	int dif = strlen(temp) - strlen(acc);
	for (int j = 0; j >= dif; j++)
	{
		for (int y = 0; y < strlen(acc) && temp[y] == acc[y]; y++)
			if (y == strlen(acc))
				return 0;
	}
	return 1;
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

Account* searchMinValue(Account *accounts, short field, int arrSize)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

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

void searchAcc(Account *accounts, int arrSize) 
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0); 

	char acc[50] = "1";/*
	printf("enter data: ");
	scanf("%s", &acc);*/

	for (int i = 0; i < arrSize; i++)
	{
		if (!(accounts + i)->isEmpty)
		{
			char temp[20];
			int j = 0;
			do {
				temp[j++] = (accounts + i)->id % 10 + '0'; // тут конвертируем 
			} while (((accounts + i)->id /= 10) > 0);	   // в перевернутую строку
			temp[j] = '\0';
			reverse(temp);								   // собственно, переворачиваем
			if(compareStr(temp, acc) == 0)				   // тут вроде как ищем подстроку acc в строке temp, типа приблизительное значение
			{											   // и если нашли, то возвращаем 0, если нет 1 в функции compareStr
				printAcc(accounts, arrSize, i);			   // печатаем, ну, потому что так тоже пока сойдет, я понимаю что не надо так
				//continue;								   // там дальше делаем это со всеми полями и, если есть хоть одно совпадение,
			}											   // печатаем всю структуру и продолжаем идти по массиву структур
/*
			do {
				temp[j++] = (accounts + i)->accNum % 10 + '0';
			} while (((accounts + i)->accNum /= 10) > 0);
			temp[j] = '\0';
			reverse(temp);
			if (compareStr(temp, acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}

			do {
				temp[j++] = (accounts + i)->fundSum % 10 + '0';
			} while (((accounts + i)->fundSum /= 10) > 0);
			temp[j] = '\0';
			reverse(temp);
			if (compareStr(temp, acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}

			do {
				temp[j++] = (accounts + i)->lasEdited.day % 10 + '0';
			} while (((accounts + i)->lasEdited.day /= 10) > 0);
			temp[j] = '\0';
			reverse(temp);
			if (compareStr(temp, acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			
			do {
				temp[j++] = (accounts + i)->lasEdited.month % 10 + '0';
			} while (((accounts + i)->lasEdited.month /= 10) > 0);
			temp[j] = '\0';
			reverse(temp);
			if (compareStr(temp, acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}
			
			do {
				temp[j++] = (accounts + i)->lasEdited.year % 10 + '0';
			} while (((accounts + i)->lasEdited.year /= 10) > 0);
			temp[j] = '\0';
			reverse(temp);
			if (compareStr(temp, acc) == 0)
			{
				printAcc(accounts, arrSize, i);
				continue;
			}*/
		}
	}
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

void sortAccsBy(Account *accounts, short field, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);   

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

int main(int argc, char **argv)
{
	int arrSize = 10;
	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	printf("Filling accounts ... ");
	fillAccs(accounts, arrSize);
	printf("Ok\n\n");
	printAccs(accounts, arrSize);
	
	searchAcc(accounts, arrSize);

	free(accounts);
	return 0;
}