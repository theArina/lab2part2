#include "Header.h"

int main(int argc, char **argv)
{
	int arrSize = 10;
	Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	printf("Filling accounts ... ");
	fillAccs(accounts, arrSize);
	printf("Ok\n\n");

	menu(accounts, &arrSize);
	//inFileAccs(accounts, arrSize);

	free(accounts);
	return 0;
}