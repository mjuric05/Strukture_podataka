#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define minimum 10
#define maximum 90

struct _Pomocna;
typedef struct _Pomocna* Position;
typedef struct _Pomocna {

    int Numb;
    Position Next;
}Pomocna;

struct _Stablo;
typedef struct _Stablo* Pos;
typedef struct _Stablo {

    int Numb;
    Pos Left;
    Pos Right;
}Stablo;

int Menu(Pos S, Position P, Position P1, int Niz[], int X);     //briamo hocemo li ispis sa "zadanim" brojevima ili rand brojevima
Pos Insert1(Pos S, int X);                                      //Dodajemo element u stablo sa random vrijednostima
int GiveRandNumbers(int X, Position P, Pos S);                  //Funkcija koja nam daje X random brojeva između 10 in 90
Position CreateListElement(int X);                              //Kreira element vezane liste
int InsertIntoList(Position P, Position S);                     //Dodaje element sortirano u vezanu listu
int PrintList(Position P);                                      //Ispis vezane liste
Pos AddElementIntoTree(int X, Pos S);                           //Dodaje element u stablo
int PrintInorder(Pos S);                                        //Inoreder ispis
int Addition(Pos S);                                            //Funkcija koja obavja zbrajanje
int Replace(Pos S, Position P);                                 //Replace
int PutIntoFile(Position P, Position P1);                       //Stavlja u file rezultate prije (zad a) i nakon (zad b)

int main() {

    Pomocna lista = {.Numb = 0, .Next = NULL };
    Pomocna lista1 = {.Numb = 0, .Next = NULL };
    Stablo stablo = {.Numb = 2, .Left = NULL, .Right = NULL};   
    int i = 0;
    Pos NewEl = (Pos)malloc(sizeof(Stablo));
    int Niz[9] = {2, 5, 7, 8, 11, 1, 4, 3, 7};
    
    srand(time (NULL));

    Menu(&stablo, &lista, &lista1, Niz, 9);

    return 0;
}

Pos Insert1(Pos S, int X) {

    if(S == NULL) {

        S = (Pos)malloc(sizeof(Stablo));
        S->Numb = X;
        S->Left = NULL;
        S->Right = NULL;
    }

    else if(S->Numb >= X)
        S->Left = AddElementIntoTree(X, S->Left);
    
    else
        S->Right = AddElementIntoTree(X, S->Right);
    
    return S;
}

int GiveRandNumbers(int X, Position P, Pos S) {

    int* Pomocni = NULL;
    int cnt = 0;
    Position newEl = NULL;
    Pos newEl1 = NULL;
    int i = 0;

    newEl = (Position)malloc(sizeof(Pomocna));
    newEl1 = (Pos)malloc(sizeof(Stablo));

    if(!newEl) {

        printf("Mem not allocated!\n");
        return -1;
    }

    Pomocni = (int*)malloc(X * sizeof(int));

    printf("%d random brojeva:\n",X);

    for (i = 0; i < X ; i++) {

        Pomocni[i] = minimum + (rand() % (maximum - minimum + 1));

        printf("%d \n",Pomocni[i]); 
    }

    for(i = 0 ; i < X ; i++) {

        newEl = CreateListElement(Pomocni[i]);

        if(newEl == NULL)
            printf("Err!\n");

        InsertIntoList(P,newEl);

        if(cnt != 0) {

            printf("Err!!\n");
            return -1;
        }
    }

    for(i = 0 ; i < X ; i++) {

        newEl1 = AddElementIntoTree(Pomocni[i], S);
    }

    return 0;
}

Position CreateListElement(int X) {

    Position q = NULL;

	q = (Position)malloc(sizeof(Pomocna));

	if (q == NULL) {

		printf("Memory not allocated!\n");
		return NULL;
	}

	q->Numb = X;
	q->Next = NULL;

    return q;
}

int PrintList(Position P) {

    if(P->Next == NULL) {

        printf("List is empty!\n");
        return -1;
    }

    while(P->Next != NULL) {

        P = P->Next;
        printf("%d ",P->Numb);    
    }

    return 0;
}

