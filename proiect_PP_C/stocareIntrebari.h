void stocareIntrebari(int* contorIntrebariScurt, int* contorIntrebariGrila, char* clasament, char* intrebariScurte, char* intrebariGrila, struct lista* scurte, struct lista* grila)
{
    adaugareIntrebariScurte(intrebariScurte, contorIntrebariScurt,scurte);
    adaugareIntrebariGrila(intrebariGrila, contorIntrebariGrila,grila);
}

void adaugareIntrebariScurte(char* intrebariScurt,int * contorIntrebariScurt, struct lista *scurte)
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
        if (scurte->head == NULL)
        {
            scurte->head = elem;
        }
        else
        {
            struct questions* aux = scurte->head;
            while (aux->next != NULL)
            {
                aux = aux->next;
            }
            aux->next = elem;
        }
        (*contorIntrebariScurt)++;
    }
    free(linie);
    fclose(pointerFis);
}

void adaugareIntrebariGrila(char* intrebariGrila,int *contorIntrebariGrila, struct lista *grila)
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
        if (grila->cap == NULL)
        {
            grila->cap = elem;
        }
        else
        {
            struct grila* aux = grila->cap;
            while (aux->urm != NULL)
            {
                aux = aux->urm;
            }
            aux->urm = elem;
        }
        memset(variante, 0, 256);
        (*contorIntrebariGrila)++;
    }
    fclose(pointerFis);
}
