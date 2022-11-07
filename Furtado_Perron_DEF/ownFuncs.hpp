#ifndef OWNFUNCS_H
#define OWNFUNCS_H

#include "heads.hpp"

void help();
void credits();
void swap(Dato &);
void checkTables(Table );
void deleteAllTuplas(Dato &);
void deleteWholeTupla(Dato &);
void equal(Dato &, int *, char *);
void fillAtr(char *, int, int, char *);
void CopyAllTuplas(Dato &, char*, Table);
void CopyWholeTupla(Dato &, char*, Table &);	
void orderTable(Dato &, char [50][100], int);
void searchCondition(Dato &, char *, int *, char *);
void CopyWholeTupla_join(Dato , Dato , char *, Table &);
void searchCondition_selectWhere(Dato &, char *, int *, char *, char*, Table &);

bool thereIsPk(Dato);
bool alreadyColumn(Dato, char *);

TipoRet dropColNMW(char *, char *, Table);
TipoRet insertIntoNMW(char *, char *, char *, Table &);

char validateEntry(Dato, char [50][100], char [50][100], int);

#endif
