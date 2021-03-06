/*
 ============================================================================
 Name        : labo1_primer_parcial.c
 Author      : Julia Tamasi
 Description : Primer Parcial Laboratorio I
 ============================================================================
 */
#include "report.h"
#include "utn.h"
static int rep_calculateClientWithMoreActiveAds(Advertisement* arrayAds, int lenAds, Client* arrayClients, int lenClients);
static int rep_calculateAreaWithMoreAds (Advertisement* arrayAds, int lenAds, int* area);
static int rep_calculateClientWithMoreAds(Advertisement* arrayAds, int lenAds, Client* arrayClients, int lenClients);
static int rep_countPausedAds (Advertisement* arrayAds, int len, int* pausedAdsCounter);
static int rep_countAreaWithMoreAds (Advertisement* arrayAds, int lenAds, int area, int* counter);
static int rep_countActiveAdsByClient (Advertisement* arrayAds, int len, int idClient, int* activeAdsCounter);
static int rep_countAdsByClient (Advertisement* arrayAds, int len, int idClient, int* adsCounter);
static int rep_countPausedAdsByClient (Advertisement* arrayAds, int len, int idClient, int* pausedAdsCounter);
static int rep_calculateClientWithMorePausedAds(Advertisement* arrayAds, int lenAds, Client* arrayClients, int lenClients);
// FUNCIONES ESTATICAS
/** \brief calculate which client has more active ads
 * \param Advertisement* arrayAds, Pointer to Ads's array
 * \param int lenAds, Ads's array lenght
 * \param Client* arrayClients, Pointer to Clients's array
 * \param int lenClients, Clients's array lenght
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_calculateClientWithMoreActiveAds(Advertisement* arrayAds, int lenAds, Client* arrayClients, int lenClients)
{
	int result = -1;
	int i;
	int clientWithMoreAds;
	int bufferClientWithMoreAds;
	int bufferIndex;
	if(arrayAds!=NULL && lenAds>0 && ad_searchForActive(arrayAds, lenAds)==1)
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
		printf("Clientes con m�s avisos activos: \n\n");
		cli_printIndex(arrayClients, bufferIndex);
		for(int j=0; j<lenClients; j++)
		{
			if( rep_countActiveAdsByClient(arrayAds, lenAds, arrayClients[j].idClient, &bufferClientWithMoreAds)==0 && bufferClientWithMoreAds==clientWithMoreAds &&
				bufferIndex != j)
			{
				cli_printIndex(arrayClients, j);
				result = 0;
			}
		}
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
static int rep_countActiveAdsByClient (Advertisement* arrayAds, int len, int idClient, int* activeAdsCounter)
{
	int result = -1;
	int i;
	int bufferCounter=0;
	if(arrayAds!=NULL && len>0 && activeAdsCounter!=NULL && idClient>0)
	{
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty==0 && arrayAds[i].idClient==idClient && arrayAds[i].status==ACTIVE)
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
static int rep_countPausedAds (Advertisement* arrayAds, int len, int* pausedAdsCounter)
{
	int result = -1;
	int i;
	int bufferCounter=0;
	if(arrayAds!=NULL && len>0 && pausedAdsCounter!=NULL)
	{
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty==0 && arrayAds[i].status==PAUSED)
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
/** \brief count how many ads a specific client has
 * \param Advertisement* pArray, Pointer to Ads's array
 * \param int len, Ads's array lenght
 * \param int idClient, client ID
 * \param int* activeAdsCounter, pointer to the memory space where the calculated value will be saved
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_countAdsByClient (Advertisement* arrayAds, int len, int idClient, int* adsCounter)
{
	int result = -1;
	int i;
	int bufferCounter=0;
	if(arrayAds!=NULL && len>0 && adsCounter!=NULL && idClient>0)
	{
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty==0 && arrayAds[i].idClient==idClient)
			{
				bufferCounter++;
			}
		}
		result = 0;
		*adsCounter = bufferCounter;
	}
	return result;
}
/** \brief calculate which client has more ads
 * \param Advertisement* arrayAds, Pointer to Ads's array
 * \param int lenAds, Ads's array lenght
 * \param Client* arrayClients, Pointer to Clients's array
 * \param int lenClients, Clients's array lenght
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_calculateClientWithMoreAds(Advertisement* arrayAds, int lenAds, Client* arrayClients, int lenClients)
{
	int result = -1;
	int i;
	int clientWithMoreAds;
	int bufferClientWithMoreAds;
	int bufferIndex;
	if(arrayAds!=NULL && lenAds>0)
	{
		printf("Clientes con m�s avisos: \n\n");
		for(i=0;i<lenClients;i++)
		{
			if( rep_countAdsByClient(arrayAds, lenAds, arrayClients[i].idClient, &bufferClientWithMoreAds)==0 &&
			  ( i==0||bufferClientWithMoreAds>clientWithMoreAds))
			{
				clientWithMoreAds = bufferClientWithMoreAds;
				bufferIndex = i;
				result=0;
			}
		}
		cli_printIndex(arrayClients, bufferIndex);
		for(int j=0; j<lenClients; j++)
		{
			if( rep_countAdsByClient(arrayAds, lenAds, arrayClients[j].idClient, &bufferClientWithMoreAds)==0 && bufferClientWithMoreAds==clientWithMoreAds &&
				bufferIndex != j)
			{
				cli_printIndex(arrayClients, j);
				result = 0;
			}
		}
	}
	return result;
}
/** \brief count how many paused ads a specific client has
 * \param Advertisement* pArray, Pointer to Ads's array
 * \param int len, Ads's array lenght
 * \param int idClient, client ID
 * \param int* activeAdsCounter, pointer to the memory space where the calculated value will be saved
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_countPausedAdsByClient (Advertisement* arrayAds, int len, int idClient, int* pausedAdsCounter)
{
	int result = -1;
	int i;
	int bufferCounter=0;
	if(arrayAds!=NULL && len>0 && pausedAdsCounter!=NULL && idClient>0)
	{
		for(i=0;i<len;i++)
		{
			if(arrayAds[i].isEmpty==0 && arrayAds[i].idClient==idClient && arrayAds[i].status==PAUSED)
			{
				bufferCounter++;
			}
		}
		*pausedAdsCounter = bufferCounter;
		result = 0;
	}
	return result;
}
/** \brief calculate which client has more paused ads
 * \param Advertisement* arrayAds, Pointer to Ads's array
 * \param int lenAds, Ads's array lenght
 * \param Client* arrayClients, Pointer to Clients's array
 * \param int lenClients, Clients's array lenght
 * \return (0) if OK or (-1) if [Invalid lenght or NULL pointer received or employee not found
 */
