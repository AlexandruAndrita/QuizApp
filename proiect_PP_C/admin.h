void confirmareStergere(int contor,int *aparitii,int *numar,int *cateNumere)
{
    system("cls");
    int existaNumere = 0;
    for (int i = 1; i <= contor; i++)
    {
        if (aparitii[i] != 0) {
            existaNumere = 1;
            (*cateNumere)++;
        }
    }
    if (existaNumere == 1) {
        if (*cateNumere > 1) {
            printf("\tDoriti sa stergeti intrebarile numerotate cu: ");
        }
        else {
            printf("\tDoriti sa stergeti intrebarea numerotata cu: ");
        }
        for (int i = 1; i <= contor; i++)
        {
            if (aparitii[i] != 0)
                printf("%d ", i);
        }
        printf("?\n");
        char optiune[10];
        (*numar) = 0;
        printf("\t[1] Da\n");
        printf("\t[2] Nu\n");
        while (1)
        {
            printf("\tOptiunea dumneavoastra: ");
            scanf("%s", optiune);
            if (validareInput(optiune) == 1)
            {
                (*numar) = atoi(optiune);
                if ((*numar) == 1 || (*numar) == 2)
                    break;
            }
            else
            {
                printf("\tCaracterele introduse nu sunt conform cerintei.\nIncercati din nou.\n\n");
            }
        }
        getchar();
    }
    else
    {
        (*numar) = 2;
        printf("\tNu au fost introdusi indecsi sau indecii introdusi sunt mai mari decat indexul ultimei intrebari.\n");
        printf("\tAstfel incat sa poata sa fie sterse intrebari.\n");
       
    }
}

void afisareIndecsiSterse(int nrMax, int* aparitii,int cateNumere)
{
    if (cateNumere > 1) {
        printf("\n\tIntrebarile numerotate cu: ");
    }
    else {
        printf("\n\tIntrebarea numerotata cu: ");
    }

    for (int i = 1; i <= nrMax; i++)
    {
        if (aparitii[i] != 0)
        {
            if (i != nrMax)
                printf("%d, ", i);
            else
                printf("%d", i);
        }
            
    }
    if (cateNumere > 1) {
        printf(" au fost sterse.\n\n");
    }
    else {
        printf(" a fost stearsa.\n\n");
    }
}

