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
#include "parolaAdmin.h"
#include "initializareNumeFisiere.h"



void paginaPrincipala(char *clasament,char* intrebariScurte, char *intrebariGrila, char *parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank,int *contor,int* contorStocIntrebari,char parola[])
{
    opprinicipala();
    while (1)
    {
        char optiune[10];
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
                    optiuniUser(clasament,intrebariScurte,intrebariGrila,parolaAdmin, contorIntrebariScurt, contorIntrebariGrila,scurte,grila,rank,contor,statusUser,contorStocIntrebari,parola);
                    break;
                case 2:
                    if (verificareParolaAdministrator(parola) == 1) {
                        system("cls");
                        optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin,scurte,grila,rank,contor,contorStocIntrebari,parola);
                    }
                    else {
                        system("cls");
                        printf("\tParola gresita. Nu aveti permisiunea de a va loga ca administrator\n\n");
                    }
                    break;
                case 4:
                    mutareDateInFisier(rank, clasament);
                    plasareParolaNouaInFisier(parola, parolaAdmin);
                    system("cls");
                    printf("\tAi parasit jocul");
                    exit(0);
                case 3:
                    system("cls");
                    reguli();
                    meniuReguli(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari,parola);
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

void meniuReguli(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor,int *contorStocIntrebari,char parola[])
{
    optiuniReguli();
    while (1)
    {
        char optiune[10];
        printf("\t");
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 1:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari,parola);
                break;
            case 2:
                plasareParolaNouaInFisier(parola, parolaAdmin);
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

void progressBar()
{
    char var1 = 177, var2 = 219;
    printf("\t\tLoading...\n\n");
    printf("\t\t");
    for (int i = 0; i < 25; i++)
        printf("%c", var1);
    printf("\r");
    printf("\t\t");
    for (int i = 0; i < 25; i++) {
        printf("%c", var2);
        Sleep(90);
    }
    system("cls");
}


int main() {
    printf("\t\t\tQuizApp\n\n\n");
    progressBar();
    srand(time(0));

    struct lista scurte;
    struct lista grila;
    struct lista rank;
    scurte.head = NULL;
    grila.cap = NULL;
    rank.primul = NULL;

    char* clasament;
    char* intrebariScurte;
    char* intrebariGrila;
    char* parolaAdmin;
    char parola[20];
    memset(parola, 0, 20);
    int contor = 0,contorStocIntrebari=0;
    clasament = initializare();
    intrebariScurte = initializare();
    intrebariGrila = initializare();
    parolaAdmin = initializare();

    numeFisiere(clasament, intrebariScurte, intrebariGrila,parolaAdmin);
    extragereParolaAdmin(parola, parolaAdmin);
    paginaPrincipala(clasament,intrebariScurte,intrebariGrila,parolaAdmin,&scurte,&grila,&rank,&contor,&contorStocIntrebari,parola);

    free(clasament);
    free(intrebariScurte);
    free(intrebariGrila);
    free(parolaAdmin);

    return 0;
}
