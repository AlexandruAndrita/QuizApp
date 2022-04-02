void transformaDinLitereMari(char s[])
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        s[i] = tolower(s[i]);
}

int verificaAparitii(int aparitii[], int maxNrIntrebari)
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

void generareNumere(int aparitii[], int maxNrIntrebari)
{
    while (1)
    {
        if (verificaAparitii(aparitii, maxNrIntrebari) == 1)
            break;
        int val = (rand() % maxNrIntrebari) + 1;
        if (aparitii[val] == 0)
        {
            aparitii[val]++;
        }
    }
}

int quizScurt(int contorIntrebariScurt, struct lista *scurte, clock_t *start_t,clock_t *end_t,clock_t *total_t)
{
    getchar();
    struct questions* a = scurte->head;
    int contor = 0, j = 0, i = 0;
    int* aparitii = (int*)calloc(contorIntrebariScurt, sizeof(int));
    generareNumere(aparitii, contorIntrebariScurt);

    *start_t = clock();
    while (a != NULL)
    {
        char rasp[150], aux[150];
        if (i == 5)
            break;
        if (aparitii[j] != 0)
        {
            printf("\t%s\n", a->intrebare);

            printf("\t");
            gets(rasp);

            strcpy(aux, a->raspuns);
            transformaDinLitereMari(aux);

            transformaDinLitereMari(rasp);

            if (strcmp(aux, rasp) == 0)
                contor += 1;
            i++;
        }

        a = a->next;
        j++;
    }
    *end_t = clock();
    *total_t= (double)((*end_t)-(*start_t)) / CLOCKS_PER_SEC;
    free(aparitii);
    return contor;
}

void afisareVariante(char auxx[], char corect[])
{
    char* p = strtok(auxx, ";");
    int nr = 0;
    while (p)
    {
        if (nr == 0)
        {
            printf("\ta) %s\n", p);
            nr++;
        }
        else
        {
            if (nr == 1)
            {
                printf("\tb) %s\n", p);
                nr++;
            }
            else
            {
                if (nr == 2)
                {
                    printf("\tc) %s\n", p);
                    nr++;
                }
                if (nr == 3)
                {
                    if (p[strlen(p) - 1] == '\n')
                        p[strlen(p) - 1] = '\0';
                    strcpy(corect, p);
                }
            }
        }
        p = strtok(NULL, ";");
    }
}

void preluareRaspuns(char rasp[], char auxx[])
{
    if (validareInput(rasp) == 1)
    {
        int varianta = atoi(rasp);
        char* p = strtok(auxx, ";");
        int nr = 0;
        while (p)
        {
            if (varianta == 1 && nr == 0)
            {
                strcpy(rasp, p);
                break;
            }
            else
            {
                if (varianta == 2 && nr == 1)
                {
                    strcpy(rasp, p);
                    break;
                }
                else
                {
                    if (varianta == 3 && nr == 2)
                    {
                        strcpy(rasp, p);
                        break;
                    }
                }
            }
            p = strtok(NULL, ";");
            nr++;
        }
    }
    else
    {
        strcpy(rasp, "-1");
    }
}

int quizGrila(int contorIntrebariGrila, struct lista* grila, clock_t* start_t, clock_t* end_t, clock_t* total_t)
{
    getchar();
    struct grila* c = grila->cap;
    int contor = 0, j = 0, i = 0;
    int* aparitii = (int*)calloc(contorIntrebariGrila, sizeof(int));
    generareNumere(aparitii, contorIntrebariGrila);

    *start_t = clock();
    while (c != NULL)
    {
        if (i == 5)
            break;
        if (aparitii[j] != 0)
        {
            printf("\t%s\n", c->intrebare);
            char auxx[150], varCorecta[150], rasp[150];
            memset(auxx, 0, 150);
            memset(varCorecta, 0, 150);
            strcpy(auxx, c->raspuns);
            afisareVariante(auxx, varCorecta);

            printf("\t");
            gets(rasp);
            memset(auxx, 0, 150);
            strcpy(auxx, c->raspuns);
            preluareRaspuns(rasp, auxx);


            transformaDinLitereMari(varCorecta);
            transformaDinLitereMari(rasp);

            if (strcmp(varCorecta, rasp) == 0)
            {
                contor += 1;
            }
            i++;
        }
        c = c->urm;
        j++;
    }
    *end_t = clock();
    *total_t = (double)((*end_t) - (*start_t)) / CLOCKS_PER_SEC;
    free(aparitii);
    return contor;
}