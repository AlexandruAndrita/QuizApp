#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "prototipuri.h"
#include "structuri.h"
#include "optiuni.h"
#include "admin.h"



void stocareIntrebari(int *contorIntrebariScurt,int * contorIntrebariGrila,char* clasament, char* intrebariScurte, char* intrebariGrila)
{
    char listaIntrebari[150][150], listaRaspunsuri[150][150], linie[150];
    int k = 0, n = 0, t = 0, nrintrebari = 0, nrraspunsuri = 0;
    int ok = 1;
    char caracter;
    FILE* fptr;
    fptr = fopen(intrebariScurte, "r");
    if (fptr == NULL)
    {
        printf("Eroare! Fisierul nu poate fi accesat");
        exit(1);
    }
    caracter = fgetc(fptr);
    while (caracter != EOF)
    {
        if (caracter == '\n')
        {
            ok = 1;
            nrintrebari += 1;
            nrraspunsuri += 1;
            linie[k] = '\0';
            if ((nrintrebari + 1) % 2 == 0)
            {
                strcpy(listaIntrebari[t++], linie);
                (*contorIntrebariScurt)++;
            }
            else
            {
                if (nrraspunsuri %2 == 0)
                    strcpy(listaRaspunsuri[n++], linie);
            }
            k = 0;
            memset(linie, 0, 100);
            ok = 0;
        }
        if (ok == 1) {
            linie[k++] = caracter;
        }
        if (ok == 0) {
            ok = 1;
        }
        caracter = fgetc(fptr);
    }
    fclose(fptr);

    stocareRaspunsMultiplu(intrebariGrila);
    adaugareIntrebariRaspScurt(listaIntrebari,t,listaRaspunsuri,n);
    numarareIntrebariGrila(contorIntrebariGrila);
}

void adaugareIntrebariRaspScurt(char listaIntrebari[][150], int t, char listaRaspunsuri[][150], int n)
{
    for (int i = 0; i < n; i++)
    {
        struct questions* elem = (struct questions*)malloc(sizeof(struct questions));
        strcpy((*elem).intrebare, listaIntrebari[i]);
        strcpy((*elem).raspuns, listaRaspunsuri[i]);
        (*elem).next = NULL;
        if (head == NULL)
        {
            head = elem;
        }
        else
        {
            struct questions* aux = head;
            while ((*aux).next != NULL)
            {
                aux = (*aux).next;
            }
            (*aux).next = elem;
        }
    }
}

void adaugareIntrebareInFisier(char *intrebariScurte)
{
    char propozitie[150],intrebare[150],raspuns[150];
    FILE* fptr;
    fptr = fopen(intrebariScurte, "a");
    printf("Introduceti intrebarea:\n");
    //getchar();
    fgets(propozitie, 150, stdin);
    strcpy(intrebare, propozitie);
    printf("Introduceti raspunsul:\n");
    fgets(propozitie, 150, stdin);
    strcpy(raspuns, propozitie);

    fprintf(fptr, "%s", intrebare);
    fprintf(fptr, "%s", raspuns);

    printf("Intrebarea a fost adaugata\n");
    fclose(fptr);
}

void extrageRaspuns(char rasp[],char variante[],int *k)
{
    memset(variante, 0, 150);
    int i = 0, poz = 0;
    i = strlen(rasp) - 2;
    while (1)
    {
        if (rasp[i] == '\n')
            break;
        i--;
        poz = i;
    }
    for (int j = 0; j <= poz; j++)
    {
        variante[(*k)++] = rasp[j];
    }
    variante[(*k) - 1] = '\0';
    variante[(*k)] = '\0';
}

void numarareIntrebariGrila(int *contorIntrebariGrila)
{
    struct grila* elemGrila = cap;

    while (elemGrila != NULL)
    {
        (*contorIntrebariGrila)++;
        elemGrila = (*elemGrila).urm;
    }
}


void transformaDinLitereMari(char s[])
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        s[i] = tolower(s[i]);
}

