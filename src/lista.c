#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#include "define.h"
/**
 * @brief      Inicializa una lista especificada en el argumento.
 *
 * @param      lista  Una lista.
 */
void crear_lista(TLista* lista)
{
    *lista = NULL;
}
/**
 * @brief      Inserta el elemento en la posicion, si la posicion es nula,
 *             se inserta el elemento en la primera posicion de la lista.
 *             Si la lista no esta inicializada, se aborta el programa.
 *
 * @param      lista  Una lista.
 * @param[in]  pos    Posicion.
 * @param[in]  elem    Elemento.
 *
 * @return     Verdadero si procede con exito, falso en caso contrario.
 */
int l_insertar(TLista* lista, TPosicion pos, TElemento elem)
{
    if(lista==NULL)
        exit(LST_NO_INI);
    int retorno;
    TPosicion n_celda =(TPosicion) malloc(sizeof(struct celda));
    n_celda->elemento = elem;

    if(pos == POS_NULA)
    {
        n_celda->celda_siguiente = *lista;
        n_celda->celda_anterior = POS_NULA;
        if((*lista)!=NULL)
            (*lista)->celda_anterior = n_celda;
        *lista = n_celda;
        retorno = TRUE;
    }
    else
    {
        if(pos->celda_siguiente != POS_NULA)
        {
            n_celda->celda_anterior = pos;
            n_celda->celda_siguiente = pos->celda_siguiente;
            pos->celda_siguiente = n_celda;
            n_celda->celda_siguiente->celda_anterior = n_celda;
            retorno = TRUE;
        }
        else
        {
            pos->celda_siguiente = n_celda;
            n_celda->celda_anterior = pos;
            retorno = TRUE;
        }
    }

    return retorno;
}
/**
 * @brief      Elimina el elemento de la posicion, luego reestablece el orden de la lista.
 *             Si la lista no esta inicializada, se aborta el programa.
 *
 * @param      lista  Una lista
 * @param[in]  pos    Posicion.
 *
 * @return     Verdadero si procede con exito, falso en caso contrario.
 */
int l_eliminar(TLista* lista, TPosicion pos)
{
    int retorno;
    if(lista == NULL)
        exit(LST_NO_INI);

    if(pos == *lista){
        *lista = pos->celda_siguiente;
        pos->celda_siguiente->celda_anterior = NULL;
    }
    else
    if(pos->celda_siguiente == NULL)
        pos->celda_anterior = NULL;
    else
    {
        pos->celda_anterior->celda_siguiente = pos->celda_siguiente;
        pos->celda_siguiente->celda_anterior = pos->celda_anterior;
    }
    free(pos);
    retorno = TRUE;
    return retorno;
}
/**
 * @brief      Retorna la primera posicion de la lista.
 *
 * @param[in]  lista  Una lista
 *
 * @return     Primera posicion de la lista.
 */
TPosicion l_primera(TLista lista){
    return lista;
}
/**
 * @brief      Retorna la ultima posicion de la lista.
 *
 * @param[in]  lista  Una lista
 *
 * @return     Ultima posicion de la lista.
 */

TPosicion l_ultima(TLista lista){
    TPosicion temp = lista;
    while(temp->celda_siguiente != NULL){
        temp = temp->celda_siguiente;
    }
    return temp;
}
/**
 * @brief      Retorna la posicion anterior a la posicion argumentada.
 *             Si la posicion es la primera posicion en la lista, retorna POS_NULA.
 *
 * @param[in]  lista  Una lista
 * @param[in]  pos    Posicion
 *
 * @return     Posicion anterior a la posicion argumentada.
 */

TPosicion l_anterior(TLista lista, TPosicion pos){
    TPosicion retorno;
    if(pos == lista)
        retorno = POS_NULA;
    else
        retorno = pos->celda_anterior;
    return retorno;
}
/**
 * @brief      Retorna la posicion siguiente a la posicion argumentada.
 *             Si la posicion es la ultima posicion en la lista, retorna POS_NULA.
 *
 * @param[in]  lista  Una lista
 * @param[in]  pos    Posicion
 *
 * @return     Posicion siguiente a la posicion argumentada.
 */

TPosicion l_siguiente(TLista lista, TPosicion pos){
    TPosicion retorno;
    if(pos->celda_siguiente == NULL)
        retorno = POS_NULA;
    else
        retorno = pos->celda_siguiente;
    return retorno;
}
/**
 * @brief      Recupera el elemento de la posicion argumentada, si la posicion es nula retorna ELE_NULO.
 *
 * @param[in]  lista  Una lista
 * @param[in]  pos    Posicion
 *
 * @return     elemento de la posicion.
 */

TElemento l_recuperar(TLista lista, TPosicion pos){
    TElemento retorno;
    if(pos == NULL)
        retorno = ELE_NULO;
    else
        retorno = pos->elemento;
    return retorno;
}
/**
 * @brief      Retorna la cantidad de elementos de la lista.
 *
 * @param[in]  lista  Una lista.
 *
 * @return     Cantidad de elementos de la lista.
 */
int l_size(TLista lista){
    int cont;
    TPosicion temp = lista;
    cont = 0;
    while(temp != NULL){
        cont++;
        temp = temp->celda_siguiente;
    }
    return cont;
}
/**
 * @brief      Elimina todos los elementos de la lista y libera la memoria utilizada.
 *             Si la lista no esta inicializada, se aborta el programa.
 *
 * @param      lista  Una lista
 *
 * @return     Verdadero si procede con exito, falso en caso contrario.
 */

int l_destruir(TLista* lista){
    if(lista == NULL)
        exit(LST_NO_INI);
    int retorno;
    TPosicion temp;
    while(temp != NULL && temp->celda_siguiente != NULL){
        temp = *lista;
        *lista = temp->celda_siguiente;
        free(temp);
    }
    retorno = TRUE;
    return retorno;
}






