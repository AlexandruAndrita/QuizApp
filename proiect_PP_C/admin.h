void optiuniAdministrator(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin)
{
    FILE* fptr;
    FILE* multiplu;
    fptr = fopen(intrebariScurte, "a");
    multiplu = fopen(intrebariGrila, "a");
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
            case 5:
                printf("Ai parasit jocul");
                fclose(fptr);
                fclose(multiplu);
                exit(0);
            case 1:
                printf("Adaugare intrebare noua\n");
                tipIntrebare(clasament, intrebariScurte, intrebariGrila, parolaAdmin);
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
                    stergereIntrebareScurt(intrebariScurte);
                }
                else
                {
                    if (numarOptiune == 2)
                    {
                        getchar();
                        stergereIntrebareGrila(intrebariGrila);
                    }
                }
                break;
            case 3:
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin);
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