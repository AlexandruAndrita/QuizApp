#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "prototipuri.h"
#include "structuri.h"
#include "optiuni.h"
#include "admin.h"
#include "stocareIntrebari.h"
#include "adaugareInFisierIntrebari.h"
#include "quiz.h"
#include "stergereIntrebari.h"



void incepeQuiz(int contorIntrebariScurt,int contorIntrebariGrila,char* clasament, char* intrebariScurte, char* intrebariGrila, struct lista *scurte, struct lista *grila, struct lista *rank)
{
    char numeJucator[50];
    memset(numeJucator, 0, 50);
    printf("Introduceti-va numele\n");
    gets(numeJucator);
    
    while (1)
    {
        if (cautare(numeJucator,clasament) == 1)
            break;
        else {
            printf("Numele introdus este luat\n");
            memset(numeJucator, 0, 50);
            gets(numeJucator);
        }
    }
    
    int catePuncte = 0;
    int catePuncteGrila = 0, catePuncteScurt = 0;
    optiuniQuiz();
    while (1)
    {
        
        char optiune[256];
        scanf("%s", optiune);
       
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            if (numar != 4 && numar != 1 && numar != 2 && numar != 3)
            {
                printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
            }
            else {
                if (numar == 4)
                {
                    printf("Ai parasit jocul");
                    exit(0);
                }
                if (numar == 1)
                {
                    printf("Doriti un test grila sau un test cu raspunsuri scurte?\n 1. Grila (Tasta 1)\n 2. Raspuns scurt (Tasta 2)\n");
                    char opt[10];
                    int numarOptiune = 0;
                    memset(opt, 0, 10);
                    while (1)
                    {
                        scanf("%s", opt);
                        if (validareInput(opt) == 1)
                        {
                            numarOptiune = atoi(opt);
                            if (numarOptiune == 1 || numarOptiune == 2)
                                break;
                            else
                            {
                                printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
                                printf("Doriti un test grila sau un test cu raspunsuri scurte?\n 1. Grila (Tasta 1)\n 2. Raspuns scurt (Tasta 2)\n");
                            }
                        }
                        else
                        {
                            printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
                            printf("Doriti un test grila sau un test cu raspunsuri scurte?\n 1. Grila (Tasta 1)\n 2. Raspuns scurt (Tasta 2)\n");
                        }
                    }
                    if (numarOptiune == 1)
                    {
                        catePuncte = quizGrila(contorIntrebariGrila,grila);
                        printf("Scorul tau este: %d / %d\n", catePuncte, 5);
                        FILE* cls;
                        cls = fopen(clasament, "a");
                        if (cls == NULL)
                        {
                            printf("Eroare! Fisierul nu poate fi accesat");
                            exit(1);
                        }
                        fprintf(cls, "%s %d / %d\n", numeJucator, catePuncte, 5);
                        fclose(cls);
                        printf("\n");
                    }
                    else {
                        catePuncte = quizScurt(contorIntrebariScurt,scurte);
                        printf("Scorul tau este: %d / %d\n", catePuncte, 5);
                        FILE* cls;
                        cls = fopen(clasament, "a");
                        if (cls == NULL)
                        {
                            printf("Eroare! Fisierul nu poate fi accesat");
                            exit(1);
                        }
                        fprintf(cls, "%s %d / %d\n", numeJucator, catePuncte, 5);
                        fclose(cls);
                        printf("\n");
                    }
                    
                }
                if (numar == 2)
                {
                    //optiuniUser();
                    //fflush(stdin);
                    //paginaPrincipala();
                    
                    //break;
                    printf("Nu este inca implementat");
                    exit(0);
                }
                if (numar == 3)
                {
                    stergeLista(rank);
                    alcatuireClasament(clasament,rank);
                    afisareClasament(rank);
                }
            }
        }
        else
        {
            printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
        }
        optiuniQuiz();
    }
}


/*partea de clasament*/
void stergeLista(struct lista *rank)
{
    struct ranking* prev = rank->primul;
    struct ranking* cur = (struct ranking*)malloc(sizeof(struct ranking));
    while (prev != NULL)
    {
        cur = prev->urmator;
        free(prev);
        prev = cur;
    }
    rank->primul = NULL;
}

int cautare(char s[],char *clasament)
{
    FILE* cls;
    cls = fopen(clasament, "r");
    if (cls == NULL)
    {
        printf("Eroare! Fisierul nu poate fi accesat");
        exit(1);
    }
    char rez[50], d[100];
    int k = 0, n = 0;
    memset(rez, 0, 50);
    while (fgets(rez, 50, cls))
    {
        memset(d, 0, 100);
        n = 0;
        k = strlen(rez);
        int i = 0;
        while (i < k-1)
        {
            if (rez[i]==' ' && rez[i + 1] >= '0' && rez[i + 1] <= '9')
                break;
            d[n++] = rez[i];
            i += 1;
        }
        d[n] = '\0';
        if (strcmp(d, s) == 0)
        {
            fclose(cls);
            return 0;
        }
    }
    fclose(cls);
    return 1;
}

int extrageScor(char s[])
{
    int numar = 0,n=strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '/')
            break;
        else
        {
            if (s[i] >= '0' && s[i] <= '9')
                numar = numar * 10 + (s[i] - '0');
        }
    }
    return numar;
}

