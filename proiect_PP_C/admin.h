void confirmareStergere(int contor,int *aparitii,int *numar)
{
    printf("Doriti sa stergeti intrebarile numerotate cu ");
    for (int i = 1; i <= contor; i++)
    {
        if (aparitii[i] != 0)
            printf("%d ", i);
    }
    printf("?\n");
    char optiune[5];
    (*numar) = 0;
    printf("1. Da (tasta 1)\n");
    printf("2. Nu (tasta 2)\n");
    while (1)
    {
        scanf("%s", optiune);
        if (validareInput(optiune) == 1)
        {
            (*numar) = atoi(optiune);
            if ((*numar) == 1 || (*numar) == 2)
                break;
        }
        else
        {
            printf("Caracterele introduse nu sunt conform cerintei.\nIncercati din nou.\n");
        }
    }
}

void afisareSterse(int nrMax, int* aparitii)
{
    printf("Intrebarile numerotate cu: ");
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

void optiuniAdministrator(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin,struct lista* scurte, struct lista* grila, struct lista* rank)
{
    opadmin();
    while (1)
    {
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 5:
                printf("Ai parasit jocul");
                exit(0);
            case 1:
                printf("Adaugare intrebare noua\n");
                tipIntrebare(clasament, intrebariScurte, intrebariGrila, parolaAdmin,scurte,grila,rank);
                break;
            case 2:
                printf("Doriti sa stergeti intrebari cu raspuns scurt sau intrebari tip grila?\n");
                printf("1. Intrebare cu raspuns scurt (tasta 1)\n2. Intrebare tip grila (tasta2)\n");
                char* optiune = (char*)calloc(10, sizeof(char));
                int numarOptiune = 0;
                while (1)
                {
                    scanf("%s", optiune);

                    if (validareInput(optiune) == 1)
                    {
                        numarOptiune = atoi(optiune);
                        if (numarOptiune == 1 || numarOptiune == 2) {

                            break;
                        }
                        else
                        {
                            printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
                            printf("1. Intrebare cu raspuns scurt (tasta 1)\n2. Intrebare tip grila (tasta2)\n");
                        }
                    }
                    else
                    {
                        printf("Valoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
                        printf("1. Intrebare cu raspuns scurt (tasta 1)\n2. Intrebare tip grila (tasta2)\n");
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
                        afisareSterse(nrMax, aparitii);
                    }
                    else
                    {
                        if (numar == 2)
                        {
                            printf("Nu a fost stearsa nicio intrebare.\n");
                        }
                    }
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
                            afisareSterse(nrMax, aparitii);
                            
                        }
                        else
                        {
                            if (numar == 2) 
                            {
                                printf("Nu a fost stearsa nicio intrebare.\n");
                            }
                        }
                    }
                }
                getchar();
                break;
            case 3:
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin,scurte,grila,rank);
                break;
            case 4:
                schimbareParolaAdmin(parolaAdmin);
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

void schimbareParolaAdmin(char* parolaAdmin)
{
    FILE* pointerFis;
    pointerFis = fopen(parolaAdmin, "w");
    if (pointerFis == NULL)
    {
        printf("Fisierul nu exista");
        exit(1);
    }
    char* parolaNoua = (char*)calloc(30, sizeof(char));
    char* confirmareparolaNoua = (char*)calloc(30, sizeof(char));
    printf("Introduceti noua parola:\n");
    gets(parolaNoua);
    printf("Introduceti din nou parola pentru confirmare:\n");
    while (1)
    {
        gets(confirmareparolaNoua);
        if (strcmp(parolaNoua, confirmareparolaNoua) == 0)
        {
            printf("Parola a fost modificata.\nNoua parola este: %s\n\n", parolaNoua);
            break;
        }
        else
        {
            printf("Parolele nu corespund.\nIncercati din nou.\n");
        }
    }
    fprintf(pointerFis, "%s", parolaNoua);
    fclose(pointerFis);
    free(parolaNoua);
    free(confirmareparolaNoua);
}

int verificareParolaAdministrator(char* parolaAdmin)
{
    FILE* pointerFis;
    pointerFis = fopen(parolaAdmin, "r");
    if (pointerFis == NULL)
    {
        printf("Fisierul nu exista\n");
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

    printf("Introduceti parola\n");
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