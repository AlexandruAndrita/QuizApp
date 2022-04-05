void adaugareScurtaInLista(struct lista* scurte, char intrebare[], char raspuns[])
{
    struct questions* elem = (struct questions*)malloc(sizeof(struct questions));
    strcpy(elem->intrebare, intrebare);
    strcpy(elem->raspuns, raspuns);
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
}

void adaugareRaspunsScurt(struct lista *scurte)
{
    char intrebare[150], raspuns[150];
    printf("\tIntroduceti intrebarea:\n");
    printf("\tIntrebarea: ");
    gets(intrebare);
    printf("\n\tIntroduceti raspunsul:\n");
    printf("\tRaspunsul: ");
    gets(raspuns);
    adaugareScurtaInLista(scurte, intrebare, raspuns);
    printf("\n\tIntrebarea a fost adaugata\n\n");
}

void adaugareGrilaInLista(struct lista* grila, char intrebare[], char raspuns[])
{
    struct grila* elem = (struct grila*)malloc(sizeof(struct grila));
    strcpy(elem->intrebare, intrebare);
    strcpy(elem->raspuns, raspuns);
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
}

void citireVar(char* intrebare, char* raspuns1, char* raspuns2, char* raspuns3, char* corect,struct lista *grila)
{
    printf("\tIntroduceti intrebarea\n");
    printf("\tIntrebarea: ");
    char copie[150];
    gets(intrebare);
    strcpy(copie, intrebare);
    intrebare[0] = '\0';
    printf("\n\tIntroduceti prima varianta de raspuns\n");
    printf("\tPrima varianta: ");
    gets(raspuns1);
    strcat(intrebare, raspuns1);
    strcat(intrebare, ";");
    printf("\n\tIntroduceti a doua varianta de raspuns\n");
    printf("\tA doua varianta: ");
    gets(raspuns2);
    strcat(intrebare, raspuns2);
    strcat(intrebare, ";");
    printf("\n\tIntroduceti a treia varianta de raspuns\n");
    printf("\tA treia varianta: ");
    gets(raspuns3);
    strcat(intrebare, raspuns3);
    strcat(intrebare, ";");
    printf("\n\tIntroduceti raspunsul corect\n");

    while (1) {
        printf("\tRaspunsul corect: ");
        gets(corect);
        printf("\n");
        if (strcmp(raspuns1, corect) == 0 || strcmp(raspuns2, corect) == 0 || strcmp(raspuns3, corect) == 0) {
            strcat(intrebare, corect);
            adaugareGrilaInLista(grila, copie, intrebare);
            break;
        }
        else
        {
            printf("\tRaspunsul corect nu coincide cu niciuna dintre variante.\n\tIntroduceti unul dintre raspunsurile introduse deja.\n\n");
        }

    }
}

void adaugareRaspunsMultiplu(struct lista *grila) {

    char* intrebare = (char*)malloc(150 * sizeof(char));
    char* raspuns1 = (char*)malloc(30 * sizeof(char));
    char* raspuns2 = (char*)malloc(30 * sizeof(char));
    char* raspuns3 = (char*)malloc(30 * sizeof(char));
    char* corect = (char*)malloc(30 * sizeof(char));
    citireVar(intrebare, raspuns1, raspuns2, raspuns3, corect,grila);

    printf("\n\tIntrebarea a fost adaugata\n\n");

    free(intrebare);
    free(raspuns1);
    free(raspuns2);
    free(raspuns3);
    free(corect);
}