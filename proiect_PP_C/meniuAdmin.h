void optiuniAdministrator(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor)
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
                tipIntrebare(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor);
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
                    citireIndecsi(aparitii, contor, &nrMax);
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
                        int contor = 0, numar = 0, nrMax = -1;
                        afisareIntrebari(scurte, grila, 2, &contor);
                        int* aparitii = (int*)calloc(contor, sizeof(aparitii));
                        citireIndecsi(aparitii, contor, &nrMax);
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
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor);
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

void tipIntrebare(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor)
{
    tipIntrebareQ();
    while (1)
    {
        printf("\t");
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 3:
                system("cls");
                optiuniAdministrator(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor);
                break;
            case 1:
                system("cls");
                adaugareRaspunsScurt(intrebariScurte);
                break;
            case 2:
                system("cls");
                adaugareRaspunsMultiplu(intrebariGrila);
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