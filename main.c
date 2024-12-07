// Inspired by Bjarne Stroustrup object inheritance vtable implementation in 1989
// https://www.usenix.org/legacy/publications/compsystems/1989/fall_stroustrup.pdf
#include <stdio.h>

//typedef int (*void_func_ptr)();
//typedef void_func_ptr VTABLE[3];
typedef int (*VTABLE[3])();

typedef struct 
{
    VTABLE const* vtable;
    int x;
    int y;
} forme;
int get_x(forme* f) { return f->x; }
int get_y(forme* f) { return f->y; }
int print_forme(forme* f) { printf("x %i y %i\n", f->x, f->y); return 0; }

typedef struct 
{
    forme forme;
    int rayon;
} cercle;
int print_cercle(forme* f) 
{
    printf("cercle de rayon %i\n", ((cercle*)f)->rayon);
    print_forme(f);
    return 0;
}
const VTABLE cercle_vtable = {get_x, get_y, print_cercle};

typedef struct 
{
    forme forme;
    int hauteur;
    int longueur;
} carre;
int print_carre(forme* f) 
{
    printf("carre de hauteur %i longueur %i\n", ((carre*)f)->hauteur, ((carre*)f)->longueur); 
    print_forme(f);
    return 0;
}
const VTABLE carre_vtable = {get_x, get_y, print_carre};

int main() 
{
    carre  ca = (carre)  { .forme = (forme){ .vtable = &carre_vtable , .x=0, .y=1 }, .hauteur = 10,.longueur = 20}; 
    cercle ce = (cercle) { .forme = (forme){ .vtable = &cercle_vtable, .x=2, .y=3 }, .rayon = 5};

    forme* formes[2] = { (void*)(&ca), (void*)(&ce) };

    for (int i = 0; i < 2; i++) 
    {
        forme* f = formes[i];

        ((*(f->vtable))[2])(f);

        int x = ((*(f->vtable))[0])(f);
        int y = ((*(f->vtable))[1])(f);
        printf("get_x() = %i, get_y() = %i\n\n", x, y);
    } 

    return 0;
}

/*
carre de hauteur 10 longueur 20
x 0 y 1
get_x() = 0, get_y() = 1       

cercle de rayon 5
x 2 y 3
get_x() = 2, get_y() = 3
*/