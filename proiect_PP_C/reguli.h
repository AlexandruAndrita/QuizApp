void meniuReguli(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor, int* contorStocIntrebari, char parola[], int* contorIntrebariScurt, int* contorIntrebariGrila)
{
    optiuniReguli();
    while (1)
    {
        char optiune[10];
        printf("\n\tOptiunea dumneavoastra: ");
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 1:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor, contorStocIntrebari, parola, contorIntrebariScurt, contorIntrebariGrila);
                break;
            case 2:
                mutareDateInFisier(rank, clasament);
                plasareParolaNouaInFisier(parola, parolaAdmin);
                completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 1);
                completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 2);
                system("cls");
                printf("\tAti parasit jocul.");
                exit(0);
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
        optiuniReguli();
    }
}