int cateCifre(long numar)
{
	int nr = 0;
	if (numar == 0)
		return 1;
	while (numar)
	{
		nr++;
		numar /= 10;
	}
	return nr;
}

void lungimeMaxima(struct lista* rank, int* maxiNume)
{
	struct ranking* aux = rank->primul;
	while (aux != NULL)
	{
		if (strlen(aux->nume) > *maxiNume)
			*maxiNume = strlen(aux->nume);
		aux = aux->urmator;
	}
}

void afisareCapTabel(int maxiNume, int maxiPunctaj, int* lungime)
{
	printf("\t");
	(*lungime) = 11 + maxiNume + 1 + maxiPunctaj + 8;
	for (int i = 0; i < (*lungime); i++)
	{
		printf("-");
	}
	printf("\n\t| Pozitie |");
	for (int i = 0; i < (maxiNume - 4) / 2; i++)
		printf(" ");
	printf("Nume");
	int start = (maxiNume - 4) / 2 + 4;
	afiseazaSpatiiRamase(maxiNume, start);

	printf("| Punctaj |");

	printf(" Timp |");
}

void afiseazaSpatiiRamase(int total, int afisate)
{
	int i = afisate;
	while (i < total)
	{
		printf(" ");
		i++;
	}
}

void formatareAfisare(int pozitie, char nume[], int punctaj, long timp, int maxiNume)
{
	printf("\n\t|");
	int cateCif = cateCifre(pozitie);
	for (int i = 0; i < (9 - cateCif) / 2; i++) {
		printf(" ");
	}
	printf("%d", pozitie);
	int start = (9 - cateCif) / 2 + cateCif;
	afiseazaSpatiiRamase(9, start);
	printf("|");

	int afisate = 0;
	if (maxiNume == strlen(nume))
	{
		printf(" %s ", nume);
	}
	else
	{
		for (int i = 0; i < (maxiNume - strlen(nume)) / 2; i++) {
			printf(" ");
			afisate++;
		}
		printf("%s", nume);
		afisate += strlen(nume);
		for (int i = 0; i < (maxiNume - strlen(nume)) / 2; i++) {
			printf(" ");
			afisate++;
		}
		if (afisate != maxiNume)
		{
			afiseazaSpatiiRamase(maxiNume, afisate);
		}
	}

	printf("|");
	for (int i = 0; i < 4; i++)
		printf(" ");
	printf("%d", punctaj);
	for (int i = 0; i < 4; i++)
		printf(" ");
	printf("|");

	cateCif = cateCifre(timp);
	for (int i = 0; i < (6 - cateCif) / 2; i++)
		printf(" ");
	printf("%ld", timp);
	start = (6 - cateCif) / 2 + cateCif;
	afiseazaSpatiiRamase(6, start);
	printf("|");
}

void delimitatorLinie(int lungime)
{
	printf("\n\t");
	for (int i = 0; i < lungime; i++)
	{
		printf("-");
	}
}

void afisareClasament(struct lista* rank)
{
	system("cls");
	printf("\t\t\tClasament\n\n");

	int maxiNume = 0, lungime = 0;
	lungimeMaxima(rank, &maxiNume);
	maxiNume += 2;
	afisareCapTabel(maxiNume, 9, &lungime);
	delimitatorLinie(lungime);

	int pozitie = 0;
	struct ranking* elem = rank->primul;
	while (elem != NULL)
	{
		pozitie++;
		formatareAfisare(pozitie, elem->nume, elem->punctaj, elem->timp, maxiNume);
		delimitatorLinie(lungime);
		elem = elem->urmator;
	}
	printf("\n\n");
}
