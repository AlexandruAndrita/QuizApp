void verificareStatusUser(int* nou)
{
    optiuniStatusUser();
    while (*nou == 0)
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
                system("cls");
                *nou = 1;
                break;
            case 2:
                system("cls");
                *nou = 2;
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
        optiuniStatusUser();
    }
}

void repetareJoc(int *ramura)
{
    printf("\t[1] Da");
    printf("\n\t[2] Nu");
    int valid = 0;
    while (valid==0)
    {
        printf("\n\t");
        char raspuns[10];
        gets(raspuns);
        if (validareInput(raspuns) == 1)
        {
            int numar = atoi(raspuns);
            switch (numar)
            {
            case 1:
                *ramura = 1;
                valid = 1;
                break;
            case 2:
                *ramura = 2;
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

void incepeQuiz(int contorIntrebariScurt, int contorIntrebariGrila, char* parolaAdmin, char* clasament, char* intrebariScurte, char* intrebariGrila, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor,int statusUser,int *contorStocIntrebari,char parola[])
{
    char numeJucator[50];
    int runda = 0;
    memset(numeJucator, 0, 50);
    preluareNumeUser(numeJucator, &statusUser, rank);

    int catePuncte = 0;
    int catePuncteGrila = 0, catePuncteScurt = 0;
    optiuniQuiz();
    while (1)
    {
        printf("\t");
        char optiune[10];
        scanf("%s", optiune);

        if (validareInput(optiune) == 1)
        {
            int numar = atoi(optiune);
            if (numar != 4 && numar != 1 && numar != 2 && numar != 3)
            {
                system("cls");
                printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
            }
            else {
                if (numar == 4)
                {
                    mutareDateInFisier(rank, clasament);
                    plasareParolaNouaInFisier(parola, parolaAdmin);
                    completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 1);
                    completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 2);
                    system("cls");
                    printf("\tAi parasit jocul");
                    exit(0);
                }
                if (numar == 1)
                {
                    int ramura = 0;
                    if (runda >= 1)
                    {
                        system("cls");
                        printf("\tAti jucat deja o runda.\n\tPuteti rejuca cu acelasi nume alta runda.Doriti?\n");
                        getchar();
                        repetareJoc(&ramura);
                        statusUser = 2;
                        if (ramura == 2) {
                            statusUser = 1;
                            system("cls");
                        }
                    }
                    if (statusUser == 1 && ramura!=0)
                        break;
                    runda++;
                    system("cls");
                    printf("\n\tDoriti un test grila sau un test cu raspunsuri scurte?\n\t[1] Grila (Tasta 1)\n\t[2] Raspuns scurt (Tasta 2)\n\n");
                    char opt[10];
                    int numarOptiune = 0;
                    memset(opt, 0, 10);
                    while (1)
                    {
                        printf("\t");
                        scanf("%s", opt);
                        if (validareInput(opt) == 1)
                        {
                            numarOptiune = atoi(opt);
                            if (numarOptiune == 1 || numarOptiune == 2)
                                break;
                            else
                            {
                                system("cls");
                                printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
                                printf("\n\t[1] Grila (Tasta 1)\n\t[2] Raspuns scurt (Tasta 2)\n\n");
                            }
                        }
                        else
                        {
                            system("cls");
                            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
                            printf("\n\t[1] Grila (Tasta 1)\n\t[2] Raspuns scurt (Tasta 2)\n\n");
                        }
                    }
                    if (numarOptiune == 1)
                    {
                        system("cls");

                        clock_t start_t, end_t, total_t;
                        start_t = 0;
                        end_t = 0;
                        total_t = 0;
                        catePuncte = quizGrila(contorIntrebariGrila, grila, &start_t, &end_t, &total_t);
                        long timp = total_t;

                        printf("\n\tScorul tau este: %d / %d\n\tAi completat quiz-ul in %ld secunde.\n\n", catePuncte, 5, timp);
                        adaugareJucatorNou(rank, numeJucator, catePuncte, timp,statusUser);
                    }
                    else {
                        system("cls");

                        clock_t start_t, end_t, total_t;
                        start_t = 0;
                        end_t = 0;
                        total_t = 0;
                        catePuncte = quizScurt(contorIntrebariScurt, scurte, &start_t, &end_t, &total_t);
                        long timp = total_t;

                        printf("\n\tScorul tau este: %d / %d\n\tAi completat quiz-ul in %ld secunde.\n\n", catePuncte, 5, timp);
                        adaugareJucatorNou(rank, numeJucator, catePuncte, timp,statusUser);
                    }

                }
                if (numar == 2)
                {
                    getchar();
                    system("cls");
                    paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari,parola,&contorIntrebariScurt,&contorIntrebariGrila);

                }
                if (numar == 3)
                {
                    system("cls");
                    if (rank->primul == NULL) {
                        system("cls");
                        printf("\n\tNu exista vreun clasament.\n\tNu a fost gasit niciun utilizator\n\n");
                    }
                    else {
                        afisareClasament(rank);
                    }
                }
            }
        }
        else
        {
            system("cls");
            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
        }
        optiuniQuiz();
    }
}

void optiuniUser(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, int contorIntrebariScurt, int contorIntrebariGrila, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor,int statusUser,int* contorStocIntrebari,char parola[])
{
    opuser();
    while (1)
    {
        printf("\t");
        char optiune[10];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 4:
                mutareDateInFisier(rank, clasament);
                plasareParolaNouaInFisier(parola, parolaAdmin);
                completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 1);
                completareInFisier(intrebariScurte, intrebariGrila, scurte, grila, 2);
                system("cls");
                printf("\tAi parasit jocul");
                exit(0);
            case 1:
                if (rank->primul == NULL)
                {
                    system("cls");
                    printf("\n\tNu exista vreun clasament.\n\tNu a fost gasit niciun utilizator\n\n");
                }
                else {
                    afisareClasament(rank);
                }
                break;
            case 2:
                system("cls");
                incepeQuiz(contorIntrebariScurt, contorIntrebariGrila, parolaAdmin, clasament, intrebariScurte, intrebariGrila, scurte, grila, rank, contor, statusUser,contorStocIntrebari,parola);
                break;
            case 3:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor,contorStocIntrebari,parola,&contorIntrebariScurt,&contorIntrebariGrila);
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
        opuser();
    }
}