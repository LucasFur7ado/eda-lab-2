#include <cctype>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "ownFuncs.hpp"
#include "heads.hpp"

using namespace std;

// FUNCIONES PROPIAS

void fillAtr(char *atr, int i, int numAtr, char *nuevo)
{
	if (i == numAtr)
		for (int c = 0; c < strlen(nuevo); c++)
			atr[c] = nuevo[c];
}

bool thereIsPk(Dato pointer)
{
	Dato aux = pointer;
	while (aux)
	{
		if (!strcmp(aux->calif, "primary key"))
			return true;
		aux = aux->sigCol;
	}
	return false;
}

void orderTable(Dato &pointer, char column[50][100], int cont)
{
	Dato aux = pointer, aux2, aux3;
	bool flag = true;
	int val1, val2, i;
	aux = pointer;
	if (!cont)
	{
		while (aux && strcmp(aux->calif, "primary key") != 0)
			aux = aux->sigCol;
	}
	else
	{
		while (strcmp(aux->attName, column[0]) != 0)
			aux = aux->sigCol;
	}
	aux = aux->sigTup;
	aux2 = aux->antTup;
	while (flag)
	{
		flag = false;
		aux = aux2->sigTup;
		if (aux->sigTup == NULL)
			return;
		while (aux && aux->sigTup)
		{
			if (aux->valInt)
				val1 = *aux->valInt;
			else
				val1 = 0;
			if (aux->sigTup->valInt)
				val2 = *aux->sigTup->valInt;
			else
				val2 = 0;
			if (((!strcmp(aux->tipo, "integer") && val1 >= val2) ||
				 (!strcmp(aux->tipo, "character") && aux->valChar[0] >= aux->sigTup->valChar[0])))
			{
				flag = true;
				while (aux->sigTup && ((!strcmp(aux->tipo, "integer") && val1 >= val2) ||
									   (!strcmp(aux->tipo, "character") && aux->valChar[0] >= aux->sigTup->valChar[0])))
				{
					swap(aux);
					aux3 = aux;
					if (aux->sigCol || aux->antCol)
					{
						while (aux->sigCol)
							aux = aux->sigCol;
						while (aux->antCol)
						{
							if (aux != aux3)
							{
								swap(aux);
								aux = aux->antCol;
							}
							else
								aux = aux->antCol;
						}
						if (aux != aux3)
							swap(aux);
						aux = aux3;
					}
					if (aux && aux->sigTup && !strcmp(aux->tipo, "integer"))
					{
						val1 = *aux->valInt;
						val2 = *aux->sigTup->valInt;
					}
				}
			}
			else
				aux = aux->sigTup;
		}
	}
}

void swap(Dato &aux)
{
	aux->antTup->sigTup = aux->sigTup;
	aux->sigTup->antTup = aux->antTup;
	if (aux->sigTup->sigTup)
	{
		aux->sigTup = aux->sigTup->sigTup;
		aux->sigTup->antTup = aux;
	}
	else
		aux->sigTup = NULL;
	aux->antTup->sigTup->sigTup = aux;
	aux->antTup = aux->antTup->sigTup;
}

char validateEntry(Dato pointer, char args[50][100], char vals[50][100], int cont)
{
	Dato aux = pointer, aux2;
	bool flag0 = true, flag1;
	int pos;
	while (aux)
	{
		flag1 = false;
		if (!strcmp(aux->calif, "primary key"))
		{
			flag0 = false;
			for (int i = 0; i < cont; i++)
				if (!strcmp(args[i], aux->attName))
				{
					pos = cont;
					flag0 = true;
				}
			aux2 = aux->sigTup;
			while (aux2 && flag0)
			{
				if (!strcmp(aux2->tipo, "integer"))
				{
					int *valor_int;
					int valor;
					valor = strtol(vals[pos - 1], NULL, 10);
					valor_int = &valor;
					if (*aux2->valInt == *valor_int)
					{
						cout << endl
							 << '\t' << "Ya existe una tupla con esa clave primaria." << endl
							 << endl;
						return false;
					}
				}
				else
				{
					if (!strcmp(aux2->valChar, vals[pos - 1]))
					{
						cout << endl
							 << '\t' << "Ya existe una tupla con esa clave primaria." << endl
							 << endl;
						return false;
					}
				}
				aux2 = aux2->sigTup;
			}
		}

		if (!strcmp(aux->calif, "not empty"))
		{
			for (int i = 0; i < cont; i++)
			{
				if (!strcmp(args[i], aux->attName))
					flag1 = true;
			}
			if (!flag1)
			{
				cout << endl
					 << '\t' << "Hay columnas que no admiten valores nulos." << endl;
				cout << '\t' << ">> printMetaData( nombreTabla ) para ver detalles." << endl
					 << endl;
				return false;
			}
		}
		aux = aux->sigCol;
	}
	if (!flag0)
	{
		cout << endl
			 << '\t' << "Debes ingresar una clave primaria." << endl
			 << endl;
		return false;
	}
	return true;
}

