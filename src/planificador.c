#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "colacp.h"
#include "lista.h"
#include "define.h"
#include "ciudad.h"
/**
 *Definicion de encabezados de funciones
 */
int mostrarAscendente(TEntrada p, TEntrada q);
int mostrarDescendente(TEntrada p, TEntrada q);
void imprimirCCP(TColaCP ccp);
void generarListaPrincipal(FILE* f,TLista* l_p);
void ordenarInformacion(int cord_x, int cord_y, TLista* l_p, TColaCP ccp);
void reducirHorasManejo(int cord_x_actual,int cord_y_actual,TLista l_p);

int main(int argv, char* args[])
{
    FILE* f;
 //   f = fopen("/home/alumno/Descargas/Proyecto_1/viajes.txt","r");
    f = fopen(args[1],"r");
    if(f == NULL)
        exit(ARCHIVO_CORRUPTO);

    TLista lista_principal;
    int cord_x_actual;
    int cord_y_actual;
    int opcion;
    //lee la coordenada inicial del usuario
    fscanf(f,"%d;%d\n", &cord_x_actual, &cord_y_actual);

    generarListaPrincipal(f,&lista_principal);

    printf("Bienvenido al planificador OCUNS. \n Por favor ingrese la forma en que las ciudades se mostrarán.\n");
    printf("1 - Mostrar Ascendente\n");
    printf("2 - Mostrar Descendente\n");
    printf("3 - Reducir horas de Manejo\n");
    printf("4 - Salir de la aplicación\n");
    while(opcion !=4)
    {
        printf("Ingrese opcion: \n");
        scanf("%i",&opcion);
        switch (opcion)
        {
        case 1:   //mostrar la lista de ciudades de forma ascendente
        {
            TColaCP cola_ascendente;
            crear_cola_cp(&cola_ascendente, mostrarAscendente);
            printf("------------------------------------------------------------------------\n");
            printf("Mostrando el listado de forma ascendente... \n");
            ordenarInformacion(cord_x_actual,cord_y_actual,&lista_principal,cola_ascendente);
            imprimirCCP(cola_ascendente);
            printf("------------------------------------------------------------------------\n");
            break;
        }
        case 2:  //mostrar la lista de ciudades de forma descendente
        {
            TColaCP cola_descendente;
            crear_cola_cp(&cola_descendente, mostrarDescendente);
            printf("------------------------------------------------------------------------\n");
            printf("Mostrando el listado de forma Descendente... \n");
            ordenarInformacion(cord_x_actual,cord_y_actual,&lista_principal,cola_descendente);
            imprimirCCP(cola_descendente);
            printf("------------------------------------------------------------------------\n");
            break;
        }
        case 3:  //reducir horas manejo
        {
            reducirHorasManejo(cord_x_actual,cord_y_actual,lista_principal);
            printf("------------------------------------------------------------------------\n");
            break;
        }
        case 4:  //salir
        {
            fclose(f);
            int i,s = l_size(lista_principal);
            TPosicion pos = l_primera(lista_principal);

            for(i=0;i<s;i++){
                TCiudad eliminada = (TCiudad) pos->elemento;
                free(eliminada->nombre);
                free(eliminada);
                pos = l_siguiente(lista_principal,pos);
            }
            l_destruir(&lista_principal);
        }
        default:
        {
            printf("Gracias por utilizar PLANIFICADOR.\n");
            exit(FIN_PROGRAMA);
        }
        }
    }
    return 0;
}

/**
 * @brief      Muestra por pantalla los nombres de las ciudades, removidas de la cola con prioridad.
 *
 * @param[in]  ccp   Una cola con prioridad.
 */


void imprimirCCP(TColaCP ccp)
{
    int i;
    TEntrada e;
    TCiudad ciudad;
    int cant_elementos_cola = cp_size(ccp);
    for(i=0; i<cant_elementos_cola; i++)
    {
        e = cp_eliminar(ccp);
        ciudad = e->valor;
        printf("%i - %s \n",i,ciudad->nombre);
    }
}
/**
 * @brief      Lee el archivo e ingresa la informacion en la lista principal.
 *
 * @param      f     Archivo de informacion.
 */
void generarListaPrincipal(FILE* f, TLista* l_p)
{
    crear_lista(l_p);

    TCiudad ciudad;
    char* nombre_ciudad;
    int cord_x,cord_y;

    while(!feof(f))
    {
        nombre_ciudad = (char*) malloc(sizeof(char) * 20);
        ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        fscanf(f,"%[^;];", nombre_ciudad);
        fscanf(f,"%d;", &cord_x);
        fscanf(f,"%d\n",&cord_y);
        ciudad->nombre = nombre_ciudad;
        ciudad->pos_x = cord_x;
        ciudad->pos_y = cord_y;
        l_insertar(l_p,NULL,ciudad);
    }
}


