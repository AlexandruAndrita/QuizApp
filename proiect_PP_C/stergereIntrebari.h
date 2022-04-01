void afisareIntrebari(struct lista* scurte, struct lista* grila, int ok,int *contor)
{
    if (ok == 1) //afiseaza intrebari cu raspuns scurt
    {
        (*contor) = 0;
        struct questions* aux = scurte->head;
        while (aux != NULL)
        {
            (*contor)++;
            printf("Intrebarea cu numarul %d:\n%s\ncu raspunsul: %s\n\n", (*contor), aux->intrebare, aux->raspuns);
            aux = aux->next;
        }
    }
    else
    {
        if (ok == 2) //afiseaza intrebarile de tip grila
        {
            (*contor) = 0;
            struct grila* aux = grila->cap;
            while (aux != NULL)
            {
                (*contor)++;
                printf("Intrebarea cu numarul %d:\n%s\ncu variantele de raspuns:\n", (*contor), aux->intrebare);
                char copie[150];
                strcpy(copie, aux->raspuns);
                char* p = strtok(copie, ";");
                printf("a)%s\n", p);
                p = strtok(NULL, ";");
                printf("b)%s\n", p);
                p = strtok(NULL, ";");
                printf("c)%s\nsi cu raspunsul corect: ", p);
                p = strtok(NULL, ";");
                printf("%s\n\n", p);
                aux = aux->urm;
            }
        }
    }
}

void citireIndecsi(int* aparitii,int contor,int* nrMax)
{
    printf("Introduceti indecsii ale caror intrebari doriti sa le stergeti:\n\n");
    (*nrMax) = -1;
    char optiune[150];
    memset(optiune, 0, 150);
    gets(optiune);
    int numar = 0, n = strlen(optiune);

    for (int i=0; i < n; i++)
    {
        if (optiune[i]>='0' && optiune[i]<='9')
        {
            numar = numar * 10 + optiune[i] - '0';
        }
        if (optiune[i] == ' ')
        {
            if (numar <= contor && numar!=0)
            {
                if (numar > *nrMax)
                    (*nrMax) = numar;
                if(aparitii[numar]==0)
                    aparitii[numar]++;
            }
            numar = 0;
        }
        else {
            if ((optiune[i] >= '0' && optiune[i] <= '9') && (strchr("0123456789\n ", optiune[i + 1]) == 0))
            {
                numar = 0;
                continue;
            }
            else
            {
                if ((optiune[i] >= '0' && optiune[i] <= '9') && (strchr("0123456789\n ", optiune[i - 1]) == 0) && i > 0)
                {
                    numar = 0;
                    continue;
                }
            }
        }
    }
    if (numar <= contor && numar != 0)
    {
        if (numar > *nrMax)
            (*nrMax) = numar;
        if (aparitii[numar] == 0)
            aparitii[numar]++;
    }
}

int verifScurteNesterse(struct lista* scurte)
{
    struct questions* elem = scurte->head;
    while (elem != NULL)
    {
        if (strcmp(elem->intrebare, "0") == 0 && strcmp(elem->raspuns, "0") == 0)
        {
            return 1;
        }
        elem = elem->next;
    }
    return 0;
}

void stergeScurte(struct lista* scurte)
{
    while (verifScurteNesterse(scurte) == 1) {
        if (strcmp(scurte->head->intrebare, "0") == 0 && strcmp(scurte->head->raspuns, "0") == 0)
        {
            struct questions* elem = scurte->head;
            scurte->head = scurte->head->next;
            free(elem);
        }
        struct questions* prev = scurte->head;
        struct questions* cur = scurte->head->next;
        while (cur != NULL)
        {
            if (strcmp(cur->intrebare, "0") == 0 && strcmp(cur->raspuns, "0") == 0)
            {
                prev->next = cur->next;
                free(cur);
                break;
            }
            prev = prev->next;
            cur = cur->next;
        }
    }
}

int verifGrilaNesterse(struct lista* grila)
{
    struct grila* elem = grila->cap;
    while (elem != NULL)
    {
        if (strcmp(elem->intrebare, "0") == 0 && strcmp(elem->raspuns, "0") == 0)
        {
            return 1;
        }
        elem = elem->urm;
    }
    return 0;
}

void stergeGrile(struct lista* grila)
{
    while (verifGrilaNesterse(grila) == 1) {
        if (strcmp(grila->cap->intrebare, "0") == 0 && strcmp(grila->cap->raspuns, "0") == 0)
        {
            struct grila* elem = grila->cap;
            grila->cap = grila->cap->urm;
            free(elem);
        }
        struct grila* prev = grila->cap;
        struct grila* cur = grila->cap->urm;
        while (cur != NULL)
        {
            if (strcmp(cur->intrebare, "0") == 0 && strcmp(cur->raspuns, "0") == 0)
            {
                prev->urm = cur->urm;
                free(cur);
                break;
            }
            prev = prev->urm;
            cur = cur->urm;
        }
    }
}

void stergereIntrebari(struct lista* scurte, struct lista* grila, int* aparitii, int contor,int ok)
{
    if (ok == 1) //sterge intrebari cu raspuns scurt
    {
        for (int i = 1; i <= contor; i++)
        {
            if (aparitii[i] == 1)
            {
                struct questions* aux = scurte->head;
                int index = 0;
                while (aux != NULL)
                {
                    index++;
                    if (index == i)
                    {
                        strcpy(aux->intrebare, "0");
                        strcpy(aux->raspuns, "0");
                        break;
                    }
                    aux = aux->next;
                }
            }
        }
        stergeScurte(scurte);
    }
    else
    {
        if (ok == 2) //sterge intrebari de tip grila
        {
            for (int i = 1; i <= contor; i++)
            {
                if (aparitii[i] == 1)
                {
                    struct grila* aux = grila->cap;
                    int index = 0;
                    while (aux != NULL)
                    {
                        index++;
                        if (index == i)
                        {
                            strcpy(aux->intrebare, "0");
                            strcpy(aux->raspuns, "0");
                            break;
                        }
                        aux = aux->urm;
                    }
                }
            }
            stergeGrile(grila);
        }
    }
}