bool alreadyColumn(Dato pointer, char *colName)
{
	Dato aux = pointer;
	if (aux)
	{
		while (aux)
		{
			if (!strcmp(aux->attName, colName))
				return true;
			aux = aux->sigCol;
		}
	}
	return false;
}

void help()
{
	cout << endl
		 << '\t' << "Comandos disponibles: " << endl
		 << endl;
	cout << '\t' << "showTables()" << endl;
	cout << '\t' << "dropTable(nombreTabla)" << endl;
	cout << '\t' << "createTable(nombreTabla)" << endl;
	cout << '\t' << "printMetadata(nombreTabla)" << endl;
	cout << '\t' << "dropCol(nombreTabla,columna)" << endl;
	cout << '\t' << "printTable(nombreDeLaTabla,columna)" << endl;
	cout << '\t' << "deleteTupla(nombreTabla,columna=valor)" << endl;
	cout << '\t' << "insertInto(nombreTabla,columna1:columna2,valor1:valor2)" << endl;
	cout << '\t' << "addCol(nombreTabla,nombreColumna,tipoColumna,calificador)" << endl
		 << endl;
}

void deleteAllTuplas(Dato &pointer)
{
	Dato aux = pointer->sigTup;
	while (aux->sigTup)
	{
		aux = aux->sigTup;
		deleteWholeTupla(aux->antTup);
	}
	deleteWholeTupla(aux);
}
void CopyAllTuplas(Dato &pointer, char *nombreTabla2, Table db)
{
	Dato aux = pointer->sigTup;
	while (aux->sigTup)
	{
		CopyWholeTupla(aux, nombreTabla2, db);
		aux = aux->sigTup;
	}
	CopyWholeTupla(aux, nombreTabla2, db);

	return;
}

void deleteWholeTupla(Dato &pointer)
{
	// RECIBIMOS PUNTERO DIRECTO EN EL NODO A ELIMINAR (Y ELIMINAMOS TODA LA TUPLA)
	Dato aux = pointer;
	while (aux->sigCol)
		aux = aux->sigCol;
	if (!aux->sigTup)
	{
		while (aux->antCol)
		{
			aux->antTup->sigTup = NULL;
			aux = aux->antCol;
			delete aux->sigCol;
		}
		aux->antTup->sigTup = NULL;
		delete aux;
	}
	else
	{
		while (aux->antCol)
		{
			aux->antTup->sigTup = aux->sigTup;
			aux->sigTup->antTup = aux->antTup;
			aux = aux->antCol;
			delete aux->sigCol;
		}
		aux->antTup->sigTup = aux->sigTup;
		aux->sigTup->antTup = aux->antTup;
		delete aux;
	}
}

