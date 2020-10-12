/*
 ============================================================================
 Name        : labo1_primer_parcial.c
 Author      : Julia Tamasi
 Description : Primer Parcial Laboratorio I
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "Client.h"

static int cli_generateNewId(void);
static int cli_findEmptyIndex(Client* pArray, int len, int* emptyIndex);
static int cli_arrayIsEmpty (Client* pArray, int len);
static int cli_printIndex(Client* pArray, int index);
/*\brief to generate a new ID to every log generated
 */
static int cli_generateNewId(void)
{
    static int id=0;
    id = id+1;
    return id;
}

/** \brief search for an empty index for a load
 * \param pArray, Pointer to array
 * \param int len, Array lenght
 * \param int* emptyIndex, pointer to the memory space where the empty index of the array will be saved
 * \return Return (0) if OK or (-1) if there is any error
 */
static int cli_findEmptyIndex(Client* pArray, int len, int* emptyIndex)
{
	int i;
	int retorno = -1;
	if(pArray!=NULL && len>0 && emptyIndex!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==1 && pArray[i].idClient==0)
			{
				*emptyIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/** \brief To indicate that all position in the array are empty,
 * 		   and all the elements ID's are 0,
 * 		   this function put the flag (isEmpty) in TRUE in all
 * 		   position of the array
 * \param pArray, Pointer to array
 * \param int len, Array lenght
 * \return int Return (-1) if Error [invalid lenght or NULL pointer] - (0) if OK
 */
int cli_initArray(Client* pArray, int len)
{
	int i;
	int retorno = -1;
	if(pArray!=NULL && len>0)
	{
		for (i=0;i<len;i++)
		{
			pArray[i].isEmpty = 1;
			pArray[i].idClient = 0;
		}
		retorno=0;
	}
	else
	{
		printf("Error");
	}
	return retorno;
}
/** \brief To indicate that all position in the array are empty,
 * 		   and all the elements ID's are 0,
 * 		   this function put the flag (isEmpty) in TRUE in all
 * 		   position of the array
 * \param pArray, Pointer to array
 * \param int len, Array lenght
 * \return int Return (-1) if Error [invalid lenght or NULL pointer] - (0) if OK
 */
int cli_addElement(Client* pArray, int len)
{
	int result = -1;
	Client bufferClient;
	int index;
	if(pArray != NULL && len>0 && cli_findEmptyIndex(pArray, len, &index)==0 && index >= 0 && index < len)
	{
		if( utn_getName("Nombre?\n", "Error\n", bufferClient.name, RETRIES, NAME_LEN)==0 &&
			utn_getName("Apellido?\n", "Error\n", bufferClient.lastName, RETRIES, NAME_LEN)==0 &&
			utn_getCuit("Ingrese su cuit\n", "Error\n", bufferClient.cuit, CUIT_LEN, RETRIES)==0)
		{
			bufferClient.isEmpty = 0;
			bufferClient.idClient = cli_generateNewId();
			pArray[index] = bufferClient;
			result = 0;
		}
	}
	return result;
}
/* \brief Modifies element data
 * \param pArray, Pointer to array
 * \param int len, Array limit
 * \return [0] if ok / [-1] if error
 */
int cli_modifyClient (Client* pArray, int len)
{
	int result = -1;
	int auxId;
	int bufferIndex;
	int chosenOption;

	if( pArray!=NULL && len>0 && cli_printArray(pArray, len)==0 && utn_getNumber("\n\nPor favor ingrese el Id del registro que desea modificar:\n",&auxId,RETRIES,INT_MAX,1)==0 &&
		cli_arrayIsEmpty(pArray, len)==0)
	{
		bufferIndex = cli_findIndexById(pArray, len, auxId);
		if(bufferIndex>=0)
		{
			cli_printIndex(pArray, bufferIndex);
			do
			{
				if( utn_getNumber("¿Que campo del registro desea modificar?\n[1] Nombre\n[2] Apellido\n[3] Cuit\n[4] Volver al menu\n", &chosenOption, RETRIES, 4, 1)==0)
				{
					switch(chosenOption)
					{
						case 1:
						{
								if(utn_getName("Por favor, ingrese el nombre del empleado:\n", "ERROR. Ingrese un nombre valido\n", pArray[bufferIndex].name, RETRIES, NAME_LEN)==0)
								{
									printf("¡Nombre ingresado con exito!\nNombre: %s\n", pArray[bufferIndex].name);
									result = 0;
								}
								else
								{
									printf("Error");
								}
								break;
						}
						case 2:
						{
								if(utn_getName("Por favor, ingrese el apellido del empleado:\n", "ERROR. Ingrese un apellido valido\n", pArray[bufferIndex].lastName, RETRIES, NAME_LEN)==0)
								{
									printf("¡Apellido ingresado con exito!\nApellido: %s\n", pArray[bufferIndex].lastName);
									result = 0;
								}
								else
								{
									printf("Error");
								}
								break;
						}
						case 3:
						{
								if(utn_getCuit("Ingrese el cuit del cliente\n", "ERROR. Ingrese un cuit valido\n", pArray[bufferIndex].cuit, CUIT_LEN, RETRIES)==0)
								{
									printf("¡CUIT ingresado con exito!\nSueldo: %s\n", pArray[bufferIndex].cuit);
									result = 0;
								}
								else
								{
									printf("Error");
								}
								break;
						}
					}
				}

			}while(chosenOption!=4);
		}
		else
		{
			printf("Error\n");
		}
	}
	else
	{
		printf("Error\n");
	}
	return result;
}
/* \brief print the content of the array
 * \param pArray, Pointer to array
 * \param int len, Limit of array
 * \return [0] if ok / [1] if error
 */
int cli_printArray(Client* pArray, int len)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && len>=0 && cli_arrayIsEmpty(pArray, len)==0)
	{
		printf("\n***************************** CLIENTES *********************************\n");
		printf("\n------------------------------------------------------------------------\n");
		printf("      APELLIDO      |       NOMBRE       |   ID   |      CUIT    ");
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 0)
			{
				printf( "\n------------------------------------------------------------------------\n"
						"%-20s|%-20s|%-8d|%-17s\n"
					    "------------------------------------------------------------------------\n",pArray[i].lastName,pArray[i].name, pArray[i].idClient, pArray[i].cuit);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/**
 * \brief Function to find out if the array is completely empty
 * \param pArray, Pointer to array
 * \param int len, Length of the array
 * \return (1) if array is empty, (0) if there is at least one full position
 */
static int cli_arrayIsEmpty (Client* pArray, int len)
{
	int i;
	int result = 1;
	if(pArray!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0)
			{
				result = 0;
				break;
			}
		}
	}
	return result;
}
/* \brief print the content of a specific array index
 * \param pArray, Pointer to array
 * \param int index, Index of the array from which the data will be printed
 * \return [0] if ok / [1] if error
 */
