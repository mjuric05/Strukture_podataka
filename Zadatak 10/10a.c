#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX (1024)

struct _Stablo;
typedef struct _Stablo* Pos;
typedef struct _Stablo {

    char CityName[MAX];
    int PopleNumb;
    Pos Left;
    Pos Right;
}Stablo;

struct _Lista;
typedef struct _Lista* Position;
typedef struct _Lista {

    char StateName[MAX];
    Pos Next1;
    Position Next;
}Lista;

char* InputFileName(Position S);                                                            //Unos imena file-a
int PrintInorder(Pos S);                                                                    //Ispis elemenata stabla
Position CreateListElement(char Name[]);                                                    //Kreira element u vazenaj listi (ime drzave)
int PrintList(Position P);                                                                  //Ispis vezane liste drzava
int AdditionalFileCretaor(Position S, char StateName[]);                                    //Otvara dodatni file i sprema gradove (ime i broj stanovnika) u stabla
Pos CreateTreeElement(Pos S, char CityName[], int Population);                              //Kreira element stabla
Pos Insert1(Position P, int X, char CityName[], Pos S);                                     //Unos elemenata u stablo
Position FindStateByName(char State[], Position S);                                         //Trazimo drzavu prema imenu tj. pretrazivamo vezanu listu drzava
Pos FindCityByName(char City[], Pos S);                                                     //Trazimo grad prema imenu tj. pretrazivamo binarno stablo
Position InsertIntoList(Position P, Position S);

int main() {

    char* Name = NULL;
    
    Lista Drzave = {.StateName = { 0 }, .Next1 = NULL, .Next = NULL };

    Pos root = NULL;

    root = (Pos)malloc(sizeof(Stablo));

    strcpy(root->CityName, "0");
    root->PopleNumb = 0;
    root->Left = NULL;
    root->Right = NULL;

    Drzave.Next1 = root;

    Name = (char*)malloc(MAX * sizeof(char));

    Name = InputFileName(&Drzave);

    Menu(&Drzave);

    printf("%s\n", Name);

    return 0;
}

