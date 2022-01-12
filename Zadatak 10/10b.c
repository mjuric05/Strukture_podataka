#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX (1024)

struct _Lista;
typedef struct _Lista* Position;
typedef struct _Lista {

    char CityName[MAX];
    int PopleNumb;
    Position Next;
}Lista;

struct _Stablo;
typedef struct _Stablo* Pos;
typedef struct _Stablo {

    char StateName[MAX];
    Pos Left;
    Pos Right;
    Position Next1;
}Stablo;

int PrintInorder(Pos S);
Pos AddElementIntoTree(Pos S, char StateName[]);
char* InputFileName(Pos S);   
Pos Insert1(Pos P,char StateName[]);
Pos CreateTreeElement(Pos S,char StateName[]);
Pos Root(Pos S,char StateName[]);
Position CreteListElement(char CityName[], int Population);
int InsertIntoList(Position P, Position S);
Position CreateHead();

int main() {

    Stablo Drzave = {.Left = NULL, .Right = NULL, .Next1 = NULL};
    char* Name = NULL;

    Name = (char*)malloc(MAX * sizeof(char));

    Position head = NULL;

    head = (Position)malloc(sizeof(Lista));

    head->Next = NULL;
    head->PopleNumb = 0;
    strcpy(head->CityName, "");

    Drzave.Next1 = head;

    Name = InputFileName(&Drzave);

    printf("Name of File: %s\n", Name);

    Menu(&Drzave);

    return 0;
}

int PrintInorder(Pos S) {

    if(S == NULL) 
        return 0;

    PrintInorder(S->Left);
    printf("Drzava: %s\n", S->StateName);
    PrintInorder(S->Right);

    return 0;
}

Pos AddElementIntoTree(Pos S, char StateName[]) {

    if(S == NULL) {

        S = (Pos)malloc(sizeof(Stablo));
        strcpy(S->StateName, StateName);
        S->Left = NULL;
        S->Right = NULL;
        S->Next1 = NULL;
    }

    else if(strcmp(S->StateName, StateName) > 0)
        S->Left = AddElementIntoTree(S->Left, StateName);
    

    else
        S->Right = AddElementIntoTree(S->Right, StateName);
    
    return S;
}