static int cli_printIndex(Client* pArray, int index)
{
	int retorno = -1;
	if(pArray!=NULL && index>=0)
	{
			if(pArray[index].isEmpty == 0)
			{
				printf("\n----------------------------------------------------------------------------------\n"
						"%-20s|%-20s|%-8d|%-17s|\n"
						"----------------------------------------------------------------------------------\n",pArray[index].lastName, pArray[index].name, pArray[index].idClient, pArray[index].cuit);
				retorno=0;
			}
	}
	return retorno;
}
/** \brief find an index by ID
 * \param pArray, Pointer to arra
 * \param int len, Array lenght
 * \param int id, Id of the element sought
 * \return Return id's index position or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
int cli_findIndexById(Client* pArray, int len, int id)
{
	int i;
	int result = -1;
	if(pArray!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].idClient==id && pArray[i].isEmpty==0)
			{
				result = i;
				break;
			}
		}
	}
	return result;
}
/* \ brief logically unsubscribe an element of array (put isEmpty Flag in TRUE)
 * \param pArray, pointer to array
 * \param int len, limit of array
 * \param int id, id of specific element
 * \ returns int Return [-1] if Error - [0] if Ok
 */
int cli_removeClient(Client* pArray, int len, int idClient)
{
	int result = -1;
	int bufferIndex;
	int answer;
	if( pArray!=NULL && len>0 && cli_arrayIsEmpty(pArray, len)==0 && utn_getNumber("\nDesea eliminar este cliente?\n[1] Si\n[2] No\n", &answer, RETRIES, 2, 1)==0 &&
		answer==1)
	{
		bufferIndex = cli_findIndexById(pArray, len, idClient);
		if(bufferIndex>=0 && pArray[bufferIndex].isEmpty==0)
		{
			pArray[bufferIndex].isEmpty = 1;
			result = 0;
		}
	}
	return result;
}
