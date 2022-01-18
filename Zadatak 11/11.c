#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX (1024)

struct _tree;
typedef struct _tree* position_tree;
typedef struct _tree {

    char cityName[MAX];
    int peopleNumb;
    position_tree left;
    position_tree right;
}tree;

struct _linkedList;
typedef struct _linkedList* position_list;
typedef struct _linkedList {

    char stateName[MAX];
    position_tree next_tree;
    position_list next;
}linkedList;

struct _hashTable;
typedef struct _hashTable* position_hash;
typedef struct _hashTable {

    position_list next_hash_el;
}hashTable;

int hashFormula(char stateName[]);                                                                      //vraca indeks hash tablice a prima zbroj prvih pet slova po ASCII vrijednosti
position_list createHeadList();                                                                         //kreira head element vezanih lista
int readFromFile(char fileName[], hashTable hashArray[]);                                               //cita imena drzava i dodatnih datoteka iz glavne datoteke
position_list createListElement(char stateName[]);                                                      //kreira element vezane liste sa imenom drzave
int insertIntoList(position_list newElement, position_list head);                                       //unosimo u vezanu listu drzave
position_tree createTreeRoot();                                                                         //kreira root element stabla
position_tree insertIntoTree(position_tree root, char cityName[], int population);                      //unosimo gradove sa imenom i brojem stanovnika u stablo
position_tree creteTreeElement(char cityName[], int peopleNumb);                                        //radimo elemnt stabla sa imenom i brojem stanovnika
int printInorder(position_tree root);                                                                   //inorder ispis stabla u kojem se nalaze gradovi i brojs stanovnika
int readFromAdditionalFile(position_list head, char additionalFile[]);                                  //cita gradove iz filea sa imenom grada i brojem stanovnika
position_list findStateByName(hashTable hashArray[], char stateName[]);                                 //pretrazujemo hash tablicu i vezanu listu i trazimo drzavu po imenu     
/*napravio pretrazivanje gradova po imenu, kasnije skuzio da je trebalo po br. st*/
position_tree findCityByName(position_tree current, char cityName[]);                                   //pretrazujemo stablo i trazimo postoji li grad sa trazenim unesenim imenom
int Menu(hashTable hashArray[]);                                                                        //jednostavni menu za pretrazivanje

int main() {

    hashTable hashArray[11];
    int i = 0;

    for(i = 0 ; i < 11 ; i++) 
        hashArray[i].next_hash_el = NULL;
    
    for(i = 0 ; i < 11 ; i++) 
        hashArray[i].next_hash_el = createHeadList();

    readFromFile("stateFile.txt", hashArray);

    Menu(hashArray);

    return 0;
}

position_list createHeadList() {

    position_list head = NULL;

    head = (position_list)malloc(sizeof(linkedList));

    if(!head) {

        printf("Memorija za head element vezane liste se ne moze alocirati!\n");
        return NULL;
    }

    strcpy(head->stateName, "");
    head->next = NULL;
    head->next_tree = NULL;
    head->next = NULL;

    return head;
}

int readFromFile(char fileName[], hashTable hashArray[]) {

    FILE* fp = NULL;
    char* buffer = NULL;
    char stateName[MAX] = { 0 };
    char additionalFile[MAX] = { 0 };
    int byteNumb = 0;
    int hashIndex = 0;
    position_list newElement = NULL;

    newElement = (position_list)malloc(sizeof(linkedList));

    if(!newElement) {

        printf("NIje moguce alocirati memoriju za novi element vezane liste!\n");
        return -1;
    }

    buffer = (char*)malloc(MAX * sizeof(char));

    if(!buffer) {

        printf("Memorija za buffer se ne moze alocirati!\n");
        return -1;
    }

    fp = fopen(fileName, "r");

    if(!fp) {

        printf("File se ne moze otvoriti!\n");
        return -1;
    }

    while(!feof(fp)) {

        fgets(buffer, MAX, fp);

        if(sscanf(buffer, "%s %s %n", stateName, additionalFile, &byteNumb) == 2) {

            hashIndex = hashFormula(stateName);

            newElement = createListElement(stateName);

            insertIntoList(newElement, hashArray[hashIndex].next_hash_el);

            printf("Drzava: %s gradovi:\n", newElement->stateName);

            readFromAdditionalFile(newElement, additionalFile);

            buffer += byteNumb;
        }

        else {

            printf("Nesto nije uredu sa formatom vaseg filea!\nMolim, prmjenite format!\n");
            printf("Format: [ime drzave] [razmak] [Gradovi_[ime drzave].txt]\n");
            return -1;
        }
    }
    

    fclose(fp);

    return 0;
}

