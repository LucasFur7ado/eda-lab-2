#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#endif

struct nodoArbol
{
	int valor;
	int cant;
	nodoArbol *izq;
	nodoArbol *der;
};
typedef nodoArbol *ABB;

ABB crearNodo(int v);
void insertar (ABB &arbol, ABB v);
void preOrden(ABB arbol);
void postOrden(ABB arbol);
void inOrden(ABB arbol);
void borrar(ABB &arbol, int x);
ABB unirABB(ABB izq, ABB der);
