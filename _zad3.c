#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX (50)
#define MAX1 (1024)

struct _Person;
typedef struct _Person* Position;		//tip podatka: pokazivac na strukturu _Person koja se zove Position
typedef struct _Person {
	char name[MAX];
	char surname[MAX];
	int birthYear;
	Position next;
}Person;

/*funkcije za 2.zad */

int addToBegin(Position p);				//a
int printList(Position p);				//b
int addToEnd(Position p);				//c
Position findBySurname(Position p);		//d
Position findBefore(Position p);		//e
int deleteAfter(Position p);			//e

/*funkcije za 3.zad*/
int addBehindElement(Position p);		//a
int addBeforeElement(Position p);		//b
int puttingIntoFile(Position p);		//d
int readingFromFile(Position p);		//e
int lineCounter(char* filename);		//broji koliko ima lnija unutar filea
int desidion(int x);					//gleda hocmo li sortirat, zelimo li normalan unos ili prekida izvodjenje programa
void sortElements(Position p);			//c	
int addElementNormaly(Position p);		//unosi elemente "normalno" tj. jedan iza drugoga, kasnije skuzia da mi ne triba

int main()
{
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position pok = NULL;
	FILE* fp = NULL;
	int i = 0, x = 0, cnt = 0;

	printf("\tDo You want elements sorted?\n");
	printf("\t1-Sorted\n\t2-Normal input.\n");
	scanf("%d",&x);

	if (desidion(x) == 2) {

		printf("Add_begin:\n");
		addToBegin(&head);

		printf("Add_begin:\n");
		addToBegin(&head);

		printf("Add_end:\n");
		addToEnd(&head);

		printf("Add_end:\n");
		addToEnd(&head);

		printf("List:\n\n");
		printList(&head);

		printf("Adding behind element:\n");
		pok = findBySurname(head.next);
		addBehindElement(pok);
		puts("");

		printf("Your list is now:\n");
		printList(&head);

		printf("Adding before element:\n");
		pok = findBefore(head.next);
		addBehindElement(pok);

		printf("Your list is now:\n");
		printList(&head);

		pok = findBySurname(head.next);
		if (pok != NULL) {
			printf("Name: %s\n", pok->name);
			printf("Surname: %s\n", pok->surname);
			printf("Birthyear: %d\n", pok->birthYear);
			puts("");
		}

		pok = findBefore(&head);
		deleteAfter(pok);

		puts("");
		puts("");

		printList(&head);

		printf("Putting people into file.txt...\n");
		puttingIntoFile(&head);

		printf("Reading from file:\n");
		readingFromFile(&head);
	}

	else if (desidion(x) == 1) {

		printf("Enter number of elements:\n");
		scanf("%d",&cnt);
	
		for (i = 0; i < cnt; i++) {

			addToEnd(&head);
			printf("List:\n\n");
			printList(&head);
		}	

		sortElements(&head);

		printf("Putting people into file.txt...\n");
		puttingIntoFile(&head);

		printf("Your people are sorted in file.txt!\n");
	}

	else {

		printf("ERROR!\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int addToBegin(Position p) {

	Position x = NULL;

	x = (Position)malloc(sizeof(Person));

	x->next = p->next;
	p->next = x;

	printf("Name:\n");
	scanf(" %s", x->name);
	printf("Surname:\n");
	scanf(" %s", x->surname);
	printf("Birthyear:\n");
	scanf("%d", &(x->birthYear));

	return 0;
}

int printList(Position p) {

	if (p->next == NULL) {
		printf("List is empty!\n");
		return 0;
	}

	while (p->next != NULL) {
		p = p->next;
		printf("Name: %s\n", p->name);
		printf("Surname: %s\n", p->surname);
		printf("Birthyear: %d\n", p->birthYear);
		puts("");
	}

	return 0;
}

int addToEnd(Position p) {

	Position x = NULL;

	x = (Position)malloc(sizeof(Person));

	while (p->next != NULL)
	{
		p = p->next;
	}

	p->next = x;
	x->next = NULL;

	printf("Name:\n");
	scanf(" %s", x->name);
	printf("Surname:\n");
	scanf(" %s", x->surname);
	printf("Birthyear:\n");
	scanf("%d", &(x->birthYear));
	puts("");

	return 0;
}

Position findBySurname(Position p) {

	char keySurname[MAX] = { 0 };

	printf("Enter surname to find:\n");
	scanf(" %s", keySurname);

	while (p->next != NULL && (strcmp(keySurname, p->surname)))
	{
		p = p->next;
	}
	if ((strcmp(keySurname, p->surname))) {
		printf("\nERROR!\n");
		return NULL;
	}

	return p;
}

Position findBefore(Position p) {

	char keySurname[MAX] = { 0 };

	printf("Enter surname:\n");
	scanf(" %s", keySurname);

	while (p->next != NULL && (strcmp(keySurname, p->next->surname))) {
		p = p->next;
	}

	if ((strcmp(keySurname, p->next->surname))) {
		printf("\nERROR!\n");
		return NULL;
	}

	return p;
}
int deleteAfter(Position p) {

	Position temp = NULL;

	temp = p;
	p = p->next;
	temp->next = p->next;

	free(p);

	return 0;
}

int addBehindElement(Position p) {

	Position x = NULL;

	x = (Position)malloc(sizeof(Person));

	x->next = p->next;
	p->next = x;

	printf("Name:\n");
	scanf(" %s", x->name);
	printf("Surname:\n");
	scanf(" %s", x->surname);
	printf("Birthyear:\n");
	scanf("%d", &(x->birthYear));

	return 0;
}

int addBeforeElement(Position p) {

	Position x;

	x = (Position)malloc(sizeof(Person));

	x->next = p->next;
	p->next = x;

	printf("Name:\n");
	scanf(" %s", x->name);
	printf("Surname:\n");
	scanf(" %s", x->surname);
	printf("Birthyear:\n");
	scanf("%d", &(x->birthYear));

	return 0;
}

int puttingIntoFile(Position p) {

	FILE* fp = NULL;

	fp = fopen("file.txt", "w");

	while (p->next != NULL) {
	
		if (p->birthYear != 0) {

			fprintf(fp, "%s\t%s\t%d\n", p->name, p->surname, p->birthYear);
			p = p->next;
		}
		else
			p = p->next;
	}

	fclose(fp);

	return 0;
}

int readingFromFile(Position p) {

	FILE* fp = NULL;
	int lineCnt = 0 , i = 0;
	//char buffer[MAX1] = { 0 };

	fp = fopen("file.txt", "r");

	//lineCnt = lineCounter(fp);	//preko ove funcije bismo prebrojili koliko iam redaka pa preko for petlje citali iz file, ali ovoka je zgodinje

	while (p->next != NULL) {
		p = p->next;
		printf("Name: %s\n", p->name);
		printf("Surname: %s\n", p->surname);
		printf("Birthyear: %d\n", p->birthYear);
		puts("");
	}

	fclose(fp);

	return 0;
}

int lineCounter(char* filename)
{
                                
	FILE* fp = NULL;
	int ch = 0 , line = 0;

	if (fp == NULL);
	return 0;

	line++;

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
			line++;
	}

	fclose(fp);

	return line;
}

int desidion(int x) {

	if (x == 1)
		return 1;
	else if (x == 2)
		return 2;
	else
		return 0;
}

int addElementNormaly(Position p) {

	Position x = NULL;

	x = (Position)malloc(sizeof(Person));

	p->next = x;
	x->next = NULL;
	
	printf("Name:\n");
	scanf(" %s", x->name);
	printf("Surname:\n");
	scanf(" %s", x->surname);
	printf("Birthyear:\n");
	scanf("%d", &(x->birthYear));

	return 0;
}

void sortElements(Position p) {

	Position j, prev_j, temp, end;

	end = NULL;

	while (p->next != end)
	{
		prev_j = p;
		j = p->next;

		while (j->next != end) {

			if (strcmp(j->surname, j->next->surname) > 0) {

				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}

			prev_j = j;
			j = j->next;
		}

		end = j;
	}

}
