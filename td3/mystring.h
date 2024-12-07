#ifndef _MYSTRING_H
#define _MYSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef const char* mystring;

// Affichage d'une chaine de type mystring
void mystring_fprintf(void* val,FILE* fp);
void mystring_printf(void* val); 

// Test l'egalite de 2 reels
int mystring_equal(void* pv1, void* pv2);

// Génération d'un reel aléatoire
void mystring_random(mystring* p);

// Clone d'un reel
void* mystring_new(mystring val);

void* mystring_delete(void* data);

unsigned int mystring_hashage(void* e);

#endif