//adaugare intrebari
void adaugareScurtaInLista(struct lista* , char [], char []);
void adaugareRaspunsScurt(char*,struct lista*);
void adaugareGrilaInLista(struct lista* , char [], char []);
void citireVar(char*, char*, char*, char*, char*,struct lista*);
void adaugareRaspunsMultiplu(char*,struct lista*);


//admin
void confirmareStergere(int, int*, int*,int*);
void afisareIndecsiSterse(int, int*,int);


//parola admin
void extragereParolaAdmin(char [], char* );
void schimbareParolaAdmin(char []);
void confirmareSchimbareParola(int*);
int verificareParolaAdministrator(char []);
void plasareParolaNouaInFisier(char [], char* );


//meniu admin
void optiuniAdministrator(char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*,int*,char []);
void tipIntrebare(char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*,int*,char []);


//meniu user
void verificareStatusUser(int*);
void repetareJoc(int* );
void incepeQuiz(int, int, char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*, int,int*,char []);
void optiuniUser(char*, char*, char*, char*, int, int, struct lista*, struct lista*, struct lista*, int*, int,int*,char []);


//clasament
void adaugareInLista(struct lista* , char* );
void preluareNumeDinFisier(struct lista* , char* );
void verificareTipJoc(int*, int*, struct lista*,char []);
void preluareNumeUser(char [], int* , struct lista* );
int cautare(struct lista*, char*);
struct ranking* creareJucator(char[], int, long);
void adaugareJucatorNou(struct lista*, char[], int, long,int );
int verificareOrdine(struct lista* );
void stergereJucator(char [], struct lista* );
void actualizarePozitie(char [], long , int , struct lista* );
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
void optiuniStatusUser();


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


//nume fisiere
char* initializare();
void numeFisiere(char* , char* , char* , char *);


//main
void paginaPrincipala(char* , char* , char* , char *,struct lista* ,struct lista* , struct lista* ,int*,int*,char []);
void meniuReguli(char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*,int*,char []);
int validareInput(char []);
void progressBar();