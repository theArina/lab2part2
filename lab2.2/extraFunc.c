#include "Header.h"
#include <assert.h>

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

void moveInFile(FILE **ptrFile, char temp, int *j)
{
	fscanf(*ptrFile, "%c", temp);

	while(temp != ' ') 
	{
		*j++;
		fseek(*ptrFile, *j, SEEK_SET);
		fscanf(*ptrFile, "%c", temp);
	} 

	while (temp == ' ')
	{
		*j++;
		fscanf(*ptrFile, "%c", temp);
		fseek(*ptrFile, *j, SEEK_SET);
	}
}

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