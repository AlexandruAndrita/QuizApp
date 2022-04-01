void adaugareRaspunsScurt(char* intrebariScurte)
{
    char intrebare[150], raspuns[150];
    FILE* fptr;
    fptr = fopen(intrebariScurte, "a");
    if (fptr == NULL)
    {
        system("cls");
        printf("\tFisierul nu exista");
        exit(1);
    }
    else {
        printf("\tIntroduceti intrebarea:\n");
        printf("\t");
        gets(intrebare);
        printf("\tIntroduceti raspunsul:\n");
        printf("\t");
        strcat(intrebare, ";");
        gets(raspuns);
        strcat(intrebare, raspuns);
        fprintf(fptr, "%s\n", intrebare);
        printf("\n\tIntrebarea a fost adaugata\n\n");
    }
    fclose(fptr);
}

void citireVar(char* intrebare, char* raspuns1, char* raspuns2, char* raspuns3, char* corect)
{
    printf("\tIntroduceti intrebarea\n");
    printf("\t");
    gets(intrebare);
    strcat(intrebare, ";");
    printf("\tIntroduceti prima varianta de raspuns\n");
    printf("\t");
    gets(raspuns1);
    strcat(intrebare, raspuns1);
    strcat(intrebare, ";");
    printf("\tIntroduceti a doua varianta de raspuns\n");
    printf("\t");
    gets(raspuns2);
    strcat(intrebare, raspuns2);
    strcat(intrebare, ";");
    printf("\tIntroduceti a treia varianta de raspuns\n");
    printf("\t");
    gets(raspuns3);
    strcat(intrebare, raspuns3);
    strcat(intrebare, ";");
    printf("\tIntroduceti raspunsul corect\n");

    while (1) {
        printf("\t");
        gets(corect);
        if (strcmp(raspuns1, corect) == 0 || strcmp(raspuns2, corect) == 0 || strcmp(raspuns3, corect) == 0) {
            strcat(intrebare, corect);
            break;
        }
        else
        {
            printf("\tRaspunsul corect nu coincide cu niciuna dintre variante.\n\tIntroduceti unul dintre raspunsurile introduse deja.\n\n");
        }

    }
}

void adaugareRaspunsMultiplu(char* intrebariGrila) {

    FILE* multiplu;
    multiplu = fopen(intrebariGrila, "a");
    if (multiplu == NULL)
    {
        system("cls");
        printf("\tFisierul nu exista");
        exit(1);
    }
    else {
        char* intrebare = (char*)malloc(150 * sizeof(char));
        char* raspuns1 = (char*)malloc(30 * sizeof(char));
        char* raspuns2 = (char*)malloc(30 * sizeof(char));
        char* raspuns3 = (char*)malloc(30 * sizeof(char));
        char* corect = (char*)malloc(30 * sizeof(char));
        citireVar(intrebare, raspuns1, raspuns2, raspuns3, corect);

        fprintf(multiplu, "%s\n", intrebare);
        

        printf("\n\tIntrebarea a fost adaugata\n\n");

        free(intrebare);
        free(raspuns1);
        free(raspuns2);
        free(raspuns3);
        free(corect);

        fclose(multiplu);
    }
}