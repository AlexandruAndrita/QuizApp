void confirmareStergere(int contor,int *aparitii,int *numar)
{
    system("cls");
    printf("\tDoriti sa stergeti intrebarile numerotate cu ");
    for (int i = 1; i <= contor; i++)
    {
        if (aparitii[i] != 0)
            printf("%d ", i);
    }
    printf("?\n");
    char optiune[5];
    (*numar) = 0;
    printf("\t[1] Da\n");
    printf("\t[2] Nu\n");
    while (1)
    {
        printf("\t");
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
}

void afisareIndecsiSterse(int nrMax, int* aparitii)
{
    printf("\n\tIntrebarile numerotate cu: ");
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
    printf(" au fost sterse.\n\n");
}

void optiuniAdministrator(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin,struct lista* scurte, struct lista* grila, struct lista* rank,int *contor)
{
    opadmin();
    while (1)
    {
        printf("\t");
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 5:
                system("cls");
                printf("\tAi parasit jocul");
                exit(0);
            case 1:
                system("cls");
                printf("\tAdaugare intrebare noua\n");
                tipIntrebare(clasament, intrebariScurte, intrebariGrila, parolaAdmin,scurte,grila,rank,contor);
                break;
            case 2:
                system("cls");
                printf("\tDoriti sa stergeti intrebari cu raspuns scurt sau intrebari tip grila?\n");
                printf("\t[1] Intrebare cu raspuns scurt\n\t[2] Intrebare tip grila\n\n");
                char* optiune = (char*)calloc(10, sizeof(char));
                int numarOptiune = 0;
                while (1)
                {
                    printf("\t");
                    scanf("%s", optiune);

                    if (validareInput(optiune) == 1)
                    {
                        numarOptiune = atoi(optiune);
                        if (numarOptiune == 1 || numarOptiune == 2) {

                            break;
                        }
                        else
                        {
                            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
                            printf("\t[1] Intrebare cu raspuns scurt\n\t[2] Intrebare tip grila\n");
                        }
                    }
                    else
                    {
                        printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
                        printf("\t[1] Intrebare cu raspuns scurt\n\t[2] Intrebare tip grila\n");
                    }
                }
                free(optiune);
                if (numarOptiune == 1)
                {
                    getchar();
                    int contor = 0,numar=0,nrMax=-1;
                    afisareIntrebari(scurte, grila, 1, &contor);
                    int* aparitii = (int*)calloc(contor, sizeof(aparitii));
                    citireIndecsi(aparitii,contor,&nrMax);
                    confirmareStergere(contor, aparitii, &numar);

                    if (numar == 1) {
                        stergereIntrebari(scurte, grila, aparitii, contor, 1);
                        afisareIndecsiSterse(nrMax, aparitii);
                        completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 1);
                    }
                    else
                    {
                        if (numar == 2)
                        {
                            printf("\n\tNu a fost stearsa nicio intrebare.\n\n");
                        }
                    }
                    free(aparitii);
                }
                else
                {
                    if (numarOptiune == 2)
                    {
                        getchar();
                        int contor = 0,numar=0,nrMax=-1;
                        afisareIntrebari(scurte, grila, 2, &contor);
                        int* aparitii = (int*)calloc(contor, sizeof(aparitii));
                        citireIndecsi(aparitii, contor,&nrMax);
                        confirmareStergere(contor, aparitii, &numar);

                        if (numar == 1) {
                            stergereIntrebari(scurte, grila, aparitii, contor, 2);
                            afisareIndecsiSterse(nrMax, aparitii);
                            completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 2);
                        }
                        else
                        {
                            if (numar == 2) 
                            {
                                printf("\n\tNu a fost stearsa nicio intrebare.\n\n");
                            }
                        }
                        free(aparitii);
                    }
                }
                getchar();
                break;
            case 3:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin,scurte,grila,rank,contor);
                break;
            case 4:
                system("cls");
                schimbareParolaAdmin(parolaAdmin);
                break;
            default:
                system("cls");
                printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
            }
        }
        else
        {
        system("cls");
            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
        }
        opadmin();
    }
}

void schimbareParolaAdmin(char* parolaAdmin)
{
    FILE* pointerFis;
    pointerFis = fopen(parolaAdmin, "w");
    if (pointerFis == NULL)
    {
        system("cls");
        printf("\tFisierul nu exista");
        exit(1);
    }
    char* parolaNoua = (char*)calloc(30, sizeof(char));
    char* confirmareparolaNoua = (char*)calloc(30, sizeof(char));
    printf("\tIntroduceti noua parola:\n");
    printf("\t");
    gets(parolaNoua);
    printf("\tIntroduceti din nou parola pentru confirmare:\n");
    while (1)
    {
        printf("\t");
        gets(confirmareparolaNoua);
        if (strcmp(parolaNoua, confirmareparolaNoua) == 0)
        {
            printf("\n\tParola a fost modificata.\n\tNoua parola este: %s\n\n", parolaNoua);
            break;
        }
        else
        {
            system("cls");
            printf("\n\tParolele nu corespund.\n\tIncercati din nou.\n\n");
        }
    }
    fprintf(pointerFis, "%s", parolaNoua);
    fclose(pointerFis);
    free(parolaNoua);
    free(confirmareparolaNoua);
}

int verificareParolaAdministrator(char* parolaAdmin)
{
    system("cls");
    FILE* pointerFis;
    pointerFis = fopen(parolaAdmin, "r");
    if (pointerFis == NULL)
    {
        system("cls");
        printf("\tFisierul nu exista");
        exit(1);
    }
    char* parola = (char*)calloc(30, sizeof(char));
    char* linie = (char*)calloc(30, sizeof(char));
    fgets(linie, 30, pointerFis);
    if (linie[strlen(linie) - 1] == '\n')
    {
        linie[strlen(linie) - 1] = '\0';
    }
    fclose(pointerFis);

    printf("\tIntroduceti parola\n\n");
    printf("\t");
    gets(parola);

    if (strcmp(parola, linie) != 0) {
        free(parola);
        free(linie);
        return 0;
    }
    free(parola);
    free(linie);
    return 1;
}