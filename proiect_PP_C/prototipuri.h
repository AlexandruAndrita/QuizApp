//adaugare intrebari
void adaugareRaspunsScurt(char*);
void citireVar(char*, char*, char*, char*, char*);
void adaugareRaspunsMultiplu(char*);

//admin
void confirmareStergere(int, int*, int*);
void afisareIndecsiSterse(int, int*);
void optiuniAdministrator(char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*);
void schimbareParolaAdmin(char*);
int verificareParolaAdministrator(char*);

//clasament
void adaugareInLista(struct lista* , char* );
void preluareNumeDinFisier(struct lista* , char* );
void afisareClasament(struct lista*);
int cautare(struct lista*, char*);
struct ranking* creareJucator(char[], int);
void adaugareJucatorNou(struct lista*, char[], int);
void mutareDateInFisier(struct lista*, char*);

//optiuni
void optiuniQuiz();
void opuser();
void opadmin();
void tipIntrebareQ();
void opprinicipala();
void reguli();

//quiz
void transformaDinLitereMari(char []);
int verificaAparitii(int [], int);
void generareNumere(int [], int);
int quizScurt(int, struct lista*);
void afisareVariante(char [], char []);
void preluareRaspuns(char [], char[]);
int quizGrila(int, struct lista*);

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
void incepeQuiz(int, int, char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*);
void tipIntrebare(char*, char*, char*, char*, struct lista*, struct lista*, struct lista*, int*);
void optiuniUser(char* , char* , char* , char *,int , int ,struct lista* ,struct lista* ,struct lista* ,int *);
void paginaPrincipala(char* , char* , char* , char *,struct lista* ,struct lista* , struct lista* ,int*);
int validareInput(char []);
char* initializare();
void numeFisiere(char* , char* , char* , char *);