char* InputFileName(Pos S) {

    char* FileName = NULL;
    char* AdditionalFileName = NULL;
    FILE* fp = NULL;
    int i = 0;
    int cnt = 0;
    Pos NewElement = NULL;
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

    NewElement = (Pos)malloc(sizeof(Stablo));
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

        NewElement = Root(S,StateName);

        NewElement->Next1 = CreateHead();

        //InsertIntoList(S, NewElement);
        
        printf("Additional file: %s\n",NewFileName);

        //printf("Gradovi za drzavu %s:\n\n", StateName);

        AdditionalFileCretaor(NewElement, NewFileName);

        puts("");
    }

    while(strlen(_buffer2) > 0) {

        sscanf(_buffer2, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer2 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = Insert1(S,StateName);

        NewElement->Next1 = CreateHead();
        
        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi drzave %s\n", StateName);

        AdditionalFileCretaor(NewElement, NewFileName);

        puts("");
    }

    while(strlen(_buffer3) > 0) {

        sscanf(_buffer3, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer3 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = Insert1(S,StateName);

        NewElement->Next1 = CreateHead();
        
        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi drzave %s\n", StateName);

        AdditionalFileCretaor(NewElement, NewFileName);

        puts("");
    }

    while(strlen(_buffer4) > 0) {

        sscanf(_buffer4, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer4 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = Insert1(S,StateName);

        NewElement->Next1 = CreateHead();
        
        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi drzave %s\n", StateName);

        AdditionalFileCretaor(NewElement, NewFileName);

        puts("");
    }

    while(strlen(_buffer5) > 0) {

        sscanf(_buffer5, " %s %s %n", &StateName, &NewFileName, &cnt);
        _buffer5 += cnt;
        printf("State Name: %s\n",StateName);

        NewElement = Insert1(S,StateName);

        NewElement->Next1 = CreateHead();
        
        printf("Additional file: %s\n",NewFileName);

        printf("Gradovi drzave %s\n", StateName);

        AdditionalFileCretaor(NewElement, NewFileName);

        puts("");
    }

    fclose(fp);

    return FileName;
}

Pos Insert1(Pos S,char StateName[]) {

    if(S == NULL) {

        S = (Pos)malloc(sizeof(Stablo));
        strcpy(S->StateName, StateName);
        S->Left = NULL;
        S->Right = NULL;
    }

    else if(strcmp(S->StateName,StateName) > 0)
        S->Left = CreateTreeElement(S->Left,StateName);
    

    else
        S->Right = CreateTreeElement(S->Right, StateName);
        
    return S;
}

Pos CreateTreeElement(Pos S,char StateName[]) {

    if(S == NULL) {

        S = (Pos)malloc(sizeof(Stablo));
        strcpy(S->StateName, StateName);
        S->Left = NULL;
        S->Right = NULL;
    }

    else if(strcmp(S->StateName,StateName) > 0)
        S->Left = CreateTreeElement(S->Left,StateName);
    

    else
        S->Right = CreateTreeElement(S->Right, StateName);

    if(!S) 
        return NULL;

    return S;
}

Pos Root(Pos S, char StateName[]) {

    strcpy(S->StateName, StateName);
    S->Next1 = NULL;
    S->Left = NULL;
    S->Right = NULL;

    return S;
}

Position CreteListElement(char CityName[], int Population) {

    Position S = NULL;

    S = (Position)malloc(sizeof(Lista));

    strcpy(S->CityName, CityName);
    S->PopleNumb = Population;
    S->Next = NULL;

    return S;
}

int InsertIntoList(Position P, Position S) {

    if(P->Next == NULL) {

        P->Next = S;
        S->Next = NULL;
    }

    else {

        while(P->Next != NULL && (P->Next->PopleNumb < S->PopleNumb)) 
            P = P->Next;

        S->Next = P->Next;
        P->Next = S; 
    }

    return 0;
}

int AdditionalFileCretaor(Pos S, char NewFileName[]) {

    FILE* fp = NULL;
    char Name[MAX] = { 0 };
    int PNumb = 0;
    int cnt = 0;

    Position NewElement = NULL;

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

    NewElement = (Position)malloc(sizeof(Lista));

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

        NewElement = CreteListElement(Name, PNumb);

        InsertIntoList(S->Next1, NewElement);
    }

    while(strlen(_buffer2) > 0) {

        sscanf(_buffer2, " %s %d %n", &Name, &PNumb, &cnt);
        _buffer2 += cnt;
        NewElement = CreteListElement(Name, PNumb);

        InsertIntoList(S->Next1, NewElement);
    }

    while(strlen(_buffer3) > 0) {

        sscanf(_buffer3, " %s %d %n", &Name, &PNumb, &cnt);
        _buffer3 += cnt;

        NewElement = CreteListElement(Name, PNumb);

        InsertIntoList(S->Next1, NewElement);
    }

    while(strlen(_buffer4) > 0) {

        sscanf(_buffer4, " %s %d %n", &Name, &PNumb, &cnt);
        _buffer4 += cnt;

        NewElement = CreteListElement(Name, PNumb);

        InsertIntoList(S->Next1, NewElement);
    }

    PrintList(S->Next1);

    fclose(fp);

    return 0;
}

int PrintList(Position P) {

    if(P->Next == NULL) {

        printf("List is empty!");
        return -1;
    }

    while(P->Next != NULL) {

        P = P->Next;
        printf("Grad: %s    Populacija: %d\n",P->CityName, P->PopleNumb);    
    }

    return 0;
}

Position CreateHead() {

    Position q = NULL;

    q = (Position)malloc(sizeof(Lista));

    if(!q) {

        printf("Greska!\n");
        return NULL;
    }  

    strcpy(q->CityName, "");
    q->Next = NULL;
    q->PopleNumb = 0;

    return q;
}

Pos FindStateByName(Pos S, char StateName[]) {

    int i = 0;

    for(i = 0; i < 1; i++) {

        if(S == NULL)
            return NULL;

        else if(strcmp(S->StateName, StateName) > 0)
            return FindStateByName(S->Left, StateName);

        else if(strcmp(S->StateName, StateName) < 0)
            return FindStateByName(S->Right, StateName);

        else    
            return S;
    }

    return S;
}

Position FindCityByName(Position S, char CityName[]) {

    while(S->Next != NULL && (strcmp(S->Next->CityName, CityName) == 0) )
        S = S->Next;

    if(S == NULL)
        return NULL;

    else    
        return S;
}

int Menu(Pos S) {

    int key = 0;
    char State[MAX] = { 0 };
    char City[MAX] = { 0 };

    Position temp = NULL;
    Pos temp1 = NULL;
    Position current = NULL;

    temp = (Position)malloc(sizeof(Lista));
    temp1 = (Pos)malloc(sizeof(Stablo));
    current = (Position)malloc(sizeof(Lista));

    while(key != 3) {

        printf("Zelite li pretraziti drzave i gradove?\n");
        printf("1-DA\n2-NE\n3-IZLAZ\n");
        scanf("%d", &key);

        if(key == 1) {

            printf("\nUnesite ime drzave: ");
            scanf(" %s", &State);
            puts("");

            temp1 = FindStateByName(S, State);

            if(temp1 == NULL)
                printf("Drzava koju ste unnjeli ne postoji!\n");


            else if(temp1 != NULL) {

                printf("Drzava koju ste unjeli je: %s\n", temp1->StateName);
                printf("Gradovi unesene drzave su:\n");

                PrintList(temp1->Next1);

                printf("Unesite grad: ");
                scanf(" %s", &City);
                puts("");

                current = temp1->Next1;

                temp = FindCityByName(temp1->Next1, City);

                if(temp == NULL)
                    printf("Taj grad ne postoji!\n");

                else
                    printf("Grad: %s , Populacija: %d\n", temp->CityName, temp->PopleNumb);
                
            }

            else if (key == 2)
                return 0;

            else    
                printf("Krivi unos!\n");
        }
    }

    return 0;
}
