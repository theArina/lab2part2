#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#define nameLen 20

typedef struct
{
	unsigned short day;
	unsigned short month;
	unsigned short year;
	unsigned long seconds;

}Date;

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

}Account;

char* generateNames(char *, char *);

unsigned long secondsSince(Account *);

void fillAccs(Account *, int);

int inFileAcc(Account *, int, int);

void inFileAccs(Account *, int);

bool printAcc(Account *, int , int);

void printAccs(Account *, int);

char* reverse(char *);

char* combineStr(char *, ...);

int compareStrs(char *, char *);

bool searchAcc(Account *, int);

Account* searchEmptyAcc(Account **, int *);

Account* searchMinValue(Account *, int);

void scanAcc(Account *);

void addAcc(Account *, int *);

bool clearAcc(Account *, int , int);

bool removeAcc(Account *, int , int);

bool updateAcc(Account *, int , int);

void sortAccsBy(Account *, int);

int menu(Account *, int *);