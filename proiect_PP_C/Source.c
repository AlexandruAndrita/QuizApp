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


void incepeQuiz(int contorIntrebariScurt,int contorIntrebariGrila,char* parolaAdmin,char* clasament, char* intrebariScurte, char* intrebariGrila, struct lista *scurte, struct lista *grila, struct lista *rank,int* contor)
{
    char numeJucator[50];
    int runda = 0;
    memset(numeJucator, 0, 50);
    printf("\tIntroduceti-va numele:\n");
    printf("\t");
    gets(numeJucator);
    
    while (1)
    {
        if (cautare(rank,numeJucator) == 1)
            break;
        else {
            printf("\n\tNumele introdus este luat.\n\tIncercati sa introduceti alt nume.\n\n");
            memset(numeJucator, 0, 50);
            printf("\t");
            gets(numeJucator);
        }
    }
    system("cls");
    int catePuncte = 0;
    int catePuncteGrila = 0, catePuncteScurt = 0;
    optiuniQuiz();
    while (1)
    {
        printf("\t");
        char optiune[256];
        scanf("%s", optiune);
       
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            if (numar != 4 && numar != 1 && numar != 2 && numar != 3)
            {
                system("cls");
                printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
            }
            else {
                if (numar == 4)
                {
                    mutareDateInFisier(rank, clasament);
                    system("cls");
                    printf("\tAi parasit jocul");
                    exit(0);
                }
                if (numar == 1)
                {
                    if (runda >= 1)
                    {
                        system("cls");
                        printf("\tAti jucat deja o runda.\n\tPuteti rejuca cu alt nume\n\n");
                        getchar();
                        break;
                    }
                    runda++;
                    system("cls");
                    printf("\n\tDoriti un test grila sau un test cu raspunsuri scurte?\n\t[1] Grila (Tasta 1)\n\t[2] Raspuns scurt (Tasta 2)\n\n");
                    char opt[10];
                    int numarOptiune = 0;
                    memset(opt, 0, 10);
                    while (1)
                    {
                        printf("\t");
                        scanf("%s", opt);
                        if (validareInput(opt) == 1)
                        {
                            numarOptiune = atoi(opt);
                            if (numarOptiune == 1 || numarOptiune == 2)
                                break;
                            else
                            {
                                system("cls");
                                printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
                                //printf("Doriti un test grila sau un test cu raspunsuri scurte?\n 1. Grila (Tasta 1)\n 2. Raspuns scurt (Tasta 2)\n");
                            }
                        }
                        else
                        {
                            system("cls");
                            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
                            //printf("Doriti un test grila sau un test cu raspunsuri scurte?\n 1. Grila (Tasta 1)\n 2. Raspuns scurt (Tasta 2)\n");
                        }
                    }
                    if (numarOptiune == 1)
                    {
                        system("cls");

                        clock_t start_t, end_t, total_t;
                        start_t = 0;
                        end_t = 0;
                        total_t = 0;
                        catePuncte = quizGrila(contorIntrebariGrila,grila,&start_t,&end_t,&total_t);
                        long timp = total_t;

                        printf("\n\tScorul tau este: %d / %d\n\tAi completat quiz-ul in %ld secunde\n\n", catePuncte, 5,timp);
                        adaugareJucatorNou(rank, numeJucator, catePuncte, timp);
                    }
                    else {
                        system("cls");

                        clock_t start_t, end_t, total_t;
                        start_t = 0;
                        end_t = 0;
                        total_t = 0;
                        catePuncte = quizScurt(contorIntrebariScurt,scurte,&start_t,&end_t,&total_t);
                        long timp = total_t;

                        printf("\n\tScorul tau este: %d / %d\n\tAi completat quiz-ul in %ld secunde\n\n", catePuncte, 5,timp);
                        adaugareJucatorNou(rank, numeJucator, catePuncte, timp);
                    }
                    
                }
                if (numar == 2)
                {
                    getchar();
                    system("cls");
                    paginaPrincipala(clasament,intrebariScurte,intrebariGrila,parolaAdmin,scurte,grila,rank,contor);
                    
                }
                if (numar == 3)
                {
                    system("cls");
                    afisareClasament(rank);
                }
            }
        }
        else
        {
            system("cls");
            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
        }
        optiuniQuiz();
    }
}

void tipIntrebare(char* clasament, char* intrebariScurte, char* intrebariGrila,char *parolaAdmin,struct lista* scurte, struct lista* grila, struct lista* rank,int *contor)
{
    tipIntrebareQ();
    while (1)
    {
        printf("\t");
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 3:
                system("cls");
                optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin,scurte,grila,rank,contor);
                break;
            case 1:
                system("cls");
                adaugareRaspunsScurt(intrebariScurte);
                break;
            case 2:
                system("cls");
                adaugareRaspunsMultiplu(intrebariGrila);
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
        tipIntrebareQ();
    }
}

void optiuniUser(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin,int contorIntrebariScurt,int contorIntrebariGrila, struct lista *scurte, struct lista *grila, struct lista *rank,int *contor)
{
    opuser();
    while (1)
    {
        printf("\t");
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 4:
                mutareDateInFisier(rank, clasament);
                system("cls");
                printf("\tAi parasit jocul");
                exit(0);
            case 1:
                afisareClasament(rank);
                break;
            case 2:
                system("cls");
                incepeQuiz(contorIntrebariScurt, contorIntrebariGrila,parolaAdmin, clasament, intrebariScurte, intrebariGrila,scurte,grila,rank,contor);
                break;
            case 3:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin,scurte,grila,rank,contor);
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
        opuser();
    }
}

void paginaPrincipala(char *clasament,char* intrebariScurte, char *intrebariGrila, char *parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank,int *contor)
{
    opprinicipala();
    while (1)
    {
        char optiune[256];
        printf("\t");
        gets(optiune);

        /*preia intrebarile din fisier la inceput, cand se deschide aplicatie*/
        /*
        Chiar daca adminul adauga intrebari, dupa cand rejoci in aceiasi tura o sa ajunga sa reincarce intrebarile.
        Astfel nu o sa fie intrebari adaugate care sa fie pierdute daca in aceiasi runda sunt si adaugate
        */
        int contorIntrebariScurt = 0;
        int contorIntrebariGrila = 0;
        stocareIntrebari(&contorIntrebariScurt, &contorIntrebariGrila, clasament, intrebariScurte, intrebariGrila,scurte,grila);

        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
                case 1:
                    system("cls");
                    if((*contor)==0)
                        preluareNumeDinFisier(rank, clasament);
                    (*contor)++;
                    optiuniUser(clasament,intrebariScurte,intrebariGrila,parolaAdmin, contorIntrebariScurt, contorIntrebariGrila,scurte,grila,rank,contor);
                    break;
                case 2:
                    if (verificareParolaAdministrator(parolaAdmin) == 1) {
                        system("cls");
                        optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin,scurte,grila,rank,contor);
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
                    meniuReguli(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor);
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

void meniuReguli(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor)
{
    optiuniReguli();
    while (1)
    {
        char optiune[256];
        printf("\t");
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 1:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor);
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

int main() {
    printf("\t\tQuizApp\n\n");
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

    int contor = 0;
    numeFisiere(clasament, intrebariScurte, intrebariGrila,parolaAdmin);
    paginaPrincipala(clasament,intrebariScurte,intrebariGrila,parolaAdmin,&scurte,&grila,&rank,&contor);

    free(clasament);
    free(intrebariScurte);
    free(intrebariGrila);
    free(parolaAdmin);

    return 0;
}