/**
 * @brief      Recorre la lista principal de ciudades y las ingresa en la cola con prioridad para ordenarlas dependiendo de su prioridad.
 *
 * @param[in]  cord_x  Coordenada x de la ciudad actual.
 * @param[in]  cord_y  Cordenada y de la ciudad actual.
 * @param      l_p     Lista principal.
 * @param[in]  ccp     Cola con prioridad a utilizar.
 */
void ordenarInformacion(int cord_x, int cord_y, TLista* l_p, TColaCP ccp)
{
    int* distancia_a_origen;
    TCiudad ciudad_actual;
    TPosicion pos = l_primera(*l_p);
    TEntrada ent;
    while(pos != NULL)
    {
        ciudad_actual = l_recuperar(*l_p, pos);
        ent = (TEntrada) malloc(sizeof(struct entrada));
        distancia_a_origen = (int*) malloc(sizeof(int));
        *distancia_a_origen = abs(cord_x - ciudad_actual->pos_x) + abs(cord_y - ciudad_actual->pos_y);
        ent->clave = distancia_a_origen;
        ent->valor = ciudad_actual;
        pos = l_siguiente(*l_p,pos);
        cp_insertar(ccp,ent);
    }
}
/**
 * @brief      Funcion de comparacion ascendente
 *
 * @param[in]  p     Entrada a comparar.
 * @param[in]  q     Entrada a comparar.
 *
 * @return     -1 si p>q, 1 si p<q, 0 si son iguales.
 */
int mostrarAscendente(TEntrada p, TEntrada q)
{
    int retorno;

    int clave_1 =  *(int*) (p->clave);
    int clave_2 = *(int*) (q->clave);

    if(clave_1 > clave_2)
        retorno = -1;
    else if(clave_1 < clave_2)
        retorno = 1;
    else
        retorno = 0;

    return retorno;
}
/**
 * @brief      Funcion de comparacion ascendente
 *
 * @param[in]  p     Entrada a comparar.
 * @param[in]  q     Entrada a comparar.
 *
 * @return     -1 si p<q, 1 si p>q, 0 si son iguales.
 */
int mostrarDescendente(TEntrada p, TEntrada q)
{
    int retorno;
    int clave_1 = *(int*) p->clave;
    int clave_2 = *(int*) q->clave;

    if(clave_1 < clave_2)
        retorno = -1;
    else if(clave_1 > clave_2)
        retorno = 1;
    else
        retorno = 0;
    return retorno;
}
/**
 * @brief      Calcula el orden en el que las ciudades tienen que ser visitadas,
 *
 * @param[in]  cord_x_actual  Cordenada x actual de la ciudad recorrida.
 * @param[in]  cord_y_actual  Cordenada x actual de la ciudad recorrida.
 * @param[in]  l_p            Copia de la lista principal.
 */

void reducirHorasManejo(int cord_x_actual,int cord_y_actual,TLista l_p)
{
    TLista l_p_duplicada;
    int cord_x_sig, cord_y_sig;
    TCiudad ciudad_actual;
    TColaCP cola_que_ordena;
    TPosicion temp_1;
    TEntrada eliminada;
    int total_horas = 0;

    crear_lista(&l_p_duplicada);
    temp_1 = l_primera(l_p);

    while(temp_1 != NULL)
    {
        l_insertar(&l_p_duplicada,NULL,l_recuperar(l_p,temp_1));
        temp_1 = l_siguiente(l_p,temp_1);
    }
    cord_x_sig = cord_x_actual;
    cord_y_sig = cord_y_actual;
    //mientras la lista duplicada no este vacia
    while(l_size(l_p_duplicada)>0)
    {
        crear_cola_cp(&cola_que_ordena,mostrarAscendente);
        ordenarInformacion(cord_x_sig, cord_y_sig, &l_p_duplicada, cola_que_ordena);
        eliminada = cp_eliminar(cola_que_ordena);
        ciudad_actual = eliminada->valor;
        total_horas = total_horas + *(int*)eliminada->clave;
        //muestro la ciudad eliminada
        printf("%s\n",ciudad_actual->nombre);
        cord_x_sig = ciudad_actual->pos_x;
        cord_y_sig = ciudad_actual->pos_y;
        free(eliminada);
        l_destruir(&l_p_duplicada);

        crear_lista(&l_p_duplicada);
        //copio la lista con los elementos que quedaron en la cola
        while(cp_size(cola_que_ordena)>0)
            l_insertar(&l_p_duplicada,NULL,cp_eliminar(cola_que_ordena)->valor);

        //destruyo la cola
        cp_destruir(cola_que_ordena);
    }
    printf("Total horas: %i \n",total_horas);
}
