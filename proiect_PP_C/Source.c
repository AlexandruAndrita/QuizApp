#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>


#include "prototipuri.h"
#include "structuri.h"
#include "optiuni.h"
#include "admin.h"
#include "stocareIntrebari.h"
#include "adaugareInFisierIntrebari.h"
#include "quiz.h"
#include "stergereIntrebari.h"
#include "clasament.h"
#include "afisareClasament.h"
#include "meniuUser.h"
#include "meniuAdmin.h"



void verificareStatusUser(int *nou)
{
    optiuniStatusUser();
    while (*nou==0)
    {
        printf("\t");
        char optiune[15];
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch(numar)
            {
            case 1:
                system("cls");
                *nou = 1;
                break;
            case 2:
                system("cls");
                *nou = 2;
                break;
            default:
                system("cls");
                printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
            }
        }
        else
        {
            system("cls");
            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
        }
        optiuniStatusUser();
    }
}

void paginaPrincipala(char *clasament,char* intrebariScurte, char *intrebariGrila, char *parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank,int *contor,int* contorStocIntrebari)
{
    opprinicipala();
    while (1)
    {
        char optiune[15];
        printf("\t");
        gets(optiune);

        /*preia intrebarile din fisier la inceput, cand se deschide aplicatie*/
        /*
        Chiar daca adminul adauga intrebari, dupa cand rejoci in aceiasi tura o sa ajunga sa reincarce intrebarile.
        Astfel nu o sa fie intrebari adaugate care sa fie pierdute daca in aceiasi runda sunt si adaugate
        */
        int contorIntrebariScurt = 0;
        int contorIntrebariGrila = 0;
        int statusUser = 0;
        if ((*contorStocIntrebari) == 0) {
            stocareIntrebari(&contorIntrebariScurt, &contorIntrebariGrila, clasament, intrebariScurte, intrebariGrila, scurte, grila, contorStocIntrebari);
            (*contorStocIntrebari)++;
        }

        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
                case 1:
                    system("cls");
                    if((*contor)==0)
                        preluareNumeDinFisier(rank, clasament);
                    (*contor)++;
                    verificareStatusUser(&statusUser);
                    system("cls");
                    optiuniUser(clasament,intrebariScurte,intrebariGrila,parolaAdmin, contorIntrebariScurt, contorIntrebariGrila,scurte,grila,rank,contor,statusUser,contorStocIntrebari);
                    break;
                case 2:
                    if (verificareParolaAdministrator(parolaAdmin) == 1) {
                        system("cls");
                        optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin,scurte,grila,rank,contor,contorStocIntrebari);
                    }
                    else {
                        system("cls");
                        printf("\tParola gresita. Nu aveti permisiunea de a va loga ca administrator\n\n");
                    }
                    break;
                case 4:
                    mutareDateInFisier(rank, clasament);
                    system("cls");
                    printf("\tAi parasit jocul");
                    exit(0);
                case 3:
                    system("cls");
                    reguli();
                    meniuReguli(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari);
                    break;
                default:
                    system("cls");
                    printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
            }
        }
        else
        {
            system("cls");
            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
        }
        opprinicipala();
    }
}

void meniuReguli(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor,int *contorStocIntrebari)
{
    optiuniReguli();
    while (1)
    {
        char optiune[15];
        printf("\t");
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 1:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari);
                break;
            case 2:
                system("cls");
                printf("\tAti parasit jocul.");
                exit(0);
            default:
                system("cls");
                printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
            }
        }
        else
        {
            system("cls");
            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
        }
        optiuniReguli();
    }
}

int validareInput(char optiune[])
{
    int n = strlen(optiune);
    for (int i = 0; i < n; i++)
    {
        if (strchr("1234567890", optiune[i]) == 0)
            return 0;
    }
    return 1;
}

char* initializare()
{
    char* numeFisier = (char*)malloc(20* sizeof(char));
    if (numeFisier != NULL) {
        for (int i = 0; i < 20; i++)
            numeFisier[i] = 0;
    }
    return numeFisier;
}

void numeFisiere(char* clasament, char* intrebariScurte, char* intrebariGrila, char *parolaAdmin)
{
    strcpy(clasament, "clasament.txt");
    strcpy(intrebariScurte, "scurtraspIntrebari.txt");
    strcpy(intrebariGrila, "mulraspIntrebari.txt");
    strcpy(parolaAdmin, "parolaAdmin.txt");
}

void progressBar()
{
    //Beep(700, 1000); -->fara Beep la predare
    char var1 = 177, var2 = 219;
    printf("\tLoading...\n\n");
    printf("\t");
    for (int i = 0; i < 20; i++)
        printf("%c", var1);
    printf("\r");
    printf("\t");
    for (int i = 0; i < 20; i++) {
        printf("%c", var2);
        Sleep(300);
    }
    system("cls");
}

int main() {
    printf("\t\tQuizApp\n\n\n");
    progressBar();
    srand(time(0));

    struct lista scurte;
    struct lista grila;
    struct lista rank;
    scurte.head = NULL;
    grila.cap = NULL;
    rank.primul = NULL;

    char* clasament = initializare();
    char* intrebariScurte = initializare();
    char* intrebariGrila = initializare();
    char* parolaAdmin = initializare();

    int contor = 0,contorStocIntrebari=0;
    numeFisiere(clasament, intrebariScurte, intrebariGrila,parolaAdmin);
    paginaPrincipala(clasament,intrebariScurte,intrebariGrila,parolaAdmin,&scurte,&grila,&rank,&contor,&contorStocIntrebari);

    free(clasament);
    free(intrebariScurte);
    free(intrebariGrila);
    free(parolaAdmin);

    return 0;
}