void alcatuireClasament(char *clasament, struct lista *rank)
{
    FILE* cls;
    cls = fopen(clasament, "r");
    if (cls == NULL)
    {
        printf("Eroare! Fisierul nu poate fi accesat");
        exit(1);
    }
    char rez[50], d[100];
    int k = 0, n = 0;
    memset(rez, 0, 50);
    while (fgets(rez, 50, cls)) //citeste linie cu linie din fisier
    {
        struct ranking* elemNou = (struct ranking*)malloc(sizeof(struct ranking));
        k = strlen(rez);
        int i = 0;
        memset(d, 0, 100);
        n = 0;
        while (i < k)
        {
            if (rez[i] == ' ')
                break;
            d[n++] = rez[i];
            i += 1;
        }
        strcpy((*elemNou).nume, d);
        memset(d, 0, 100);
        n = 0;
        i += 1;
        int curent = 0, anterior = 0,stop=0;
        while (i < k - 1)
        {
            if (rez[i] == '/')
                stop = 1;
            if (stop == 0 && rez[i] >= '0' && rez[i] <= '9')
                curent = curent*10 + (rez[i] - '0');
            d[n++] = rez[i];
            i += 1;
        }
        strcpy((*elemNou).punctaj, d);
        memset(d, 0, 100);
        n = 0;
        (*elemNou).urmator = NULL;
        char p[50];
        memset(p, 0,50);
        if (rank->primul != NULL) {
            strcpy(p, rank->primul->punctaj);
            anterior = extrageScor(p);
        }
        if (rank->primul == NULL || curent>anterior)
        {
            (*elemNou).urmator = rank->primul;
            rank->primul = elemNou;
        }
        else
        {
            struct ranking* aux = rank->primul;
            strcpy(p, (*(*aux).urmator).punctaj);
            anterior = extrageScor(p);
            while ((*aux).urmator != NULL)
            {
                if (anterior <= curent)
                    break;
                if ((*(*aux).urmator).punctaj != NULL) {
                    strcpy(p, (*(*aux).urmator).punctaj);
                    anterior = extrageScor(p);
                }
                aux = (*aux).urmator;
            }
            (*elemNou).urmator = (*aux).urmator;
            (*aux).urmator = elemNou;
        }
    }
    fclose(cls);
}

void afisareClasament(struct lista *rank)
{
    struct ranking* elem = rank->primul;
    while (elem != NULL)
    {
        printf("%s %s\n", (*elem).nume, (*elem).punctaj);
        elem = (*elem).urmator;
    }
}




/*stergere intrebari*/






void tipIntrebare(char* clasament, char* intrebariScurte, char* intrebariGrila,char *parolaAdmin,struct lista* scurte, struct lista* grila, struct lista* rank)
{
    tipIntrebareQ();
    while (1)
    {
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 3:
                optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin,scurte,grila,rank);
                break;
            case 1:
                adaugareRaspunsScurt(intrebariScurte);
                break;
            case 2:
                adaugareRaspunsMultiplu(intrebariGrila);
                break;
            default:
                printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
            }
        }
        else
        {
            printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
        }
        tipIntrebareQ();
    }
}

void optiuniUser(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin,int contorIntrebariScurt,int contorIntrebariGrila, struct lista *scurte, struct lista *grila, struct lista *rank)
{
    opuser();
    while (1)
    {
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 4:
                printf("Ai parasit jocul");
                exit(0);
            case 1:
                stergeLista(clasament);
                alcatuireClasament(clasament,rank);
                afisareClasament(rank);
                break;
            case 2:
                incepeQuiz(contorIntrebariScurt, contorIntrebariGrila, clasament, intrebariScurte, intrebariGrila,scurte,grila,rank);
                break;
            case 3:
                //paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin);
                break;
            default:
                printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
            }
        }
        else
        {
            printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
        }
        opuser();
    }
}

void paginaPrincipala(char *clasament,char* intrebariScurte, char *intrebariGrila, char *parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank)
{
    opprinicipala();
    while (1)
    {
        char optiune[256];
        gets(optiune);

        /*preia intrebarile din fisier la inceput, cand se deschide aplicatie*/
        /*
        Chiar daca adminul adauga intrebari, dupa cand rejoci in aceiasi tura o sa ajunga sa reincarce intrebarile.
        Astfel nu o sa fie intrebari adaugate care sa fie pierdute daca in aceiasi runda sunt si adaugate
        */
        int contorIntrebariScurt = 0;
        int contorIntrebariGrila = 0;
        stocareIntrebari(&contorIntrebariScurt, &contorIntrebariGrila, clasament, intrebariScurte, intrebariGrila,scurte,grila);
        /*struct questions* a = scurte->head;
        while (a != NULL)
        {
            printf("%s %s\n", a->intrebare, a->raspuns);
            a = a->next;
        }
        exit(0);*/

        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
                case 1:
                    optiuniUser(clasament,intrebariScurte,intrebariGrila,parolaAdmin, contorIntrebariScurt, contorIntrebariGrila,scurte,grila,rank);
                    break;
                case 2:
                    if (verificareParolaAdministrator(parolaAdmin) == 1) {
                        optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin,scurte,grila,rank);
                    }
                    else {
                        printf("Parola gresita. Nu aveti permisiunea de a va loga ca administrator\n\n");
                    }
                    break;
                case 4:
                    system("cls");
                    printf("Ai parasit jocul");
                    exit(0);
                case 3:
                    system("cls");
                    reguli();
                    break;
                default:
                    printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
            }
        }
        else
        {
            printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
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
    printf("QuizApp\n");
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

    numeFisiere(clasament, intrebariScurte, intrebariGrila,parolaAdmin);
    paginaPrincipala(clasament,intrebariScurte,intrebariGrila,parolaAdmin,&scurte,&grila,&rank);

    free(clasament);
    free(intrebariScurte);
    free(intrebariGrila);
    free(parolaAdmin);

    return 0;
}
