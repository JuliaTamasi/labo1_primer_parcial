#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "LinkedList.h"
#include "Client.h"
#include "Sale.h"
#include "validations.h"
#include "utn.h"
#include "controller.h"
#include "reports.h"

int rep_generateSalesReport (LinkedList* pArrayListSales, LinkedList* pArrayListClients, int op)
{
	int output = -1;
	LinkedList* bufferSales;
	FILE* pFile;
	Client* pBufferClient;
	Client bufferClient;
	int i;
	int counter;

	if(pArrayListSales != NULL && pArrayListClients != NULL)
	{
		if(op==5)
		{
			bufferSales = ll_filterClone(pArrayListSales,sale_fCriterioFilterCharged,CHARGED);
			pFile = fopen("cobradas.csv","w");
			if(bufferSales!=NULL && pFile != NULL)
			{
				fprintf(pFile,"ID,NOMBRE,APELLIDO,CUIT,VENTAS_COBRADAS\n");
			}
		}
		else if(op==6)
		{
			bufferSales = ll_filterClone(pArrayListSales,sale_fCriterioFilterUnpaid,UNPAID);
			pFile = fopen("a_cobrar.csv","w");
			if(bufferSales!=NULL && pFile != NULL)
			{
				fprintf(pFile,"ID,NOMBRE,APELLIDO,CUIT,VENTAS_A_COBRAR\n");
			}
		}
		for(i=0; i<ll_len(pArrayListClients);i++)
		{
			pBufferClient = ll_get(pArrayListClients, i);
			if(pBufferClient!=NULL)
			{
				if( !client_getIdClient(pBufferClient, &bufferClient.idClient) && !client_getName(pBufferClient, bufferClient.name) &&
					!client_getLastName(pBufferClient, bufferClient.lastName) && !client_getCuit(pBufferClient, bufferClient.cuit))
				{
					counter = ll_reduceInt(bufferSales, sale_fCriterioReduceCompareIdClient,bufferClient.idClient);
					if(counter!=0)
					{
						fprintf(pFile,"%d,%s,%s,%s,%d\n",bufferClient.idClient,bufferClient.name,bufferClient.lastName,bufferClient.cuit,counter);
					}
				}
			}
		}
		output = 0;
	}
	return output;
}

int rep_generateStats (LinkedList* pArrayListSales, LinkedList* pArrayListClients)
{
	int output = -1;
	int chosenOp;
	LinkedList* auxiliarChargeSales = ll_filterClone(pArrayListSales, sale_fCriterioFilterCharged, CHARGED);

	if( auxiliarChargeSales!=NULL && pArrayListClients!=NULL &&
		!utn_getNumber("¿Qué informe desea mostrar?\n[1] Cliente al que se le vendieron más afiches\n[2] Cliente al que se le vendieron menos afiches\n[3] Venta con mas afiches vendidos\n[4] Volver al menú\n\n", &chosenOp, RETRIES, 4, 1))
	{
		switch(chosenOp)
		{
			case 1:
					printf("El/los cliente/s con más cantidad de afiches comprados son:  \n\n");
					if(!rep_generateStatsClients(auxiliarChargeSales, pArrayListClients, chosenOp))
					{
						output = 0;
					}
					break;
			case 2:
					printf("El/los cliente/s con menos cantidad de afiches comprados son:  \n\n");
					if(!rep_generateStatsClients(auxiliarChargeSales, pArrayListClients, chosenOp))
					{
						output = 0;
					}
					break;
			case 3:
					if(!rep_saleWithMorePosters(auxiliarChargeSales, pArrayListClients))
					{
						output = 0;
					}
					break;
		}
	}
	return output;
}