char* InputFileName(Position S) {

    char* FileName = NULL;
    char* AdditionalFileName = NULL;
    FILE* fp = NULL;
    int i = 0;
    int cnt = 0;
    Position NewElement = NULL;
    Position current = NULL;
    Pos current1 = NULL;

    char StateName[MAX] = { 0 };
    char NewFileName[MAX] = { 0 };

    char buffer1[MAX] = { 0 };
    char buffer2[MAX] = { 0 };
    char buffer3[MAX] = { 0 };
    char buffer4[MAX] = { 0 };
    char buffer5[MAX] = { 0 };

    char* _buffer1 = NULL;
    char* _buffer2 = NULL;
    char* _buffer3 = NULL;
    char* _buffer4 = NULL;
    char* _buffer5 = NULL;

    _buffer1 = (char*)malloc(MAX * sizeof(char));
    _buffer2 = (char*)malloc(MAX * sizeof(char));
    _buffer3 = (char*)malloc(MAX * sizeof(char));
    _buffer4 = (char*)malloc(MAX * sizeof(char));
    _buffer5 = (char*)malloc(MAX * sizeof(char));
    
    FileName = (char*)malloc(MAX * sizeof(char));
    AdditionalFileName = (char*)malloc(MAX * sizeof(char));

    NewElement = (Position)malloc(sizeof(Lista));
    current = (Position)malloc(sizeof(Lista));
    current1 = (Pos)malloc(sizeof(Stablo));

    if(!FileName) {

        printf("Something went wrong with mem allocation!\n");
        return NULL;
    }

    if(!_buffer1) {

        printf("Something went wrong with mem allocation!\n");
        return NULL;
    }

    if(!_buffer2) {

        printf("Something went wrong with mem allocation!\n");
        return NULL;
    }     
    
    if(!_buffer3) {

        printf("Something went wrong with mem allocation!\n");
        return NULL;
    }

    if(!_buffer4) {

        printf("Something went wrong with mem allocation!\n");
        return NULL;
    }

    if(!_buffer5) {

        printf("Something went wrong with mem allocation!\n");
        return NULL;
    }


    printf("Input Filename(hint: drzava.txt):\n");
    scanf(" %s", FileName);

    fp = fopen(FileName, "r");

    if(!fp) {

        printf("File cannot be opened or accesed!\n");
        return NULL;
    }

    fgets(buffer1, MAX, fp);
    fgets(buffer2, MAX, fp);
    fgets(buffer3, MAX, fp);
    fgets(buffer4, MAX, fp);
    fgets(buffer5, MAX, fp);

    _buffer1 = buffer1;
    _buffer2 = buffer2;
    _buffer3 = buffer3;
    _buffer4 = buffer4;
    _buffer5 = buffer5;


    while(strlen(_buffer1) > 0) {

        sscanf(_buffer1, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer1 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = CreateListElement(StateName);

        current = InsertIntoList(S, NewElement);
        
        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi za drzavu %s:\n\n", StateName);

        AdditionalFileCretaor(S, NewFileName);

        PrintInorder(S->Next1);

        puts("");
    }



    while(strlen(_buffer2) > 0) {

        sscanf(_buffer2, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer2 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = CreateListElement(StateName);

        current = InsertIntoList(S, NewElement);

        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi za drzavu %s:\n\n", StateName);

        AdditionalFileCretaor(current, NewFileName);

        PrintInorder(S->Next1);

        puts("");
    }


    while(strlen(_buffer3) > 0) {

        sscanf(_buffer3, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer3 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = CreateListElement(StateName);

        current = InsertIntoList(S, NewElement);

        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi za drzavu %s:\n\n", StateName);

        AdditionalFileCretaor(current, NewFileName);

        PrintInorder(S->Next1);

        puts("");
    }

    while(strlen(_buffer4) > 0) {

        sscanf(_buffer4, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer4 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = CreateListElement(StateName);

       current = InsertIntoList(S, NewElement);

        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi za drzavu %s:\n\n", StateName);

        AdditionalFileCretaor(current, NewFileName);

        PrintInorder(S->Next1);

        puts("");
    }

    while(strlen(_buffer5) > 0) {

        sscanf(_buffer5, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer5 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = CreateListElement(StateName);

        current = InsertIntoList(S, NewElement);

        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi za drzavu %s:\n\n", StateName);

        AdditionalFileCretaor(current, NewFileName);

        PrintInorder(S->Next1);

        puts("");
    }

    printf("Lista drzava glasi:\n");
    PrintList(S);
    puts("");

    fclose(fp);

    return FileName;
}

int PrintInorder(Pos S) {

    if(S == NULL) 
        return 0;

    PrintInorder(S->Left);
    printf("Grad: %s\nBroj stanovnika: %d\n", S->CityName, S->PopleNumb);
    PrintInorder(S->Right);

    return 0;
}


Position CreateListElement(char Name[]) {

    Position q = NULL;

	q = (Position)malloc(sizeof(Lista));

	if (q == NULL) {

		printf("Memory not allocated!\n");
		return NULL;
	}

	strcpy(q->StateName, Name);
	q->Next = NULL;
    q->Next1 = NULL;

    return q;
}

Position InsertIntoList(Position P, Position S) {

    if(P->Next == NULL) {

        P->Next = S;
        S->Next = NULL;
        S->Next1 = NULL;
    }

    else {

        while(P->Next != NULL && ((strcmp(P->Next->StateName, S->StateName) < 0))) 
            P = P->Next;

        S->Next = P->Next;
        P->Next = S; 
        S->Next1 = NULL;
    }

    return S;
}

int PrintList(Position P) {

    if(P->Next == NULL) {

        printf("List is empty!");
        return -1;
    }

    while(P->Next != NULL) {

        P = P->Next;
        printf("%s\n",P->StateName);    
    }

    return 0;
}

int AdditionalFileCretaor(Position S, char NewFileName[]) {

    FILE* fp = NULL;
    char Name[MAX] = { 0 };
    int PNumb = 0;
    int cnt = 0;

    Pos current = S->Next1;

    Pos NewElement = NULL;

    char buffer1[MAX] = { 0 };
    char buffer2[MAX] = { 0 };
    char buffer3[MAX] = { 0 };
    char buffer4[MAX] = { 0 };

    char* _buffer1 = NULL;
    char* _buffer2 = NULL;
    char* _buffer3 = NULL;
    char* _buffer4 = NULL;

    _buffer1 = (char*)malloc(MAX * sizeof(char));
    _buffer2 = (char*)malloc(MAX * sizeof(char));
    _buffer3 = (char*)malloc(MAX * sizeof(char));
    _buffer4 = (char*)malloc(MAX * sizeof(char));

    NewElement = (Pos)malloc(sizeof(Stablo));

    if(!_buffer1) {

        printf("Something went wrong with mem allocation!\n");
        return -1;
    }

    if(!_buffer2) {

        printf("Something went wrong with mem allocation!\n");
        return -1;
    }     
    
    if(!_buffer3) {

        printf("Something went wrong with mem allocation!\n");
        return -1;
    }

    if(!_buffer4) {

        printf("Something went wrong with mem allocation!\n");
        return -1;
    }

    if(!Name) {

        printf("Something went wrong with mem allocation!\n");
        return -1;
    }

    if(!NewElement) {

        printf("Something went wrong with mem allocation!\n");
        return -1;
    }

    fp = fopen(NewFileName, "r");

    if(!fp) {

        printf("File cannot be opened or accesed!\n");
        return -1;
    }

    fgets(buffer1, MAX, fp);
    fgets(buffer2, MAX, fp);
    fgets(buffer3, MAX, fp);
    fgets(buffer4, MAX, fp);

    _buffer1 = buffer1;
    _buffer2 = buffer2;
    _buffer3 = buffer3;
    _buffer4 = buffer4;

    while(strlen(_buffer1) > 0) {

        sscanf(_buffer1, " %s %d %n", &Name, &PNumb, &cnt);
        _buffer1 += cnt;

        NewElement = Insert1(S, PNumb, Name, S->Next1);
    }

    while(strlen(_buffer2) > 0) {

        sscanf(_buffer2, " %s %d %n", &Name, &PNumb, &cnt);
        _buffer2 += cnt;

        NewElement = Insert1(S, PNumb, Name, S->Next1);
    }

    while(strlen(_buffer3) > 0) {

        sscanf(_buffer3, " %s %d %n", &Name, &PNumb, &cnt);
        _buffer3 += cnt;

        NewElement = Insert1(S, PNumb, Name, S->Next1);
    }

    while(strlen(_buffer4) > 0) {

        sscanf(_buffer4, " %s %d %n", &Name, &PNumb, &cnt);
        _buffer4 += cnt;

        NewElement = Insert1(S, PNumb, Name, S->Next1);
    }

    fclose(fp);

    return 0;
}

Pos CreateTreeElement(Pos S,char CityName[], int Population) {

    if(S == NULL) {

        S = (Pos)malloc(sizeof(Stablo));
        S->PopleNumb = Population;
        strcpy(S->CityName, CityName);
        S->Left = NULL;
        S->Right = NULL;
    }

    else if(S->PopleNumb > Population)
        S->Left = CreateTreeElement(S->Left,CityName, Population);
    

    else
        S->Right = CreateTreeElement(S->Right, CityName, Population);

    if(!S) 
        return NULL;

    return S;
}

Pos Insert1(Position P, int X, char CityName[], Pos S) {

    if(S == NULL) {

        S = (Pos)malloc(sizeof(Stablo));
        S->PopleNumb = X;
        strcpy(S->CityName,CityName);
        S->Left = NULL;
        S->Right = NULL;
    }

    else if(S->PopleNumb >= X)
        S->Left = CreateTreeElement(S->Left, CityName, X);
    
    else
        S->Right = CreateTreeElement(S->Right, CityName, X);
    
    return S;
}

int Menu(Position S) {

    int key = 0;
    char State[MAX] = { 0 };
    char City[MAX] = { 0 };

    Pos temp = NULL;
    Position temp1 = NULL;
    Pos current = NULL;

    temp = (Pos)malloc(sizeof(Stablo));
    temp1 = (Position)malloc(sizeof(Lista));
    current = (Pos)malloc(sizeof(Stablo));

    while(key != 3) {

        printf("Zelite li pretraziti drzave i gradove?\n");
        printf("1-DA\n2-NE\n3-IZLAZ\n");
        scanf("%d", &key);

        if(key == 1) {

            printf("\nUnesite ime drzave: ");
            scanf(" %s", &State);
            puts("");

            temp1 = FindStateByName(State,S);

            if(temp1 == NULL)
                printf("Drzava koju ste unnjeli ne postoji!\n");

            else if(temp1 != NULL) {

                printf("Drzava koju ste unjeli je: %s\n", temp1->StateName);
                printf("Unesite grad: ");
                scanf(" %s", &City);
                puts("");

                current = temp1->Next1;

                temp = FindCityByName(City, current);

                if(temp == NULL)
                    printf("Taj grad ne postoji!\n");


                else {

                    printf("Grad: %s , Populacija: %d", temp->CityName, temp->PopleNumb);
                }
            }

            else if (key == 2)
                return 0;

            else    
                printf("Krivi unos!\n");

        }

    }

    return 0;

}

Position FindStateByName(char State[], Position S) {

    while(S->Next != NULL && (strcmp(S->Next->StateName, State) == 0) )
        S = S->Next;

    if(S == NULL)
        return NULL;

    else    
        return S;
}

Pos FindCityByName(char City[], Pos S) {

    int i = 0;

    for(i = 0; i < 1; i++) {

        if(S == NULL)
            return NULL;

        else if(strcmp(S->CityName, City) > 0)
            return FindCityByName(City, S->Left);

        else if(strcmp(S->CityName, City) < 0)
            return FindCityByName(City, S->Right);

        else    
            return S;
    }

    return S;
}