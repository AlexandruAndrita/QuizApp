//adaugare intrebari
void adaugareRaspunsScurt(char*);
void citireVar(char*, char*, char*, char*, char*);
void adaugareRaspunsMultiplu(char*);


//admin
void confirmareStergere(int, int*, int*);
void afisareIndecsiSterse(int, int*);
void schimbareParolaAdmin(char*);
int verificareParolaAdministrator(char*);


//meniu admin
void optiuniAdministrator(char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*);
void tipIntrebare(char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*);


//meniu user
void incepeQuiz(int, int, char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*);
void optiuniUser(char*, char*, char*, char*, int, int, struct lista*, struct lista*, struct lista*, int*);


//clasament
void adaugareInLista(struct lista* , char* );
void preluareNumeDinFisier(struct lista* , char* );
int cautare(struct lista*, char*);
struct ranking* creareJucator(char[], int, long);
void adaugareJucatorNou(struct lista*, char[], int, long);
void mutareDateInFisier(struct lista*, char*);


//afisare clasament
int cateCifre(long );
void lungimeMaxima(struct lista* , int* );
void afisareCapTabel(int , int ,int* );
void afiseazaSpatiiRamase(int, int);
void formatareAfisare(int , char [], int , long , int );
void delimitatorLinie(int );
void afisareClasament(struct lista*);


//optiuni
void optiuniQuiz();
void opuser();
void opadmin();
void tipIntrebareQ();
void opprinicipala();
void reguli();
void optiuniReguli();


//quiz
void transformaDinLitereMari(char []);
int verificaAparitii(int [], int);
void generareNumere(int [], int);
int quizScurt(int, struct lista*, clock_t* , clock_t* , clock_t* );
void afisareVariante(char [], char []);
void preluareRaspuns(char [], char[]);
int quizGrila(int, struct lista*, clock_t*, clock_t*, clock_t*);


//stergere intrebari
void afisareIntrebari(struct lista*, struct lista*, int, int*);
void citireIndecsi(int*, int, int*);
int verifScurteNesterse(struct lista*);
void stergeScurte(struct lista*);
int verifGrilaNesterse(struct lista*);
void stergeGrile(struct lista*);
void stergereIntrebari(struct lista*, struct lista*, int*, int, int);
void completareInFisier(char*, char*, struct lista*, struct lista*, int);


//stocare intrebari
void stocareIntrebari(int* , int* , char* , char* , char* , struct lista* , struct lista* );
void adaugareIntrebariScurte(char* ,int * ,struct lista* );
void adaugareIntrebariGrila(char* ,int * ,struct lista* );


//main
void paginaPrincipala(char* , char* , char* , char *,struct lista* ,struct lista* , struct lista* ,int*);
void meniuReguli(char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*);
int validareInput(char []);
char* initializare();
void numeFisiere(char* , char* , char* , char *);
