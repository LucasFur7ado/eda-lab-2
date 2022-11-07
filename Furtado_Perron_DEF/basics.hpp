#ifndef BASICS_H
#define BASICS_H

#include "heads.hpp"

void insertarInicio(Table &, Table); 
void insertarInicioCol(Dato &, Dato);  
void insertarInicioDato(Dato &, Dato);  

Table createTableNode(char *); 

Dato createDataNode(char *, char *, char *);

void borrar(Table &, char *);

Table unirABB(Table , Table);

#endif
