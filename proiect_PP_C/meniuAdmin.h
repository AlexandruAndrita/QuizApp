void optiuniAdministrator(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor,int* contorStocIntrebari,char parola[], int* contorIntrebariScurt, int* contorIntrebariGrila)
{
    opadmin();
    while (1)
    {
        printf("\t");
        char optiune[10];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 5:
                mutareDateInFisier(rank, clasament);
                plasareParolaNouaInFisier(parola, parolaAdmin);
                completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 1);
                completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 2);
                system("cls");
                printf("\tAi parasit jocul");
                exit(0);
            case 1:
                system("cls");
                printf("\tAdaugare intrebare noua\n");
                tipIntrebare(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari,parola,contorIntrebariScurt,contorIntrebariGrila);
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
                    int contor = 0, numar = 0, nrMax = -1;
                    afisareIntrebari(scurte, grila, 1, &contor);
                    int* aparitii = (int*)calloc(contor, sizeof(aparitii));
                    int cateNumere = 0;
                    citireIndecsi(aparitii, contor, &nrMax);
                    confirmareStergere(contor, aparitii, &numar,&cateNumere);

                    if (numar == 1) {
                        stergereIntrebari(scurte, grila, aparitii, contor, 1,contorIntrebariScurt,contorIntrebariGrila);
                        afisareIndecsiSterse(nrMax, aparitii,cateNumere);
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
                        int contor = 0, numar = 0, nrMax = -1;
                        afisareIntrebari(scurte, grila, 2, &contor);
                        int* aparitii = (int*)calloc(contor, sizeof(aparitii));
                        int cateNumere = 0;
                        citireIndecsi(aparitii, contor, &nrMax);
                        confirmareStergere(contor, aparitii, &numar,&cateNumere);

                        if (numar == 1) {
                            stergereIntrebari(scurte, grila, aparitii, contor, 2,contorIntrebariScurt,contorIntrebariGrila);
                            afisareIndecsiSterse(nrMax, aparitii,cateNumere);
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
                break;
            case 3:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari,parola,contorIntrebariScurt,contorIntrebariGrila);
                break;
            case 4:
                system("cls");
                schimbareParolaAdmin(parola);
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

void tipIntrebare(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor,int* contorStocIntrebari,char parola[], int* contorIntrebariScurt, int* contorIntrebariGrila)
{
    tipIntrebareQ();
    while (1)
    {
        printf("\t");
        char optiune[10];
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 3:
                system("cls");
                optiuniAdministrator(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari,parola,contorIntrebariScurt,contorIntrebariGrila);
                break;
            case 1:
                system("cls");
                adaugareRaspunsScurt(scurte);
                break;
            case 2:
                system("cls");
                adaugareRaspunsMultiplu(grila);
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
        tipIntrebareQ();
    }
}