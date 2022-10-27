#include <stdio.h>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "heads.hpp"

using namespace std;

// FUNCIONES

TipoRet dropTable(char *atr1, Table &db)
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
	else
	{
		Dato pointer_aux = aux->pointer;
		Dato aux_dato;
		Dato aux2;
		while (pointer_aux)
		{
			aux2 = pointer_aux;

			while (aux2->sigTup)
			{
				aux_dato = aux2;
				aux2 = aux2->sigTup;
				delete aux_dato;
			}

			pointer_aux = pointer_aux->sigCol;
		}
		/*Table aux_table = aux, aux_table2;*/
//		if (aux == NULL)
//		{
//			delete aux;
//		}
		
		borrar(aux);
		cout<<"BORRADO"<<endl;
		return OK;
		}
		return OK;
}


TipoRet deleteTupla(char *atr1, char *atr2, Table &db)
{
	char delim[] = "=<>";
	char *copia = new char[100];
	strcpy(copia, atr2);
	char delim2[100] = {0};
	char matrizVals[50][100] = {0};
	char *nuev = strtok(atr2, delim);
	int i = 0;
	if (nuev)
	{
		while (nuev)
		{
			strcpy(matrizVals[i], nuev);
			nuev = strtok(NULL, delim);
			i++;
		}
	}
	strcat(delim2, matrizVals[0]);
	strcat(delim2, matrizVals[1]);
	char *operand = strtok(copia, delim2);

	int *valor_int;
	int valor;
	valor = strtol(matrizVals[1], NULL, 10);
	valor_int = &valor;

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
	Dato pointer_aux = aux->pointer;
	if (!i)
	{
		deleteAllTuplas(aux->pointer);
		return OK;
	}
	while (pointer_aux && strcmp(pointer_aux->attName, matrizVals[0]) != 0)
		pointer_aux = pointer_aux->sigCol;
	if (!pointer_aux)
	{
		cout << endl
			 << '\t' << "Parece que la columna no existe." << endl
			 << endl;
		return ERROR;
	}
	else
	{
		char *valor_char = new char[100];
		strcpy(valor_char, matrizVals[1]);
		searchCondition(pointer_aux, valor_char, valor_int, operand);
	}
	return OK;
}

TipoRet insertInto(char *nombreTabla, char *columnaTupla, char *valoresTupla, Table &db)
{
	Table aux = db, aux2 = db;
	Dato puntero;
	char delimitador[] = ":", _integer[100] = "integer", _character[100] = "character", empty[100] = "EMPTY";
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
	if (!strcmp(columnaTupla, ""))
	{
		cout << endl
			 << '\t' << "Debes ingresar al menos una columna." << endl
			 << endl;
		return ERROR;
	}
	if (contVals != contAtts)
	{
		cout << endl
			 << '\t' << "Debes ingresar la misma cantidad de valores que de columnas ingresadas." << endl
			 << endl;
		return ERROR;
	}
	if (checkName(aux, nombreTabla))
	{
		cout << "Parece que la tabla no existe." << endl;
		return ERROR;
	}
	else
		checkNameP(aux2, aux, nombreTabla);
	if (!aux)
	{
		cout << endl
			 << '\t' << "Parece que la tabla no existe." << endl
			 << endl;
		return ERROR;
	}

	if (!validateEntry(aux->pointer, matrizAtts, matrizVals, contAtts))
		return ERROR;

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
		insertarInicioDato(empty_aux, createDataNode(empty_aux->attName, empty_aux->tipo, empty));
		int valor = 0;
		empty_aux->sigTup->valInt = new int;
		*empty_aux->sigTup->valInt = valor;
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
		// ==C2==
	}
	// Conexión horizontal entre nodos datos.
	pointer_aux = aux->pointer;
	while (pointer_aux->sigCol)
	{
		pointer_aux->sigTup->sigCol = pointer_aux->sigCol->sigTup;
		pointer_aux->sigCol->sigTup->antCol = pointer_aux->sigTup;
		pointer_aux = pointer_aux->sigCol;
	}

	return OK;
}

