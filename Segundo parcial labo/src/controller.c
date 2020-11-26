#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "LinkedList.h"
#include "controller.h"
#include "Client.h"
#include "Sale.h"
#include "utn.h"
#include "parser.h"


int controller_loadClientFromText(char* path , LinkedList* pArrayListClient)
{
	int result = -1;
	FILE* pFile;

	if(path!=NULL && pArrayListClient!=NULL)
	{
		pFile = fopen(path,"r");
		if(pFile!=NULL && !parser_clientFromText(pFile, pArrayListClient))
		{
			result = 0;
		}
		else
		{
			printf("[No se pudo abrir el archivo de manera correcta]\n");
		}
		fclose(pFile);
	}
	return result;
}

int controller_loadSaleFromText(char* path , LinkedList* pArrayListSale)
{
	int result = -1;
	FILE* pFile;

	if(path!=NULL && pArrayListSale!=NULL)
	{
		pFile = fopen(path,"r");
		if(pFile!=NULL && !parser_saleFromText(pFile, pArrayListSale))
		{
			result = 0;
		}
		else
		{
			printf("[No se pudo abrir el archivo correctamente]\n");
		}
		fclose(pFile);
	}
	return result;
}

int controller_listClient(LinkedList* pArrayListClient)
{
	int result = -1;
	int len;
	int i;

	if(pArrayListClient!=NULL && !ll_isEmpty(pArrayListClient))
	{
		len = ll_len(pArrayListClient);
		client_printHeader();
		for (i=0;i<len;i++)
		{
			if(!client_printByIndex(pArrayListClient, i))
			{
				result = 0;
			}
		}
	}
    return result;
}

int controller_listSale(LinkedList* pArrayListSale)
{
	int result = -1;
	int len;
	int i;

	if(pArrayListSale!=NULL && !ll_isEmpty(pArrayListSale))
	{
		len = ll_len(pArrayListSale);
		sale_printHeader();
		for (i=0;i<len;i++)
		{
			if(!sale_printByIndex(pArrayListSale, i))
			{
				result = 0;
			}
		}
	}
    return result;
}

int controller_addClient(LinkedList* pArrayListClients)
{
	int result = -1;
	Client bufferClient;
	Client* pClient;

	if(pArrayListClients!=NULL)
	{
		pClient = client_new();
		if( pClient!=NULL &&
			!utn_getName("[Ingrese el nombre del cliente]\n", "[Error. Ingrese un nombre valido]\n", bufferClient.name, RETRIES, NAME_LEN) &&
			!utn_getName("[Ingresa el apellido del cliente]\n", "[Error. Ingrese un apellido valido]\n", bufferClient.lastName, RETRIES, NAME_LEN) &&
			!utn_getCuit("[Ingrese el CUIT del cliente]\n", "[Error. Ingrese un CUIT valido]\n", bufferClient.cuit, CUIT_LEN, RETRIES) &&
			client_findByCuit(pArrayListClients, bufferClient.cuit)!=0)
		{
			bufferClient.idClient = client_searchMaxId(pArrayListClients);
			if(bufferClient.idClient>0)
			{
				pClient = client_newWithParameters(bufferClient.idClient, bufferClient.name, bufferClient.lastName, bufferClient.cuit);
				if(pClient!=NULL)
				{
					ll_add(pArrayListClients, pClient);
					printf("\n[ID para el nuevo cliente: %d]\n", bufferClient.idClient);
					result = 0;
				}
			}
		}
	}
    return result;
}
int controller_addSale(LinkedList* pArrayListSales, LinkedList* pArrayListClients)
{
	int result = -1;
	Sale bufferSale;
	Sale* pSale;

	if(pArrayListSales!=NULL)
	{
		pSale = sale_new();
		if( pSale!=NULL && !controller_listClient(pArrayListClients) &&
			!utn_getNumber("[Ingrese el ID del cliente]\n", &bufferSale.idClient, RETRIES, INT_MAX,1) &&
			!utn_getNumber("[Ingrese la cantidad de afiches que desea comprar]\n", &bufferSale.qtyPosters,RETRIES,INT_MAX,1) &&
			!utn_getName("[Ingrese el nombre del archivo con la imagen del afiche]\n", "[ERROR. Ingrese un nombre valido]", bufferSale.fileName, RETRIES, NAME_LEN) &&
			!utn_getNumber("Ingrese la zona donde se pegará el/los afiche/s\n[1] CABA\n[2] ZONA SUR\n[3] ZONA OESTE\n", &bufferSale.posterArea, RETRIES, 3, 1))
		{
			bufferSale.idSale = sale_searchMaxId(pArrayListSales);
			bufferSale.status = UNPAID;
			if(bufferSale.idSale>0)
			{
				pSale = sale_newWithParameters(bufferSale.idSale, bufferSale.idClient, bufferSale.qtyPosters, bufferSale.fileName, bufferSale.posterArea, bufferSale.status);
				ll_add(pArrayListSales, pSale);
				printf("\nID de venta: %d\n", bufferSale.idSale);
				result = 0;
			}
		}
	}
    return result;
}

