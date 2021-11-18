#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (1024)

struct _Stog;
typedef struct _Stog* Position;
typedef struct _Stog {

	double Number;
	Position Next;
}Stog;

Position CreateStackElement(double number);
int Push(Position S, double number);
int Pop(Position S, double* operator);
int InsertAfter(Position position, Position newElement);
int DeleteAfter(Position position);
int DeleteAllElements(Position S);
int ReadFileName(char* fileName, Position Head);
int CheckFileName(char* fileName);
int CalculateResultOfPostfix(Position S, char operator);
int GetPostfixFromFile(Position S, char* fileName);
int PrintStack(Position S);
int Menu(int numb1);
int ChangePostfixFile(char* fileName);
int GetPostionOfStackHead(Stog Head);


int main() {

	char fileName[MAX] = { 0 };
	double resultOfPostfix = 0;
	Stog Head = { .Number = 0 , .Next = NULL };
	Position P = &Head;
	int status = 0;

	ReadFileName(fileName,P);

	printf("%.2lf\n",P->Next->Number);

	return 0;
}

Position CreateStackElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Stog));

	if (!newElement) {

		perror("Nije moguce alocirati trazenu memoriju!\n");
		return NULL;
	}

	newElement->Number = number;
	newElement->Next = NULL;

	return newElement;
}

int Push(Position head, double number) {

	Position newElement = NULL;

	newElement = CreateStackElement(number);

	if (!newElement) {

		printf("Novi element nije moguce napraviti!\n");
		return EXIT_FAILURE;
	}

	InsertAfter(head, newElement);

	return 0;
}

int Pop(Position S, double* operator)
{
	if (S->Next == NULL)
	{
		printf("Vas postfix nije ispravan!\n");
		printf("Posjetite stranicu https://raj457036.github.io/Simple-Tools/prefixAndPostfixConvertor.html \n");
		printf("Da biste ispravili vas postfix izraz!\n");
		return EXIT_FAILURE;
	}

	*operator = S->Next->Number;

	DeleteAfter(S);

	return 0;
}

int InsertAfter(Position position, Position newElement) {

	newElement->Next = position->Next;
	position->Next = newElement;

	return EXIT_SUCCESS;
}

int DeleteAfter(Position position) {

	Position temp = position->Next;

	if (!temp)
		return EXIT_FAILURE;

	position->Next = temp->Next;

	free(temp);

	return EXIT_SUCCESS;
}

int ReadFileName(char* fileName, Position Head) {

	printf("Unesite ime datoteke:\n");
	scanf(" %s", fileName);

	CheckFileName(fileName);

	GetPostfixFromFile(Head, fileName);

	return EXIT_SUCCESS;
}

int CheckFileName(char* fileName) {

	FILE* fp = NULL;

	printf("Testno otvaranje filea...\n");

	fp = fopen(fileName, "r");

	if (!fp) {

		printf("File ili ne postoji ili mu se ne moze pristupiti!\n");
		return EXIT_FAILURE;
	}

	else {

		printf("File je uspjesno otvoren!\n");
		return EXIT_SUCCESS;
	}

	fclose(fp);
}

int PrintStack(Position S) {

	printf("Stog je:\n");
	while (S->Next != NULL) {

		S = S->Next;

		printf("%.2lf\n", S->Number);
	}

	return EXIT_SUCCESS;
}

int GetPostfixFromFile(Position S, char* fileName)
{
	FILE* fp = NULL;
	char* buffer1 = NULL;
	int cnt = 0;
	double number = 0;
	int status = 0;
	char operator=0, buffer[MAX] = { 0 };

	fp = fopen(fileName,"r");

	fgets(buffer,MAX,fp);

	buffer1 = buffer;

	while (strlen(buffer1) > 0)
	{
		status = sscanf(buffer1, "%lf %n", &number, &cnt);
		if (status == 1)
		{
			status = Push(S, number);
			if (status != 0)
				DeleteAllElements(S);
		}
		else
		{
			sscanf(buffer1, " %c %n", &operator, &cnt);
			status = CalculateResultOfPostfix(S, operator);
			if (status != 0)
				DeleteAllElements(S);
		}

		buffer1 += cnt;
	}

	PrintStack(S);

	return EXIT_SUCCESS;
}

int DeleteAllElements(Position S) {

	while (S->Next != NULL) {

		DeleteAfter(S);
	}

	return EXIT_SUCCESS;
}

int CalculateResultOfPostfix(Position S, char operator) {


	double operator1 = 0;
	double operator2 = 0;
	int status = 0;

	status = Pop(S,&operator1);
	if (status != 0)
		return -1;

	status = Pop(S,&operator2);
	if (status != 0)
		return -1;

	switch (operator) {

		case '+':
			Push(S, operator1 + operator2);
			break;

		case '-':
			Push(S, operator1 - operator2);
			break;

		case '*':
			Push(S, operator1 * operator2);
			break;

		case '/':
			if (operator2 == 0) {

				printf("Nije moguce dijeliti sa 0!\n");
				printf("Molimo, pregledajte vas postfix!\n");
				return EXIT_FAILURE;
			}
			else
				Push(S, operator1 / operator2);
			break;

		default:
			break;
	}

	return EXIT_SUCCESS;
}