TipoRet addCol(char *nombreTabla, char *NombreCol, char *tipoCol, char *calificadorCol, Table &db)
{
	
	Table aux = db, aux2 = db;
	char primary[14] = "primary key", empty[6] = "empty", not_empty[10] = "not empty", _any[4] = "any";
	char _character[10] = "character", _string[7] = "string", _integer[8] = "integer";

	// VALIDACIONES
	if (!calificadorCol[0])
	{
		cout << endl
			 << '\t' << "Faltan argumentos. /help para mas ayuda." << endl
			 << endl;
		return ERROR;
	}
	if (!(!strcmp(tipoCol, _integer) ||
		  !strcmp(tipoCol, _character) ||
		  !strcmp(tipoCol, _string)))
	{
		cout << endl
			 << '\t' << "Debes ingresar un tipo de dato valido." << endl;
		cout << '\t' << "Tipos de dato: integer, character, string" << endl
			 << endl;
		return ERROR;
	}
	if (!(!strcmp(calificadorCol, primary) ||
		  !strcmp(calificadorCol, _any) ||
		  !strcmp(calificadorCol, not_empty) ||
		  !strcmp(calificadorCol, empty)))
	{
		cout << endl
			 << '\t' << "Debes ingresar un calificador valido." << endl;
		cout << '\t' << "Calificadores disponibles: PRIMARY_KEY, EMPTY, NOT_EMPTY, ANY" << endl
			 << endl;
		return ERROR;
	}

	if (checkName(aux, nombreTabla))
	{
		cout << endl
			 << '\t' << "Parece que la tabla no existe." << endl
			 << endl;
		return ERROR;
	}
	checkNameP(aux2, aux, nombreTabla);
	if (!aux)
	{
		cout << "La tabla no existe." << endl;
		return ERROR;
	}
	if (alreadyColumn(aux->pointer, NombreCol))
	{
		cout << endl
			 << '\t' << "Ya existe una columna con ese nombre." << endl
			 << endl;
		return ERROR;
	}
	if (aux->pointer && (!strcmp(calificadorCol, primary) || !strcmp(calificadorCol, not_empty)))
	{
		if (aux->pointer->sigTup)
		{
			cout << endl
				 << '\t' << "No puedes ingresar una columna " << calificadorCol << " a una tabla con tuplas existentes." << endl
				 << endl;
			return ERROR;
		}
	}
	Dato aux_2 = aux->pointer;
	if (!strcmp(calificadorCol, primary))
	{
		while (aux_2)
		{
			if (!strcmp(aux_2->calif, primary))
			{
				cout << endl
					 << '\t' << "Ya existe una columna PRIMARY_KEY en esta tabla." << endl
					 << endl;
				return ERROR;
			}
			aux_2 = aux_2->sigCol;
		}
	}
	if (strcmp(tipoCol, _string) != 0)
		insertarInicioCol(aux->pointer, createDataNode(NombreCol, tipoCol, calificadorCol));
	else
	{
		strcpy(tipoCol, _character);
		insertarInicioCol(aux->pointer, createDataNode(NombreCol, tipoCol, calificadorCol));
	}
	int integerValue = 1;
	aux->pointer->valChar = new char[50];
	aux->pointer->valInt = &integerValue;
	strcpy(aux->pointer->valChar, "origin_node");
	// Si hay otras columnas.
	if (aux->pointer->sigCol)
	{
		Dato aux_2 = aux->pointer->sigCol->sigTup;
		// Recorro cada tupla existente de otra columna para crear nodos empty en la nueva.
		char *tipoColChar = new char[50];
		strcpy(tipoColChar, "character");
		while (aux_2)
		{
			insertarInicioDato(aux->pointer, createDataNode(NombreCol, tipoColChar, empty));
			aux->pointer->sigTup->valChar = new char[50];
			strcpy(aux->pointer->sigTup->valChar, empty);
			int integerValue2 = 0;
			aux->pointer->sigTup->valInt = &integerValue2;
			aux_2 = aux_2->sigTup;
		}
		Dato aux_3 = aux->pointer->sigTup;
		aux_2 = aux->pointer->sigCol->sigTup;
		while (aux_2)
		{
			// Enlace horizontal de nodos de datos.
			aux_3->sigCol = aux_2;
			aux_2->antCol = aux_3;
			aux_2 = aux_2->sigTup;
			aux_3 = aux_3->sigTup;
		}
	}
	return OK;
}

TipoRet createTable(char *atr1, Table &db)
{
	if (!strcmp(atr1, ""))
	{
		cout << endl
			 << '\t' << "Faltan argumentos. /help para mas ayuda." << endl
			 << endl;
		return ERROR;
	}
	Table aux = db;

	if (!checkName(aux, atr1))
	{
		cout << "La tabla ya existe" << endl;
		return ERROR;
	}

	// insertarInicio(db, createTableNode(atr1));
	insertar(db, createTableNode(atr1));
	if (!db)
		return ERROR;
	return OK;
}

void insertar(Table &arbol, Table v)
{
	if (!arbol)
		arbol = v;
	else if (strcmp(v->name, arbol->name) < 0)
		insertar(arbol->izq, v);
	else if (strcmp(v->name, arbol->name) > 0)
		insertar(arbol->der, v);
}

