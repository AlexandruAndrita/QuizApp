void adaugareIntrebariScurte(char* intrebariScurt)
{
    FILE* pointerFis;
    pointerFis = fopen(intrebariScurt, "r");
    if (pointerFis == NULL)
    {
        printf("Fisierul nu exista.\n");
        exit(1);
    }
    char* linie = (char*)calloc(256, sizeof(char));
    while (fgets(linie, 256, pointerFis))
    {
        struct questions* elem = (struct questions*)malloc(sizeof(struct questions));
        char* p = strtok(linie, ";");
        strcpy(elem->intrebare, p);
        p = strtok(NULL, ";");
        while (p)
        {
            if (p[strlen(p) - 1] == '\n')
            {
                p[strlen(p) - 1] = '\0';
            }
            strcpy(elem->raspuns, p);
            p = strtok(NULL, ";");
        }
        elem->next = NULL;
        if (head == NULL)
        {
            head = elem;
        }
        else
        {
            struct questions* aux = head;
            while (aux->next != NULL)
            {
                aux = aux->next;
            }
            aux->next = elem;
        }
    }
    free(linie);
    fclose(pointerFis);
}

void adaugareIntrebariGrila(char* intrebariGrila)
{
    FILE* pointerFis;
    pointerFis = fopen(intrebariGrila, "r");
    if (pointerFis == NULL)
    {
        printf("Fisierul nu exista.\n");
        exit(1);
    }
    char linie[256], variante[256];
    memset(linie, 0, 256);
    memset(variante, 0, 256);
    while (fgets(linie, 256, pointerFis))
    {
        struct grila* elem = (struct grila*)malloc(sizeof(struct grila));
        char* p = strtok(linie, ";");
        strcpy(elem->intrebare, p);
        p = strtok(NULL, ";");
        while (p != NULL)
        {
            if (p[strlen(p) - 1] == '\n')
            {
                p[strlen(p) - 1] = '\0';
            }
            strcat(variante, p);
            strcat(variante, ";");
            p = strtok(NULL, ";");
        }
        strcpy(elem->raspuns, variante);
        elem->urm = NULL;
        if (cap == NULL)
        {
            cap = elem;
        }
        else
        {
            struct grila* aux = cap;
            while (aux->urm != NULL)
            {
                aux = aux->urm;
            }
            aux->urm = elem;
        }
        memset(variante, 0, 256);
    }
    fclose(pointerFis);
}

void stocareIntrebari(int* contorIntrebariScurt, int* contorIntrebariGrila, char* clasament, char* intrebariScurte, char* intrebariGrila)
{
    adaugareIntrebariScurte(intrebariScurte);
    adaugareIntrebariGrila(intrebariGrila);
}

