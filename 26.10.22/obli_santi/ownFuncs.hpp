#ifndef OWNFUNCS_H
#define OWNFUNCS_H

#include "heads.hpp"

void help();
void credits();
void swap(Dato &);
void showTables(Table db);
void deleteAllTuplas(Dato &);
void deleteWholeTupla(Dato &);
void equal(Dato &, int *, char *);
void fillAtr(char *, int, int, char *);
void orderTable(Dato &, char [50][100], int);
void searchCondition(Dato &, char *, int *, char *);

bool thereIsPk(Dato);
bool alreadyColumn(Dato, char *);

char validateEntry(Dato, char [50][100], char [50][100], int);

#endif
