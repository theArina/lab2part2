#pragma once
#include <windows.h>
#include <stdio.h>
#define nameLen 20

struct Date
{
	unsigned short day;
	unsigned short month;
	unsigned short year;
	unsigned long seconds;

};

struct Account
{
	bool isEmpty;
	int id;

	unsigned long long accNum;
	unsigned long fundSum;
	Date lasEdited;

	char firstName[nameLen];
	char lastName[nameLen];
	char patronymic[nameLen];

};

char* generateNames(char *, char *);
unsigned long secondsSince(Account *);
void fillAccs(Account *, int);
int printAcc(Account *, int , int);
void printAccs(Account *, int);
char* reverse(char *);
char* combineStr(char *, ...);
int compareStrs(char *, char *);
int searchAcc(Account *, int);
Account* searchEmptyAcc(Account **, int *);
Account* searchMinValue(Account *, int);
void scanAcc(Account *);
void addAcc(Account *, int *);
int clearAcc(Account *, int , int);
int removeAcc(Account *, int , int);
int updateAcc(Account *, int , int);
void sortAccsBy(Account *, int);
int menu(Account *, int *);