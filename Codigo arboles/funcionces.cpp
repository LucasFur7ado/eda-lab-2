#include<iostream>
#include "prototipos.hpp"
using namespace std;

ABB crearNodo(int v)
{
	ABB nuevo=new nodoArbol;
	nuevo->valor=v;
	nuevo->izq=NULL;
	nuevo->der=NULL;
	return nuevo;
}

void insertar (ABB &arbol, ABB v)
{
	if (arbol==NULL)
		arbol=v;
	else
		if(v->valor<arbol->valor)
		insertar(arbol->izq,v);
		else
			if(v->valor>arbol->valor)
			insertar(arbol->der, v);
}

void preOrden(ABB arbol)
{
	if (arbol==NULL)
		return;
	cout<<arbol->valor<<" ";
	preOrden(arbol->izq);
	preOrden(arbol->der);
}

void postOrden(ABB arbol)
{
	if (arbol==NULL)
		return;
	postOrden(arbol->izq);
	postOrden(arbol->der);
	cout<<arbol->valor<<" ";
}

void inOrden(ABB arbol)
{
	if (arbol==NULL)
		return;
	inOrden(arbol->izq);
	cout<<arbol->valor<<" ";
	inOrden(arbol->der);
}

void borrar(ABB &arbol, int x)
{
	if(arbol==NULL) return;
	if(x<arbol->valor)
		borrar(arbol->izq, x);
	else
		if(x>arbol->valor)
		borrar(arbol->der, x);
		else
		{
			ABB p = arbol;
			arbol = unirABB(arbol->izq, arbol->der);
			delete p;
		}
}

ABB unirABB(ABB izq, ABB der)
{
	if(izq==NULL) return der;
	if(der==NULL) return izq;
	ABB centro = unirABB(izq->der, der->izq);
	izq->der = centro;
	der->izq = izq;
	return der;
}

