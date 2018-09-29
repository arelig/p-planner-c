#include "TLista.h"
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define LST_NO_INI 2
#define LST_VAC 3
#define CCP_NO_INI 4
#define POS_NULA NULL
#define ELE_NULO NULL

void crear_lista(TLista* lista)
{
    lista = NULL;
}

int l_insertar(TLista* lista, TPosicion pos, TElemento val)
{
    int retorno;
    if(lista==NULL)
        exit(LST_NO_INI);

    TPosicion n_nodo = (TPosicion) malloc(sizeof(struct nodo));
    n_nodo->valor = val;

    if(pos == POS_NULA)
    {
        n_nodo->sig = *lista;
        n_nodo->ant = NULL;
        n_nodo->sig->ant = n_nodo;
        *lista = n_nodo;
        retorno = TRUE;
    }
    else
    {
        if(pos->sig != POS_NULA)
        {
            n_nodo->ant = pos;
            n_nodo->sig = pos->sig;
            pos->sig = n_nodo;
            n_nodo->sig->ant = n_nodo;
            retorno = TRUE;
        }
        else
        {
            n_nodo->ant = pos;
            pos->sig = n_nodo;
            retorno = TRUE;
        }
    }

    return retorno;
}

int l_eliminar(TLista* lista, TPosicion pos)
{
    int retorno;
    if(lista == NULL)
        exit(LST_NO_INI);

    if(pos == *lista)
        *lista = pos->sig;
    else
    if(pos->sig == NULL)
        pos->ant = NULL;
    else
    {
        pos->ant->sig = pos->sig;
        pos->sig->ant = pos->ant;
    }
    free(pos->valor);
    free(pos);
    retorno = TRUE;
    return retorno;
}

TPosicion l_primera(TLista lista){
    if(lista==NULL)
        exit(LST_NO_INI);
    return lista;
}

TPosicion l_ultima(TLista lista){
    if(lista==NULL)
        exit(LST_NO_INI);
    TPosicion temp = lista;
    while(temp->sig != NULL){
        temp = temp->sig;
    }
    return temp;
}

TPosicion l_anterior(TLista lista, TPosicion pos){
    TPosicion retorno;
    if(lista == NULL)
        exit(LST_NO_INI);
    if(pos == lista)
        retorno = POS_NULA;
    else
        retorno = pos->ant;
    return retorno;
}

TPosicion l_siguiente(TLista lista, TPosicion pos){
    TPosicion retorno;
    if(lista==NULL)
        exit(LST_NO_INI);
    if(pos->sig == NULL)
        retorno = POS_NULA;
    else
        retorno = pos->sig;
    return retorno;
}

TElemento l_recuperar(TLista lista, TPosicion pos){
    TElemento retorno;
    if(lista==NULL)
        exit(LST_NO_INI);
    if(pos == NULL)
        retorno = ELE_NULO;
    else
        retorno = pos->valor;
    return retorno;
}

int l_size(TLista lista){
    if(lista == NULL)
        exit(LST_NO_INI);
    TPosicion temp = lista;
    int cont = 0;
    while(temp->sig != NULL){
        temp = temp->sig;
        cont++;
    }
    return cont;
}

int l_destruir(TLista* lista){
    if(lista == NULL)
        exit(LST_NO_INI);
    int retorno;
    TPosicion temp;
    while(temp->sig != NULL){
        temp = *lista;
        *lista = temp->sig;
        free(temp->valor);
        free(temp);
    }
    retorno = TRUE;
    return retorno;
}