int rep_generateStatsClients (LinkedList* pArrayListSales, LinkedList* pArrayListClients, int op)
{
	int output = -1;
	Client* pClient;
	LinkedList* max = ll_newLinkedList();
	LinkedList* min = ll_newLinkedList();
	int bufferIdClient;
	int bufferQtyPosters;
	int maxQtyPosters;
	int minQtyPosters;
	int i;

	if(pArrayListClients!=NULL && pArrayListSales!= NULL && !ll_isEmpty(pArrayListClients))
	{
		output = 0;
		for (i=0; i<ll_len(pArrayListClients); i++)
		{
			pClient = ll_get(pArrayListClients, i);
			if(pClient!=NULL && !client_getIdClient(pClient, &bufferIdClient))
			{
				bufferQtyPosters = ll_reduceInt(pArrayListSales, sale_fCriterioReduceAccQtyPosters, bufferIdClient);
				if(op==1 && (i==0 || bufferQtyPosters>maxQtyPosters))
				{
					maxQtyPosters = bufferQtyPosters;
					ll_clear(max);
					ll_add(max, pClient);
				}
				else if(op==1 && bufferIdClient==maxQtyPosters)
				{
					ll_add(max, pClient);
				}
				if(op==2 && (i==0 || bufferQtyPosters<minQtyPosters))
				{
					minQtyPosters = bufferQtyPosters;
					ll_clear(min);
					ll_add(min, pClient);
				}
				else if(op==2 && bufferQtyPosters == minQtyPosters)
				{
					ll_add(min, pClient);
				}
			}
		}
		if(op==1)
		{
			controller_listClient(max);
		}
		else if(op==2)
		{
			controller_listClient(min);
		}
		/*for (i=0; i<ll_len(pArrayListClients); i++)
		{
			pClient = ll_get(pArrayListClients, i);
			if(pClient!=NULL && !client_getIdClient(pClient, &bufferIdClient))
			{
				bufferQtyPosters = ll_reduceInt(pArrayListSales, sale_fCriterioReduceAccQtyPosters, bufferIdClient);
				if(op && bufferQtyPosters==maxQtyPosters)
				{
					client_printByIndex(pArrayListClients, i);
				}
				else if(op==2 && bufferQtyPosters==minQtyPosters)
				{
					client_printByIndex(pArrayListClients, i);
				}
			}
		}*/
	}
	return output;
}

int rep_saleWithMorePosters(LinkedList* pArrayListSales, LinkedList* pArrayListClients)
{
	int output= -1;
	int bufferPosterQty;
	int maxPosterQty;
	int bufferIdSale;
	int bufferIdClient;
	int bufferIndexClient;
	char bufferCuit[CUIT_LEN];
	Sale* pSale;
	Client* bufferClient;

	if(pArrayListClients!=NULL && pArrayListSales!=NULL)
	{
		output=0;
		for(int i=0;i<ll_len(pArrayListSales);i++)
		{
			pSale = ll_get(pArrayListSales, i);
			if(pSale!=NULL && !sale_getQtyPosters(pSale, &bufferPosterQty))
			{
				if(i==0 || maxPosterQty<bufferPosterQty)
				{
					maxPosterQty=bufferPosterQty;
				}
			}
		}
		printf("\nLa/s venta/s con mas afiches vendidos es/son: \n");
		for(int i=0;i<ll_len(pArrayListSales);i++)
		{
			pSale = ll_get(pArrayListSales, i);
			if(pSale!=NULL && !sale_getQtyPosters(pSale, &bufferPosterQty))
			{
				if( bufferPosterQty==maxPosterQty && !sale_getIdClient(pSale, &bufferIdClient) &&
					!sale_getIdSale(pSale, &bufferIdSale)  && !client_findIndexById(pArrayListClients, bufferIdClient, &bufferIndexClient))
				{
					bufferClient = ll_get(pArrayListClients, bufferIndexClient);
					if(bufferClient!=NULL && !client_getCuit(bufferClient, bufferCuit))
					{
						printf("\nID venta: %d - Cuit cliente: %s", bufferIdSale, bufferCuit);
					}
				}
			}
		}
	}
	return output;
}
