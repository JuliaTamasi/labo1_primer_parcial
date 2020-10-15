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
static int ad_findEmptyIndex(Advertisement* arrayAds, int len, int* emptyIndex);
static int ad_printIndex(Advertisement* arrayAds, int index);
static int ad_printArray(Advertisement* arrayAds, int len);
static int ad_addData(Advertisement* pArrayAds, int lenAds,int area, char* ad_text, int idClient);

/*\brief to generate a new ID to every log generated
 */
static int ad_generateNewId(void)
{
    static int id=0;
    id = id+1;
    return id;
}
/* \brief print the content of a specific array index
 * \param arrayAds, Pointer to array
 * \param int index, Index of the array from which the data will be printed
 * \return [0] if ok / [-1] if error
 */
static int ad_printIndex(Advertisement* arrayAds, int index)
{
	int result = -1;
	char adStatus[7];
	if(arrayAds!=NULL && index>=0)
	{
			if(arrayAds[index].isEmpty == 0)
			{
				if(arrayAds[index].status==1)
				{
					strncpy(adStatus,"ACTIVE",7);
				}
				else
				{
					strncpy(adStatus,"PAUSED",7);
				}
				printf("\n***************************************** ¡AVISO CARGADO EXITOSAMENTE! ******************************************\n");
				printf("\n-----------------------------------------------------------------------------------------------------------------\n");
				printf("ID CLIENTE |   RUBRO   | DESCRIPCION                                                      |    ESTADO    |  ID  |");
				printf("\n-----------------------------------------------------------------------------------------------------------------\n");
				printf("%-11d| %-10d| %-65s| %-13s| %-5d|\n"
				"-----------------------------------------------------------------------------------------------------------------\n",arrayAds[index].idClient,arrayAds[index].area,arrayAds[index].adText,adStatus,arrayAds[index].idAd);
				result=0;
			}
	}
	return result;
}
/** \brief search for an empty index for a load
 * \param arrayAds, Pointer to Ads's array
 * \param int len, Array lenght
 * \param int* emptyIndex, pointer to the memory space where the empty index of the array will be saved
 * \return Return (0) if OK or (-1) if there is any error
 */
