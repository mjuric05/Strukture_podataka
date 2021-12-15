#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX (1024)


struct _Direktorij;
typedef struct _Direktorij* Position;
typedef struct _Direktorij {

	char Name[MAX];
	Position Sibling;
	Position Child;
}Directorij;

struct _Stog;
typedef struct _Stog* StogPosition;
typedef struct _Stog {

	Position Dir;
	StogPosition Next;
}Stog;

int PrintDir(Position P);   
Position InsertNewEl(Position S, Position P);    
Position CreateNewDir(char name[]);   
StogPosition NewStackEl(Position S);    
int Push(StogPosition S, StogPosition P);   
Position Pop(StogPosition S, Position P);    
Position MoveToDir(Position S, char* name, StogPosition P);
int Menu(Position S, StogPosition P);

int main() {

    Directorij root = {.Name = "C:", .Sibling = NULL, .Child = NULL};
    Stog head = {.Dir = NULL, .Next = NULL};
    int result = 0;

    result = Menu(&root, &head);
    
    if(result == 0) {

        printf("Thanks for using CMD ver 1.0.0!\n");
        return 0;
    }

    else {

        printf("Oops, something went wrong...\n");
        return -1;
    }
}

Position InsertNewEl(Position S, Position P) {

	if (S == NULL)
		return P;

	if (strcmp(S->Name, P->Name) < 0)
		S->Sibling = InsertNewEl(S->Sibling, P);

	else if (strcmp(S->Name, P->Name) > 0)
	{
		P->Sibling = S;
		return P;
	}

	return S;
}

Position CreateNewDir(char name[]) {

	Position q = NULL;

	q = (Position)malloc(sizeof(Directorij));

	if (q == NULL) {

		printf("Memory not allocated!\n");
		return NULL;
	}

	strcpy(q->Name, name);
	q->Sibling = NULL;
	q->Child = NULL;

	return q;
}

int Push(StogPosition S, StogPosition P) {

    while (S->Next != NULL)
        S = S->Next;

    S->Next	= P;
    P->Next = NULL;

    return 0;
}

Position Pop(StogPosition S, Position P) {

    Position temp = NULL;
    StogPosition q = NULL;

    if(S->Next == NULL) {   //provjera da li je prazan stack, ako je nema parent dir-a

        printf("No Parent Dir!\n");
        return NULL;
    }

    while(S->Next->Next != NULL)
        S = S->Next;

    q = S->Next;
    S->Next = q->Next;

    temp = q->Dir;

    free(q);

    return temp;
}

int PrintDir(Position P) {

    Position temp = NULL;

    temp = P->Child;  //ocemo vidit ko mu je dite jer cemo to ispisivat kod naredbe dir

    while(temp != NULL) {

        printf("C:/");
        printf(" %s/ ", temp->Name);
        temp = temp->Sibling;
    }

    puts("");

    return 0;
}

Position MoveToDir(Position S, char* name, StogPosition P) {

    Position temp = NULL;
    StogPosition q = NULL;

    temp = S->Child;

    while(temp != NULL && (strcmp(temp->Name, name)))
        temp = temp->Sibling;

    if(temp == NULL) {

        printf("Invalid dir name!\n");
        return NULL;
    }

    else {

        q = NewStackEl(S);
        Push(P, q);
        return temp;
    }

}

StogPosition NewStackEl(Position S) {

    StogPosition q = NULL;

    q = (StogPosition)malloc(sizeof(Stog));

    if(!q) {

        printf("Memory not allocated!\n");
        return NULL;
    }

    q->Dir = S;
    q->Next = NULL;

    return q;

}

int Menu(Position S, StogPosition P) {

    int command = 1;
    int retVal = 0;
    char dirName[MAX] = { 0 };
    Position q = NULL;
    Position q1 = S;

    while (command != 0) {

        printf("Input Command:\n");
        printf("1-cd <name>\n2-cd ..\n3-md <name>\n4-dir\n0-exit\n");
        scanf("%d", &command);

        if(command == 1) {

            printf("Enter dir name: ");
            scanf(" %s", dirName);

            q1 = MoveToDir(q1, dirName, P);
        }

        else if(command == 2)
            q1 = Pop(P,q1);

        else if(command == 3) {

            printf("Enter dir name: ");
            scanf(" %s",dirName);

            q  = CreateNewDir(dirName);

            q1->Child =InsertNewEl(q1->Child, q);
        }

        else if(command == 4) {

            retVal =  PrintDir(q1);

            if(retVal != 0)
                printf("Greska!\n");
        }
           

        else if(command != 0)
            printf("Plesae input right command!\n");
    }

    return 0;
}