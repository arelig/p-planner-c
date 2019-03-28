#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"
/**
 * @brief Define el prototipo de funcion del comparador.
 * @param p entrada a comparar.
 * @param q entrada a comparar.
 */
int (*comparador)(TEntrada p, TEntrada q);

/**
 * @brief      Busca recursivamente el ultimo nodo padre de la cola con prioridad.
 *
 * @param[in]  cola  Una cola con prioridad.
 * @param[in]  cant  Cantidad de elementos de la cola.
 *
 * @return     Ultimo nodo padre.
 */
TNodo buscarPadre(TColaCP cola, int cant)
{
    TNodo nodo, siguiente;
    if(cant==1)
        nodo = cola->raiz;
    else
    {
        nodo = buscarPadre(cola, cant/2);
        if(cant % 2 != 0)
            siguiente = nodo->hijo_derecho;
        else
            siguiente = nodo->hijo_izquierdo;
        if(siguiente != NULL)
            nodo = siguiente;
    }
    return nodo;
}
/**
 * @brief      Intercambia dos entradas de dos nodos dados.
 *
 * @param[in]  p     Nodo con entrada a intercambiar.
 * @param[in]  q     Nodo con entrada a intercambiar.
 */
void swap(TNodo p, TNodo q)
{
    TEntrada temp = p->entrada;
    p->entrada = q->entrada;
    q->entrada = temp;
}
/**
 * @brief      Retorna el hijo menor de un nodo.
 *
 * @param[in]  padre  El nodo padre de los nodos hijos.
 *
 * @return     Menor de los dos nodos hijos.
 */
TNodo hijo_menor(TNodo padre)
{
    TNodo hijo_menor = padre->hijo_izquierdo;
    if(padre->hijo_derecho != NULL && comparador(hijo_menor->entrada,padre->hijo_derecho->entrada) == -1)
        hijo_menor = padre->hijo_derecho;
    return hijo_menor;
}
/**
 * @brief      Intercambia de forma recursiva un nodo con el mayor de sus dos hijos si el nodo es menor que alguno de ellos,
 *
 * @param[in]  cola  Una cola con prioridad.
 * @param[in]  n     Nodo a comparar.
 */
void downHeap(TColaCP cola,TNodo n)
{
    TNodo menor = hijo_menor(n);
    if(menor != NULL && comparador(n->entrada,menor->entrada) == -1)
    {
        swap(n,menor);
        downHeap(cola,menor);
    }
}

/**
 * @brief      Intercambia de forma recursiva si un nodo que mayor que su padre.
 *
 * @param[in]  cola  Una cola con prioridad.
 * @param[in]  n     Nodo a comparar.
 */
void upHeap(TColaCP cola, TNodo n)
{
    if(n != cola->raiz && comparador(n->entrada,n->padre->entrada) == 1)
    {
        swap(n,n->padre);
        upHeap(cola,n->padre);
    }
}
/**
 * @brief      Inicializa una cola con prioridad, con cantidad de elementos 0 y raiz nula.
 *
 * @param[in]  cola  Una cola con prioridad.
 * @param[in]  f     Puntero de funcion de prioridad.
 */
void crear_cola_cp(TColaCP* cola, int (*f)(TEntrada p, TEntrada q))
{
    *cola = (TColaCP) malloc(sizeof(struct cola_con_prioridad));
    comparador = f;
    (*cola)->cantidad_elementos = 0;
    (*cola)->raiz = NULL;
}
/**
 * @brief      Inserta una entrada en la cola con prioridad y reestablece el orden de prioridad.
 *
 * @param[in]  cola  Una cola con prioridad.
 * @param[in]  entr  Entrada a insertar.
 *
 * @return     Verdadero si procede con exito, falso en caso contrario.
 */
