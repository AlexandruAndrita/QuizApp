#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void optiuniUser();
void opuser();
void optiuniAdministrator();
void opadmin();
void paginaPrincipala();
void adaugareIntrebareInFisier();
void opprinicipala();
int verificareAdministrator();
void stocareIntrebari(int * contorIntrebariScurt,int * contorIntrebariGrila);
void adaugareIntrebariRaspScurt(char listaIntrebari[][150], int t, char listaRaspunsuri[][150], int n);
void incepeQuiz(int contorIntrebariScurt,int contorIntrebariGrila);
void optiuniQuiz();
void transformaDinLitereMari(char s[]);
void afisareClasament();
int cautare(char s[]);
void alcatuireClasament();
void tipIntrebare();
void tipIntrebareQ();
void adaugareRaspunsMultiplu();
void stocareRaspunsMultiplu();
void numarareIntrebariGrila(int *contorIntrebari);
void extrageRaspunsCorect(char d[], char s[], int* k);
void afisareVariante(char auxx[]);
void extrageRaspuns(char rasp[], char variante[], int* k);
int validareInput(char optiune[]);
void stergeLista();
int transformaInNumar(char rasp[]);
void extrageGrila(char variante[], char grila[], char rasp[],int *m);
void reguli();
int quizScurt(int contorIntrebariScurt);
int quizGrila(int contorIntrebariGrila);
void generareNumere(int aparitii[], int maxNrIntrebari);
int verificaAparitii(int aparitii[]);


FILE* fptr;
FILE* cls;
FILE* multiplu;

struct questions {
    char intrebare[150];
    char raspuns[150];
    struct questions* next;
};
struct questions* head = NULL;

struct grila {
    char intrebare[150];
    char raspuns[150];
    struct grila* urm;
};
struct grila* cap = NULL;

struct ranking {
    char nume[50];
    char punctaj[50];
    struct ranking* urmator;
};
struct ranking* primul = NULL;

