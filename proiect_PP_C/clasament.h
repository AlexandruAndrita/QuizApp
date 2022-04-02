void adaugareInLista(struct lista* rank, char *linie)
{
	char* p = strtok(linie, ";");
	struct ranking* elem = (struct ranking*)malloc(sizeof(struct ranking));
	strcpy(elem->nume, p);
	p = strtok(NULL, ";");
	if (p[strlen(p) - 1] == '\n')
		p[strlen(p) - 1] = '\0';

	elem->punctaj = atoi(p);
	p = strtok(NULL, ";");
	if (p[strlen(p) - 1] == '\n')
		p[strlen(p) - 1] = '\0';
	elem->timp = atoll(p);
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
		char* linie = (char*)calloc(150, sizeof(char));
		while (fgets(linie, 150, pointerFis))
		{
			adaugareInLista(rank, linie);
		}
	}
	fclose(pointerFis);
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

struct ranking* creareJucator(char numeJucator[], int catePuncte,long timp)
{
	struct ranking* elem = (struct ranking*)malloc(sizeof(struct ranking));
	strcpy(elem->nume, numeJucator);
	elem->punctaj = catePuncte;
	elem->timp = timp;
	elem->urmator = NULL;
	return elem;
}

void adaugareJucatorNou(struct lista* rank, char numeJucator[], int catePuncte, long timp)
{
	struct ranking* elem = creareJucator(numeJucator, catePuncte,timp);
	if (rank->primul == NULL)
	{
		rank->primul = elem;
	}
	else
	{
		if (rank->primul->punctaj < catePuncte)
		{
			elem->urmator = rank->primul;
			rank->primul = elem;
		}
		else
		{
			if (rank->primul->punctaj == catePuncte && rank->primul->timp > timp)
			{
				elem->urmator = rank->primul;
				rank->primul = elem;
			}
			else
			{
				int ok = 0;
				struct ranking* p = rank->primul;
				struct ranking* c = rank->primul->urmator;
				while (c!= NULL)
				{
					if (c->punctaj <= catePuncte)
					{
						elem->urmator = c;
						p->urmator = elem;
						ok = 1;
						break;
					}
					p = p->urmator;
					c = c->urmator;
				}
				if (ok == 0)
					p->urmator = elem;
			}
		}
	}
}

void mutareDateInFisier(struct lista* rank, char* clasament)
{
	FILE* pointerFis;
	pointerFis = fopen(clasament, "w");
	char linie[60],pct[10],num[50],timp[10];
	struct ranking* elem = rank->primul;
	while (elem != NULL)
	{
		memset(linie, 0, 60);
		memset(pct, 0, 10);
		memset(num, 0, 50);
		memset(timp, 0, 10);

		strcpy(num, elem->nume);
		strcat(linie,num);
		strcat(linie, ";");
		_itoa(elem->punctaj, pct, 10);
		strcat(linie, pct);
		strcat(linie, ";");
		_ltoa(elem->timp, timp, 10);
		strcat(linie, timp);
		fprintf(pointerFis, "%s\n", linie);
		
		elem = elem->urmator;
	}
	fclose(pointerFis);
}

