void extragereParolaAdmin(char parola[], char* parolaAdmin)
{
    FILE* pointerFis;
    pointerFis = fopen(parolaAdmin, "r");
    if (pointerFis == NULL)
    {
        printf("Fisierul nu exista");
        exit(1);
    }
    else
    {
        fgets(parola, 20, pointerFis);
        if (parola[strlen(parola) - 1] == '\n')
            parola[strlen(parola) - 1] = '\0';
    }
    fclose(pointerFis);
}

void schimbareParolaAdmin(char parola[])
{
    char* parolaNoua = (char*)calloc(30, sizeof(char));
    char* confirmareparolaNoua = (char*)calloc(30, sizeof(char));
    int schimba = -1;
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
            schimba = -1;
            confirmareSchimbareParola(&schimba);

            if (schimba == 1) {
                system("cls");
                printf("\n\tParola a fost modificata.\n\tNoua parola este: %s\n\n", parolaNoua);
            }
            else {
                system("cls");
                printf("\n\tParola nu a fost modificata.\n\tParola curenta este: %s\n\n", parola);
            }
            break;
        }
        else
        {
            printf("\n\tParolele nu corespund.\n\tIncercati din nou.\n\n");
        }
    }
    if (schimba == 1)
        strcpy(parola, parolaNoua);
    free(parolaNoua);
    free(confirmareparolaNoua);
}

void confirmareSchimbareParola(int* schimba)
{
    printf("\n\tSunteti sigur ca doriti sa schimbati parola:\n");
    printf("\t[1] Da\n\t[2] Nu\n\n");
    int valid = 0;
    while (valid == 0)
    {
        printf("\t");
        char optiune[10];
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 1:
                *schimba = 1;
                valid = 1;
                break;
            case 2:
                *schimba = 0;
                valid = 1;
                break;
            default:
                system("cls");
                printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
                printf("\t[1] Da\n\t[2] Nu\n\n");
            }
        }
        else
        {
            system("cls");
            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
            printf("\t[1] Da\n\t[2] Nu\n\n");
        }
    }
}

int verificareParolaAdministrator(char parola[])
{
    system("cls");
    char userInput[20];

    printf("\tIntroduceti parola\n\n");
    printf("\t");
    gets(userInput);

    if (strcmp(parola, userInput) != 0)
    {
        return 0;
    }
    return 1;
}

void plasareParolaNouaInFisier(char parola[], char* parolaAdmin)
{
    FILE* pointerFis;
    pointerFis = fopen(parolaAdmin, "w");
    if (pointerFis == NULL)
    {
        system("cls");
        printf("\tFisierul nu exista");
        exit(1);
    }
    fprintf(pointerFis, "%s", parola);
    fclose(pointerFis);
}