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

void verificareTipJoc(int *incercari,int *statusUser,struct lista* rank,char numeJucator[])
{
	printf("\n\tSunteti sigur ca ati mai jucat acest joc in trecut?\n");
	printf("\t[1] Da\n");
	printf("\t[2] Nu\n");
	int valid = 0;
	while (valid==0)
	{
		printf("\tOptiunea dumneavoastra: ");
		char optiune[10];
		gets(optiune);
		if (validareInput(optiune) == 1)
		{
			int numar = atoi(optiune);
			switch(numar)
			{
			case 1:
				*statusUser = 2;
				*incercari = 1;
				valid = 1;
				numeJucator[0] = 0;
				break;
			case 2:
				*statusUser = 1;
				valid = 1;
				break;
			default:
				system("cls");
				printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
				printf("\tSunteti sigur ca ati mai jucat acest joc in trecut?\n");
				printf("\t[1] Da\n\t[2] Nu\n\n");
			}
		}
		else
		{
			system("cls");
			printf("\tValoarea introdusa nu corespunde cerintelor. Incercati din nou.\n");
			printf("\tSunteti sigur ca ati mai jucat acest joc in trecut?\n");
			printf("\t[1] Da\n\t[2] Nu\n\n");
		}
	}
}

void preluareNumeUser(char numeJucator[], int *statusUser, struct lista* rank)
{
	printf("\tIntroduceti-va numele:\n");
	printf("\tNumele: ");
	gets(numeJucator);
	int incercari = 1,validat=0;
	while (validat==0)
	{
		if (cautare(rank, numeJucator) == 0) //numele a fost gasit in structura
		{
			if (*statusUser == 1) //user nou
			{
				printf("\n\tNumele introdus a fost deja folosit.\n\tIncercati din nou.\n\n");
				printf("\tNumele: ");
				gets(numeJucator);
			}
			else //user existent
			{
				printf("\n\tNumele a fost gasit.\n\n");
				validat = 1;
			}
		}
		else //numele nu a fost gasit in structura
		{
			if (*statusUser == 1) //user nou
			{
				printf("\n\tNumele a fost memorat.\n\n");
				validat = 1;
			}
			else //user existent
			{
				if (incercari == 2)
				{
					verificareTipJoc(&incercari, statusUser, rank,numeJucator);
					if (*statusUser == 1)
					{
						system("cls");
						printf("\n\tIntroduceti-va numele\n\n");
						printf("\tNumele: ");
						gets(numeJucator);
					}
					else
					{
						if (numeJucator[0] == 0)
						{
							system("cls");
							printf("\n\tIntroduceti-va numele\n\n");
							printf("\tNumele: ");
							gets(numeJucator);
						}
					}
				}
				else {
					printf("\n\tNumele introdus nu a fost gasit.\n\tIncercati din nou.\n\n");
					printf("\tNumele: ");
					gets(numeJucator);
					incercari++;
				}
			}
		}
	}
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

void adaugareJucatorNou(struct lista* rank, char numeJucator[], int catePuncte, long timp,int statusUser)
{
	if (statusUser == 1) {
		actualizarePozitie(numeJucator, timp, catePuncte, rank);
	}
	else
	{
		struct ranking* elem = rank->primul;
		while (elem != NULL)
		{
			if (strcmp(elem->nume, numeJucator) == 0)
			{
				if (elem->punctaj <= catePuncte) {
					elem->punctaj = catePuncte;
					elem->timp = timp;
					if (verificareOrdine(rank) == 0) {
						stergereJucator(numeJucator, rank);
						actualizarePozitie(numeJucator, timp, catePuncte, rank);
					}
					break;
				}
			}
			elem = elem->urmator;
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

int verificareOrdine(struct lista* rank)
{
	struct ranking* aux = rank->primul;
	while (aux->urmator != NULL)
	{
		if (aux->punctaj < aux->urmator->punctaj)
			return 0;
		else
		{
			if (aux->punctaj == aux->urmator->punctaj && aux->timp > aux->urmator->timp)
				return 0;
		}
		aux = aux->urmator;
	}
	return 1;
}

void stergereJucator(char numeJucator[], struct lista* rank)
{
	if (strcmp(rank->primul->nume, numeJucator) == 0)
	{
		struct ranking* elem = rank->primul;
		rank->primul = rank->primul->urmator;
		free(elem);
	}
	else {
		struct ranking* prev = rank->primul;
		struct ranking* cur = rank->primul->urmator;
		while (strcmp(cur->nume, numeJucator) != 0)
		{
			cur = cur->urmator;
			prev = prev->urmator;
		}
		prev->urmator = cur->urmator;
		free(cur);
	}
}

void actualizarePozitie(char numeJucator[], long timp, int catePuncte, struct lista* rank)
{
	struct ranking* elem = creareJucator(numeJucator, catePuncte, timp);
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
				while (c != NULL)
				{
					if (c->punctaj < catePuncte)
					{
						elem->urmator = c;
						p->urmator = elem;
						ok = 1;
						break;
					}
					else
					{
						if (c->punctaj == catePuncte)
						{
							while (c->urmator!=NULL && c->timp < timp)
							{
								if ((p->timp < timp && timp<c->timp) || c->punctaj<catePuncte)
									break;
								p = p->urmator;
								c = c->urmator;
							}
							elem->urmator = c;
							p->urmator = elem;
							ok = 1;
							break;
						}
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
