void incepeQuiz(int contorIntrebariScurt, int contorIntrebariGrila, char* parolaAdmin, char* clasament, char* intrebariScurte, char* intrebariGrila, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor)
{
    char numeJucator[50];
    int runda = 0;
    memset(numeJucator, 0, 50);
    printf("\tIntroduceti-va numele:\n");
    printf("\t");
    gets(numeJucator);

    while (1)
    {
        if (cautare(rank, numeJucator) == 1)
            break;
        else {
            printf("\n\tNumele introdus este luat.\n\tIncercati sa introduceti alt nume.\n\n");
            memset(numeJucator, 0, 50);
            printf("\t");
            gets(numeJucator);
        }
    }
    system("cls");
    int catePuncte = 0;
    int catePuncteGrila = 0, catePuncteScurt = 0;
    optiuniQuiz();
    while (1)
    {
        printf("\t");
        char optiune[256];
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
                    system("cls");
                    printf("\tAi parasit jocul");
                    exit(0);
                }
                if (numar == 1)
                {
                    if (runda >= 1)
                    {
                        system("cls");
                        printf("\tAti jucat deja o runda.\n\tPuteti rejuca cu alt nume\n\n");
                        getchar();
                        break;
                    }
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
                                //printf("Doriti un test grila sau un test cu raspunsuri scurte?\n 1. Grila (Tasta 1)\n 2. Raspuns scurt (Tasta 2)\n");
                            }
                        }
                        else
                        {
                            system("cls");
                            printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n\n");
                            //printf("Doriti un test grila sau un test cu raspunsuri scurte?\n 1. Grila (Tasta 1)\n 2. Raspuns scurt (Tasta 2)\n");
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

                        printf("\n\tScorul tau este: %d / %d\n\tAi completat quiz-ul in %ld secunde\n\n", catePuncte, 5, timp);
                        adaugareJucatorNou(rank, numeJucator, catePuncte, timp);
                    }
                    else {
                        system("cls");

                        clock_t start_t, end_t, total_t;
                        start_t = 0;
                        end_t = 0;
                        total_t = 0;
                        catePuncte = quizScurt(contorIntrebariScurt, scurte, &start_t, &end_t, &total_t);
                        long timp = total_t;

                        printf("\n\tScorul tau este: %d / %d\n\tAi completat quiz-ul in %ld secunde\n\n", catePuncte, 5, timp);
                        adaugareJucatorNou(rank, numeJucator, catePuncte, timp);
                    }

                }
                if (numar == 2)
                {
                    getchar();
                    system("cls");
                    paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor);

                }
                if (numar == 3)
                {
                    system("cls");
                    afisareClasament(rank);
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

void optiuniUser(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin, int contorIntrebariScurt, int contorIntrebariGrila, struct lista* scurte, struct lista* grila, struct lista* rank, int* contor)
{
    opuser();
    while (1)
    {
        printf("\t");
        char optiune[256];
        gets(optiune);
        if (validareInput(optiune) == 1) {
            int numar = atoi(optiune);
            switch (numar)
            {
            case 4:
                mutareDateInFisier(rank, clasament);
                system("cls");
                printf("\tAi parasit jocul");
                exit(0);
            case 1:
                afisareClasament(rank);
                break;
            case 2:
                system("cls");
                incepeQuiz(contorIntrebariScurt, contorIntrebariGrila, parolaAdmin, clasament, intrebariScurte, intrebariGrila, scurte, grila, rank, contor);
                break;
            case 3:
                system("cls");
                paginaPrincipala(clasament, intrebariScurte, intrebariGrila, parolaAdmin, scurte, grila, rank, contor);
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