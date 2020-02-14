/* Copyright 2018 Margineanu Nicolae-Vladut */

#ifndef __HASH_FUNCTIONS__H
#define __HASH_FUNCTIONS__H

#define INT_HASH	10
#define	STRING_HASH	117

#include <string.h>

/* Funcția hash de bază pentru cheile de tp întreg. */
unsigned int hashingFunction(int nr){
    return nr;
}

/* Functia hash de baza pentru cheile de tip string */
unsigned int charHashingFunction(std::string str){
    return str.length() ;
}
#endif // __HASH_FUNCTIONS__H