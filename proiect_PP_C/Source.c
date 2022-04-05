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
#include "adaugareInStructuriIntrebari.h"
#include "quiz.h"
#include "stergereIntrebari.h"
#include "clasament.h"
#include "afisareClasament.h"
#include "meniuUser.h"
#include "meniuAdmin.h"
#include "parolaAdmin.h"
#include "initializareNumeFisiere.h"
#include "reguli.h"



void paginaPrincipala(char *clasament,char* intrebariScurte, char *intrebariGrila, char *parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank,int *contor,int* contorStocIntrebari,char parola[],int* contorIntrebariScurt,int* contorIntrebariGrila)
{
    opprinicipala();
    while (1)
    {
        char optiune[10];
        printf("\n\tOptiunea dumneavoastra: ");
        gets(optiune);

        int statusUser = 0;
        if ((*contorStocIntrebari) == 0) {
            stocareIntrebari(contorIntrebariScurt, contorIntrebariGrila, clasament, intrebariScurte, intrebariGrila, scurte, grila, contorStocIntrebari,contorIntrebariScurt,contorIntrebariGrila);
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
                    if (statusUser == 2 && rank->primul == NULL)
                    {
                        printf("\n\tNu aveti cum sa fiti utilizator existent intrucat jocul nu a fost jucat de nimeni.\n\n");
                        statusUser = 1;
                    }
                    optiuniUser(clasament,intrebariScurte,intrebariGrila,parolaAdmin, *contorIntrebariScurt, *contorIntrebariGrila,scurte,grila,rank,contor,statusUser,contorStocIntrebari,parola);
                    break;
                case 2:
                    if (verificareParolaAdministrator(parola) == 1) {
                        system("cls");
                        optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin,scurte,grila,rank,contor,contorStocIntrebari,parola,contorIntrebariScurt,contorIntrebariGrila);
                    }
                    else {
                        system("cls");
                        printf("\tParola gresita. Nu aveti permisiunea de a va loga ca administrator\n\n");
                    }
                    break;
                case 4:
                    mutareDateInFisier(rank, clasament);
                    plasareParolaNouaInFisier(parola, parolaAdmin);
                    completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 1);
                    completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 2);
                    system("cls");
                    printf("\tAi parasit jocul");
                    exit(0);
                case 3:
                    system("cls");
                    reguli();
                    meniuReguli(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari,parola,contorIntrebariScurt,contorIntrebariGrila);
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
    printf("\t\tSe incarca...\n\n");
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
    int contor = 0,contorStocIntrebari=0,contorIntrebariScurt = 0,contorIntrebariGrila = 0;
    clasament = initializare();
    intrebariScurte = initializare();
    intrebariGrila = initializare();
    parolaAdmin = initializare();

    numeFisiere(clasament, intrebariScurte, intrebariGrila,parolaAdmin);
    extragereParolaAdmin(parola, parolaAdmin);
    paginaPrincipala(clasament,intrebariScurte,intrebariGrila,parolaAdmin,&scurte,&grila,&rank,&contor,&contorStocIntrebari,parola,&contorIntrebariScurt,&contorIntrebariGrila);

    free(clasament);
    free(intrebariScurte);
    free(intrebariGrila);
    free(parolaAdmin);

    return 0;
}
