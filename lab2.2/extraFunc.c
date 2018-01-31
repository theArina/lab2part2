#include "Header.h"

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