void printTables(Table arbol)
{
	if (!arbol)
		cout << "No hay tablas" << endl;
	else
		checkTables(arbol);
}

void checkTables(Table arbol)
{
	if (!arbol)
		return;
	printTables(arbol->izq);
	cout << arbol->name << " ";
	printTables(arbol->der);
};

bool checkName(Table arbol, char *tableName)
{
	if (!arbol)
		return true;
	if (!strcmp(arbol->name, tableName))
		return false;
	checkName(arbol->izq, tableName);
	checkName(arbol->der, tableName);
}

void checkNameP(Table &arbol, Table &aux, char *tableName)
{
	if (!arbol)
	{
		aux = arbol;
		return;
	}
	else
	{
		if (!strcmp(arbol->name, tableName))
		{
			aux = arbol;
			return;
		}
		else
		{
			checkNameP(arbol->izq, aux, tableName);
			checkNameP(arbol->der, aux, tableName);
		}
	}
}

TipoRet printDataTable(char *NombreTabla, char *ordenadaPor, Table db)
{
	char delimitador[] = ":";
	char matrizVals[50][100] = {0};
	char *nuev = strtok(ordenadaPor, delimitador);
	int i = 0, contAtts = 0, contVals = 0;
	if (nuev)
	{
		while (nuev)
		{
			strcpy(matrizVals[i], nuev);
			nuev = strtok(NULL, delimitador);
			i++;
			contAtts++;
		}
	}
	Table aux = db, aux2 = db;
	if (!strcmp(NombreTabla, ""))
	{
		cout << endl
			 << '\t' << "Faltan argumentos. /help para mas ayuda." << endl
			 << endl;
		return ERROR;
	}
	else
	{
		if (!aux)
		{
			cout << endl
				 << '\t' << "Parece que la tabla no existe." << endl
				 << endl;
			return ERROR;
		}
		if (checkName(aux, NombreTabla))
		{
			cout << "Parece que la tabla no existe." << endl;
			return ERROR;
		}
		else
			checkNameP(aux2, aux, NombreTabla);
		if (!aux)
		{
			cout << endl
				 << '\t' << "Parece que la tabla no existe." << endl
				 << endl;
			return ERROR;
		}
		if (!aux->pointer)
		{
			cout << endl
				 << '\t' << "No hay datos en la tabla." << endl
				 << endl;
			return ERROR;
		}
		if (!aux->pointer->sigTup)
		{
			cout << endl
				 << '\t' << "No hay datos en la tabla." << endl
				 << endl;
			return ERROR;
		}
		if (strcmp(ordenadaPor, "") != 0 || thereIsPk(aux->pointer))
			orderTable(aux->pointer, matrizVals, contAtts);
		if (!strcmp(aux->name, NombreTabla))
		{
			Dato pointer_aux = aux->pointer;
			Dato pointer_aux_2 = aux->pointer;
			cout << endl
				 << '\t';
			while (pointer_aux_2->sigCol)
			{
				pointer_aux_2 = pointer_aux_2->sigCol;
			}

			while (pointer_aux_2->antCol)
			{

				cout << pointer_aux_2->attName << ":";
				pointer_aux_2 = pointer_aux_2->antCol;
			}
			cout << pointer_aux_2->attName << endl;

			pointer_aux_2 = aux->pointer;

			while (pointer_aux_2->sigCol)
			{
				pointer_aux_2 = pointer_aux_2->sigCol;
			}
			pointer_aux = pointer_aux_2->sigTup;
			pointer_aux_2 = pointer_aux;

			while (pointer_aux->antCol || pointer_aux->sigTup)
			{
				cout << endl
					 << '\t';
				while (pointer_aux->antCol)
				{

					if (!strcmp(pointer_aux->valChar, "empty") && (*pointer_aux->valInt == 0))
						cout << "empty"
							 << ":";
					else
					{
						if (strcmp(pointer_aux->tipo, "integer") != 0)
							cout << pointer_aux->valChar << ":";
						else
							cout << *pointer_aux->valInt << ":";
					}

					pointer_aux = pointer_aux->antCol;
				}
				if (!pointer_aux->sigCol && !pointer_aux->antCol)
				{
					cout << endl
						 << '\t';
				}
				if (strcmp(pointer_aux->tipo, "integer") != 0)
					cout << pointer_aux->valChar;
				else
					cout << *pointer_aux->valInt;
				if (pointer_aux_2->sigTup)
				{
					pointer_aux = pointer_aux_2->sigTup;
					pointer_aux_2 = pointer_aux;
				}
			}

			if (!pointer_aux->sigCol) //?
			{
				cout << endl
					 << '\t';
				if (strcmp(pointer_aux->tipo, "integer") != 0)
					cout << pointer_aux->valChar;
				else
					cout << *pointer_aux->valInt;
			}
		}
	}
	cout << endl
		 << endl;
	return OK;
}

