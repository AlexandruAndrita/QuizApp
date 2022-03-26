struct questions {
    char intrebare[150];
    char raspuns[150];
    struct questions* next;
};
struct questions* head = NULL;

struct grila {
    char intrebare[150];
    char raspuns[150];
    struct grila* urm;
};
struct grila* cap = NULL;

struct ranking {
    char nume[50];
    char punctaj[50];
    struct ranking* urmator;
};
struct ranking* primul = NULL;