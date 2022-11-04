#include <cctype>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "basics.hpp"
#include "heads.hpp"

// FUNCIONES BASICAS

Table createTableNode(char *name)
{
	Table n = new table;
	n->name = name;
	n->pointer = NULL;
	n->der = NULL;
	n->izq = NULL;
	return n;
}

Dato createDataNode(char *NombreCol, char *tipoCol, char *calif)
{
	Dato n = new dato;
	n->attName = NombreCol;
	n->tipo = tipoCol;
	n->calif = calif;
	n->valChar = new char[100];
	n->valInt = NULL;
	
	n->sigCol = NULL;
	n->antCol = NULL;
	n->sigTup = NULL;
	n->antTup = NULL;
	return n;
}

void insertarInicio(Table &db, Table newTable)
{
	if (!db)
	{
		db = newTable;
		db->der = NULL;
		db->izq = NULL;
	}
	else
	{
		db->izq = newTable;
		newTable->der = db;
		db = newTable;
	}
}

void insertarInicioDato(Dato &pointer, Dato newData)
{
	if (!pointer->sigTup)
	{
		pointer->sigTup = newData;
		newData->antTup = pointer;
		newData->sigTup = NULL;
		newData->sigCol = NULL;
		newData->antCol = NULL;
	}
	else
	{
		newData->sigTup = pointer->sigTup;
		pointer->sigTup->antTup = newData;
		pointer->sigTup = newData;
		newData->antTup = pointer;
	}
}
void insertarInicioCol(Dato &col, Dato newCol)
{
	if (!col)
	{
		col = newCol;
		col->sigTup = NULL;
		col->antTup = NULL;
		col->sigCol = NULL;
		col->antCol = NULL;
	}
	else
	{
		newCol->sigCol = col;
		col->antCol = newCol;
		col = newCol;
	}
}

void borrar(Table &arbol)
{
	if(arbol==NULL) return;
		else
		{
			Table p = arbol;
			arbol = unirABB(arbol->izq, arbol->der);
			delete p;
		}
}

Table unirABB(Table izq, Table der)
{
	if(izq==NULL) return der;
	if(der==NULL) return izq;
	Table centro = unirABB(izq->der, der->izq);
	izq->der = centro;
	der->izq = izq;
	return der;
}


