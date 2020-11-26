#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*) malloc (sizeof(LinkedList));
    if(this!=NULL)
    {
    	this->pFirstNode = NULL;
    	this->size = 0;
    }
    return this;
}
/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}
/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode = NULL;
	int i;
	int len = ll_len(this);
	if(this!=NULL && nodeIndex>=0 && nodeIndex<len)
	{
		pNode = this->pFirstNode;
		for(i=0; i<nodeIndex; i++)
		{
			pNode = pNode->pNextNode;
		}
	}
    return pNode;
}
/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}
/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int result = -1;
    Node* pNode = NULL;
    Node* pPrevNode = NULL;
    if(this!=NULL && nodeIndex>-1 && nodeIndex<=ll_len(this))
    {
		pNode = (Node*) malloc (sizeof(Node));
		if(pNode!=NULL)
		{
			if(nodeIndex==0)
			{
				pNode->pNextNode = this->pFirstNode;
				this->pFirstNode = pNode;
				//quiero agregar un nodo en el medio
			}
			else
			{
				pPrevNode = getNode(this,nodeIndex-1);
				if(pPrevNode != NULL)
				{
					pNode->pNextNode = pPrevNode->pNextNode;
					pPrevNode->pNextNode = pNode;
				}
			}
		}
    	pNode->pElement = pElement;
    	this->size++;
    	result = 0;
    }
    return result;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int len = ll_len(this);

    if(this!=NULL && len>-1 && addNode(this, len, pElement)==0)
    {
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* aux = NULL;
    int len;
    if(this!=NULL && index>-1)
    {
    	len = ll_len(this);
    	if(index < len)
    	{
    		aux = getNode(this, index);
			if(aux!=NULL)
			{
				returnAux = aux->pElement;
			}
    	}
    }
    return returnAux;
}
/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxiliar = NULL;
    if(this != NULL && index>-1 && index<ll_len(this))
    {
    	auxiliar = getNode(this, index);
    	if(auxiliar!=NULL)
    	{
    		auxiliar->pElement = pElement;
    	}
		returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* auxiliar = NULL;
    Node* prevNode = NULL;
    int len;
    if(this!=NULL && index>-1)
    {
    	len = ll_len(this);
    	if(index<len)
    	{
    		auxiliar = getNode(this, index);
    		if(auxiliar!=NULL)
    		{
    			if(index==0)
    			{
    				this->pFirstNode = auxiliar->pNextNode;
    				this->size--;
    				free(auxiliar->pElement);
    				free(auxiliar);
    			}
    			else
    			{
    	    		prevNode = getNode(this,index-1);
    	    		if(prevNode!=NULL)
    	    		{
    	    			prevNode->pNextNode = auxiliar->pNextNode;
    	    			this->size--;
        				free(auxiliar->pElement);
        				free(auxiliar);
    	    		}
    			}
				returnAux = 0;
    		}
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;
    int len;
    if(this!=NULL)
    {
    	len = ll_len(this);
    	for(i=0;i<len;i++)
    	{
    		ll_remove(this, i);
    	}
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    int len;
    if(this!=NULL)
    {
    	len = ll_len(this);
    	ll_clear(this);
    	free(this);
    	if(len==0)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* aux = NULL;
    int i;
    int len;
    if(this!=NULL)
    {
    	len = ll_len(this);
    	for(i=0; i<len; i++)
    	{
    		aux = ll_get(this, i);
    		if(aux == pElement)
    		{
    			returnAux = i;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
    	if(this->pFirstNode!=NULL && this->size>0)
    	{
    		returnAux = 0;
    	}
    	else
    	{
    		returnAux = 1;
    	}
    }
    return returnAux;
}
/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int len;
    if(this!=NULL && index>-1)
    {
    	len = ll_len(this);
    	if(index<=len)
    	{
    		if(!addNode(this, index, pElement))
    		{
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}
/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* aux = NULL;

    if(this!=NULL && index>-1 && index<ll_len(this))
    {
    	aux = ll_get(this, index);
    	if(aux!=NULL)
    	{
    		returnAux = aux;
    		this->size--;
    		ll_remove(this, index);
    	}
    }
    return returnAux;
}
/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* aux = NULL;
    int i;

    if(this!=NULL)
    {
    	returnAux = 0;
    	for(i=0;i<ll_len(this);i++)
    	{
    		aux = ll_get(this, i);
    		if(aux!=NULL && aux == pElement)
    		{
    			returnAux = 1;
    			break;
    		}
    	}
    }
    return returnAux;
}
/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* aux = NULL;
    int i;

    if(this!=NULL && this2!=NULL)
    {
    	returnAux= 1;
    	for(i=0;i<ll_len(this2);i++)
    	{
    		aux = ll_get(this2, i);
    		if(aux!=NULL)
    		{
				if(!ll_contains(this, aux))
				{
					returnAux = 0;
					break;
				}
    		}
    	}
    }
    return returnAux;
}
/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int len;
    void* aux = NULL;
    int i;
   	len = ll_len(this);

    if(this!=NULL && from>-1 && to>-1 && from<len && to<=len && from<to)
    {
		cloneArray = ll_newLinkedList();
		if(cloneArray!=NULL)
		{
			for(i=from;i<=to;i++)
			{
				aux = ll_get(this, i);
				if(aux!=NULL)
				{
					ll_add(cloneArray, aux);
				}
			}
		}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this!=NULL)
    {
		cloneArray = ll_subList(this, 0, ll_len(this));
    }
    return cloneArray;
}
/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int flagSort = 0;
    int index;
    void* firstAux;
    void* nextAux;

    if(this!=NULL && pFunc!=NULL && (order==0 || order==1))
    {
    	while(!flagSort)
    	{
    		flagSort = 1;
    		for(index=0;index<ll_len(this)-1;index++)
    		{
    			firstAux = ll_get(this, index);
				nextAux = ll_get(this, index+1);
    			if( (firstAux!=NULL && nextAux!=NULL && pFunc(firstAux,nextAux)<0 && order==0) || (pFunc(firstAux,nextAux)>0 && order==1))
    			{
    				ll_set(this, index+1, firstAux);
    				ll_set(this,index,nextAux);
    				flagSort = 0;
    				returnAux = 0;
    			}
    		}
    	}
    }
    return returnAux;
}
/** \brief Itera la lista y utiliza a la funcion criterio en cada iteracion
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
 *                      ( 0) Si ok
 */
int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int result = -1;
	int i;
	void* pElemento = NULL;

	if(this != NULL && pFunc != NULL)
	{
		for(i=0;i<ll_len(this);i++)
		{
			pElemento = ll_get(this,i);
			pFunc(pElemento);
		}
		result = 0;
	}
	return result;
}
/** \brief Mapea los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_map2(LinkedList* this, int (*pFunc)(void*,void*),void* pElement)
{
    int returnAux = -1;
    int length = ll_len(this);
    void* auxElement;
    if(this != NULL)
    {
        for(int i = 0 ; i < length ; i++)
        {
            auxElement = ll_get(this, i);
            if(pFunc(auxElement, pElement) == 0)
            {
                returnAux = 0;
            }
        }
    }
    return returnAux;
}
/*int ll_map2(LinkedList* this, int (*pFunc)(void*)) //devuelve lo que devuelve la funcion criterio (siempre un entero)
{
	int i;
	void* pElemento = NULL;
	int output;

	if(this != NULL && pFunc != NULL)
	{
		for(i=0;i<ll_len(this);i++)
		{
			pElemento = ll_get(this,i);
			output = pFunc(pElemento);
		}
	}
	return output;
}*/
/** \brief Filtra la lista usando a la funcion criterio recibida como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
 *                      ( 0) Si ok
 */
int ll_filter(LinkedList * this, int (*pFunc)(void*))
{
	int result = -1;
	void* pAux = NULL;
	int answer;
	int i;

	if(this != NULL && pFunc != NULL)
	{
		for(i=ll_len(this)-1; i >= 0; i--)
		{
			pAux = ll_get(this,i);
			if(pAux != NULL)
			{
				answer = pFunc(pAux);
				if(!answer)
				{
					result = ll_remove(this,i);
				}
			}
		}
	}
	return result;
}

/** \brief Reduce la lista a un numero (tipo Int), usando a la funcion criterio recibida como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna acum - Valor acumulado o (0) Error: si el puntero a la listas es NULL
 */
int ll_reduceInt(LinkedList* this, int (*pFunc)(void*,int), int parameter)
{
	void *pAux = NULL;
	int i;
	int acc = 0;

	if (this != NULL && pFunc != NULL)
	{
		for (i = 0; i < ll_len(this); i++)
		{
			pAux = ll_get(this, i);
			if (pAux != NULL)
			{
				acc += pFunc(pAux,parameter);
			}
		}
	}
	return acc;
}

/** \brief Reduce la lista a un numero (tipo Float), usando a la funcion criterio recibida como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return float Retorna acum - Valor acumulado o (0) Error: si el puntero a la listas es NULL
 */
float ll_reduceFloat(LinkedList* this, int (*pFunc)(void*))
{
	void* pAux = NULL;
	int i;
	float acc = 0;

	if (this != NULL && pFunc != NULL)
	{
		for (i = 0; i < ll_len(this); i++)
		{
			pAux = ll_get(this, i);
			if (pAux != NULL)
			{
				acc = acc + pFunc(pAux);
			}
		}
	}
	return acc;
}

/** \brief Filtra la lista usando a la funcion criterio recibida como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param arg void* Puntero a argumento de tipo void*
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
 *                      ( 0) Si ok
 */
int ll_filterConParametros(LinkedList * this, int (*pFunc)(void*,void*), void* parameter)
{
	int result = -1;
	void* pAux;
	int i;

	if (this != NULL && pFunc != NULL)
	{
		for (i = ll_len(this)-1; i >= 0; i--)
		{
			pAux = ll_get(this, i);
			if (pAux != NULL)
			{
				if (!pFunc(pAux,parameter))
				{
					result = ll_remove(this, i);
				}
			}
		}
	}
	return result;
}

LinkedList* ll_filterClone(LinkedList* this, int (*pFunc)(void*), int option) //preguntarle a Ernesto como castear el puntero a void a int
{
    void* aux = NULL;
    LinkedList* newList = ll_newLinkedList();

    if(this!=NULL && pFunc!=NULL && newList!=NULL && (option==1 || option==0))
    {
        for(int i=0;i<ll_len(this);i++)
        {
            aux = ll_get(this, i);
            if(aux != NULL && !pFunc(aux)) // Puede ser == 0 / == 1 dependiendo de la función criterio
            {
                ll_add(newList, aux);
            }
        }
    }
    return newList;
}
