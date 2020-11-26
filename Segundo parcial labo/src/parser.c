#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Client.h"
#include "Sale.h"

/** \brief Parse client data from file client.csv(text)
 * \param FILE* pFile Pointer to file to load
 * \param LinkedList* pArrayListClient Pointer to LinkedList
 * \return [0] if OK / [-1] if error
 *
 */
int parser_clientFromText(FILE* pFile , LinkedList* pArrayListClient)
{
	int result = -1;
	Client* pClient;
	char bufferId [BUFFER_SIZE];
	char bufferName [BUFFER_SIZE];
	char bufferLastName[BUFFER_SIZE];
	char bufferCuit [BUFFER_SIZE];

	if(pFile!=NULL && pArrayListClient!=NULL)
	{
		ll_clear(pArrayListClient); //LIMPIA LA LISTA
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId,bufferName,bufferLastName,bufferCuit)==4)
			{
				pClient = client_newParametros(bufferId, bufferName, bufferLastName, bufferCuit);
				if(pClient!=NULL && !ll_add(pArrayListClient, pClient))
				{
					result = 0;
				}
			}
			else
			{
				client_delete(pClient);
			}
		}while(!feof(pFile));
	}
    return result;
}
/** \brief Parse sale data from file sale.csv(text)
 * \param FILE* pFile Pointer to file to load
 * \param LinkedList*  pArrayListSale Pointer to LinkedList
 * \return [0] if OK / [-1] if error
 *
 */
int parser_saleFromText(FILE* pFile , LinkedList* pArrayListSale)
{
	int result = -1;
	Sale* pSale;
	char bufferIdSale [BUFFER_SIZE];
	char bufferIdClient [BUFFER_SIZE];
	char bufferQtyPosters [BUFFER_SIZE];
	char bufferFileName [NAME_LEN];
	char bufferPosterArea [BUFFER_SIZE];
	char bufferStatus [BUFFER_SIZE];

	if(pFile!=NULL && pArrayListSale!=NULL)
	{
		ll_clear(pArrayListSale); //LIMPIA LA LISTA
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",bufferIdSale,bufferIdClient,bufferQtyPosters,bufferFileName,bufferPosterArea, bufferStatus)==6)
			{
				pSale = sale_newParametros(bufferIdSale, bufferIdClient, bufferQtyPosters, bufferFileName, bufferPosterArea, bufferStatus);
				if(pSale!=NULL && !ll_add(pArrayListSale, pSale))
				{
					result = 0;
				}
			}
			else
			{
				sale_delete(pSale);
			}
		}while(!feof(pFile));
	}
    return result;
}
