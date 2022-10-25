#include<iostream>
#include "prototipos.hpp"
using namespace std;

int main (int argc, char *argv[]) {
	
ABB arbol = NULL;
int valor, opcion;
char seguir;
do{
	cout<<"Ingrese un valor "<<endl;
	cin>>valor;
	insertar(arbol, crearNodo(valor));
	cout<<"Desea seguir ingresando datos? ";
	cin>>seguir;
} while(seguir == 's');

do{
	cout<<"MENU"<<endl;
	cout<<"1) Insertar"<<endl;
	cout<<"2) preOrden"<<endl;
	cout<<"3) postOrden"<<endl;
	cout<<"4) inOrden"<<endl;
	cout<<"5) borrar"<<endl;
	cout<<"6) unirABB"<<endl;
	
	
	cout<<"0) Terminar"<<endl;
	cin>>opcion;
	switch(opcion)
	{
	case 1:
		cout<<"Ingrese un valor para insertar";
		cin>>valor;
		insertar(arbol, crearNodo(valor));
		break;
	case 2:
		preOrden(arbol);
		cout<<endl;
		break;
	case 3:
		postOrden(arbol);
		cout<<endl;
		break;
	case 4:
		inOrden(arbol);
		cout<<endl;
		break;
	case 5:
		cout<<"ingrese un valor ";
		cin>>valor;
		borrar(arbol, valor);
		break;
	}
} while(opcion != 0);

return 0;
}
