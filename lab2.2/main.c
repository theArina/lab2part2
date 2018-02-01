#include "Header.h"

int main(int argc, char **argv)
{
	FILE * f = fopen("accounts.txt", "r");
	int arrSize = 0;
	fscanf(f, "%d", &arrSize);
	fclose(f);

	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	readFileAccs(accounts, arrSize);
	//menu(accounts, &arrSize);

	_getch();
	free(accounts);
	return 0;
}