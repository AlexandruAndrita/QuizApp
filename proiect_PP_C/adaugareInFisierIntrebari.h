void adaugareRaspunsScurt(char* intrebariScurte)
{
    char intrebare[150], raspuns[150];
    FILE* fptr;
    fptr = fopen(intrebariScurte, "a");
    if (fptr == NULL)
    {
        printf("Fisierul nu exista");
        exit(1);
    }
    else {
        printf("Introduceti intrebarea:\n");
        gets(intrebare);
        printf("Introduceti raspunsul:\n");
        strcat(intrebare, ";");
        gets(raspuns);
        strcat(intrebare, raspuns);
        fprintf(fptr, "%s\n", intrebare);
        printf("Intrebarea a fost adaugata\n");
    }
    fclose(fptr);
}

void citireVar(char* intrebare, char* raspuns1, char* raspuns2, char* raspuns3, char* corect)
{
    printf("Introduceti intrebarea\n");
    gets(intrebare);
    strcat(intrebare, ";");
    printf("Introduceti prima varianta de raspuns\n");
    gets(raspuns1);
    strcat(intrebare, raspuns1);
    strcat(intrebare, ";");
    printf("Introduceti a doua varianta de raspuns\n");
    gets(raspuns2);
    strcat(intrebare, raspuns2);
    strcat(intrebare, ";");
    printf("Introduceti a treia varianta de raspuns\n");
    gets(raspuns3);
    strcat(intrebare, raspuns3);
    strcat(intrebare, ";");
    printf("Introduceti raspunsul corect\n");

    while (1) {

        gets(corect);
        if (strcmp(raspuns1, corect) == 0 || strcmp(raspuns2, corect) == 0 || strcmp(raspuns3, corect) == 0) {
            strcat(intrebare, corect);
            break;
        }
        else
        {
            printf("Raspunsul corect nu coincide cu niciuna dintre variante.\nIntroduceti unul dintre raspunsurile introduse deja.\n");
        }

    }
}

void adaugareRaspunsMultiplu(char* intrebariGrila) {

    FILE* multiplu;
    multiplu = fopen(intrebariGrila, "a");
    if (multiplu == NULL)
    {
        printf("Fisierul nu exista");
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
        

        printf("Intrebarea a fost adaugata\n");

        free(intrebare);
        free(raspuns1);
        free(raspuns2);
        free(raspuns3);
        free(corect);

        fclose(multiplu);
    }
}