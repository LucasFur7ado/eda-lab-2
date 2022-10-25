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
	char comando[100] = {0}, delimitador[] = "(,) ",
		*atr1, *atr2, *atr3, *atr4, *atr5;
	
	char helpComm[100] = "/help";
	char addColComm[100] = "addCol";
	char dropColComm[100] = "dropCol";
	char creditsComm[100] = "/credits";
	char createComm[100] = "createTable";
	char dropTableComm[100] = "dropTable";
	char insertIntoComm[100] = "insertInto";
	char showTablesComm[100] = "showTables";
	char deleteTuplaComm[100] = "deleteTupla";
	char printMetadataComm[100] = "printMetadata";
	char printDataTableComm[100] = "printDataTable";
	
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
		cin>> comando;
		
		/*gets(comando);
		int largo = strlen(comando);
		for (int letra = 0; letra < largo; ++letra)  
			comando[letra] = tolower(comando[letra]); 
		*/
		
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
		else if (!strcmp(comando, showTablesComm))
			showTables(db);
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
		else
		{
			cout << endl
				<< '\t' << "No existe ese comando, /help para mas ayuda" << endl;
			cout << '\t' << "Advertencia: evita utilizar espacios." << endl
				<< endl;
		}
	}
	return 0;
}
