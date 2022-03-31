struct questions {
    char intrebare[150];
    char raspuns[150];
    struct questions* next;
}questions;

struct grila {
    char intrebare[150];
    char raspuns[150];
    struct grila* urm;
}grila;

struct ranking {
    char nume[50];
    char punctaj[50];
    struct ranking* urmator;
}ranking;

struct lista {
    struct questions* head;
    struct grila* cap;
    struct ranking* primul;
}lista;