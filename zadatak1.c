#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student
{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
}student;

int procitajBrojRedakaIzDatoteke(char* nazivDatoteke);          //funkcija vraca broj redaka tj. studenata
student* alocirajMemoriju(int brojSutdenata,char* nazivDatoteke);   //funkcija koja ce sa brojem studenata zauzeti potrebnu memoriju
void ispisNaEkran(char*nazivDatoteke,int brojSutdenata);        //funkcija za ispis studenata na standardni izlaz tj. ekran            

int main()
{
    int i=0,brRedaka=0;
    FILE* dat=NULL;
    student* s;
    char* nazivDatoteke = NULL;
    
    printf("Unesite ime datoteke:\n");
    scanmf(" %s",&nazivDatoteke);
    
    dat=fopen(nazivDatoteke,"r");
    
    brRedaka=procitajBrojRedakaIzDatoteke(nazivDatoteke);
    s=alocirajMemoriju(brRedaka,nazivDatoteke);

    ispisNaEkran(nazivDatoteke,brRedaka);    
    
    fclose(dat);

    return 0;
}

int procitajBrojRedakaIzDatoteke(char* nazivDatoteke)
{
    int brojac=0;
    FILE* dat=NULL;
    char buffer[MAX_LINE]={0};
    
    dat=fopen(nazivDatoteke,"r");
    
    if(!dat)
    {
        printf("Greska pri otvaranju Vase datoteke!\n");
        return -1;
    }
    while(!feof(dat)) 
    {
        fgets(buffer,MAX_LINE,dat);
        brojac++;
    }
    
    fclose(dat);
    
    return brojac;
}

student* alocirajMemoriju(int brojSutdenata,char* nazivDatoteke)
{
    int brojac=0;
    FILE* dat=NULL;
    student* studenti=NULL;

    studenti=(student*)malloc(brojSutdenata*sizeof(student));
    
    dat=fopen(nazivDatoteke,"r");
    
    if(!dat)
    {
        printf("Greska prilikom alociranja memeorije!\n");
        free(studenti);
        return NULL;
    }
    while(!feof(dat))
    {
        fscanf(dat," %s %s %lf",studenti[brojac].ime,studenti[brojac].prezime,&studenti[brojac].bodovi);
        brojac++;
    }
    
    fclose(dat);
    
    return studenti;
}

void ispisNaEkran(char*nazivDatoteke,int brojSutdenata)
{
    int i=0;
    FILE* dat=NULL;
    student* s;
    double max=0.0;
    
    s=(student*)malloc(brojSutdenata*sizeof(student));
    
    dat=fopen(nazivDatoteke,"r");
     if(!dat)
    {
        printf("Greska prilikom otcaranja!\n");
    }
    
    for(i=0;i<brojSutdenata;i++)
    {
        fscanf(dat," %s %s %lf",s[i].ime,s[i].prezime,&s[i].bodovi);
    }
    
    max=s[0].bodovi;
    
    for(i=1;i<brojSutdenata;i++)
    {
        if(max<s[i].bodovi)
            max=s[i].bodovi;
    }
    
    for(i=0;i<brojSutdenata;i++)
    {
        printf("Rezultati:\n");
        printf("Ime: %s Prezime: %s Bodovi(apsloutni): %lf Bodovi(relativni): %lf\n",s[i].ime,s[i].prezime,s[i].bodovi,s[i].bodovi/max*100);
    }
    
    fclose(dat);
}
