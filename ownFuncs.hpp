#ifndef OWNFUNCS_H
#define OWNFUNCS_H

#include "heads.hpp"

void help();
void credits();
void swap(Dato &);
void deleteAllTuplas(Dato &);
void deleteWholeTupla(Dato &);
void equal(Dato &, int *, char *);
void fillAtr(char *, int, int, char *);
void orderTable(Dato &, char [50][100], int);
void searchCondition(Dato &, char *, int *, char *);
void searchCondition_selectWhere(Dato &, char *, int *, char *, char*, Table &);
void CopyWholeTupla(Dato &, char*, Table &);	
void CopyAllTuplas(Dato &, char*, Table);
void CopyWholeTupla_join(Dato , Dato , char *, Table &);
TipoRet dropColNMW(char *, char *, Table);
void checkTables(Table );
bool thereIsPk(Dato);
bool alreadyColumn(Dato, char *);

char validateEntry(Dato, char [50][100], char [50][100], int);

#endif
