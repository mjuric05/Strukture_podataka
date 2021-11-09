#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX (1024)

struct _Polinom;
typedef struct _Polinom* listPoli;
typedef struct _Polinom {

	int Koef;
	int Pot;
	listPoli Next;
}Polinom;

/*unaprijed: nisam imao pojma kakv menu ovdje napaviti pa sam radio bez njega */

int readFromFile(FILE* fp, listPoli P1, listPoli P2);			//cita retke iz dokumenta									
int addPolynoms(listPoli P1, listPoli P2, listPoli P);			//zbrajanje polinoma
int multyplyPolynoms(listPoli P1, listPoli P2, listPoli P);		//mnozenje polinoma
int printListOfPoly(listPoli P);								//ispis polinoma
int inputElements(listPoli P, int Koef, int Pot);				//funkcija za unos elemanta

int main()
{
	FILE* fp = NULL;
	Polinom P1 = { .Koef = 0 , .Pot = 0 , .Next = NULL };
	Polinom P2 = { .Koef = 0 , .Pot = 0 , .Next = NULL };
	Polinom pMulty = { .Koef = 0 , .Pot = 0 , .Next = NULL };
	Polinom pAdd = { .Koef = 0 , .Pot = 0 , .Next = NULL };

	printf("Pocetak programa:\n");

	fp = fopen("dat.txt", "r");

	readFromFile(fp, &P1, &P2);
	addPolynoms(&P1 , &P2 , &pAdd);
	multyplyPolynoms(&P1 , &P2 , &pMulty);

	printListOfPoly(&pAdd);
	puts("");
	printListOfPoly(&pMulty);

	fclose(fp);

	return EXIT_SUCCESS;
}

int readFromFile(FILE* fp, listPoli P1, listPoli P2) {

	char buffer[MAX] = { 0 };
	char buffer3[MAX] = { 0 };
	char* buffer1 = NULL;
	char* buffer2 = NULL;
	int cnt = 0, koef = 0, pot = 0;
	FILE* ft = NULL;
	char c = { 0 };

	ft = fopen("dat.txt", "r");

	if (!ft) {

		printf("File can not be opened/accesed!\n");
		return EXIT_FAILURE;
	}

	fgets(buffer, 1024, ft);

	buffer1 = buffer;

	fgets(buffer3, 1024, ft);

	buffer2 = buffer3;

	while (strlen(buffer1) > 0) {

		sscanf(buffer1, " %d %d %n", &koef, &pot, &cnt);
		buffer1 += cnt;
		inputElements(P1, koef, pot);

	}

	while (strlen(buffer2) > 0) {

		sscanf(buffer2, " %d %d %n", &koef, &pot, &cnt);
		buffer2 += cnt;
		inputElements(P2, koef, pot);

	}

	printListOfPoly(P1);
	puts("");
	printListOfPoly(P2);
	puts("");

	fclose(ft);

	return EXIT_SUCCESS;
}

int printListOfPoly(listPoli P) {

	printf("Polinom glasi:\n");
	while (P->Next != NULL) {

		P = P->Next;

		if (P->Pot > 0) {

			printf(" %dx^%d  ", P->Koef, P->Pot);
			

		}

		else if (P->Pot < 0) {

			printf(" %dx^(%d)  ", P->Koef, P->Pot);
			
		}

		else {

			printf(" %d  ", P->Koef);
			
		}
	}

	return EXIT_SUCCESS;
}

int multyplyPolynoms(listPoli P1, listPoli P2, listPoli P) {

	listPoli begin = NULL;

	begin = P2;

	while (P1->Next != NULL) {

		P1 = P1->Next;

		while (P2->Next != NULL) {
			
			P2 = P2->Next;
			inputElements(P, P1->Koef * P2->Koef, P1->Pot + P2->Pot);
			
		}
		
		P2 = begin;
		
	}

	return EXIT_SUCCESS;
}

int inputElements(listPoli P, int Koef, int Pot) {

	listPoli x = NULL;
	listPoli temp = NULL;

	x = (listPoli)malloc(sizeof(Polinom));

	x->Koef = Koef;
	x->Pot = Pot;

	while (P->Next != NULL && P->Next->Pot > Pot)
	{
		P = P->Next;
	}

	if (P->Next == NULL && P->Pot > Pot) {

		x->Next = P->Next;
		P->Next= x;
	}

	else if (P->Next != NULL && P->Next->Pot == Pot) {
	
		P->Next->Koef += Koef;
		

		if (P->Next->Koef == 0) {
		
			temp = P->Next;
			P->Next = P->Next->Next;
			free(temp);			
		}

		free(x);
	}

	else {
	
		x->Next = P->Next;
		P->Next = x;
	}

	return EXIT_SUCCESS;
}
int addPolynoms(listPoli P1, listPoli P2, listPoli P) {

	while (P1->Next != NULL && P2->Next != NULL) {

			P1 = P1->Next; 
			P2 = P2->Next;

			inputElements(P, P1->Koef, P1->Pot);
			inputElements(P, P2->Koef, P2->Pot);
		
		 if (P1->Next == NULL) {

			 while (P2->Next != NULL) {

				 P2 = P2->Next;
				 inputElements(P, P2->Koef, P2->Pot);
			 }
			
		}
		else {

			 while (P1->Next != NULL) {

				 P1 = P1->Next;
				 inputElements(P, P1->Koef, P1->Pot);
			 }
		}
	}

	return EXIT_SUCCESS;
}