TipoRet printMetadata(char *tableName, Table db)
{
	Table aux = db, aux2 = db;
	if (!strcmp(tableName, ""))
	{
		cout << endl
			 << '\t' << "Faltan argumentos. /help para mas ayuda." << endl
			 << endl;
		return ERROR;
	}
	else
	{
		if (!aux)
		{
			cout << endl
				 << '\t' << "Parece que la tabla no existe." << endl
				 << endl;
			return ERROR;
		}
		if (checkName(aux, tableName))
		{
			cout << "Parece que la tabla no existe." << endl;
			return ERROR;
		}
		else
			checkNameP(aux2, aux, tableName);
		if (!aux)
		{
			cout << endl
				 << '\t' << "Parece que la tabla no existe." << endl
				 << endl;
			return ERROR;
		}
		if (!aux->pointer)
		{
			cout << endl
				 << '\t' << "No hay datos en la tabla." << endl
				 << endl;
			return ERROR;
		}
		if (!strcmp(aux->name, tableName))
		{
			Dato pointer_aux = aux->pointer;
			Dato pointer_aux_2 = aux->pointer;
			cout << endl
				 << endl;

			while (pointer_aux_2->sigCol)
			{
				pointer_aux_2 = pointer_aux_2->sigCol;
			}

			while (pointer_aux_2->antCol)
			{
				cout << '\t';
				cout << pointer_aux_2->attName;
				cout << "-";
				cout << pointer_aux_2->tipo;
				cout << "-";
				cout << pointer_aux_2->calif;
				cout << endl;
				pointer_aux_2 = pointer_aux_2->antCol;
			}
			cout << '\t';
			cout << pointer_aux_2->attName;
			cout << "-";
			cout << pointer_aux_2->tipo;
			cout << "-";
			cout << pointer_aux_2->calif;
			cout << endl
				 << endl;
		}
	}
	return OK;
}

TipoRet dropCol(char *atr1, char *atr2, Table db)
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
	else if (strcmp(pointer_aux->calif, "primary key") == 0 && (pointer_aux->sigCol || pointer_aux->antCol))
	{
		cout << endl
			 << endl
			 << '\t' << "No puede eliminar una columna con calificador PRIMARY KEY." << endl
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
		/*aux->pointer = pointer_aux; */
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

TipoRet selectWhere(char *nombreTabla1, char *condicion, char *nombreTabla2, Table &db){
	char delim[] = "=<>";
	char *copia = new char[100];
	strcpy(copia, condicion);
	char delim2[100] = {0};
	char matrizVals[50][100] = {0};
	char *nuev = strtok(condicion, delim);
	int i = 0;
	if (nuev)
	{
		while (nuev)
		{
			strcpy(matrizVals[i], nuev);
			nuev = strtok(NULL, delim);
			i++;
		}
	}
	strcat(delim2, matrizVals[0]);
	strcat(delim2, matrizVals[1]);
	char *operand = strtok(copia, delim2);
	
	int *valor_int;
	int valor;
	valor = strtol(matrizVals[1], NULL, 10);
	valor_int = &valor;
	
	Table aux = db, aux2 = db;
	if (!checkName(aux, nombreTabla2))
	{
		cout << "Ya existe una tabla "<<nombreTabla2 << endl;
		return ERROR;
	}
	if (checkName(aux, nombreTabla1))
	{
		cout << "Parece que la tabla1 no existe." << endl;
		return ERROR;
	}
	else
		checkNameP(aux2, aux, nombreTabla1);
	if (!aux)
	{
		cout << endl
			<< '\t' << "Parece que la tabla1 no existe." << endl
			<< endl;
		return ERROR;
	}
	Dato pointer_aux = aux->pointer;
	
	insertar(db, createTableNode(nombreTabla2));
	
	while (pointer_aux && strcmp(pointer_aux->attName, matrizVals[0]) != 0)
		pointer_aux = pointer_aux->sigCol;
	if (!pointer_aux)
	{
		cout << endl
			<< '\t' << "Parece que la columna no existe." << endl
			<< endl;
		return ERROR;
	}
	else
	{
		char *valor_char = new char[100];
		strcpy(valor_char, matrizVals[1]);
		searchCondition_selectWhere(pointer_aux, valor_char, valor_int, operand, nombreTabla2, db);
	}
	
	
	
	return OK;
}