int controller_modifySale(LinkedList* pArrayListSales, LinkedList* pArrayListClients, int option)
{
	int output = -1;
	LinkedList* auxiliar;
	Sale* auxSale;
	int bufferIdSale;
	int bufferIdClient;
	int indexSale;
	int buffer;
	int indexClient;

	if(pArrayListSales!=NULL && pArrayListClients!=NULL && !ll_isEmpty(pArrayListSales))
	{
		auxiliar = ll_filterClone(pArrayListSales, sale_fCriterioFilterUnpaid,UNPAID);
		if( auxiliar != NULL && !controller_listSale(auxiliar) &&
			!utn_getNumber("[Ingrese el ID de la venta que desea modificar]\n", &bufferIdSale, RETRIES, INT_MAX, 1) &&
			!sale_findIndexById(pArrayListSales, bufferIdSale, &indexSale) &&
			sale_findIndexById(auxiliar, bufferIdSale, &buffer)!=-1)
		{
			auxSale = ll_get(pArrayListSales, indexSale);
			client_printHeader();
			if( auxSale!=NULL && !sale_getIdClient(auxSale, &bufferIdClient) &&
				!client_findIndexById(pArrayListClients, bufferIdClient, &indexClient) &&
				!client_printByIndex(pArrayListClients, indexClient) &&
				option==3)
			{
				 output = sale_editFields(auxSale);
			}
			else if(option==4)
			{
				output = sale_editStatus(auxSale);
			}
		}
	}
	else
	{
		printf("[Debe cargar el archivo o dar de alta una venta antes de intentar modificar]\n");
	}
	return output;
}

int controller_saveClientAsText(char* path, LinkedList* clientList)
{
	int retornar=-1;
	FILE* pFile;
	Client* bufferClient;
	int bufferId;
	char bufferName [NAME_CLIENT_LEN];
	char bufferLastName [NAME_CLIENT_LEN];
	char bufferCuit [CUIT_LEN];
	if(path!=NULL && clientList!=NULL)
	{
		pFile = fopen(path, "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id,nombre,apellido,cuit\n");
			retornar=0;
			for(int i=0;i<ll_len(clientList);i++)
			{
				bufferClient = ll_get(clientList, i);
				if(bufferClient!=NULL)
				{
					if( !client_getIdClient(bufferClient, &bufferId) && !client_getName(bufferClient, bufferName) &&
						!client_getLastName(bufferClient, bufferLastName) && !client_getCuit(bufferClient, bufferCuit))
					{
						fprintf(pFile, "%d,%s,%s,%s\n",bufferId, bufferName, bufferLastName, bufferCuit);

					}

				}
			}

		}
		fclose(pFile);
	}
	return retornar;
}

int controller_saveSalesAsText(char* path, LinkedList* pArrayListSale)
{
	int retornar=-1;
	FILE* pFile;
	Sale* bufferSale;
	int bufferIdSale;
	int bufferIdClient;
	int bufferPosterQty;
	char bufferFileName[NAME_LEN];
	int bufferPosterArea;
	int bufferStatus;
	if(path!=NULL && pArrayListSale!=NULL)
	{
		pFile = fopen(path, "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id_venta,id_cliente,cantidad_afiches,nombre_archivo,zona,estado\n");
			retornar=0;
			for(int i=0;i<ll_len(pArrayListSale);i++)
			{
				bufferSale = ll_get(pArrayListSale, i);
				if( !sale_getIdSale(bufferSale, &bufferIdSale) && !sale_getIdClient(bufferSale, &bufferIdClient) && !sale_getQtyPosters(bufferSale, &bufferPosterQty) &&
					!sale_getFileName(bufferSale, bufferFileName) && !sale_getPosterArea(bufferSale, &bufferPosterArea) && !sale_getStatus(bufferSale, &bufferStatus))
				{
					fprintf(pFile, "%d,%d,%d,%s,%d,%d\n",bufferIdSale,bufferIdClient,bufferPosterQty,bufferFileName,bufferPosterArea,bufferStatus);
				}
			}
		}
		fclose(pFile);
	}
	return retornar;
}
