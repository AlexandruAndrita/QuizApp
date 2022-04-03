char* initializare()
{
    char* numeFisier = (char*)malloc(20 * sizeof(char));
    if (numeFisier != NULL) {
        for (int i = 0; i < 20; i++)
            numeFisier[i] = 0;
    }
    return numeFisier;
}

void numeFisiere(char* clasament, char* intrebariScurte, char* intrebariGrila, char* parolaAdmin)
{
    strcpy(clasament, "clasament.txt");
    strcpy(intrebariScurte, "scurtraspIntrebari.txt");
    strcpy(intrebariGrila, "mulraspIntrebari.txt");
    strcpy(parolaAdmin, "parolaAdmin.txt");
}

