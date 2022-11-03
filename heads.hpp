#ifndef HEADS_H
#define HEADS_H

struct dato{
	char *attName; 
	char *tipo; 
	char *calif;
	char *valChar; 
	int *valInt; 
	
	dato *sigCol; 
	dato *antCol;
	dato *sigTup;
	dato *antTup;
};
typedef dato *Dato;

struct table{
	char *name;
	Dato pointer; 
	table *der;
	table *izq;
};
typedef table *Table;

enum retorno {OK, ERROR, NO_IMPLEMENTADA};
typedef enum retorno TipoRet;

TipoRet addCol(char *, char *, char *, char *, Table &);
TipoRet insertInto(char *, char *, char *, Table &);
TipoRet printDataTable(char *, char *, Table);  
TipoRet deleteTupla(char *, char *, Table &);
TipoRet dropCol(char *, char *, Table);
TipoRet printMetadata(char *, Table);
TipoRet createTable(char *, Table &);
TipoRet dropTable(char *, Table &);
TipoRet select(char *, char *, char *, Table);
TipoRet selectWhere(char *, char *, char *, Table &);

void insertar(Table &, Table);
void printTables(Table);
void checkTables(Table);

void checkNameP(Table &, Table &, char *);

bool checkName(Table, char *);

#include "basics.hpp"
#include "ownFuncs.hpp"

#endif
