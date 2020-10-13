/*
 ============================================================================
 Name        : labo1_primer_parcial.c
 Author      : Julia Tamasi
 Description : Primer Parcial Laboratorio I
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utn.h"
#include "Client.h"
#include "Advertisement.h"
#include "report.h"

int main(void) {
	setbuf(stdout,NULL);
	Client arrayClients [CLIENT_LEN];
	Advertisement arrayAds [QTY_AD];
	int chosenOption;
	int bufferIdClient;
	if(cli_initArray(arrayClients, CLIENT_LEN)==0 && ad_initArray(arrayAds, QTY_AD)==0)
	{
		do
		{
			if(utn_getMenu(&chosenOption, RETRIES, 9, 1)==0)
			{
				switch(chosenOption)
				{
					case 1:
							if(cli_addElement(arrayClients, CLIENT_LEN)==0)
							{
								printf("\n[ALTA EXITOSA]\n\n");
							}
							else
							{
								printf("\n[ERROR. Intentelo nuevamente]\n\n");
							}
							break;
					case 2:
							if(cli_modifyClient(arrayClients, CLIENT_LEN)==0)
							{
								printf("\n\n[MODIFICACION EXITOSA]\n\n");
							}
							break;
					case 3:
							if( cli_printArray(arrayClients, CLIENT_LEN)==0 && utn_getNumber("- Ingrese el ID del cliente que desea dar de baja - \n", &bufferIdClient, RETRIES, INT_MAX, 1)==0 &&
								cli_findIndexById(arrayClients, CLIENT_LEN, bufferIdClient) >-1 &&
								ad_printByClientId(arrayAds, QTY_AD, bufferIdClient)==0)
							{
								if(cli_removeClient(arrayClients, CLIENT_LEN, bufferIdClient)==0)
								{
									ad_removeAd(arrayAds, QTY_AD,bufferIdClient);
									printf("[CLIENTE DADO DE BAJA EXITOSAMENTE]\n");
								}
							}
							else
							{
								printf("[ERROR. Intentelo nuevamente]\n\n");
							}
							break;
					case 4:
							if(ad_addElement(arrayAds, QTY_AD, arrayClients, CLIENT_LEN)==0)
							{
								printf("\n\n[Volviendo al menú...]\n\n");
							}
							else
							{
								printf("[ERROR. Intentelo nuevamente]\n\n");
							}
							break;
					case 5:
							if(ad_status(arrayAds, QTY_AD, arrayClients, CLIENT_LEN, 5)==0)
							{
								printf("[AVISO PAUSADO EXITOSAMENTE]\n\n");
							}
							else
							{
								printf("[ERROR. Intentelo nuevamente]\n\n");
							}
							break;
					case 6:
							if(ad_status(arrayAds, QTY_AD, arrayClients, CLIENT_LEN, 6)==0)
							{
								printf("[AVISO REANUDADO EXITOSAMENTE]\n\n");
							}
							else
							{
								printf("[ERROR. Intentelo nuevamente]\n\n");
							}
							break;
					case 7:
							if(rep_printClientsAndActiveAds(arrayClients, CLIENT_LEN, arrayAds, QTY_AD)==0)
							{
								printf("\n***FIN DEL REPORTE***\n\n");
							}
							else
							{
								printf("[ERROR. Intentelo nuevamente]\n\n");
							}
							break;
					case 8:
							if(rep_reports(arrayClients, CLIENT_LEN, arrayAds, QTY_AD)==0)
							{
								printf("\n***FIN DEL REPORTE***\n\n");
							}
							else
							{
								printf("[ERROR. Intentelo nuevamente]\n");
							}
							break;
				}
			}
		}while(chosenOption!=9);
		printf("\n\n\nGOODBYE!\n\n\n");
	}
	return EXIT_SUCCESS;
}