void stocareIntrebari(int *contorIntrebariScurt,int * contorIntrebariGrila)
{
    char listaIntrebari[150][150], listaRaspunsuri[150][150], linie[150];
    int k = 0, n = 0, t = 0, nrintrebari = 0, nrraspunsuri = 0;
    int ok = 1;
    char caracter;
    fptr = fopen("listaIntrebari.txt", "r");
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
            if ((nrintrebari - 1) % 3 == 0)
            {
                strcpy(listaIntrebari[t++], linie);
                (*contorIntrebariScurt)++;
            }
            else
            {
                if ((nrraspunsuri + 1) % 3 == 0)
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

    stocareRaspunsMultiplu();
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

void adaugareIntrebareInFisier()
{
    char* intrebare = (char*)malloc(150 * sizeof(char));
    char* raspuns = (char*)malloc(150 * sizeof(char));
    char propozitie[150];
    printf("Introduceti intrebarea:\n");
    getchar();
    fgets(propozitie, 150, stdin);
    strcpy(intrebare, propozitie);
    printf("Introduceti raspunsul:\n");
    fgets(propozitie, 150, stdin);
    strcpy(raspuns, propozitie);

    fprintf(fptr, "%s", intrebare);
    fprintf(fptr, "%s", raspuns);
    fprintf(fptr, "\n");

    printf("Intrebarea a fost adaugata\n");
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

void optiuniQuiz()
{
    printf("1. Incepe quiz (tasta 1)\n");
    printf("2. Mergi la pagina principala (tasta 2)\n");
    printf("3. Vezi clasament (tasta 3)\n");
    printf("4. Paraseste jocul (tasta 4)\n");
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

int verificaAparitii(int aparitii[])
{
    int cateNumere = 0;
    for (int i = 0; i <= 9; i++)
    {
        if (aparitii[i] != 0)
            cateNumere++;
    }
    if (cateNumere != 5)
        return 0;
    return 1;
}

void generareNumere(int aparitii[],int maxNrIntrebari)
{
    while (1)
    {
        if (verificaAparitii(aparitii, maxNrIntrebari) == 1)
            break;
        int val = rand() % (maxNrIntrebari+1);
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
    int* aparitii = (int*)calloc(10, sizeof(int));
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
    int* aparitii = (int*)calloc(10, sizeof(int));
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

void incepeQuiz(int contorIntrebariScurt,int contorIntrebariGrila)
{
    char numeJucator[50];
    memset(numeJucator, 0, 50);
    printf("Introduceti-va numele\n");
    gets(numeJucator);
    
    while (1)
    {
        if (cautare(numeJucator) == 1)
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
                        cls = fopen("clasament.txt", "a");
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
                        cls = fopen("clasament.txt", "a");
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
                    alcatuireClasament();
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

int cautare(char s[])
{
    cls = fopen("clasament.txt", "r");
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

void alcatuireClasament()
{
    cls = fopen("clasament.txt", "r");
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

void optiuniUser()
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
                    stergeLista();
                    alcatuireClasament();
                    afisareClasament();
                    break;
                case 2:
                    contorIntrebariScurt = 0;
                    contorIntrebariGrila = 0;
                    stocareIntrebari(&contorIntrebariScurt,&contorIntrebariGrila);
                    incepeQuiz(contorIntrebariScurt,contorIntrebariGrila);
                    break;
                case 3:
                    paginaPrincipala();
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

void opuser()
{
    printf("1. Vizualizare clasament (tasta 1).\n");
    printf("2. Incepe quiz (tasta 2)\n");
    printf("3. Pagina principala (tasta 3)\n");
    printf("4. Paraseste jocul (tasta 4)\n");
}

void opadmin()
{
    printf("1. Adauga intrebare noua (tasta 1).\n");
    printf("2. Stergere/editare intrebare(nu inca implementat) (tasta2).\n");
    printf("3. Pagina principala (tasta 3)\n");
    printf("4. Paraseste jocul (tasta 4)\n");
}

void optiuniAdministrator()
{
    fptr = fopen("listaIntrebari.txt", "a");
    multiplu = fopen("mulraspIntrebari.txt", "a");
    if (fptr == NULL)
    {
        printf("Eroare! Fisierul nu poate fi accesat");
        exit(1);
    }
    if (multiplu == NULL)
    {
        printf("Eroare! Fisierul nu poate fi accesat");
        exit(1);
    }
    opadmin();
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
                    fclose(fptr);
                    fclose(multiplu);
                    exit(0);
                case 1:
                    printf("Adaugare intrebare noua\n");
                    tipIntrebare();
                    break;
                    //adaugareIntrebareInFisier();
                case 2:
                    printf("Stergere/editare intrebare(nu inca implementat)\n");
                    exit(0);
                case 3:
                    paginaPrincipala();
                    break;
                default:
                    printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
            }
        }
        else
        {
            printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
        }
        opadmin();
    }
}

void tipIntrebareQ()
{
    printf("1. Introducere intrebare cu raspuns scurt (tasta 1)\n");
    printf("2. Introducere intrebare cu raspuns multiplu (tasta 2)\n");
    printf("3. Intoarce-te la meniul de administrator(tasta 3)\n");
}

void tipIntrebare()
{
    tipIntrebareQ();
    while (1)
    {
        /*int optiune = 0;
        scanf("%d", &optiune);*/
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 3:
                optiuniAdministrator();
                break;
            case 1:
                adaugareIntrebareInFisier();
                break;
            case 2:
                adaugareRaspunsMultiplu();
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

void stocareRaspunsMultiplu()
{
    multiplu = fopen("mulraspIntrebari.txt", "r");
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

void adaugareRaspunsMultiplu() {
    
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
        if (strcmp(raspuns1, corect) != 0 && strcmp(raspuns2, corect) != 0 && strcmp(raspuns3, corect) != 0)
        {
            printf("Raspunsul corect nu coincide cu niciuna dintre variante.\nIntroduceti unul dintre raspunsurile introduse deja.\n");
        }
        else
        {
            break;
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

void opprinicipala()
{
    printf("1. Sunt utilizator, nu administrator (tasta 1)\n");
    printf("2. Sunt administrator (tasta 2)\n");
    printf("3. Reguli (tasta 3)\n");
    printf("4. Paraseste jocul (tasta 4)\n");
    
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

void reguli()
{
    printf("\n");
    printf("1.Pentru intrebariel cu raspuns scurt, va fi introdus doar raspunsul care este considerat corect de catre utilizator.\n");
    printf("2.Pentru intrebarile de tip grila, se va raspunde cu 1 (adica a) ),2 (adica b) ) sau 3 (adica c) ).\n  Orice alt raspuns va fi considerat gresit.\n");
    printf("3.Scorul va fi afisat la final, iar numele si scorul vor fi puse intr-un clasament.\n  Clasamentul poate fi vizuzalizat de catre utilizator daca se doreste acest lucru.\n");
    printf("\n");
}

void paginaPrincipala()
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
                    optiuniUser();
                    break;
                case 2:
                    if (verificareAdministrator() == 1) {
                        optiuniAdministrator();
                    }
                    else
                        printf("Parola gresita. Nu aveti permisiunea de a va loga ca administrator\n");
                    break;
                case 4:
                    printf("Ai parasit jocul");
                    exit(0);
                case 3:
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

int verificareAdministrator()
{
    char parola[50];
    printf("Introduceti parola\n");
    gets(parola);
    if (strcmp(parola, "admin") != 0)
        return 0;
    return 1;
}

int main() {
    printf("QuizApp\n");
    srand(time(0));
    paginaPrincipala();

    return 0;
}