static int ad_findEmptyIndex(Advertisement* arrayAds, int len, int* emptyIndex)
{
	int i;
	int retorno = -1;
	if(arrayAds!=NULL && len>0 && emptyIndex!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty==1 && arrayAds[i].idClient==0)
			{
				*emptyIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/* \brief print the content of the ads's array
 * \param arrayAds, Pointer to array
 * \param int len, Limit of array
 * \return [0] if ok / [1] if error
 */
static int ad_printArray(Advertisement* arrayAds, int len)
{
	int retorno = -1;
	int i;
	char adStatus[7];
	if(arrayAds!=NULL && len>=0 && ad_arrayIsEmpty(arrayAds, len)==0)
	{
		printf("\n************************************************ AVISOS *********************************************************\n");
		printf("\n-----------------------------------------------------------------------------------------------------------------\n");
		printf("ID CLIENTE |   RUBRO   | DESCRIPCION                                                      |    ESTADO    |  ID  |");
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty == 0 && arrayAds[i].idAd>0)
			{
				if(arrayAds[i].status==1)
				{
					strncpy(adStatus,"ACTIVE",7);
				}
				else
				{
					strncpy(adStatus,"PAUSED",7);
				}
				printf( "\n-----------------------------------------------------------------------------------------------------------------\n"
						"%-11d| %-10d| %-65s| %-13s| %-5d|\n"
					    "-----------------------------------------------------------------------------------------------------------------\n",arrayAds[i].idClient,arrayAds[i].area,arrayAds[i].adText,adStatus,arrayAds[i].idAd);
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
 * \param arrayAds, Pointer to array
 * \param int len, Array lenght
 * \return int Return (-1) if Error [invalid lenght or NULL pointer] - (0) if OK
 */
int ad_initArray(Advertisement* arrayAds, int len)
{
	int i;
	int retorno = -1;
	if(arrayAds!=NULL && len>0)
	{
		for (i=0;i<len;i++)
		{
			arrayAds[i].isEmpty = 1;
			arrayAds[i].idAd = 0;
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
 * \param arrayAds, Pointer to Add's array
 * \param int len, Ads's array lenght
 * \param Client* Aclients, pointer to Clients's array
 * \param int lenClients, Clients's array lenght
 * \return int Return (-1) if Error [invalid lenght or NULL pointer] - (0) if OK
 */
int ad_addElement(Advertisement* arrayAds, int len, Client* AClients, int lenClients)
{
	int result = -1;
	Advertisement bufferAd;
	int index;
	if( arrayAds != NULL && len>0 && ad_findEmptyIndex(arrayAds, len, &index)==0 && index >= 0 && index < len &&
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
			arrayAds[index] = bufferAd;
			ad_printIndex(arrayAds, index);
			result = 0;
		}
		else
		{
			printf("[Debe ingresar un ID valido]\n");
		}
	}
	return result;
}
/**
 * \brief Function to find out if the ads's array is completely empty
 * \param arrayAds, Pointer to array
 * \param int len, Length of the array
 * \return (1) if array is empty, (0) if there is at least one full position
 */
int ad_arrayIsEmpty (Advertisement* arrayAds, int len)
{
	int i;
	int result = 1;
	if(arrayAds!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty==0)
			{
				result = 0;
				break;
			}
		}
	}
	return result;
}
/* \brief print the ads of a specific client ID
 * \param Advertisement* arrayAds, Pointer to array
 * \param int len, Lenght of array
 * \param int idClient, client ID from which data should be printed
 * \return [0] if ok / [1] if error
 */
int ad_printByClientId(Advertisement* arrayAds, int len, int idClient)
{
	int result = -1;
	int i;
	char adStatus[7];
	if(arrayAds!=NULL && len>0 && idClient>0 && ad_arrayIsEmpty(arrayAds, len)==0)
	{
		printf("\n****************************************** PUBLICACIONES DEL CLIENTE ********************************************\n");
		printf("ID CLIENTE |   RUBRO   | DESCRIPCION                                                      |    ESTADO    |  ID  |");
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty==0 && arrayAds[i].idClient == idClient)
			{
				if(arrayAds[i].status == 1)
				{
					strncpy(adStatus,"ACTIVE",7);
				}
				else
				{
					strncpy(adStatus,"PAUSED",7);
				}
				printf("\n-----------------------------------------------------------------------------------------------------------------\n");
				printf("%-11d| %-10d| %-65s| %-13s| %-5d|\n"
				"-----------------------------------------------------------------------------------------------------------------\n",arrayAds[i].idClient,arrayAds[i].area,arrayAds[i].adText,adStatus,arrayAds[i].idAd);
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
 * \param Advertisement* arrayAds, pointer to ads's array
 * \param int len, limit of ads's array
 * \param int idClient, id of the client which the ads to be deleted belong
 * \ returns int Return [-1] if Error - [0] if Ok
 */
int ad_removeAd(Advertisement* arrayAds, int len, int idClient)
{
	int result = -1;
	int i;
	int answer;
	if( arrayAds!=NULL && len>0 && idClient>0 && utn_getNumber("\nDesea eliminar este cliente y todas sus publicaciones?\n[1] Si\n[2] No\n", &answer, RETRIES, 2, 1)==0 &&
		answer==1)
	{
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty==0 && arrayAds[i].idClient == idClient)
			{
				arrayAds[i].isEmpty = 1;
				result = 0;
			}
			else
			{
				printf("[Eliminando el cliente...]\n\n");
				result = 0;
				break;
			}
		}
	}
	else
	{
		if(answer==2)
		{
			printf("[Volviendo al menú...]\n");
		}
	}
	return result;
}
/* \ brief modifies the "status" field of an Ad. If chosenOption = 5 modifies status to PAUSED. If chosenOption = 6, modifies status to ACTIVE.
 * \param Advertisement* arrayAds, pointer to ads's array
 * \param int len, limit of ads's array
 * \param Client* aClients, pointer to Clients's array
 * \param int lenClients, length of Clients's array
 * \param int chosenOption, menu option chosen by the user
 * \ returns int Return [-1] if Error - [0] if Ok
 */
int ad_status(Advertisement *arrayAds, int len, Client *aClients, int lenClients, int chosenOption)
{
    int result = -1;
	int bufferIdAd;
    int answer;
    int bufferIndexAd;
    int bufferIndexClient;

    if ( arrayAds != NULL && len > 0 && aClients != NULL && lenClients > 0 && ad_printArray(arrayAds, len)==0 &&
    	 utn_getNumber("[Ingresá el ID del aviso que deseas modificar]\n", &bufferIdAd, RETRIES,INT_MAX, 1)==0 &&
		 ad_findIndexById(arrayAds, len, bufferIdAd)>-1)
    {
    	bufferIndexAd = ad_findIndexById(arrayAds, len, bufferIdAd);
    	bufferIndexClient = cli_findIndexById(aClients, lenClients, arrayAds[bufferIndexAd].idClient);
        if (chosenOption == 5)
        {
        	if ( arrayAds[bufferIndexAd].status==ACTIVE && cli_printIndex(aClients, bufferIndexClient)==0 && utn_getNumber("\n[¿Deseás pausar este aviso?]\n[1]- Si\n[2]- No\n", &answer, RETRIES, 2, 1)==0 &&
        		 answer==1)
        	{
        		arrayAds[bufferIndexAd].status = PAUSED;
        		result = 0;
            }
        	else
        	{
        		if(answer==2)
        		{
        			printf("[Volviendo al menú...]\n");
        		}
        		else
        		{
					printf("[Esta publicación ya está pausada]\n");
        		}
        	}
        }
        else
        {
            if (chosenOption == 6)
            {
				if ( arrayAds[bufferIndexAd].status==PAUSED && cli_printIndex(aClients, bufferIndexClient)==0 && utn_getNumber("\n[¿Deseás reanudar este aviso?]\n[1]- Si\n[2]- No\n", &answer, RETRIES, 2, 1) == 0 &&
					 answer == 1)
				{
					arrayAds[bufferIndexAd].status = ACTIVE;
					result = 0;
				}
				else
				{
					if(answer==2)
					{
	        			printf("[Volviendo al menú...]\n");
					}
					else
					{
						printf("[Esta publicación ya esta activa]\n\n");
					}
				}
            }
        }
    }
    return result;
}
/** \brief find an index by ad's ID
 * \param Advertisement* arrayAds, Pointer to ads's array
 * \param int len, Array lenght
 * \param int id, Id of the element sought
 * \return Return id's index position or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
int ad_findIndexById(Advertisement* arrayAds, int len, int id)
{
	int i;
	int result = -1;
	if(arrayAds!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].idAd==id && arrayAds[i].isEmpty==0 &&(arrayAds[i].status == ACTIVE || arrayAds[i].status==PAUSED))
			{
				result = i;
				break;
			}
		}
	}
	return result;
}
//HARDCODEO
int ad_addHardcode(Advertisement* pArrayAds, int lenAds)
{
	int result = -1;
	if(pArrayAds != NULL && lenAds >0)
	{
		int ad_area[6]={3,2,2,1,4,2};
		char ad_text[7][AD_LEN]={ "Se vende heladera.5000. Llamar a 1235480",
								  "Venta Ford Ka. 30.000 KM. Tel: 3245546",
								  "Feria americana en Lanus. Interesados comunicarse al 467654.",
								  "Se busca camarera para turno noche. Tel: 247458965.",
								  "Busco novio, el mio me dejo ayer. Besitos.",
								  "Deje el piano por la programacion."};
		int ad_idCliente[]={5, 4, 3, 3, 1, 1};
		for(int i = 0; i < 6; i++)
		{
			ad_addData(pArrayAds, lenAds, ad_area[i], ad_text[i], ad_idCliente[i]);
			result = 0;
		}
	}
	return result;
}
static int ad_addData(Advertisement* pArrayAds, int lenAds,int area, char* ad_text, int idClient)
{
	int result = -1;
	int emptyIndex;

	if(pArrayAds != NULL && lenAds >0 && ad_text != NULL && idClient>0)
	{
		if(ad_findEmptyIndex(pArrayAds, lenAds, &emptyIndex)==0)
		{
				pArrayAds[emptyIndex].idAd = ad_generateNewId();
				pArrayAds[emptyIndex].isEmpty = 0;
				pArrayAds[emptyIndex].status = ACTIVE;
				pArrayAds[emptyIndex].area = area;
				strncpy(pArrayAds[emptyIndex].adText,ad_text,AD_LEN);
				pArrayAds[emptyIndex].idClient = idClient;
				result=0;
		}
	}
    return result;
}
