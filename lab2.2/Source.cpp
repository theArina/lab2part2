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

	srand(0);

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

int printAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

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

				printf("%u.", (accounts + i)->lasEdited.day);
				printf("%u.", (accounts + i)->lasEdited.month);
				printf("%u\t", (accounts + i)->lasEdited.year);

				printf("%s ", (accounts + i)->firstName);
				printf("%s ", (accounts + i)->lastName);
				printf("%s		", (accounts + i)->patronymic);
				printf("\n");
				flag = true;
			}
		}
	}
	if (!flag)
		return 1;
	return 0;
}

void printAccs(Account *accounts, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	printf("\n Id\tAccount number\t  Sum\t\tDate\t\tFull name\n\n");
	for (int i = 0; i < arrSize; i++)
		printAcc(accounts, arrSize, (accounts + i)->id);
	printf("\n");
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

char* combineStr(char *str, ...)
{
	char **p = &str;
	*p++;
	int i;

	for (i = 0; *p != 0; *p++)
	{
		memcpy(&str[i], *p, strlen(*p));
		i += strlen(*p);
		str[i++] = ' ';
	}

	str[i] = '\0';
	return str;
}

int compareStrs(char *str, char *str2)
{
	int y;
	for (y = 0; str[y] == str2[y] && str[y] != '\0' && str2[y] != '\0'; y++);
	if (str[y] > str2[y] || (str[y] != '\0' && str2[y] == '\0'))
		return 0;
	return 1;
}

int searchAcc(Account *accounts, int arrSize)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

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
			if (strstr(reverse(ultoa(id, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			unsigned long long num = (accounts + i)->accNum;
			if (strstr(reverse(ultoa(num, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			unsigned long sum = (accounts + i)->fundSum;
			if (strstr(reverse(ultoa(sum, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			unsigned short date = (accounts + i)->lasEdited.day;
			if (strstr(reverse(ultoa(date, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			date = (accounts + i)->lasEdited.month;
			if (strstr(reverse(ultoa(date, temp, 10)), acc) != NULL)
			{
				printAcc(accounts, arrSize, i);
				flag = true;
				continue;
			}
			date = (accounts + i)->lasEdited.year;
			if (strstr(reverse(ultoa(date, temp, 10)), acc) != NULL)
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

	if (!flag)
		return 1;
	return 0;
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
	assert(accounts != NULL);
	assert(arrSize > 0);

	Account *acc = searchEmptyAcc(&accounts, arrSize);

	acc->isEmpty = false;

	scanAcc(acc);
}

int clearAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);
	assert(arrSize > 0);

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
			memcpy((accounts + id)->firstName, "0", 1);
			memcpy((accounts + id)->lastName, "0", 1);
			memcpy((accounts + id)->patronymic, "0", 1);
			flag = true;
		}
	}
	if (!flag)
		return 1;
	return 0;
}

int removeAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	bool flag = false;
	for (int i = 0; i < arrSize; i++)
		if ((accounts + i)->id == id)
		{
			(accounts + i)->isEmpty = true;
			flag = true;
		}
	if (!flag)
		return 1;
	return 0;
}

int updateAcc(Account *accounts, int arrSize, int id)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);

	bool flag = false;
	for (int i = 0; i < arrSize; i++)
		if ((accounts + i)->id == id)
		{
			scanAcc(accounts + i);
			flag = true;
		}
	if (!flag)
		return 1;
	return 0;
}

void sortAccsBy(Account *accounts, int arrSize)
{
	assert(accounts != NULL);                                                                                     
	assert(arrSize > 0);   

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

int menu(Account *accounts, int *arrSize)
{
	printf("\n\t please, write a number to select an option\n\n");
	printf("\t 1. show all accounts\n");
	printf("\t 2. show account\n"); 
	printf("\t 3. create new account\n");
	printf("\t 4. edit account\n");
	printf("\t 5. erase all account data\n");
	printf("\t 6. close an account\n");
	printf("\t 7. sort accounts\n");
	printf("\t 8. find the minimum value\n");
	printf("\t 9. find an account\n");
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
		printf("\n\t you selected to show an account");
		printf("\n\t enter id: ");
		scanf("%d", &id);
		printf("\n");
		if(printAcc(accounts, *arrSize, id))
			printf("\n\t account with this id doesn't exist\n");
		break;

	case 3:
		printf("\n\t you selected to create a new account");
		addAcc(accounts, arrSize);
		printf("\n\t the account has been created successfully\n");
		break;

	case 4:
		printf("\n\t you selected to edit account");
		printf("\n\t enter id: ");
		scanf("%d", &id);
		if(updateAcc(accounts, *arrSize, id))
			printf("\n\t account with this id doesn't exist\n");
		printf("\n\t the account data has been changed successfully\n");
		break;

	case 5:
		printf("\n\t you selected to erase all account data");
		printf("\n\t enter id: ");
		scanf("%d", &id);
		if(clearAcc(accounts, *arrSize, id))
			printf("\n\t account with this id doesn't exist\n");
		printf("\n\t all the account data has been removed successfully\n");
		break;

	case 6:
		printf("\n\t you selected to close an account");
		printf("\n\t enter id: ");
		scanf("%d", &id);
		if(removeAcc(accounts, *arrSize, id))
			printf("\n\t account with this id doesn't exist\n");
		printf("\n\t the account has been closed successfully\n");
		break;

	case 7:
		printf("\n\t you selected to sort accounts");
		printf("\n\t write a number to select by which data you want to sort\n\n");
		printf("\t 0. Id\n");
		printf("\t 1. Account number\n");
		printf("\t 2. Sum of fund\n");
		printf("\t 3. Date\n");
		printf("\t 4. First name\n");
		printf("\t 5. Last name\n");
		printf("\t 6. Patronymic\n");

		sortAccsBy(accounts, *arrSize); 
		printAccs(accounts, *arrSize);
		break;

	case 8:
		printf("\n\t you selected to find the minimum value");
		printf("\n\t write a number to select in which data\n\n");
		printf("\t 0. Id\n");
		printf("\t 1. Account number\n");
		printf("\t 2. Sum of fund\n");
		printf("\t 3. Date\n");

		printAcc(accounts, *arrSize, searchMinValue(accounts, *arrSize)->id);
		break;

	case 9:
		printf("\n\t you selected to find an account");
		printf("\n\t enter data: \n");
		if (searchAcc(accounts, *arrSize))
			printf("\t no matches found\n");
		break;

	case 0:
		system("cls");
		return 0;
	}

	printf("\n");
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
		system("cls");
		return 0;
	}
}

int main(int argc, char **argv)
{
	int arrSize = 10;
	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	printf("Filling accounts ... ");
	fillAccs(accounts, arrSize);
	printf("Ok\n\n");
	//printAcc(accounts, arrSize);
	menu(accounts, &arrSize);
	
	free(accounts);
	return 0;
}