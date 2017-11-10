/*Ëàáà 2, ÷àñòü 2, âàðèàíò 2. 
Ôàìèëèÿ È.Î., íîìåð ñ÷åòà, ñóììà íà ñ÷åòå, äàòà ïîñëåäíåãî èçìåíåíèÿ.*/
/*
1 - ââîä ýëåìåíòîâ(ïîëåé) ñòðóêòóðû +
2 - âûâîä +
3 - «î÷èñòêà» ñòðóêòóðèðîâàííûõ ïåðåìåííûõ +
4 - ïîèñê ñâîáîäíîé ñòðóêòóðèðîâàííîé ïåðåìåííîé +
5 - ïîèñê â ìàññèâå ñòðóêòóðû è ìèíèìàëüíûì çíà÷åíèåì çàäàííîãî ïîëÿ
6 - ïîèñê â ìàññèâå ñòðóêòóð ýëåìåíòà ñ çàäàííûì çíà÷åíèåì ïîëÿ èëè ñ íàèáîëåå áëèçêèì ê íåìó ïî çíà÷åíèþ
7 - óäàëåíèå çàäàííîãî ýëåìåíòà
8 - èçìåíåíèå(ðåäàêòèðîâàíèå) çàäàííîãî ýëåìåíòà
9 - ñîðòèðîâêà ìàññèâà ñòðóêòóð â ïîðÿäêå âîçðàñòàíèÿ çàäàííîãî ïîëÿ
	(ïðè ñîðòèðîâêå ìîæíî èñïîëüçîâàòü òîò ôàêò, ÷òî â Ñè++ ðàçðåøàåòñÿ ïðèñâàèâàíèå ñòðóêòóðèðîâàííûõ ïåðåìåííûõ)
10 - âû÷èñëåíèå ñ ïðîâåðêîé è èñïîëüçîâàíèåì âñåõ ýëåìåíòîâ ìàññèâà ïî çàäàííîìó óñëîâèþ è ôîðìóëå
	(íàïðèìåð, îáùàÿ ñóììà íà âñåõ ñ÷åòàõ) - äàåòñÿ èíäèâèäóàëüíî 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int test;
	
} Account;

void fillAcc(Account *accounts, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
		(accounts + i)->test = 1+rand()%100;
}

void printArrayTest(Account *accounts, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
		printf("%d ", (accounts + i)->test);
	printf("\n\n");
}

void scanAcc(Account *accounts, int id)
{
	printf("please type a number:\n");
	scanf("%d", &(accounts + id)->test);
}

void printAcc(Account *accounts, int id)
{
	if ((accounts + id)->test != 0)
		printf("%d \n", (accounts + id)->test);
	else
		printf("account with this id doesent exist\n");
}

void clearingAcc(Account *accounts, int id, int arrSize)
{
	if (id < arrSize)
		(accounts + id)->test = 0;
}

void searchFreePlace(Account *accounts, int arrSize, int *acc)
{
	int i;
	for (i = 0; i < arrSize && (accounts + i)->test != 0; i++); 
	if ((accounts + i)->test == 0)
		(accounts + i)->test = *acc;
	else
		printf("there is no free places\n");
	
}

void main()
{
	int arrSize = 20;
	int id = 0;
	int acc = 1999;
	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	printf("enter id: \n");
	scanf("%d", &id);

	fillAcc(accounts, arrSize);
	printArrayTest(accounts, arrSize);
	searchFreePlace(accounts, arrSize, &acc);
	printArrayTest(accounts, arrSize);

	free(accounts);
}