int hashFormula(char stateName[]) {

    int hashIndex = 0;
    int i = 0;
    char additionArray[5] = { 0 };

    for(i = 0 ; i < 5 ; i++)
        additionArray[i] = stateName[i];

    for(i = 0 ; i < 5  ; i++) 
        hashIndex += additionArray[i];

    hashIndex = hashIndex %11;

    return hashIndex;
}

position_list createListElement(char stateName[]) {

    position_list newElement = NULL;

    newElement = (position_list)malloc(sizeof(linkedList));

    if(!newElement) {

        printf("Memorija za novi element vezane liste ne moze biti alocirana!\n");
        return NULL;
    }

    strcpy(newElement->stateName, stateName);
    newElement->next = NULL;
    newElement->next_tree = createTreeRoot();

    return newElement;
}

int insertIntoList(position_list newElement, position_list head) {

    if(head->next == NULL) {

        head->next = newElement;
        newElement->next = NULL;
    }

    else {

        while (head->next != NULL && (strcmp(head->next->stateName, newElement->stateName) < 0))
            head = head->next;

        newElement->next = head->next;
        head->next = newElement;       
    }

    return 0;
}

position_tree createTreeRoot() {

    position_tree root = NULL;

    root = (position_tree)malloc(sizeof(tree));

    if(!root) {

        printf("Memorija za root ne moze biti alocirana!\n");
        return NULL;
    }

    strcpy(root->cityName, "");
    root->left = NULL;
    root->right = NULL;
    root->peopleNumb = 0;

    return	root;
}   

position_tree insertIntoTree(position_tree root, char cityName[], int population) {

    if(root == NULL) {

        root = (position_tree)malloc(sizeof(tree));
        strcpy(root->cityName, cityName);
        root->peopleNumb = population;
        root->left = NULL;
        root->right = NULL;
    }

    if(root->peopleNumb > population)
        root->left = insertIntoTree(root->left, cityName, population);
    
    else if (root->peopleNumb < population)
        root->right = insertIntoTree(root->right, cityName, population);
    
    return root;
}

position_tree creteTreeElement(char cityName[], int peopleNumb) {

    position_tree newElement = NULL;

    newElement = (position_tree)malloc(sizeof(tree));

    if(!newElement) {

        printf("Memorija za novi element stabla ne moze se alocirati!\n");
        return NULL;
    }

    strcpy(newElement->cityName, cityName);
    newElement->peopleNumb = peopleNumb;
    newElement->left = NULL;
    newElement->right = NULL;

    return newElement;
}

int printInorder(position_tree root) {

    if(root == NULL) 
        return 0;

    printInorder(root->left);

    if(root->peopleNumb != 0)
        printf("Grad: %s    Populacija:%d\n", root->cityName, root->peopleNumb);

    printInorder(root->right);

    return 0;
}

