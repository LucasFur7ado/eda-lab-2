#include <cctype>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "heads.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	Table db = NULL;
	char comando[100] = {0}, delimitador[] = "(,)",
		*atr1, *atr2, *atr3, *atr4, *atr5;
	
	char helpComm[100] = "/help";
	char addColComm[100] = "addcol";
	char dropColComm[100] = "dropcol";
	char creditsComm[100] = "/credits";
	char createComm[100] = "createtable";
	char dropTableComm[100] = "droptable";
	char insertIntoComm[100] = "insertinto";
	char printTablesComm[100] = "printtables";
	char deleteTuplaComm[100] = "deletetupla";
	char printMetadataComm[100] = "printmetadata";
	char printDataTableComm[100] = "printdatatable";
	char selectWhereComm[100] = "selectwhere";
	char selectComm[100] = "select";
	
	while (true)
	{
		atr1 = new char[100];
		atr2 = new char[100];
		atr3 = new char[100];
		atr4 = new char[100];
		atr5 = new char[100];
		for (int l = 0; l < 100; l++)
		{
			atr1[l] = NULL;
			atr2[l] = NULL;
			atr3[l] = NULL;
			atr4[l] = NULL;
		}
		cout << ">> ";
	/*	cin>> comando;*/
		
		gets(comando);
		int largo = strlen(comando);
		for (int letra = 0; letra < largo; ++letra)  
			comando[letra] = tolower(comando[letra]); 
		
		
		char *nuevo = strtok(comando, delimitador);
		nuevo = strtok(NULL, delimitador);
		if (nuevo)
		{
			int i = 0;
			while (nuevo)
			{
				fillAtr(atr1, i, 0, nuevo);
				fillAtr(atr2, i, 1, nuevo);
				fillAtr(atr3, i, 2, nuevo);
				fillAtr(atr4, i, 3, nuevo);
				fillAtr(atr5, i, 4, nuevo);
				nuevo = strtok(NULL, delimitador);
				i++;
			}
		}
		if (!strcmp(comando, createComm))
			createTable(atr1, db);
		else if (!strcmp(comando, addColComm))
			addCol(atr1, atr2, atr3, atr4, db);
		else if (!strcmp(comando, printTablesComm))
			printTables(db);
		else if (!strcmp(comando, printDataTableComm))
			printDataTable(atr1, atr2, db);
		else if (!strcmp(comando, insertIntoComm))
			insertInto(atr1, atr2, atr3, db);
		else if (!strcmp(comando, deleteTuplaComm))
			deleteTupla(atr1, atr2, db);
		else if (!strcmp(comando, dropColComm))
			dropCol(atr1, atr2, db);
		else if (!strcmp(comando, dropTableComm))
			dropTable(atr1, db);
		else if (!strcmp(comando, printMetadataComm))
			printMetadata(atr1, db);
		else if (!strcmp(comando, creditsComm))
			credits();
		else if (!strcmp(comando, helpComm))
			help();
		else if (!strcmp(comando,selectWhereComm))
				 selectWhere(atr1, atr2, atr3, db);
		else if (!strcmp(comando,selectComm))
				 select(atr1, atr2, atr3, db);
		else
		{	
			cout << endl
				<< '\t' << "No existe ese comando, /help para mas ayuda" << endl;
		}
	}
	return 0;
}
