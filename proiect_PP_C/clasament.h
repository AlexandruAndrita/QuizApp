void adaugareInLista(struct lista* rank, char *linie)
{
	char* p = strtok(linie, ";");
	struct ranking* elem = (struct ranking*)malloc(sizeof(struct ranking));
	strcpy(elem->nume, p);
	p = strtok(NULL, ";");
	if (p[strlen(p) - 1] == '\n')
		p[strlen(p) - 1] = '\0';

	elem->punctaj = atoi(p);
	elem->urmator = NULL;
	if (rank->primul == NULL)
	{
		rank->primul = elem;
	}
	else
	{
		struct ranking* aux = rank->primul;
		while (aux->urmator != NULL)
		{
			aux = aux->urmator;
		}
		aux->urmator = elem;
	}
}

void preluareNumeDinFisier(struct lista* rank, char* clasament)
{
	FILE* pointerFis;
	pointerFis = fopen(clasament, "r");
	if (pointerFis == NULL)
	{
		system("cls");
		printf("\tFisierul nu exista");
		exit(1);
	}
	else
	{
		char* linie = (char*)calloc(102, sizeof(char));
		while (fgets(linie, 100, pointerFis))
		{
			adaugareInLista(rank, linie);
		}
	}
	fclose(pointerFis);
}

void afisareClasament(struct lista* rank)
{
	system("cls");
	printf("\tClasament:\n\n");
	int pozitie = 0;
	struct ranking* elem = rank->primul;
	while (elem != NULL)
	{
		pozitie++;
		printf("\t%d: %s %d\n", pozitie,elem->nume, elem->punctaj);
		elem = elem->urmator;
	}
	printf("\n");
}

int cautare(struct lista* rank, char *nume)
{
	struct ranking* aux = rank->primul;
	while (aux != NULL) {
		if (strcmp(aux->nume, nume) == 0)
			return 0;
		aux = aux->urmator;
	}
	return 1;
}

struct ranking* creareJucator(char numeJucator[], int catePuncte)
{
	struct ranking* elem = (struct ranking*)malloc(sizeof(struct ranking));
	strcpy(elem->nume, numeJucator);
	elem->punctaj = catePuncte;
	elem->urmator = NULL;
	return elem;
}

void adaugareJucatorNou(struct lista* rank, char numeJucator[], int catePuncte)
{
	struct ranking* elem = creareJucator(numeJucator, catePuncte);
	if (rank->primul == NULL)
	{
		rank->primul = elem;
	}
	else
	{
		if (rank->primul->punctaj <= catePuncte)
		{
			elem->urmator = rank->primul;
			rank->primul = elem;
		}
		else
		{
			struct ranking* aux = rank->primul;
			while (aux->urmator != NULL)
			{
				if (aux->punctaj >= catePuncte && aux->urmator->punctaj <= catePuncte)
				{
					elem->urmator = aux->urmator;
					aux->urmator = elem;
					break;
				}
				aux = aux->urmator;
			}
		}
	}
}

void mutareDateInFisier(struct lista* rank, char* clasament)
{
	FILE* pointerFis;
	pointerFis = fopen(clasament, "w");
	char linie[60],pct[10],num[50];
	struct ranking* elem = rank->primul;
	while (elem != NULL)
	{
		memset(linie, 0, 60);
		memset(pct, 0, 10);
		memset(num, 0, 50);

		strcpy(num, elem->nume);
		strcat(linie,num);
		strcat(linie, ";");
		_itoa(elem->punctaj, pct, 10);
		strcat(linie, pct);
		fprintf(pointerFis, "%s\n", linie);
		
		elem = elem->urmator;
	}
	fclose(pointerFis);
}

