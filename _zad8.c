#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct _Stablo;
typedef struct _Stablo* Position;
typedef struct _Stablo {

	int Number;
	Position Right;
    Position Left;
}Stablo;

int Menu(int numb, Position S);                                 //Jednostavni menu za odabir: ispis(vrsta), pretrazivanje, unos, brisanje i izlaz
Position CreateEmpty(Position S);                               //Kreira na pocetku jednostavno prazno stablo
Position FindElement(int keyVal, Position S);                   //Funkcija za trazenje elemenata
Position AddElementIntoTree(int X, Position S);                 //Dodaje element u stablo
int PrintIrorder(Position S);                                   //Inorder ispis			
int PrintPostorder(Position S);                                 //Postorder ispis
int PrintPreorder(Position S);                                  //Preorder ispis
int printLevelOrder(Position S);				//Njega nisam znao napraviti
Position DeleteElement(int X, Position S);                      //Brise elemant iz stabla
Position FindMin(Position S);                                   //Trazi minimum
int AddRootElement(int X, Position S);                          //Dodaje "korjen" stabla

int main() {

    Stablo root = {.Number = 0, .Right = NULL, .Left = NULL};
    int numb = 0;

    printf("Pozdrav! Prije no sto pocnemo, unesite root stabla\n");
    root.Number = AddRootElement(numb,&root);

    numb = Menu(numb, &root);
 
    if(numb == 7) {

        printf("Program se gasi...\n");
        return 0;      
    }
    
    return 0;
}

int Menu(int numb, Position S) {

    int key = 1;    //postavio ga na 1 samo da nebih imao problema u while petlji jer je uvjet za izlaz 0
    int X = 0;
    int control = 0;
    Position temp = NULL;

    temp = (Position)malloc(sizeof(Stablo));

    while (key != 0) {

        printf("Menu:\n");
        printf("1-Ispis\n2-Pretrazivanje\n3-Unos novog elemanta\n4-Brisanje\n0-Izlaz\n\n");
        scanf("%d",&key);

        if(key == 1) {

            printf("Kakav ispis zelite?\n");
            printf("1-Inorder\n2-Postorder\n3-Preorder\n\n");
            scanf("%d",&key);

            if(key == 1) {

                PrintInorder(S);
                puts("");
            }
            
            else if(key == 2) {

                PrintPostorder(S);
                puts("");
            }
            else if(key == 3) {

                PrintPreorder(S);
                puts("");
            }
                
            else 
                printf("Netocan unos!\n\n");
        
        }

        else if(key == 2) {

            printf("Unesite vrijednost koju zelite naci:");
            scanf("%d",&X);
            
           temp = FindElement(X,S);

           if(temp == NULL)
                printf("Element ne postoji u stablu!\n\n");

            else
                printf("Element %d postoji u stablu!\n\n",temp->Number);          
        }

        else if(key == 3) {

            printf("Unesite elemant koji zelite unjeti:\n");
            scanf("%d",&X);

            temp = FindElement(X,S);

            if(temp != NULL) {

                printf("Element vec postoji!\n\n");
                free(temp);
            }

            else {

                temp = AddElementIntoTree(X,S);
                printf("Element %d je dodan u stablo!\n\n", X);
            }
        }

        else if(key == 4) {

            printf("Unesite element za brisanje:\n");
            scanf("%d", &X);

            temp = DeleteElement(X,S);

            if(temp != NULL)
                printf("Emlement %d je izbrisan iz stabla!\n\n", X);
        }

        else if(key != 0)
            printf("Nesipravan unos! Pokusajte ponovno!\n\n");

    }

    free(temp);

    return 7;
}

int PrintInorder(Position S) {

    if(S == NULL) 
        return 0;

    PrintInorder(S->Left);
    printf("%d ", S->Number);
    PrintInorder(S->Right);

    return 0;
}

int PrintPostorder(Position S) {

    if(S == NULL)
        return 0;

    PrintPostorder(S->Left);
    PrintPostorder(S->Right);
    printf("%d ", S->Number);

    return 0;
}

int PrintPreorder(Position S) {

    if(S == NULL)
        return 0;

    printf("%d ", S->Number);
    PrintPreorder(S->Left);
    PrintPreorder(S->Right);

    return 0;
}

Position AddElementIntoTree(int X, Position S) {

    if(S == NULL) {

        S = (Position)malloc(sizeof(Stablo));
        S->Number = X;
        S->Left = NULL;
        S->Right = NULL;
    }

    else if(S->Number > X)
        S->Left = AddElementIntoTree(X, S->Left);
    

    else
        S->Right = AddElementIntoTree(X, S->Right);
    
    return S;
}

Position DeleteElement(int X, Position S) {

    Position temp = NULL;

    if(S == NULL) 
        printf("Elementa nema unutar stabla!\n");

    else if(S->Number > X) 
        S->Left = DeleteElement(X, S->Left);

    else if(S->Number < X)
        S->Right = DeleteElement(X, S->Right);

    else if(S->Left != NULL && S->Right != NULL) {

        temp = FindMin(S->Right);
        S->Number = temp->Number;
        S->Right = DeleteElement(S->Number, S->Right);
    }

    else {

        temp = S;

        if(S->Left == NULL)
            S = S->Right;

        else
            S = S->Left;

        free(temp);
    }

    return S;
}

Position FindElement(int keyVal, Position S) {

    int i = 0;

    for(i = 0; i < 1; i++) {

        if(S == NULL)
            return NULL;

        else if(S->Number > keyVal)
            return FindElement(keyVal, S->Left);

        else if(S->Number < keyVal)
            return FindElement(keyVal, S->Right);

        else    
            return S;
    }

    return S;
}

Position FindMin(Position S) {

    if(S == NULL)
        return NULL;

    else if(S->Left == NULL)
        return S;
    
    else    
        return FindMin(S->Left);
}

int AddRootElement(int X, Position S) {

    X = 1;
 
    while (X != 0) {  //ako je 0 korjen stabla, stablo je besmisleno, ali moze biti i 0 jer se while petlja svakako vrti samo 1 put

        printf("Unsite korjen stabla: ");
        scanf("%d",&X);

        puts("");

        if(X != 0)
            return X;
    }

    return X;
}
