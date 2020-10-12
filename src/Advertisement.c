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
#include "Advertisement.h"
#include "utn.h"

static int ad_generateNewId(void);
static int ad_arrayIsEmpty (Advertisement* pArray, int len);
static int ad_findEmptyIndex(Advertisement* pArray, int len, int* emptyIndex);
static int ad_printIndex(Advertisement* pArray, int index);
/*\brief to generate a new ID to every log generated
 */
static int ad_generateNewId(void)
{
    static int id=0;
    id = id+1;
    return id;
}
/** \brief To indicate that all position in the array are empty,
 * 		   and all the elements ID's are 0,
 * 		   this function put the flag (isEmpty) in TRUE in all
 * 		   position of the array
 * \param pArray, Pointer to array
 * \param int len, Array lenght
 * \return int Return (-1) if Error [invalid lenght or NULL pointer] - (0) if OK
 */
int ad_addElement(Advertisement* pArray, int len, Client* AClients, int lenClients)
{
	int result = -1;
	Advertisement bufferAd;
	int index;
	if( pArray != NULL && len>0 && ad_findEmptyIndex(pArray, len, &index)==0 && index >= 0 && index < len &&
		cli_printArray(AClients, lenClients)==0)
	{
		if( utn_getNumber("- Ingrese el ID del cliente -\n", &bufferAd.idClient, RETRIES, INT_MAX, 1)==0 &&
			cli_findIndexById(AClients, lenClients, bufferAd.idClient)>-1 &&
			utn_getName("- Ingrese el texto del aviso ((máximo 64 caracteres)) -\n", "Error\n", bufferAd.adText, RETRIES, NAME_LEN)==0 &&
			utn_getNumber("- Ingrese el numero de rubro del aviso -\n", &bufferAd.area, RETRIES, INT_MAX, 0)==0)
		{
			bufferAd.isEmpty = 0;
			bufferAd.idAd = ad_generateNewId();
			bufferAd.status = ACTIVE;
			pArray[index] = bufferAd;
			ad_printIndex(pArray, index);
			result = 0;
		}
	}
	return result;
}
/** \brief search for an empty index for a load
 * \param pArray, Pointer to array
 * \param int len, Array lenght
 * \param int* emptyIndex, pointer to the memory space where the empty index of the array will be saved
 * \return Return (0) if OK or (-1) if there is any error
 */
static int ad_findEmptyIndex(Advertisement* pArray, int len, int* emptyIndex)
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
/* \brief print the content of the array
 * \param pArray, Pointer to array
 * \param int len, Limit of array
 * \return [0] if ok / [1] if error
 */
int ad_printArray(Advertisement* pArray, int len)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && len>=0 && ad_arrayIsEmpty(pArray, len)==0)
	{
		printf("\n********************************************* AVISOS ACTIVOS ************************************************\n");
		printf("\n-------------------------------------------------------------------------------------------------------------\n");
		printf("ID CLIENTE |   RUBRO   | DESCRIPCION                                                      |  ESTADO  |  ID  |");
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 0 && pArray[i].idAd>0 && pArray[i].status == ACTIVE)
			{
				printf( "\n-------------------------------------------------------------------------------------------------------------\n"
						"%-11d| %-10d| %-65s| %-9d| %-5d|\n"
					    "-------------------------------------------------------------------------------------------------------------\n",pArray[i].idClient,pArray[i].area,pArray[i].adText,pArray[i].status,pArray[i].idAd);
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
static int ad_arrayIsEmpty (Advertisement* pArray, int len)
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
/** \brief To indicate that all position in the array are empty,
 * 		   and all the elements ID's are 0,
 * 		   this function put the flag (isEmpty) in TRUE in all
 * 		   position of the array
 * \param pArray, Pointer to array
 * \param int len, Array lenght
 * \return int Return (-1) if Error [invalid lenght or NULL pointer] - (0) if OK
 */
int ad_initArray(Advertisement* pArray, int len)
{
	int i;
	int retorno = -1;
	if(pArray!=NULL && len>0)
	{
		for (i=0;i<len;i++)
		{
			pArray[i].isEmpty = 1;
			pArray[i].idAd = 0;
		}
		retorno=0;
	}
	else
	{
		printf("Error");
	}
	return retorno;
}
/* \brief print the content of a specific array index
 * \param pArray, Pointer to array
 * \param int index, Index of the array from which the data will be printed
 * \return [0] if ok / [1] if error
 */
static int ad_printIndex(Advertisement* pArray, int index)
{
	int result = -1;
	if(pArray!=NULL && index>=0)
	{
			if(pArray[index].isEmpty == 0)
			{
				printf("\n*************************************** ¡AVISO CARGADO EXITOSAMENTE! ****************************************\n");
				printf("\n-------------------------------------------------------------------------------------------------------------\n");
				printf("ID CLIENTE |   RUBRO   | DESCRIPCION                                                      |  ESTADO  |  ID  |");
				printf("\n-------------------------------------------------------------------------------------------------------------\n");
				printf("%-11d| %-10d| %-65s| %-9d| %-5d|\n"
				"-------------------------------------------------------------------------------------------------------------\n",pArray[index].idClient,pArray[index].area,pArray[index].adText,pArray[index].status,pArray[index].idAd);
				result=0;
			}
	}
	return result;
}
int ad_printByClientId(Advertisement* pArray, int len, int idClient)
{
	int result = -1;
	int i;
	if(pArray!=NULL && len>0 && idClient>0 && ad_arrayIsEmpty(pArray, len)==0)
	{
		printf("\n**************************************** PUBLICACIONES DEL CLIENTE ******************************************\n");
		printf("ID CLIENTE |   RUBRO   | DESCRIPCION                                                      |  ESTADO  |  ID  |");
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0 && pArray[i].idClient == idClient)
			{
				printf("\n-------------------------------------------------------------------------------------------------------------\n");
				printf("%-11d| %-10d| %-65s| %-9d| %-5d|\n"
				"-------------------------------------------------------------------------------------------------------------\n",pArray[i].idClient,pArray[i].area,pArray[i].adText,pArray[i].status,pArray[i].idAd);
				result = 0;
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
int ad_removeAd(Advertisement* pArray, int len, int idClient)
{
	int result = -1;
	int i;
	//int bufferIndex;
	if(pArray!=NULL && len>0 && ad_arrayIsEmpty(pArray, len)==0 && idClient>0)
	{
		//bufferIndex = ad_findIndexById(pArray, len, idClient);
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0 && pArray[i].idClient == idClient)
			{
				pArray[i].isEmpty = 1;
				result = 0;
			}
		}
	}
	return result;
}