int cp_insertar(TColaCP cola, TEntrada entr)
{
    if(cola == NULL)
        exit(CCP_NO_INI);

    TNodo n_nodo = (TNodo) malloc(sizeof(struct nodo));
    n_nodo->entrada = entr;
    n_nodo->padre = NULL;
    n_nodo->hijo_derecho = NULL;
    n_nodo->hijo_izquierdo = NULL;

    int retorno = FALSE;
    TNodo padre;

    if(cola->cantidad_elementos == 0)
    {
        cola->raiz = n_nodo;
        retorno = TRUE;
    }
    else
    {
        padre = buscarPadre(cola,cola->cantidad_elementos+1);

        if(padre->hijo_izquierdo == NULL)
            padre->hijo_izquierdo = n_nodo;
        else
            padre->hijo_derecho = n_nodo;

        n_nodo->padre = padre;
        upHeap(cola,n_nodo);
        retorno = TRUE;

    }
    cola->cantidad_elementos++;
    return retorno;
}
/**
 * @brief      Retorna el ultimo hijo de un nodo.
 *
 * @param[in]  p     Nodo padre.
 *
 * @return     Ultimo hijo.
 */
TNodo ultimo_hijo(TNodo p)
{
    TNodo ultimo = p->hijo_izquierdo;
    if(p->hijo_derecho != NULL)
        ultimo = p->hijo_derecho;
    return ultimo;
}
/**
 * @brief      Elimina el ultimo hijo de un nodo.
 *
 * @param[in]  n     Nodo padre los hijos.
 */
void eliminar_ultimo_hijo(TNodo n)
{
    if(n->hijo_derecho != NULL)
    {
        free(n->hijo_derecho);
        n->hijo_derecho = NULL;
    }
    else
    {
        free(n->hijo_izquierdo);
        n->hijo_izquierdo = NULL;
    }
}
/**
 * @brief      Elimina la entrada de mayor prioridad de la cola y la retorna.
 *             Reestablece el orden de la cola luego de la eliminacion.
 *
 * @param[in]  cola  Una cola con prioridad
 *
 * @return     Entrada de mayor prioridad.
 */
TEntrada cp_eliminar(TColaCP cola)
{
    if(cola == NULL)
        exit(CCP_NO_INI);
    if(cola->cantidad_elementos == 0)
        return ELE_NULO;
    TEntrada a_remover = cola->raiz->entrada;

    if(cola->cantidad_elementos == 1)
    {
        free(cola->raiz);
        cola->raiz = NULL;
    }
    else
    {
        TNodo ultimo = buscarPadre(cola,cola->cantidad_elementos);
        swap(cola->raiz,ultimo);
        eliminar_ultimo_hijo(ultimo->padre);
        downHeap(cola,cola->raiz);
    }
    cola->cantidad_elementos--;
    return a_remover;
}
/**
 * @brief      Retorna la cantidad de elementos de una cola.
 *
 * @param[in]  cola  Una cola con prioridad
 *
 * @return     Cantidad de elementos.
 */
int cp_size(TColaCP cola)
{
    return cola->cantidad_elementos;
}
/**
 * @brief      Libera recursivamente cada nodo del heap.
 *
 * @param[in]  cola  Una cola con prioridad.
 * @param[in]  nodo  Un nodo.
 */
void destruir_rec(TColaCP cola, TNodo nodo)
{
    if(nodo->hijo_derecho != NULL)
        destruir_rec(cola,nodo->hijo_derecho);
    if(nodo->hijo_izquierdo != NULL)
        destruir_rec(cola, nodo->hijo_izquierdo);

    nodo->hijo_derecho = NULL;
    nodo->hijo_izquierdo=NULL;
    nodo->padre = NULL;
    free(nodo);
}
/**
 * @brief      Libera el espacio ocupado por la cola con prioridad argumentada.
 *
 * @param[in]  cola  Una cola con prioridad.
 *
 * @return     Verdadero si procedio con exito, falso en caso contrario.
 */
int cp_destruir(TColaCP cola)
{
    int retorno;
    if(cola == NULL)
        exit(CCP_NO_INI);
    if(cola->raiz != NULL)
        destruir_rec(cola, cola->raiz);
    free(cola);
    retorno = TRUE;
    return retorno;

}




