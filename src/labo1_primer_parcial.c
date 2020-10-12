/*
 ============================================================================
 Name        : labo1_primer_parcial.c
 Author      : Julia Tamasi
 Description : Primer Parcial Laboratorio I
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "Client.h"
#include "Advertisement.h"

int main(void) {
	setbuf(stdout,NULL);
	Client arrayClient [CLIENT_LEN];
	Advertisement arrayAd [QTY_AD];
	int chosenOption;
	int bufferIdClient;
	if(cli_initArray(arrayClient, CLIENT_LEN)==0 && ad_initArray(arrayAd, QTY_AD)==0)
	{
		do
		{
			if(utn_getMenu(&chosenOption, RETRIES, 9, 1)==0)
			{
				switch(chosenOption)
				{
					case 1:
							if(cli_addElement(arrayClient, CLIENT_LEN)==0)
							{
								printf("\n[ALTA EXITOSA]\n\n");
							}
							break;
					case 2:
							if(cli_modifyClient(arrayClient, CLIENT_LEN)==0)
							{
								printf("\n\n[MODIFICACION EXITOSA]\n\n");
							}
							break;
					case 3:
							if( cli_printArray(arrayClient, CLIENT_LEN)==0 && utn_getNumber("- Ingrese el ID del cliente que desea dar de baja - \n", &bufferIdClient, RETRIES, 999, 1)==0 &&
								ad_printByClientId(arrayAd, QTY_AD, bufferIdClient)==0)
							{
								if(cli_removeClient(arrayClient, CLIENT_LEN, bufferIdClient)==0)
								{
									ad_removeAd(arrayAd, QTY_AD,bufferIdClient);
									printf("CLIENTE DADO DE BAJA EXITOSAMENTE\n");
								}
							}
							break;
					case 4:
							if(ad_addElement(arrayAd, QTY_AD, arrayClient, CLIENT_LEN)==0)
							{
								printf("\n\n[Volviendo al menú...]\n\n");
							}
							else
							{
								printf("-ERROR. Intentelo nuevamente-\n");
							}
							break;
				}
			}
		}while(chosenOption!=9);
	}
	return EXIT_SUCCESS;
}
