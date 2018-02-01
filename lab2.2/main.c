#include "Header.h"

int main(int argc, char **argv)
{
	FILE * f = fopen("accounts.txt", "r");
	char temp[200];
	int i = 0, j = 0;

	fscanf(f, "%s", temp);
	printf("%s\n", temp);

	fseek(f, 93, SEEK_SET);

	fscanf(f, "%s", temp);
	//while (temp != EOF)
	//{
	//	if (temp == '\n')
	//		i++;
	//	j++;
	//	fseek(f, j, SEEK_SET);
	//	fscanf(f, "%c", temp);
	//}
	//fclose(f);
	//int arrSize = 10;
	printf("%s\n", temp);
	//Account *accounts = (Account *)malloc(arrSize * sizeof(Account));

	//menu(accounts, &arrSize);
	//addFAcc(accounts, arrSize, 1);

	_getch();
	//free(accounts);
	return 0;
}