void searchCondition(Dato &pointer_aux, char *valor_char, int *valor_int, char *operand)
{
	if (!pointer_aux->sigTup)
	{
		cout << "La columna esta vacia" << endl;
		return;
	}

	Dato aux = pointer_aux->sigTup, aux2;
	while (aux->sigTup)
	{
		if (((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) != 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt != *valor_int)) && !strcmp(operand, "<>")) ||

			((!strcmp(aux->tipo, "character") && !strcmp(aux->valChar, valor_char) || !strcmp(aux->tipo, "integer") && (*aux->valInt == *valor_int)) && !strcmp(operand, "=")) ||

			((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) < 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt < *valor_int)) && !strcmp(operand, "<")) ||

			((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) > 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt > *valor_int)) && !strcmp(operand, ">")))
		{
			aux = aux->sigTup;
			deleteWholeTupla(aux->antTup);
		}
		else
			aux = aux->sigTup;
	}
	if (((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) != 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt != *valor_int)) && !strcmp(operand, "<>")) ||

		((!strcmp(aux->tipo, "character") && !strcmp(aux->valChar, valor_char) || !strcmp(aux->tipo, "integer") && (*aux->valInt == *valor_int)) && !strcmp(operand, "=")) ||

		((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) < 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt < *valor_int)) && !strcmp(operand, "<")) ||

		((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) > 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt > *valor_int)) && !strcmp(operand, ">")))
		deleteWholeTupla(aux);
}

void searchCondition_selectWhere(Dato &pointer_aux, char *valor_char, int *valor_int, char *operand, char *nombreTabla2, Table &db)
{
	if (!pointer_aux->sigTup)
	{
		cout << "La columna esta vacia" << endl;
		return;
	}

	Dato aux = pointer_aux->sigTup, aux2;
	while (aux->sigTup)
	{
		if (((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) != 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt != *valor_int)) && !strcmp(operand, "<>")) ||

			((!strcmp(aux->tipo, "character") && !strcmp(aux->valChar, valor_char) || !strcmp(aux->tipo, "integer") && (*aux->valInt == *valor_int)) && !strcmp(operand, "=")) ||

			((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) < 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt < *valor_int)) && !strcmp(operand, "<")) ||

			((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) > 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt > *valor_int)) && !strcmp(operand, ">")))
		{
			//			aux = aux->sigTup;
			//			deleteWholeTupla(aux->antTup);
			CopyWholeTupla(aux, nombreTabla2, db);
			aux = aux->sigTup;
		}
		else
			aux = aux->sigTup;
	}
	if (((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) != 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt != *valor_int)) && !strcmp(operand, "<>")) ||

		((!strcmp(aux->tipo, "character") && !strcmp(aux->valChar, valor_char) || !strcmp(aux->tipo, "integer") && (*aux->valInt == *valor_int)) && !strcmp(operand, "=")) ||

		((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) < 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt < *valor_int)) && !strcmp(operand, "<")) ||

		((!strcmp(aux->tipo, "character") && strcmp(aux->valChar, valor_char) > 0 || !strcmp(aux->tipo, "integer") && (*aux->valInt > *valor_int)) && !strcmp(operand, ">")))
		CopyWholeTupla(aux, nombreTabla2, db);
	aux = aux->sigTup;
}

// void int_a_char(int n, char cad[]){
//	int nroDig = 0;
//	int aux = n;
//	while(aux>0){
//		aux = aux/10;
//		nroDig++;
//	}
//	cad[nroDig] = '\0';
//	aux=n;
//	int pos = nroDig-1;
//	while(pos>=0){
//		dig = aux%10;
//		aux = aux/10;
//	}
// }

void CopyWholeTupla(Dato &pointer, char *nombreTabla2, Table &db)
{

	Table aux_T = db, aux2 = db;
	int cont = 0;
	char *valores;
	char *columnas;
	char *valor_entero;
	Dato aux = pointer;
	valores = new char[100];
	valor_entero = new char[100];
	columnas = new char[100];

	//	aux=aux->antTup;
	//	cout<<"caf"<<aux->calif;
	while (aux->sigCol)
		aux = aux->sigCol;

	while (aux->antCol)
	{

		if (cont > 0)
		{
			valores = strcat(valores, ":");
			columnas = strcat(columnas, ":");
		}

		if (!strcmp(aux->tipo, "integer"))
		{
			sprintf(valor_entero, "%d", *aux->valInt);
			valores = strcat(valores, valor_entero);
		}
		else
			valores = strcat(valores, aux->valChar);

		columnas = strcat(columnas, aux->attName);

		/*aux->calif = "any";*/

		checkNameP(aux2, aux_T, nombreTabla2);

		if (!alreadyColumn(aux_T->pointer, aux->attName))
		{
			addCol(nombreTabla2, aux->attName, aux->tipo, aux->calif, db);
		}
		aux = aux->antCol;

		cont++;
	}

	valores = strcat(valores, ":");
	columnas = strcat(columnas, ":");

	if (!strcmp(aux->tipo, "integer"))
	{
		sprintf(valor_entero, "%d", *aux->valInt);
		valores = strcat(valores, valor_entero);
	}
	else
		valores = strcat(valores, aux->valChar);

	columnas = strcat(columnas, aux->attName);

	checkNameP(aux2, aux_T, nombreTabla2);

	if (!alreadyColumn(aux_T->pointer, aux->attName))
	{
		addCol(nombreTabla2, aux->attName, aux->tipo, aux->calif, db);
	}
	aux = aux->antCol;

	insertInto(nombreTabla2, columnas, valores, db);

	return;
}