static int rep_calculateClientWithMorePausedAds(Advertisement* arrayAds, int lenAds, Client* arrayClients, int lenClients)
{
	int result = -1;
	int i;
	int clientWithMoreAds;
	int bufferClientWithMoreAds;
	int bufferIndex;
	if(arrayAds!=NULL && lenAds>0 && ad_searchForPaused(arrayAds, lenAds)==1)
	{
		printf("Clientes con m�s avisos pausados: \n\n");
		for(i=0;i<lenClients;i++)
		{
			if( rep_countPausedAdsByClient(arrayAds, lenAds, arrayClients[i].idClient, &bufferClientWithMoreAds)==0 &&
			  ( i==0||bufferClientWithMoreAds>clientWithMoreAds))
			{
				clientWithMoreAds = bufferClientWithMoreAds;
				bufferIndex = i;
				result=0;
			}
		}
		cli_printIndex(arrayClients, bufferIndex);
		for(int j=0; j<lenClients; j++)
		{
			if( rep_countPausedAdsByClient(arrayAds, lenAds, arrayClients[j].idClient, &bufferClientWithMoreAds)==0 && bufferClientWithMoreAds==clientWithMoreAds &&
				bufferIndex != j)
			{
				cli_printIndex(arrayClients, j);
				result = 0;
			}
		}
	}
	return result;
}
//FUNCIONES PUBLICAS
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
	int pausedAdsCounter;
	int areaWithMoreAds;
	if( aClients!=NULL && lenClients>0 && arrayAds!=NULL && lenAds>0 && cli_arrayIsEmpty(aClients, lenClients)==0 && ad_arrayIsEmpty(arrayAds, lenAds)==0 &&
		utn_getNumber("Ingrese una opcion\n[1] Mostrar el cliente con mas avisos\n[2] Cantidad de avisos pausados\n[3] Rubro con mas avisos\n[4] Clientes con mas avisos activos\n[5] Clientes con m�s avisos pausados\n[6] Volver al men�\n", &chosenOption, RETRIES, 6, 1)==0)
	{
		switch(chosenOption)
		{
			case 1:
					if(rep_calculateClientWithMoreAds(arrayAds, lenAds, aClients, lenClients)==0)
					{
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
							printf("[El rubro con m�s avisos es el %d]\n",areaWithMoreAds);
						}
						else
						{
							printf("[No hay rubros cargados]\n");
						}
						result=0;
					}
					break;
			case 4:
					if(rep_calculateClientWithMoreActiveAds(arrayAds, lenAds, aClients, lenClients)==0)
					{
						result = 0;
					}
					else
					{
						printf("No hay avisos activos\n");
					}
					break;
			case 5:
					if(rep_calculateClientWithMorePausedAds(arrayAds, lenAds, aClients, lenClients)==0)
					{
						result = 0;
					}
					else
					{
						printf("No hay avisos pausados\n");
					}
					break;
			case 6:
					result = 0;
					break;
		}
	}
	return result;
}