void extrageRaspunsCorect(char d[], char s[], int* k)
{
    memset(s, 0, 150);
    int i = strlen(d) - 2;
    while (1)
    {
        if (d[i] == '\n')
            break;
        else
            s[(*k)++] = d[i];
        i--;
    }
    s[(*k)] = '\0';
    for (int i = 0; i < (*k) / 2; i++)
    {
        char aux = s[i];
        s[i] = s[(*k) - i - 1];
        s[(*k) - i - 1] = aux;
    }
}

void afisareVariante(char auxx[])
{
    int ok1 = 0, ok2 = 0;
    int i = 0, caractereNewLine=0;
    while (i < strlen(auxx))
    {
        if (i == 0)
            printf("a)");
        if ((auxx[i] >= '0' && auxx[i] <= '9') || (auxx[i] >= 'a' && auxx[i] <= 'z') || (auxx[i] >= 'A' && auxx[i] <= 'Z'))
            printf("%c", auxx[i]);
        if (auxx[i] == '\n') {
            printf("\n");
            caractereNewLine++;
        }
        if (auxx[i] == '\n' && caractereNewLine == 3)
        {
            break;
        }
        if (auxx[i] == ' ')
            printf(" ");
        if (auxx[i] == '\n' && ok1 == 0)
        {
            ok1 = 1;
            printf("b)");
        }
        else
        {
            if (auxx[i] == '\n' && ok1 == 1 && ok2 == 0)
            {
                ok2 = 0;
                printf("c)");
            }
        }
        i += 1;
    }
    printf("\n");
}

int transformaInNumar(char rasp[])
{
    int n = strlen(rasp), nr = 0, i = 0;
    while (i < n)
    {
        if (rasp[i] >= '0' && rasp[i] <= '9')
            nr = nr * 10 + rasp[i] - '0';
        i++;
    }
    return nr;
}