int readFromAdditionalFile(position_list head, char additionalFile[]) {

    FILE* fp = NULL;
    char cityName[MAX] = { 0 };
    int population = 0;
    char* buffer = NULL;
    int byteNumb = 0;
    position_tree newElement = NULL;
    position_tree root = head->next_tree; 

    buffer = (char*)malloc(MAX * sizeof(char));

    if(!buffer) {

        printf("Memorija za buffer se ne moze alocirati!\n");
        return -1;
    }

    fp = fopen(additionalFile, "r");

    if(!fp) {

        printf("Fileu %s ne moze se pristupiti!\n", additionalFile);
        return -1;
    }

    while(!feof(fp)) {

        fgets(buffer, MAX, fp);

        if(sscanf(buffer, "%s %d %n", cityName, &population, &byteNumb) == 2) {

            newElement = createTreeRoot();

            newElement =  insertIntoTree(root, cityName, population);

            buffer += byteNumb;
        }

        else {

            printf("Nesto nije uredu sa formatom vaseg filea!\nMolim, prmjenite format!\n");
            printf("Format: [ime grada] [razmak] [broj stanovnika]\n");
            return -1;           
        }
    }

    printInorder(newElement);  
    puts("");

    fclose(fp);

    return 0;
}

position_list findStateByName(hashTable hashArray[], char stateName[]) {

    position_list keyVal = NULL;
    position_list current = hashArray[0].next_hash_el;
    int hashIndex = 0;

    keyVal = (position_list)malloc(sizeof(linkedList));

    if(!keyVal) {

        printf("Memorija za keyVal [pretrazivanje] nije alocirana!\n");
        return NULL;
    }

    current = (position_list)malloc(sizeof(linkedList));

    if(!current) {

        printf("Memorija za current [pretrazivanje] nije alocirana!\n");
        return NULL;
    }

    hashIndex = hashFormula(stateName);

    current = hashArray[hashIndex].next_hash_el;

    while (current->next != NULL && (strcmp(current->next->stateName, stateName)))
        current = current->next;
    
    if((strcmp(stateName, current->next->stateName))) {

        printf("Drazava ne postoji!\n");
        return NULL;
    }

    current = current->next;

    return current;
}

position_tree findCityByName(position_tree current, char cityName[]) {

    int i = 0;

    for(i = 0; i < 1; i++) {

        if(current == NULL)
            return NULL;

        else if(strcmp(current->cityName, cityName) > 0)
            return findCityByName(current->left, cityName);

        else if(strcmp(current->cityName, cityName) < 0)
            return findCityByName(current->right, cityName);

        else    
            return current;
    }

    return current;
}

int Menu(hashTable hashArray[]) {

    int key = 0;
    char stateName[MAX] = { 0 };
    char cityName[MAX] = { 0 };
    position_list currentList = NULL;
    position_tree currentTree = NULL;
    position_tree temp = NULL;

    currentList = (position_list)malloc(sizeof(linkedList));

    if(!currentList) {

        printf("Memorija za listu [pretrazivanje] ne moze biti alocirana!\n");
        return -1;
    }
    
    currentTree = (position_tree)malloc(sizeof(tree));

    if(!currentTree) {

        printf("Memorija za stablo [pretrazivanje] ne moze biti alocirana!\n");
        return -1;
    }

    temp = (position_tree)malloc(sizeof(tree));

    while(key != 2) {

        printf("Zelite li pretrazivati?\n");
        printf("1-DA\n2-NE\n");
        scanf("%d", &key);

        if(key == 1) {

            printf("Unesite ime drzave: ");
            scanf(" %s", stateName);

            currentList = findStateByName(hashArray, stateName);

            if(!currentList) 
                printf("Ta drzava ne postoji!\n");

            else {

                printf("Drzava: %s je pronadjena!\n", currentList->stateName);
                printf("Gradovi drzave su:\n");
                printInorder(currentList->next_tree);

                printf("Unseite ime grada: ");
                scanf(" %s", cityName);

                temp = currentList->next_tree;

                currentTree = findCityByName(temp, cityName);

                if(!currentTree) 
                    printf("Grada nema!\n");

                else
                    printf("Grad: %s    Populacija: %d\n", currentTree->cityName, currentTree->peopleNumb);               
            }          
        }

        else if(key == 2) {

            printf("Dovidjenja!\n\n");
            return 0;
        }

        else 
            printf("Netocan unos, pokusajte ponovo!\n");
    }

    return 0;
}