int InsertIntoList(Position P, Position S) {

    if(P->Next == NULL) {

        P->Next = S;
        S->Next = NULL;
    }

    else {

        while(P->Next != NULL && (P->Next->Numb <= S->Numb)) 
            P = P->Next;

        S->Next = P->Next;
        P->Next = S; 
    }

    return 0;
}

Pos AddElementIntoTree(int X, Pos S) {

    if(S == NULL) {

        S = (Pos)malloc(sizeof(Stablo));
        S->Numb = X;
        S->Left = NULL;
        S->Right = NULL;
    }

    else if(S->Numb > X)
        S->Left = AddElementIntoTree(X, S->Left);
    

    else
        S->Right = AddElementIntoTree(X, S->Right);
    
    return S;
}

int PrintInorder(Pos S) {

    if(S == NULL) 
        return 0;

    PrintInorder(S->Left);
    printf("%d ", S->Numb);
    PrintInorder(S->Right);

    return 0;
}

int Addition(Pos S) {

    if(!S)
        return 0;

    else 
        return (S->Numb + Addition(S->Left) + Addition(S->Right));
}

int Replace(Pos S, Position P) {

    Position newEl = NULL;

    newEl = (Position)malloc(sizeof(Pomocna));

    if(!S)
        return 0;

    S->Numb = Addition(S->Right) + Addition(S->Left);

    newEl = CreateListElement(S->Numb);

    InsertIntoList(P,newEl);

    Replace(S->Left, P);
    Replace(S->Right, P);

    return 0;
}

int Menu(Pos S, Position P, Position P1, int Niz[], int X) {

    int key = 0, i = 0;
    Pos NewEl = NULL;
    Position NewEl1 = NULL;
    Position NewEl2 = NULL;

    NewEl = (Pos)malloc(sizeof(Stablo));
    NewEl1 = (Position)malloc(sizeof(Pomocna));
    NewEl2 = (Position)malloc(sizeof(Pomocna));

    printf("Zelite li raditi sa generickim nizom ili X rand brojeva?\n");
    printf("1-genericki niz\n2-X rand brojeva ");
    scanf("%d", &key);

    if(key == 1) {

        for (i = 0 ; i < X ; i++)
            NewEl = Insert1(S,Niz[i]);

        printf("Vase stablo glasi: \n");
        PrintInorder(S);
        puts("");

        for (i = 0 ; i < X ; i++) {

            NewEl1 = CreateListElement(Niz[i]);
            InsertIntoList(P,NewEl1);
        }

        Addition(S);
        Replace(S,P1);

        puts("Nakon zamjene:\n");
        PrintInorder(S);

        for(i = 0 ; i < X ; i++) {

            NewEl2 = CreateListElement(Niz[i]);
            InsertIntoList(P1,NewEl2);
        }

        PutIntoFile(P,P1);     
    }

    else if(key == 2) {

        printf("Koliko random brojeva zelite?\n");
        scanf("%d", &X);

        GiveRandNumbers(X,P,S);

        printf("Vase stablo glasi: \n");     
        PrintInorder(S);

        Addition(S);
        Replace(S,P1);

        puts("Nakon zamjene:\n");
        PrintInorder(S);

        PutIntoFile(P,P1);
    }

    return 0;
}

int PutIntoFile(Position P, Position P1) {

    FILE* fp = NULL;

    fp = fopen("dat.txt", "w");

    if(!fp) {

        printf("File nije moguce otvoriti!\n");
        return -1;
    }

    fprintf(fp, "Prije funkcije (zad a)\n");

    while (P->Next != NULL) {

        fprintf(fp, "%d ", P->Numb);
        P = P->Next;       
    }

    fprintf(fp, "\nNakon funkcije (zad b)\n");

    while (P1->Next != NULL) {

        fprintf(fp, "%d ", P1->Numb);
        P1 = P1->Next;       
    }

    fclose(fp);

    return 0;
}