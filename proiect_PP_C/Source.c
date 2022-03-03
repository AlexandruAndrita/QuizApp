#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void optiuniUser();
void opuser();
void optiuniAdministrator();
void opadmin();
void paginaPrincipala();
void adaugareIntrebareInFisier();
void opprinicipala();
int verificareAdministrator();
void stocareIntrebari();
void adaugIntrebareInLista(char listaIntrebari[][150], int t);
void adaugRaspunsInLista(char listaRaspunsuri[][150], int n);
void incepeQuiz();
void optiuniQuiz();
int quiz();
void transformaInLitereMari(char s[]);
void afisareClasament();
int cautare(char s[]);
void alcatuireClasament();

FILE* fptr;
FILE* cls;

struct questions {
    char intrebare[150];
    struct questions* next;
};
struct questions* head = NULL;

struct answers {
    char raspuns[150];
    struct answers* nextt;
};
struct answers* headd = NULL;

struct ranking {
    char nume[50];
    char punctaj[50];
    struct ranking* urmator;
};
struct ranking* primul = NULL;

int contorIntrebari = 0;

void stocareIntrebari()
{
    char listaIntrebari[150][150], listaRaspunsuri[150][150], linie[150];
    int k = 0, n = 0, t = 0, nrintrebari = 0, nrraspunsuri = 0;
    int ok = 1;
    char caracter;
    fptr = fopen("listaIntrebari.txt", "r");
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
                contorIntrebari++;
            }
            else
            {
                if ((nrraspunsuri + 1) % 3 == 0)
                    strcpy(listaRaspunsuri[n++], linie);
            }
            //printf("%d %d\n", strlen(linie),k);
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
    adaugIntrebareInLista(listaIntrebari, t);
    adaugRaspunsInLista(listaRaspunsuri, n);

    //    for(int i=0;i<t;i++)
    //        printf("%s\n",listaIntrebari[i]);
    //
    //    printf("\n");
    //
    //    for(int i=0;i<n;i++)
    //        printf("%s\n",listaRaspunsuri[i]);

}

void adaugIntrebareInLista(char listaIntrebari[][150], int t)
{
    for (int i = 0; i < t; i++)
    {
        struct questions* elemNou = (struct questions*)malloc(sizeof(struct questions));
        strcpy((*elemNou).intrebare, listaIntrebari[i]);
        (*elemNou).next = NULL;
        if (head == NULL)
        {
            head = elemNou;
        }
        else {
            struct questions* elem = head;
            while ((*elem).next != NULL)
            {
                elem = (*elem).next;
            }
            (*elem).next = elemNou;
        }
    }
    //    struct questions *parcurge=head;
    //    while((*parcurge).next!=NULL)
    //    {
    //        printf("%s\n",(*parcurge).intrebare);
    //        parcurge=(*parcurge).next;
    //    }
}

void adaugRaspunsInLista(char listaRaspunsuri[][150], int n)
{
    for (int i = 0; i < n; i++)
    {
        struct answers* elemNou = (struct answers*)malloc(sizeof(struct answers));
        strcpy((*elemNou).raspuns, listaRaspunsuri[i]);
        (*elemNou).nextt = NULL;
        if (headd == NULL)
        {
            headd = elemNou;
        }
        else
        {
            struct answers* elem = headd;
            while ((*elem).nextt != NULL)
            {
                elem = (*elem).nextt;
            }
            (*elem).nextt = elemNou;
        }
    }
    //    struct answers *parcurge=headd;
    //    while(parcurge!=NULL)
    //    {
    //        printf("%s\n",parcurge->raspuns);
    //        parcurge=parcurge->nextt;
    //    }
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

void optiuniQuiz()
{
    printf("1. Incepe quiz (tasta 1)\n");
    printf("2. Mergi la pagina principala (tasta 2)\n");
    printf("3. Vezi clasament (tasta 3)\n");
    printf("4. Paraseste jocul (tasta 4)\n");
}

void transformaInLitereMari(char s[])
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        s[i] = tolower(s[i]);
}

int quiz()
{
    getchar();
    struct questions* a = head;
    struct answers* b = headd;
    int contor = 0, cateIntrebari = 0;
    while (a != NULL && b != NULL)
    {
        //printf("%s\n",(*a).intrebare);
        //printf("%s\n",(*b).raspuns);
        
        char rasp[150], aux[150];
       
        printf("%s\n", (*a).intrebare);
        //fflush(stdin);

        //fgets(rasp,150,stdin);
        gets(rasp);
        strcpy(aux, (*b).raspuns);

        transformaInLitereMari(rasp);
        transformaInLitereMari(aux);

        //printf("%d %d\n\n",strlen(rasp),strlen(aux));

        if (strcmp(aux, rasp) == 0)
            contor += 1;
        a = (*a).next;
        b = (*b).nextt;
        cateIntrebari += 1;
    }
    return contor;
}