void CopyWholeTupla_join(Dato aux, Dato aux_2, char *nombreTabla3, Table &db)
{

	Table aux_T = db, aux2 = db;
	int cont = 0;
	char *valores;
	char *columnas;
	char *eliminar;
	char *valor_entero;
	char *valor_entero2;
	valores = new char[100];
	valor_entero = new char[100];
	valor_entero2 = new char[100];
	eliminar = new char[100];
	columnas = new char[100];
	strcpy(eliminar, "eliminar");

	while (aux->sigCol)
		aux = aux->sigCol;

	while (aux_2->sigCol)
		aux_2 = aux_2->sigCol;

	while (aux->antCol || aux_2->antCol)
	{

		if (cont > 0)
		{
			valores = strcat(valores, ":");
			columnas = strcat(columnas, ":");
		}
		if (aux)
		{
			if (!strcmp(aux->tipo, "integer"))
			{
				sprintf(valor_entero, "%d", *aux->valInt);
				strcat(valores, valor_entero);
			}
			else
				strcat(valores, aux->valChar);

			strcat(columnas, aux->attName);
		}
		// PUEDE OCURRIR ERROR AQUI
		strcat(valores, ":");
		strcat(columnas, ":");

		if (aux_2)
		{
			if (!strcmp(aux_2->tipo, "integer"))
			{
				sprintf(valor_entero2, "%d", *aux_2->valInt);
				strcat(valores, valor_entero2);
			}
			else
				strcat(valores, aux_2->valChar);

			strcat(columnas, aux_2->attName);
		}

		checkNameP(aux2, aux_T, nombreTabla3);

		if (aux && !alreadyColumn(aux_T->pointer, aux->attName))
		{
			addCol(nombreTabla3, aux->attName, aux->tipo, aux->calif, db);
		}
		if (aux_2 && !alreadyColumn(aux_T->pointer, aux_2->attName))
		{
			if (strcmp(aux_2->calif, "primary key"))
				addCol(nombreTabla3, aux_2->attName, aux_2->tipo, aux_2->calif, db);
		}

		if (aux->antCol)
			aux = aux->antCol;
		if (aux_2->antCol)
			aux_2 = aux_2->antCol;

		cont++;
	}

	strcat(valores, ":");
	strcat(columnas, ":");

	if (aux)
	{
		if (!strcmp(aux->tipo, "integer"))
		{
			sprintf(valor_entero, "%d", *aux->valInt);
			strcat(valores, valor_entero);
		}
		else
			strcat(valores, aux->valChar);

		strcat(columnas, aux->attName);
	}

	// PUEDE OCURRIR ERROR AQUI
	strcat(valores, ":");
	strcat(columnas, ":");

	if (aux_2)
	{
		if (!strcmp(aux_2->tipo, "integer"))
		{
			sprintf(valor_entero2, "%d", *aux_2->valInt);
			strcat(valores, valor_entero2);
		}
		else
			strcat(valores, aux_2->valChar);

		strcat(columnas, aux_2->attName);
	}

	checkNameP(aux2, aux_T, nombreTabla3);

	if (aux && !alreadyColumn(aux_T->pointer, aux->attName))
	{
		addCol(nombreTabla3, aux->attName, aux->tipo, aux->calif, db);
	}
	if (aux_2 && !alreadyColumn(aux_T->pointer, aux_2->attName))
	{
		if (strcmp(aux_2->calif, "primary key"))
			addCol(nombreTabla3, aux_2->attName, aux_2->tipo, aux_2->calif, db);
	}

	aux = aux->antCol;
	aux_2 = aux_2->antCol;

	cout << columnas << endl;
	cout << valores << endl;

	insertInto(nombreTabla3, columnas, valores, db);

	return;
}

