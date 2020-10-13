/*
 ============================================================================
 Name        : labo1_primer_parcial.c
 Author      : Julia Tamasi
 Description : Primer Parcial Laboratorio I
 ============================================================================
 */
#include "report.h"
#include "utn.h"
static int rep_calculateClientWithMoreAds(Advertisement* arrayAds, int lenAds, Client* arrayClients, int lenClients, int* indexClientMoreAds);
static int rep_calculateAreaWithMoreAds (Advertisement* arrayAds, int lenAds, int* area);
static int rep_countPausedAds (Advertisement* pArray, int len, int* pausedAdsCounter);
static int rep_countAreaWithMoreAds (Advertisement* arrayAds, int lenAds, int area, int* counter);
static int rep_countActiveAdsByClient (Advertisement* pArray, int len, int idClient, int* activeAdsCounter);

// FUNCIONES ESTATICAS
/** \brief calculate which client has more ads
 * \param Advertisement* arrayAds, Pointer to Ads's array
 * \param int lenAds, Ads's array lenght
 * \param Client* aClients, Pointer to Clients's array
 * \param int lenClients, Clients's array lenght
 * \param int* indexClientMoreAds pointer to the memory space where the client index will be saved
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_calculateClientWithMoreAds(Advertisement* arrayAds, int lenAds, Client* arrayClients, int lenClients, int* indexClientMoreAds)
{
	int result = -1;
	int i;
	int clientWithMoreAds;
	int bufferClientWithMoreAds;
	int bufferIndex;
	if(arrayAds!=NULL && lenAds>0)
	{
		for(i=0;i<lenClients;i++)
		{
			if( rep_countActiveAdsByClient(arrayAds, lenAds, arrayClients[i].idClient, &bufferClientWithMoreAds)==0 &&
			  ( i==0||bufferClientWithMoreAds>clientWithMoreAds))
			{
				clientWithMoreAds = bufferClientWithMoreAds;
				bufferIndex = i;
				result=0;
			}
		}
		*indexClientMoreAds = bufferIndex;
	}
	return result;
}
/** \brief count how many active ads a specific client has
 * \param Advertisement* pArray, Pointer to Ads's array
 * \param int len, Ads's array lenght
 * \param int idClient, client ID
 * \param int* activeAdsCounter, pointer to the memory space where the calculated value will be saved
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_countActiveAdsByClient (Advertisement* pArray, int len, int idClient, int* activeAdsCounter)
{
	int result = -1;
	int i;
	int bufferCounter=0;
	if(pArray!=NULL && len>0 && activeAdsCounter!=NULL && idClient>0)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0 && pArray[i].idClient==idClient && pArray[i].status==ACTIVE)
			{
				bufferCounter++;
			}
		}
		result = 0;
		*activeAdsCounter = bufferCounter;
	}
	return result;
}
/** \brief counts the number of paused ads
 * \param Advertisement* pArray, Pointer to Ads's array
 * \param int len, Ads's array lenght
 * \param int* pausedAdsCounter, pointer to the memory space where the calculated value will be saved
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_countPausedAds (Advertisement* pArray, int len, int* pausedAdsCounter)
{
	int result = -1;
	int i;
	int bufferCounter=0;
	if(pArray!=NULL && len>0 && pausedAdsCounter!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(pArray[i].isEmpty==0 && pArray[i].status==PAUSED)
			{
				bufferCounter++;
			}
		}
		*pausedAdsCounter = bufferCounter;
		result = 0;
	}
	return result;
}
/** \brief calculate which area has more ads
 * \param Advertisement* arrayAds, Pointer to Ads's array
 * \param int lenAds, Ads's array lenght
 * \param int* area, Pointer to the memory space where the calculated value will be saved
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_calculateAreaWithMoreAds (Advertisement* arrayAds, int lenAds, int* area)
{
	int result = -1;
	int i;
	int counterAreaWithMoreAds;
	int bufferMax;
	int bufferArea;
	if(arrayAds!=NULL && lenAds>0)
	{
		for(i=0;i<lenAds;i++)
		{
			if( arrayAds[i].isEmpty==0 && rep_countAreaWithMoreAds(arrayAds, lenAds, arrayAds[i].area, &bufferMax)==0 &&
			  ( i==0 || bufferMax>counterAreaWithMoreAds))
			{
				counterAreaWithMoreAds = bufferMax;
				bufferArea = arrayAds[i].area;
				result = 0;
			}
		}
		*area = bufferArea;
	}
	return result;
}
/** \brief count how many ads a specific area has
 * \param Advertisement* arrayAds, Pointer to Ads's array
 * \param int lenAds, Ads's array lenght
 * \param int area, area to be evaluated
 * \param int* counter, pointer to the memory space where the calculated value will be saved
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_countAreaWithMoreAds (Advertisement* arrayAds, int lenAds, int area, int* counter)
{
	int result = -1;
	int i;
	int bufferCounter = 0;
	if(arrayAds!=NULL && lenAds>0 && area>=0 && counter!=NULL)
	{
		for(i=0;i<lenAds;i++)
		{
			if(arrayAds[i].isEmpty==0 && arrayAds[i].area==area)
			{
				bufferCounter++;
				result = 0;
			}
		}
	}
	*counter = bufferCounter;
	return result;
}
/** \brief print client data and its active ads
 * \param Client* aClients, Pointer to Clients's array
 * \param int len, Clients's array lenght
 * \param Advertisement* arrayAds, Pointer to Ads's array
 * \param int lenAds, Ads's array lenght
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
int rep_printClientsAndActiveAds (Client* aClients, int len, Advertisement* arrayAds, int lenAds)
{
	int result = -1;
	int i;
	int counterActiveAds = 0;
	if(aClients!=NULL && len>0 && arrayAds!=NULL && lenAds>0 && cli_arrayIsEmpty(aClients, len)==0)
	{
		printf("\n************************************* CLIENTES ******************************************\n");
		printf("\n----------------------------------------------------------------------------------------\n");
		printf("      APELLIDO      |       NOMBRE       |   ID   |      CUIT       |  AVISOS ACTIVOS  |");
		for(i=0;i<len;i++)
		{
			if(aClients[i].isEmpty==0 && rep_countActiveAdsByClient(arrayAds, lenAds, aClients[i].idClient, &counterActiveAds)==0)
			{
				printf("\n----------------------------------------------------------------------------------------\n"
						"%-20s|%-20s|%-8d|%-17s|%-18d|\n"
						"----------------------------------------------------------------------------------------\n",aClients[i].lastName, aClients[i].name, aClients[i].idClient, aClients[i].cuit, counterActiveAds);
			}
		}
		result = 0;
	}
	return result;
}
/** \brief prints the report
 * \param Client* aClients, Pointer to Clients's array
 * \param int lenClients, Clients's array lenght
 * \param Advertisement* arrayAds, Pointer to Ads's array
 * \param int lenAds, Ads's array lenght
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
int rep_reports (Client* aClients, int lenClients, Advertisement* arrayAds, int lenAds)
{
	int result = -1;
	int chosenOption;
	int bufferIndexClientWithMoreAds;
	int pausedAdsCounter;
	int areaWithMoreAds;
	if( aClients!=NULL && lenClients>0 && arrayAds!=NULL && lenAds>0 && cli_arrayIsEmpty(aClients, lenClients)==0 && ad_arrayIsEmpty(arrayAds, lenAds)==0 &&
		utn_getNumber("Ingrese una opcion\n[1] Mostrar el cliente con mas avisos\n[2] Cantidad de avisos pausados\n[3] Rubro con mas avisos\n[4] Volver al menú\n", &chosenOption, RETRIES, 4, 1)==0)
	{
		switch(chosenOption)
		{
			case 1:
					if(rep_calculateClientWithMoreAds(arrayAds, lenAds, aClients, lenClients, &bufferIndexClientWithMoreAds)==0)
					{
						cli_printIndex(aClients, bufferIndexClientWithMoreAds);
						printf("[CLIENTE CON MÁS AVISOS]\n");
						result = 0;
					}
					break;
			case 2:
					if(rep_countPausedAds(arrayAds, lenAds, &pausedAdsCounter)==0)
					{
						if(pausedAdsCounter>0)
						{
							printf("[En este momento hay %d avisos pausados]\n",pausedAdsCounter);
						}
						else
						{
							printf("[En este momento no existe ningun aviso pausado]\n");
						}
						result = 0;
					}
					break;
			case 3:
					if(rep_calculateAreaWithMoreAds(arrayAds, lenAds, &areaWithMoreAds)==0)
					{
						if(areaWithMoreAds>-1)
						{
							printf("[El rubro con más avisos es el %d]\n",areaWithMoreAds);
						}
						else
						{
							printf("[No hay rubros cargados]\n");
						}
						result=0;
					}
					break;
		}
	}
	return result;
}