void extrageGrila(char variante[], char grila[],char rasp[],int *m)
{
    int n = strlen(variante),nr = 0;
    int varUser = transformaInNumar(rasp);
    if (varUser == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (variante[i] == '\n')
                nr += 1;
            if (nr == 0 && variante[i]!='\n')
            {
                grila[(*m)++] = variante[i];
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        if (varUser == 2)
        {
            for (int i = 0; i < n; i++)
            {
                if (variante[i] == '\n')
                    nr += 1;
                if (nr == 1 && variante[i]!='\n')
                {
                    grila[(*m)++] = variante[i];
                }
                else
                {
                    if (nr > 1)
                        break;
                }
            }
        }
        else
        {
            if (varUser == 3)
            {
                for (int i = 0; i < n; i++)
                {
                    if (variante[i] == '\n')
                        nr += 1;
                    if (nr == 2 && variante[i]!='\n')
                    {
                        grila[(*m)++] = variante[i];
                    }
                }
            }
        }
    }
    grila[(*m)] = '\0';
}

void stergeLista()
{
    struct ranking* prev = primul;
    struct ranking* cur=(struct ranking*)malloc(sizeof(struct ranking));
    while (prev != NULL)
    {
        cur = prev->urmator;
        free(prev);
        prev = cur;
    }
    primul = NULL;
}

int verificaAparitii(int aparitii[],int maxNrIntrebari)
{
    int cateNumere = 0;
    for (int i = 0; i < maxNrIntrebari; i++)
    {
        if (aparitii[i] != 0)
            cateNumere++;
    }
    if (cateNumere != 5) //pentru ca vreau sa am 5 intrebari la fiecare quiz
        return 0;
    return 1;
}

void generareNumere(int aparitii[],int maxNrIntrebari)
{
    while (1)
    {
        if (verificaAparitii(aparitii,maxNrIntrebari) == 1)
            break;
        int val =(rand() % maxNrIntrebari)+1;
        if (aparitii[val] == 0)
        {
            aparitii[val]++;
        }
    }
}

int quizScurt(int contorIntrebariScurt)
{
    getchar();
    struct questions* a = head;
    int contor = 0, j = 0, i = 0;
    int* aparitii = (int*)calloc(contorIntrebariScurt, sizeof(int));
    generareNumere(aparitii,contorIntrebariScurt);
    
    while (a != NULL)
    {
        char rasp[150], aux[150];
        if (i == 5)
            break;
        if (aparitii[j]!=0)
        {
            printf("%s\n", (*a).intrebare);

            gets(rasp); //raspunsul userului
            char auxx[150], grila[150];
            int n = 0, m = 0;
            memset(auxx, 0, 150);
            memset(grila, 0, 150);

            strcpy(aux, (*a).raspuns);
            transformaDinLitereMari(aux);

            transformaDinLitereMari(rasp);

            if (strcmp(aux, rasp) == 0)
                contor += 1;
            i++;
        }

        a = (*a).next;
        j++;
    }
    free(aparitii);
    return contor;
}

int quizGrila(int contorIntrebariGrila)
{
    getchar();
    struct grila* c = cap;
    int contor = 0, j = 0, i = 0;
    int* aparitii = (int*)calloc(contorIntrebariGrila, sizeof(int));
    generareNumere(aparitii, contorIntrebariGrila);
       
    while (c != NULL)
    {
        char rasp[150], aux[150];
        if (i == 5)
            break;
        if (aparitii[j] != 0) 
        {
            printf("%s\n", (*c).intrebare);
            char auxx[150];
            memset(auxx, 0, 150);
            strcpy(auxx, (*c).raspuns);
            afisareVariante(auxx);

            gets(rasp); //raspunsul userului
            char grila[150];
            int n = 0, m = 0;
            memset(auxx, 0, 150);
            memset(grila, 0, 150);
            extrageRaspunsCorect((*c).raspuns, auxx, &n);

            char variante[150];
            memset(variante, 0, 150);
            strcpy(variante, (*c).raspuns);
            extrageGrila(variante, grila, rasp, &m);

            transformaDinLitereMari(auxx);
            transformaDinLitereMari(grila);

            if (strcmp(auxx, grila) == 0)
            {
                contor += 1;
            }
            i++;
        }
        c = (*c).urm;
        j++;
    }
    free(aparitii);
    return contor;
}

void incepeQuiz(int contorIntrebariScurt,int contorIntrebariGrila,char* clasament, char* intrebariScurte, char* intrebariGrila)
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
                        catePuncte = quizGrila(contorIntrebariGrila);
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
                        catePuncte = quizScurt(contorIntrebariScurt);
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
                    stergeLista();
                    alcatuireClasament(clasament);
                    afisareClasament();
                    //break;
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

void alcatuireClasament(char *clasament)
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
        if (primul != NULL) {
            strcpy(p, (*primul).punctaj);
            anterior = extrageScor(p);
        }
        if (primul == NULL || curent>anterior)
        {
            (*elemNou).urmator = primul;
            primul = elemNou;
        }
        else
        {
            struct ranking* aux = primul;
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

void afisareClasament()
{
    struct ranking* elem = primul;
    while (elem != NULL)
    {
        printf("%s %s\n", (*elem).nume, (*elem).punctaj);
        elem = (*elem).urmator;
    }
}

void optiuniUser(char* clasament, char* intrebariScurte, char* intrebariGrila,char *parolaAdmin)
{
    opuser();
    while (1)
    {
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            int contorIntrebariScurt = 0;
            int contorIntrebariGrila = 0;
            switch (numar)
            {
                case 4:
                    printf("Ai parasit jocul");
                    exit(0);
                case 1:
                    stergeLista(clasament);
                    alcatuireClasament(clasament);
                    afisareClasament();
                    break;
                case 2:
                    contorIntrebariScurt = 0;
                    contorIntrebariGrila = 0;
                    stocareIntrebari(&contorIntrebariScurt,&contorIntrebariGrila,clasament,intrebariScurte,intrebariGrila);
                    incepeQuiz(contorIntrebariScurt,contorIntrebariGrila,clasament,intrebariScurte,intrebariGrila);
                    break;
                case 3:
                    paginaPrincipala(clasament,intrebariScurte,intrebariGrila,parolaAdmin);
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

void afisareIntrebariGrila(char** matrice, int index)
{
    printf("Pe care intrebari doriti sa le stergeti?\n\n");
    int i = 0;
    while(i<index)
    {
        int aux = (i + 1) / 5 + 1;
        printf("Intrebarea cu indexul=%d: %s", aux, matrice[i]);
        i++;
        printf("Variantele de raspuns ale intrebarii cu indexul=%d:\n",aux);
        printf("a)%s", matrice[i]);
        i++;
        printf("b)%s", matrice[i]);
        i++;
        printf("c)%s", matrice[i]);
        i++;
        printf("Raspuns corect de la intrebarea cu indexul=%d: %s\n", aux,matrice[i]);
        i++;
    }
}

void completareInFisierGrila(int *ind,int k,char **matrice,int index,char *intrebariGrila)
{
    FILE* multiplu;
    multiplu = fopen(intrebariGrila, "w");
    if (multiplu == NULL)
    {
        printf("Fisierul nu exista");
        exit(1);
    }
    else
    {
        int i = 0, j = 1;
        while (i < index)
        {
            if (cautareBinara(j, ind, k) == -1)
            {
                fprintf(multiplu, "%s", matrice[i]);
                i++;
                fprintf(multiplu, "%s", matrice[i]);
                i++;
                fprintf(multiplu, "%s", matrice[i]);
                i++;
                fprintf(multiplu, "%s", matrice[i]);
                i++;
                fprintf(multiplu, "%s", matrice[i]);
                i++;
                j++;
            }
            else
            {
                if (cautareBinara(j, ind, k) == 1)
                {
                    i += 5;
                    j++;
                }
            }
        }
    }
    fclose(multiplu);
}

void stergereIntrebareGrila(char *intrebariGrila)
{
    char** matrice;
    matrice = initializareMatrice();
    char* spare = (char*)calloc(150, sizeof(char));
    int index = 0;

    FILE* multiplu;
    multiplu = fopen(intrebariGrila, "r");
    if (multiplu == NULL)
    {
        printf("Fisierul nu poate fi accesat.");
        exit(1);
    }
    else {
        while (fgets(spare, 150, multiplu))
        {
            strcpy(matrice[index], spare);
            index++;
        }
    }
    fclose(multiplu);

    free(spare);
    afisareIntrebariGrila(matrice, index);
    int k = 0;
    int* ind = (int*)calloc(150, sizeof(int));
    citireIndecsi(ind, &k, index);
    sortare(ind, k);
    getchar();
    completareInFisierGrila(ind, k, matrice, index,intrebariGrila);
    free(ind);
    for (int i = 0; i < 150; i++)
        free(matrice[i]);
    free(matrice);
}

void afisareIntrebari(char** mat, int n)
{
    printf("Pe care intrebari doriti sa le stergeti?\n\n");
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0) {
            printf("Intrebarea cu indexul=%d: %s", (i+1)/2+1, mat[i]);
        }
        else
        {
            printf("Raspunsul intrebarii cu indexul=%d: %s\n", (i+1)/2, mat[i]);
        }
    }
    printf("Introduceti indecsii intrebarilor pe care doriti sa le stergeti:\n");
}

char** initializareMatrice()
{
    char** matrice = (char**)malloc(150 * sizeof(char*));
    if (matrice != NULL)
    {
        for (int i = 0; i < 150; i++)
        {
            matrice[i] = (char*)calloc(150, sizeof(char));
        }
    }
    return matrice;
}

void citireIndecsi(int* ind, int* k,int index)
{
    char* optiune = (char*)calloc(150, sizeof(char));
    scanf("%[^\n]s", optiune);
    int n = strlen(optiune), numar = 0;
    for(int i=0;i<n;i++)
    {
        if (optiune[i] >= '0' && optiune[i] <= '9')
        {
            numar = numar * 10 + optiune[i] - '0';
        }
        if (optiune[i] == ' ')
        {
            if (numar <= index)
            {
                ind[(*k)++] = numar;
            }
            numar = 0;
        }
        else {
            if ((optiune[i] >= '0' && optiune[i] <= '9') && (strchr("0123456789\n ",optiune[i+1])==0))
            {
                numar = 0;
                continue;
            }
            else
            {
                if ((optiune[i] >= '0' && optiune[i] <= '9') && (strchr("0123456789\n ", optiune[i-1]) == 0) && i>0)
                {
                    numar = 0;
                    continue;
                }
            }
        }
    }
    //if (optiune[n - 1] >= '0' && optiune[n - 1] <= '9')
    //{
    if (numar <= index)
    {
        ind[(*k)++] = numar;
    }
    //}
    free(optiune);
}

void sortare(int* ind, int k)
{
    for (int i = 0; i < k; i++)
    {
        int elem = ind[i],indice=i;
        for (int j = i + 1; j < k; j++)
        {
            if (elem > ind[j])
            {
                elem = ind[j];
                indice = j;
            }
        }
        ind[indice] = ind[i];
        ind[i] = elem;
    }
}

void stergereIntrebareScurt(char *intreabariScurt)
{
    char** matrice = initializareMatrice();
    char* spare = (char*)malloc(150 * sizeof(char));
    int index = 0;
    
    FILE* fptr;
    fptr = fopen(intreabariScurt, "r");
    if (fptr == NULL)
    {
        printf("Fisierul nu poate fi accesat");
        exit(1);
    }
    else
    {
        while (fgets(spare, 150, fptr))
        {
            strcpy(matrice[index], spare);
            index++;
        }
    }
    fclose(fptr);

    free(spare);
    afisareIntrebari(matrice,index);
    int k = 0;
    int* ind = (int*)calloc(150, sizeof(int));
    citireIndecsi(ind, &k,index);
    sortare(ind, k);
    
    getchar();

    completareInFisier(ind, k,matrice,index,intreabariScurt);
    free(ind);
    for (int i = 0; i < 150; i++)
        free(matrice[i]);
    free(matrice);
}

int cautareBinara(int val, int* ind, int k)
{
    int st = 0, dr = k - 1;
    while (st <= dr)
    {
        int mij = (st + dr) / 2;
        if (ind[mij] == val)
            return 1;
        if (val > ind[mij])
        {
            st = mij + 1;
        }
        else
        {
            dr = mij - 1;
        }
    }
    return -1;
}

void completareInFisier(int *ind,int k,char **matrice,int index,char *intrebariScurt)
{
    FILE* fptr;
    fptr = fopen(intrebariScurt, "w");
    if (fptr == NULL)
    {
        printf("Fisierul nu exista");
        exit(1);
    }
    else {
        int i = 0, j = 1;
        while(i<index)
        {
            if (cautareBinara(j, ind, k) == -1) {
                fprintf(fptr, "%s", matrice[i]);
                i++;
                fprintf(fptr, "%s", matrice[i]);
                i++;
                j++;
            }
            else
            {
                if (cautareBinara(j, ind, k) == 1)
                {
                    i += 2;
                    j++;
                }
            }
        }
        
    }
    fclose(fptr);
}

void tipIntrebare(char* clasament, char* intrebariScurte, char* intrebariGrila,char *parolaAdmin)
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
                optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin);
                break;
            case 1:
                adaugareIntrebareInFisier(intrebariScurte);
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

void stocareRaspunsMultiplu(char *intrebariGrila)
{
    FILE* multiplu;
    multiplu = fopen(intrebariGrila, "r");
    if (multiplu == NULL)
    {
        printf("Eroare! Fisierul nu poate fi accesat");
        exit(1);
    }
    char rez[150],intrebari[150];
    int linie = 1, k = 0;
    memset(rez, 0, 150);
    memset(intrebari, 0, 150);
    struct grila* elemNou = (struct grila*)malloc(sizeof(struct grila));
    while (fgets(rez, 150, multiplu))
    {
        if ((linie - 1) % 5 == 0)
        {
            rez[strlen(rez) - 1] = '\0';
            strcpy((*elemNou).intrebare, rez);
        }
        else
        {
            for (int i = 0; i < strlen(rez); i++)
            {
                intrebari[k++] = rez[i];
            }
            if (linie %5==0)
            {
                intrebari[k] = '\0';
                strcpy((*elemNou).raspuns, intrebari);
                (*elemNou).urm = NULL;
                if (cap == NULL)
                {
                    cap = elemNou;
                }
                else
                {
                    struct grila* elem = cap;
                    while ((*elem).urm != NULL)
                    {
                        elem = (*elem).urm;
                    }
                    (*elem).urm = elemNou;
                }
                memset(intrebari, 0, 150);
                k = 0;
                elemNou = (struct grila*)malloc(sizeof(struct grila));
            }
        }
        linie += 1;
    }
}

void adaugareRaspunsMultiplu(char *intrebariGrila) {
    
    FILE* multiplu;
    multiplu = fopen(intrebariGrila, "a");
    char* intrebare = (char*)malloc(150 * sizeof(char));
    char* raspuns1 = (char*)malloc(30 * sizeof(char));
    char* raspuns2 = (char*)malloc(30 * sizeof(char));
    char* raspuns3 = (char*)malloc(30 * sizeof(char));
    char* corect = (char*)malloc(30 * sizeof(char));
    //getchar();
    printf("Introduceti intrebarea\n");
    gets(intrebare);
    printf("Introduceti prima varianta de raspuns\n");
    gets(raspuns1);
    printf("Introduceti a doua varianta de raspuns\n");
    gets(raspuns2);
    printf("Introduceti a treia varianta de raspuns\n");
    gets(raspuns3);
    printf("Introduceti raspunsul corect\n");
    

    while (1) {

        gets(corect);
        if (strcmp(raspuns1, corect) == 0) {
            break;
        }
        if (strcmp(raspuns2, corect) == 0) {
            break;
        }
        if (strcmp(raspuns3, corect) == 0) {
            break;
        }
        if (strcmp(raspuns1, corect) != 0 && strcmp(raspuns2, corect) != 0 && strcmp(raspuns3, corect) != 0)
        {
            printf("Raspunsul corect nu coincide cu niciuna dintre variante.\nIntroduceti unul dintre raspunsurile introduse deja.\n");
        }
        
    }
    
    fprintf(multiplu, "%s\n", intrebare);
    fprintf(multiplu, "%s\n", raspuns1);
    fprintf(multiplu, "%s\n", raspuns2);
    fprintf(multiplu, "%s\n", raspuns3);
    fprintf(multiplu, "%s\n", corect);

    printf("Intrebarea a fost adaugata\n");

    free(intrebare);
    free(raspuns1);
    free(raspuns2);
    free(raspuns3);
    free(corect);
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

void paginaPrincipala(char *clasament,char* intrebariScurte, char *intrebariGrila, char *parolaAdmin)
{
    opprinicipala();
    while (1)
    {
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
                case 1:
                    //system("cls");
                    optiuniUser(clasament,intrebariScurte,intrebariGrila,parolaAdmin);
                    break;
                case 2:
                    if (verificareAdministrator(parolaAdmin) == 1) {
                        //system("cls");
                        optiuniAdministrator(clasament,intrebariScurte,intrebariGrila,parolaAdmin);
                    }
                    else {
                        //system("cls");
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
    char* clasament = initializare();
    char* intrebariScurte = initializare();
    char* intrebariGrila = initializare();
    char* parolaAdmin = initializare();
    numeFisiere(clasament, intrebariScurte, intrebariGrila,parolaAdmin);
    paginaPrincipala(clasament,intrebariScurte,intrebariGrila,parolaAdmin);
    free(clasament);
    free(intrebariScurte);
    free(intrebariGrila);
    free(parolaAdmin);

    return 0;
}