TipoRet insertIntoNMW(char *nombreTabla, char *columnaTupla, char *valoresTupla, Table &db)
{
	Table aux = db, aux2 = db;
	Dato puntero;
	char delimitador[] = ":", _integer[100] = "integer", _character[100] = "character", empty[100] = "empty";
	char matrizAtts[50][100] = {0}, matrizVals[50][100] = {0};
	char *nuev = strtok(columnaTupla, delimitador);
	int i = 0, contAtts = 0, contVals = 0;

	if (nuev)
	{
		while (nuev)
		{
			strcpy(matrizAtts[i], nuev);
			nuev = strtok(NULL, delimitador);
			i++;
			contAtts++;
		}
	}
	nuev = strtok(valoresTupla, delimitador);
	i = 0;
	if (nuev)
	{
		while (nuev)
		{
			strcpy(matrizVals[i], nuev);
			nuev = strtok(NULL, delimitador);
			i++;
			contVals++;
		}
	}
	checkNameP(aux2, aux, nombreTabla);
	if (!aux)
	{
		cout << endl
			 << '\t' << "Parece que la tabla no existe." << endl
			 << endl;
		return ERROR;
	}
	int c = 0;
	Dato pointer_aux, empty_aux = aux->pointer;
	char *empty_tipo = new char[100];
	strcpy(empty_tipo, _character);
	for (c = 0; c < contAtts; c++)
	{
		pointer_aux = aux->pointer;
		while (pointer_aux && strcmp(pointer_aux->attName, matrizAtts[c]) != 0)
			pointer_aux = pointer_aux->sigCol;
		if (!pointer_aux)
		{
			cout << endl
				 << '\t' << "Parece que la columna no existe." << endl
				 << endl;
			return ERROR;
		}
	}
	while (empty_aux)
	{
		insertarInicioDato(empty_aux, createDataNode(empty_aux->attName, empty_aux->tipo, empty_aux->calif));
		int integerValue2 = 0;
		empty_aux->sigTup->valInt = &integerValue2;
		strcpy(empty_aux->sigTup->valChar, empty);
		empty_aux = empty_aux->sigCol;
	}
	for (c = 0; c < contAtts; c++)
	{
		pointer_aux = aux->pointer;
		while (pointer_aux && strcmp(pointer_aux->attName, matrizAtts[c]) != 0)
			pointer_aux = pointer_aux->sigCol;
		if (strcmp(pointer_aux->tipo, _integer) != 0)
		{
			pointer_aux->sigTup->valChar = new char[100];
			strcpy(pointer_aux->sigTup->valChar, matrizVals[c]);
		}
		else
		{
			pointer_aux->sigTup->valInt = new int;
			int valor = strtol(matrizVals[c], NULL, 10);
			*pointer_aux->sigTup->valInt = valor;
		}
	}
	pointer_aux = aux->pointer;
	while (pointer_aux->sigCol)
	{
		pointer_aux->sigTup->sigCol = pointer_aux->sigCol->sigTup;
		pointer_aux->sigCol->sigTup->antCol = pointer_aux->sigTup;
		pointer_aux = pointer_aux->sigCol;
	}

	return OK;
}

