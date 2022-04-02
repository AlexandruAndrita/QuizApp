void optiuniQuiz()
{
    printf("\t[1] Incepe quiz\n");
    printf("\t[2] Mergi la pagina principala\n");
    printf("\t[3] Vezi clasament\n");
    printf("\t[4] Paraseste jocul\n");
}

void opuser()
{
    printf("\t[1] Vizualizare clasament\n");
    printf("\t[2] Incepe quiz\n");
    printf("\t[3] Pagina principala\n");
    printf("\t[4] Paraseste jocul\n");
}

void opadmin()
{
    printf("\t[1] Adauga intrebare noua\n");
    printf("\t[2] Stergere intrebare\n");
    printf("\t[3] Pagina principala\n");
    printf("\t[4] Schimba parola\n");
    printf("\t[5] Paraseste jocul\n");
}

void tipIntrebareQ()
{
    printf("\t[1] Introducere intrebare cu raspuns scurt\n");
    printf("\t[2] Introducere intrebare cu raspuns multiplu\n");
    printf("\t[3] Intoarce-te la meniul de administrator\n");
}

void opprinicipala()
{
    printf("\t[1] Sunt utilizator, nu administrator\n");
    printf("\t[2] Sunt administrator\n");
    printf("\t[3] Reguli\n");
    printf("\t[4] Paraseste jocul\n");

}

void reguli()
{
    printf("\n");
    printf("\t1. Pentru intrebariel cu raspuns scurt, va fi introdus doar raspunsul care este considerat corect de catre utilizator.\n");
    printf("\t2. Pentru intrebarile de tip grila, se va raspunde cu 1 (adica a) ),2 (adica b) ) sau 3 (adica c) ).\n\tOrice alt raspuns va fi considerat gresit.\n");
    printf("\t3. Scorul va fi afisat la final, iar numele si scorul vor fi puse intr-un clasament.\n\tClasamentul poate fi vizuzalizat de catre utilizator daca se doreste acest lucru.\n");
    printf("\t4. Pentru stergerea de intrebari vor fi introdusi indecsii intrebarilor ce vor fi a sterse separati printr-un spatiu.\n");
    printf("\n");
}

void optiuniReguli()
{
    printf("\t[1] Continuati in aplicatie\n");
    printf("\t[2] Parasiti aplicatia\n");
}

void optiuniStatusUser()
{
    printf("\n\tSunteti un utilizator nou?\n");
    printf("\t[1] Da\n");
    printf("\t[2] Nu\n\n");
}

