#include "Header.h"

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
	printf("\t 10. upload account from the file\n");
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
		if (printAcc(accounts, *arrSize, id))
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
		if (updateAcc(accounts, *arrSize, id))
			printf("\n\t account with this id doesn't exist\n");
		printf("\n\t the account data has been changed successfully\n");
		break;

	case 5:
		printf("\n\t you selected to erase all account data");
		printf("\n\t enter id: ");
		scanf("%d", &id);
		if (clearAcc(accounts, *arrSize, id))
			printf("\n\t account with this id doesn't exist\n");
		printf("\n\t all the account data has been removed successfully\n");
		break;

	case 6:
		printf("\n\t you selected to close an account");
		printf("\n\t enter id: ");
		scanf("%d", &id);
		if (removeAcc(accounts, *arrSize, id))
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

	/*case 10:
		printf("\n\t upload account from the file");
		printf("\n\t enter id: ");
		scanf("%d", &id);
		if (addFileAcc(accounts, *arrSize, id))
			printf("\n\t there is no account with this id in the file\n");
		printAcc(accounts, *arrSize, id);
		break;*/

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