TipoRet dropColNMW(char *atr1, char *atr2, Table db)
{
	Table aux = db, aux2 = db;
	if (checkName(aux, atr1))
	{
		cout << "Parece que la tabla no existe." << endl;
		return ERROR;
	}
	else
		checkNameP(aux2, aux, atr1);
	if (!aux)
	{
		cout << endl
			 << '\t' << "Parece que la tabla no existe." << endl
			 << endl;
		return ERROR;
	}
	Dato pointer_aux;
	pointer_aux = aux->pointer;
	while (pointer_aux && strcmp(pointer_aux->attName, atr2) != 0)
		pointer_aux = pointer_aux->sigCol;
	if (!pointer_aux)
	{
		cout << endl
			 << '\t' << "Parece que la columna no existe." << endl
			 << endl;
		return ERROR;
	}
	else if (!pointer_aux->sigCol && !pointer_aux->antCol)
	{
		while (pointer_aux)
		{
			Dato aux = pointer_aux;
			pointer_aux = pointer_aux->sigTup;
			delete aux;
		}
		aux->pointer = NULL;
		return OK;
	}
	else if (!pointer_aux->antCol && pointer_aux->sigCol)
	{
		Dato auxiliar = pointer_aux;
		pointer_aux = pointer_aux->sigCol;
		Dato aux2;
		aux->pointer = pointer_aux;
		while (auxiliar)
		{
			aux2 = auxiliar;
			auxiliar = auxiliar->sigTup;
			delete aux2;
		}
		aux2 = NULL;
		while (pointer_aux)
		{
			pointer_aux->antCol = NULL;
			pointer_aux = pointer_aux->sigTup;
		}
		return OK;
	}
	else if (pointer_aux->antCol && !pointer_aux->sigCol)
	{
		Dato auxiliar = pointer_aux;
		pointer_aux = pointer_aux->antCol;
		Dato aux2;
		while (auxiliar)
		{
			aux2 = auxiliar;
			auxiliar = auxiliar->sigTup;
			delete aux2;
		}
		aux2 = NULL;
		while (pointer_aux)
		{
			pointer_aux->sigCol = NULL;
			pointer_aux = pointer_aux->sigTup;
		}
		return OK;
	}
	else if (pointer_aux->antCol && pointer_aux->sigCol)
	{
		Dato auxiliar_ant = pointer_aux->antCol;
		Dato auxiliar_sig = pointer_aux->sigCol;

		while (auxiliar_ant)
		{
			auxiliar_ant->sigCol = auxiliar_sig;
			auxiliar_sig->antCol = auxiliar_ant;

			auxiliar_ant = auxiliar_ant->sigTup;
			auxiliar_sig = auxiliar_sig->sigTup;
		}
		Dato aux22;
		while (pointer_aux)
		{
			aux22 = pointer_aux;
			pointer_aux = pointer_aux->sigTup;
			delete aux22;
		}
		return OK;
	}
	return OK;
}

void checkTables(Table arbol)
{
	if (!arbol)
		return;
	checkTables(arbol->izq);
	cout << '\t' << arbol->name << " ";
	checkTables(arbol->der);
}

void credits()
{
	cout << endl
		 << endl;
	cout << '\t' << ":::::.'::::::::::::::::" << endl;
	cout << '\t' << ":::::   '::::::::::::::" << endl;
	cout << '\t' << ":::'   .:::::::::::::::" << endl;
	cout << '\t' << "::'   :::::::::::::::::" << endl;
	cout << '\t' << ":'   :::::::::.  ::::::" << endl;
	cout << '\t' << ":    ::::''''.:.    :::" << endl;
	cout << '\t' << ":    :::      ':::    :" << endl;
	cout << '\t' << "::   '::      .:::    :" << endl;
	cout << '\t' << "::          .::'     ::" << endl;
	cout << '\t' << "::                :::::" << endl;
	cout << '\t' << "::'            ::::::::" << endl;
	cout << '\t' << ":::           :::::::::" << endl;
	cout << '\t' << ":::          ::::::::::" << endl;
	cout << '\t' << ":::          ::::::::::" << endl;
	cout << '\t' << ":::          ::::::::::" << endl;
	cout << '\t' << "::'           :::::::::" << endl;
	cout << '\t' << "::            :::::::::" << endl;
	cout << '\t' << ":.            :::::::::" << endl
		 << endl;
	cout << '\t' << "developed by" << endl;
	cout << '\t' << "Lucas Furtado" << endl;
	cout << '\t' << "& Santiago Perron" << endl
		 << endl;
}
