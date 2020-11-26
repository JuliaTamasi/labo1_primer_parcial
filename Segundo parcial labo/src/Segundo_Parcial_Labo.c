/*
 ============================================================================
 Name        : Segundo_Parcial_Labo.c
 Author      : Julia Tamasi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Linkedlist.h"
#include "utn.h"
#include "controller.h"
#include "reports.h"

int main(void)
{
	setbuf(stdout,NULL);

	LinkedList* pClientsList = ll_newLinkedList();
	LinkedList* pSalesList = ll_newLinkedList();
	int op;
	int answer;

	if(!controller_loadClientFromText("clients.csv", pClientsList) && !controller_loadSaleFromText("sales.csv", pSalesList))
	{
		do
		{
			if(!utn_getMenu(&op, RETRIES, 8, 1))
			{
				switch (op)
				{
					case 1:
							if(!controller_addClient(pClientsList))
							{
								controller_saveClientAsText("clients.csv", pClientsList);
								printf("[¡Cliente dado de alta de manera exitosa!]\n\n");
							}
							else
							{
								printf("[ERROR. El cuit ya fue ingresado anteriormente]\n\n");
							}
							break;
					case 2:
							if(!ll_isEmpty(pClientsList) && !controller_addSale(pSalesList, pClientsList))
							{
								controller_saveSalesAsText("sales.csv", pSalesList);
								printf("[¡Venta cargada con exito!]\n\n");
							}
							break;
					case 3:
							if(!ll_isEmpty(pClientsList) && !ll_isEmpty(pSalesList))
							{
								answer = controller_modifySale(pSalesList, pClientsList,op);
								if(!answer)
								{
									controller_saveSalesAsText("sales.csv", pSalesList);
									printf("[¡Registro modificado con éxito!]\n\n");
								}
								else if(answer==-2)
								{
									printf("[Volviendo al menú...]\n\n");
								}
								else
								{
									printf("[ERROR. El ID ingresado es incorrecto o no está disponible para esta operación]\n\n");
								}
							}
							break;
					case 4:
							if(!ll_isEmpty(pClientsList) && !ll_isEmpty(pSalesList))
							{
								answer = controller_modifySale(pSalesList, pClientsList, op);
								if(!answer)
								{
									controller_saveSalesAsText("sales.csv", pSalesList);
									printf("[¡Estado modificado con éxito!]\n\n");
								}
								else if(answer==-2)
								{
									printf("[Volviendo al menú...]\n\n");
								}
								else
								{
									printf("[ERROR. El ID ingresado es incorrecto o no está disponible para esta operación]\n\n");
								}
							}
							break;
					case 5:
							if(!ll_isEmpty(pClientsList) && !ll_isEmpty(pSalesList) && !rep_generateSalesReport(pSalesList, pClientsList,op))
							{
								printf("[¡Archivo de ventas COBRADAS generado con éxito!]\n\n");
							}
							else
							{
								printf("[ERROR. No se pudo generar el archivo]\n\n");
							}
							break;
					case 6:
							if(!ll_isEmpty(pClientsList) && !ll_isEmpty(pSalesList) && !rep_generateSalesReport(pSalesList, pClientsList, op))
							{
								printf("[¡Archivo de ventas A COBRAR generado con éxito!]\n\n");
							}
							else
							{
								printf("[ERROR. No se pudo generar el archivo]\n\n");
							}
							break;
					case 7:
							if(!ll_isEmpty(pClientsList) && !ll_isEmpty(pSalesList) && !rep_generateStats(pSalesList, pClientsList))
							{
								printf("\n***FIN DEL REPORTE***\n\n");
							}
							else
							{
								printf("[ERROR. Intentelo nuevamente]\n\n");
							}
							break;
				}
			}
		}while(op!=8);
		printf("Goodbye!");
	}
	return EXIT_SUCCESS;
}
