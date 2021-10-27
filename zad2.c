#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX (50)

struct _Person;			
typedef struct _Person* Position;		//tip podatka: pokazivac na strukturu _Person koja se zove Position
typedef struct _Person {
	char name[MAX];
	char surname[MAX];
	int birthYear;
	Position next;
}Person;

int addToBegin(Position p);	//a
int printList(Position p); //b
int addToEnd(Position p); //c
Position findBySurname(Position p);	//d
Position findBefore(Position p);
int deleteAfter(Position p);

int main()
{
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position pok = NULL;


	printf("add_begin:\n\n");
	addToBegin(&head);
	printf("add_begin:\n\n");
	addToBegin(&head);
	printf("add_end:\n\n");
	addToEnd(&head);

	printf("List:\n\n");
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



	return 0;
}

int addToBegin(Position p) {

	Position x = NULL;

	x = (Position)malloc(sizeof(Person));

	x->next = p->next;
	p->next = x;

	printf("Name:\n");
	scanf(" %s",x->name);
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

	

	while (p->next != NULL){
		p = p->next;
		printf("Name: %s\n", p ->name);
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

	return 0;
}

Position findBySurname(Position p) {

	char keySurname[MAX] = { 0 };

	printf("Enter surname to find:\n");
	scanf(" %s",keySurname);

	while (p->next != NULL && (strcmp(keySurname,p->surname)))
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

	printf("Enter surname to delete:\n");
	scanf(" %s", keySurname);

	while (p->next != NULL && (strcmp(keySurname, p->next->surname))){
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