void incepeQuiz()
{
    char numeJucator[50];
    memset(numeJucator, 0, 50);
    printf("Introduceti-va numele\n");
    scanf("%s", &numeJucator);
    while (1)
    {
        if (cautare(numeJucator) == 1)
            break;
        else {
            printf("Numele introdus este luat\n");
            memset(numeJucator, 0, 30);
            scanf("%s", &numeJucator);
        }
    }
    int catePuncte = 0;
    optiuniQuiz();
    while (1)
    {
        int optiune = 0;
        scanf("%d", &optiune);
        if (optiune == 4)
        {
            printf("Ai parasit jocul");
            exit(0);
        }
        if (optiune == 1)
        {
            catePuncte = quiz();
            printf("Scorul tau este: %d / %d\n", catePuncte, contorIntrebari);
            cls = fopen("clasament.txt", "a");
            fprintf(cls, "%s %d / %d\n", numeJucator, catePuncte, contorIntrebari);
            fclose(cls);
            printf("\n");
            break;
        }
        if (optiune == 2)
        {
            optiuniUser();
            break;
        }
        if (optiune == 3)
        {
            alcatuireClasament();
            afisareClasament();
            break;
        }
        optiuniQuiz();
    }
}

//cauta in fisier daca numele persoanei a fost introdus deja sau nu
int cautare(char s[])
{
    cls = fopen("clasament.txt", "r");
    char rez[50], d[100];
    int k = 0, n = 0;
    memset(rez, 0, 50);
    while (fgets(rez, 50, cls))
    {
        memset(d, 0, 100);
        n = 0;
        k = strlen(rez);
        int i = 0;
        while (i < k)
        {
            if (rez[i] == ' ')
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

void alcatuireClasament()
{
    cls = fopen("clasament.txt", "r");
    char rez[50], d[100];
    //char aux[100];
    int k = 0, n = 0;
    memset(rez, 0, 50);
    while (fgets(rez, 50, cls)) //citeste linie cu linie din fisier
    {
        struct ranking* elemNou = (struct ranking*)malloc(sizeof(struct ranking));
        k = strlen(rez);
        int i = 0;
        memset(d, 0, 100);
        //memset(aux, 0, 100);
        n = 0;
        while (i < k)
        {
            if (rez[i] == ' ')
                break;
            d[n++] = rez[i];
            ;           i += 1;
        }
        strcpy((*elemNou).nume, d);
        //strcpy(aux, d);
        memset(d, 0, 100);
        n = 0;
        i += 1;
        while (i < k - 1)
        {
            d[n++] = rez[i];
            i += 1;
        }
        strcpy((*elemNou).punctaj, d);
        //append(&clasament, aux, d);
        memset(d, 0, 100);
        n = 0;
        (*elemNou).urmator = NULL;
        if (primul == NULL)
        {
            primul = elemNou;
        }
        else {
            struct ranking* element = primul;
            while ((*element).urmator != NULL)
            {
                element = (*element).urmator;
            }
            (*element).urmator = elemNou;
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
        int optiune = 0;
        scanf("%d", &optiune);
        if (optiune == 4)
        {
            printf("Ai parasit jocul");
            exit(0);
        }
        if (optiune == 1)
        {
            alcatuireClasament();
            afisareClasament();
        }
        if (optiune == 2)
        {
            stocareIntrebari();
            incepeQuiz();
        }
        if (optiune == 3)
        {
            paginaPrincipala();
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
    printf("2. Modifica o intrebare existenta (tasta2).\n");
    printf("3. Pagina principala (tasta 3)\n");
    printf("4. Paraseste jocul (tasta 4)\n");
}

void optiuniAdministrator()
{
    fptr = fopen("listaIntrebari.txt", "a");
    opadmin();
    while (1)
    {
        int optiune = 0;
        scanf("%d", &optiune);
        if (optiune == 4)
        {
            printf("Ai parasit jocul");
            fclose(fptr);
            exit(0);
        }
        if (optiune == 1)
        {
            printf("Adaugare intrebare noua\n");
            adaugareIntrebareInFisier();
        }
        if (optiune == 2)
        {
            printf("Modificare intrebare curenta\n");
            exit(0);
        }
        if (optiune == 3)
        {
            paginaPrincipala();
        }
        opadmin();
    }
}

void opprinicipala()
{
    printf("1. Sunt un user obisnuit, nu administrator (tasta 1)\n");
    printf("2. Sunt administrator (tasta 2)\n");
    printf("3. Paraseste jocul (tasta 3)\n");
}

void paginaPrincipala()
{
    printf("QuizApp\n");
    opprinicipala();
    while (1)
    {
        int optiune = 0;
        scanf("%d", &optiune);
        if (optiune == 3)
        {
            printf("Ai parasit jocul");
            exit(0);
        }
        if (optiune == 1)
        {
            optiuniUser();
            break;
        }
        if (optiune == 2)
        {
            if (verificareAdministrator() == 1)
                optiuniAdministrator();
            else
                printf("Parola gresita. Nu aveti permisiunea de a va loga ca administrator\n\n");
        }
        opprinicipala();
    }

}

int verificareAdministrator()
{
    char* parola = (char*)malloc(14 * sizeof(char));
    printf("Introduceti parola\n");
    scanf("%s", parola);
    if (strcmp(parola, "administrator") != 0)
        return 0;
    return 1;
}

int main() {
    paginaPrincipala();

    return 0;
}
