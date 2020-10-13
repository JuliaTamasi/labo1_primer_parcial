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
static int ad_findEmptyIndex(Advertisement* pArray, int len, int* emptyIndex);
static int ad_printIndex(Advertisement* pArray, int index);
static int ad_searchForActive(Advertisement* arrayAds, int len);
static int ad_printArray(Advertisement* pArray, int len);

/*\brief to generate a new ID to every log generated
 */
static int ad_generateNewId(void)
{
    static int id=0;
    id = id+1;
    return id;
}
/* \brief print the content of a specific array index
 * \param pArray, Pointer to array
 * \param int index, Index of the array from which the data will be printed
 * \return [0] if ok / [-1] if error
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
/** \brief search for an empty index for a load
 * \param pArray, Pointer to Ads's array
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
/**
 * \brief Function to search in the advertisement array if there's any active
 * \param Advertisement* arrayAds: Pointer to an Advertisement array
 * \param int len: Length of the array
 * \return (1) is there any active field TRUE or (0) if not
 */
static int ad_searchForActive(Advertisement* arrayAds, int len)
{
	int retornar = 0;
	if(arrayAds != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(arrayAds[i].status == ACTIVE)
			{
				retornar = 1;
				break;
			}
		}
	}
	return retornar;
}
/* \brief print the content of the ads's array
 * \param pArray, Pointer to array
 * \param int len, Limit of array
 * \return [0] if ok / [1] if error
 */
static int ad_printArray(Advertisement* pArray, int len)
{
	int retorno = -1;
	int i;
	if(pArray!=NULL && len>=0 && ad_arrayIsEmpty(pArray, len)==0)
	{
		printf("\n********************************************** AVISOS *******************************************************\n");
		printf("\n-------------------------------------------------------------------------------------------------------------\n");
		printf("ID CLIENTE |   RUBRO   | DESCRIPCION                                                      |  ESTADO  |  ID  |");
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty == 0 && pArray[i].idAd>0)
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
/** \brief To register a new advertisement
 * \param pArray, Pointer to Add's array
 * \param int len, Ads's array lenght
 * \param Client* Aclients, pointer to Clients's array
 * \param int lenClients, Clients's array lenght
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
			utn_getStringAlphanumeric("- Ingrese el texto del aviso ((máximo 64 caracteres)) -\n", "Error\n", bufferAd.adText, RETRIES, NAME_LEN)==0 &&
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
/**
 * \brief Function to find out if the ads's array is completely empty
 * \param pArray, Pointer to array
 * \param int len, Length of the array
 * \return (1) if array is empty, (0) if there is at least one full position
 */
int ad_arrayIsEmpty (Advertisement* pArray, int len)
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
/* \brief print the ads of a specific client ID
 * \param Advertisement* pArray, Pointer to array
 * \param int len, Lenght of array
 * \param int idClient, client ID from which data should be printed
 * \return [0] if ok / [1] if error
 */
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
	else
	{
		printf("[Este cliente no posee ninguna publicación]\n\n");
		result = 0;
	}
	return result;
}
/* \ brief logically unsubscribe a specific client's advertisement (put isEmpty Flag in TRUE)
 * \param Advertisement* pArray, pointer to ads's array
 * \param int len, limit of ads's array
 * \param int idClient, id of the client which the ads to be deleted belong
 * \ returns int Return [-1] if Error - [0] if Ok
 */
int ad_removeAd(Advertisement* pArray, int len, int idClient)
{
	int result = -1;
	int i;
	if(pArray!=NULL && len>0 && ad_arrayIsEmpty(pArray, len)==0 && idClient>0)
	{
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
/* \ brief modifies the "status" field of an Ad. If chosenOption = 5 modifies status to PAUSED. If chosenOption = 6, modifies status to ACTIVE.
 * \param Advertisement* pArray, pointer to ads's array
 * \param int len, limit of ads's array
 * \param Client* aClients, pointer to Clients's array
 * \param int lenClients, length of Clients's array
 * \param int chosenOption, menu option chosen by the user
 * \ returns int Return [-1] if Error - [0] if Ok
 */
int ad_status(Advertisement *pArray, int len, Client *aClients, int lenClients, int chosenOption)
{
    int result = -1;
	int bufferIdAd;
    int answer;
    int bufferIndexAd;
    int bufferIndexClient;

    if ( pArray != NULL && len > 0 && aClients != NULL && lenClients > 0 && ad_printArray(pArray, len)==0 &&
    	 utn_getNumber("[Ingresá el ID del aviso que deseas modificar]\n", &bufferIdAd, RETRIES,INT_MAX, 1)==0 &&
		 ad_findIndexById(pArray, len, bufferIdAd)>-1)
    {
    	bufferIndexAd = ad_findIndexById(pArray, len, bufferIdAd);
    	bufferIndexClient = cli_findIndexById(aClients, lenClients, pArray[bufferIndexAd].idClient);
    	cli_printIndex(aClients, bufferIndexClient);
        if (chosenOption == 5 && ad_searchForActive(pArray, len)==1)
        {
        	if (utn_getNumber("\n[¿Deseás pausar este aviso?]\n[1]- Si\n[2]- No\n", &answer, RETRIES, 2, 1)==0 && answer==1 && pArray[bufferIndexAd].status == ACTIVE)
        	{
        		pArray[bufferIndexAd].status = PAUSED;
        		result = 0;
            }
        }
        else
        {
            if (chosenOption == 6 && ad_searchForActive(pArray, len)==0)
            {
				if (utn_getNumber("\n[¿Deseás reanudar este aviso?]\n[1]- Si\n[2]- No\n", &answer, RETRIES, 2, 1) == 0 && answer == 1 && pArray[bufferIndexAd].status == PAUSED)
				{
					pArray[bufferIndexAd].status = ACTIVE;
					result = 0;
				}
            }
        }
    }
    return result;
}
/** \brief find an index by ad's ID
 * \param Advertisement* pArray, Pointer to ads's array
 * \param int len, Array lenght
 * \param int id, Id of the element sought
 * \return Return id's index position or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
int ad_findIndexById(Advertisement* pArray, int len, int id)
{
	int i;
	int result = -1;
	if(pArray!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].idAd==id && pArray[i].isEmpty==0 &&(pArray[i].status == ACTIVE || pArray[i].status==PAUSED))
			{
				result = i;
				break;
			}
		}
	}
	return result;
}
