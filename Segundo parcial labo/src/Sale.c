#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "LinkedList.h"
#include "Sale.h"
#include "validations.h"
#include "utn.h"

Sale* sale_new()
{
	return (Sale*)malloc(sizeof(Sale));
}

void sale_delete(Sale* this)
{
	free(this);
}

/* \brief add in a existing list of employees the values received as they are
 * \param in id: get id as int
 * \param char* name: get name as text
 * \param int workedHours: get worked hours as int
 * \param float salary: get salary as float
 * \returns memory address of employee with loaded data or NULL if error
 */
Sale* sale_newWithParameters(int idSale, int idClient, int qtyPosters, char* fileName, int posterArea, int status)
{
	Sale *this = sale_new();

	if (this != NULL)
	{
		if( !sale_setIdSale(this, idSale) &&
			!sale_setIdClient(this, idClient) &&
		    !sale_setQtyPosters(this, qtyPosters) &&
			!sale_setFileName(this, fileName) &&
			!sale_setPosterArea(this, posterArea) &&
			!sale_setStatus(this, status))
		{
			return this;
		}
	}
	sale_delete(this);
	return NULL;
}
/* \brief add in a existing list of employees the values received as parameters as text
 * \param char* idStr: get id as text
 * \param char* name: get name as text
 * \param char* workedHours: get worked hours as text
 * \param char* salary: get salary as text
 * \returns memory address of employee with loaded data or NULL if error
 */
Sale* sale_newParametros(char* idSale, char* idClient, char* qtyPosters, char* fileName, char* posterArea, char* status)
{
	Sale* this = sale_new();
	if (this != NULL)
	{
		if( !sale_setIdSaleTxt(this, idSale) &&
			!sale_setIdClientTxt(this, idClient) &&
			!sale_setQtyPostersTxt(this, qtyPosters) &&
			!sale_setFileName(this, fileName) &&
			!sale_setPosterAreaTxt(this, posterArea) &&
			!sale_setStatusTxt(this, status))
		{
			return this;
		}
	}
	sale_delete(this);
	return NULL;
}
void sale_printHeader()
{
	printf("\n******************************************** VENTAS *************************************************\n");
	printf("\n-----------------------------------------------------------------------------------------------------\n");
	printf("  ID VENTA   |  ID CLIENTE  |   QTY AFICHES  |   NOMBRE DEL ARCHIVO   |      ZONA      |   ESTADO   |");
}

int sale_printByIndex(LinkedList* pArrayListSale, int index)
{
	int result = -1;
	Sale* pSale;
	Sale bufferSale;
	char bufferStatus[8];
	char bufferPosterArea[BUFFER_SIZE];

	if(pArrayListSale!=NULL && index>-1)
	{
		pSale = ll_get(pArrayListSale, index);
		if( !sale_getIdSale(pSale,&bufferSale.idSale) &&
			!sale_getIdClient(pSale, &bufferSale.idClient) &&
			!sale_getQtyPosters(pSale, &bufferSale.qtyPosters) &&
			!sale_getFileName(pSale, bufferSale.fileName) &&
			!sale_getPosterArea(pSale, &bufferSale.posterArea) &&
			!sale_getStatus(pSale, &bufferSale.status))
		{
			if(bufferSale.status==1)
			{
				strncpy(bufferStatus,"CHARGED",8);
			}
			else
			{
				strncpy(bufferStatus,"UNPAID",8);
			}
			sale_castZoneToChar(bufferSale.posterArea, bufferPosterArea);
			printf( "\n-----------------------------------------------------------------------------------------------------\n"
					"%-13d|%-14d|%-16d|%-24s|%-16s|%-12s|\n"
					"-----------------------------------------------------------------------------------------------------\n",bufferSale.idSale, bufferSale.idClient, bufferSale.qtyPosters,bufferSale.fileName,bufferPosterArea,bufferStatus);
			result = 0;
		}
	}
	return result;
}

int sale_searchMaxId(LinkedList *pArraySales)
{
	int result = -1;
	Sale* bufferSale;
	int i;
	int id;
	int maxId;
	if (pArraySales != NULL)
	{
		for (i=0 ; i<ll_len(pArraySales) ; i++)
		{
			bufferSale = ll_get(pArraySales, i);
			sale_getIdSale(bufferSale,&id);

			if (i == 0 || id > maxId)
			{
				maxId = id;
			}
		}
		result = maxId + 1;
	}
	return result;
}

int sale_findIndexById (LinkedList* this, int idSale, int* index)
{
	int output = -1;
	Sale* buffer;
	int bufferId;
	int i;

	if(this!=NULL && idSale>0)
	{
		for(i=0;i<ll_len(this);i++)
		{
			buffer = (Sale*) ll_get(this, i);
			if(buffer!=NULL && !sale_getIdSale(buffer, &bufferId) && idSale==bufferId)
			{
				*index = i;
				output = 0;
				break;
			}
		}
	}
	return output;
}

int sale_fCriterioFilterUnpaid(void* pElement)
{
	int output = -1;
	int bufferStatus;
	Sale* pSale = (Sale*) pElement;

	if(pSale!=NULL)
	{
		sale_getStatus(pSale, &bufferStatus);
		if(bufferStatus == UNPAID)
		{
			output = 0;
		}
	}
	return output;
}

int sale_fCriterioFilterCharged(void* pElement)
{
	int output = -1;
	int bufferStatus;
	Sale* pSale = (Sale*) pElement;

	if(pSale!=NULL)
	{
		sale_getStatus(pSale, &bufferStatus);
		if(bufferStatus == CHARGED)
		{
			output = 0;
		}
	}
	return output;
}

int sale_editFields(Sale* this)
{
	int output = -1;
	int op;
	Sale bufferSale;
	char bufferPosterArea [BUFFER_SIZE];

	if(this!=NULL && !utn_getNumber("¿Qué campo del registro desea modificar?\n\n[1] Nombre del archivo que contiene la foto del afiche\n[2] Cantidad de afiches\n[3] Zona donde se pegaran los afiches\n[4] Volver atrás\n", &op, 3, 4, 1))
	{
		switch(op)
		{
			case 1:
					if(!utn_getName("[Ingrese el nombre del archivo con la imagen del afiche]\n", "[ERROR. Ingrese un nombre valido]",bufferSale.fileName,3, NAME_LEN) && !sale_setFileName(this, bufferSale.fileName))
					{
						printf("¡Nombre del archivo cargado con exito!\nNombre: %s\n\n",bufferSale.fileName);
						output = 0;
					}
					break;
			case 2:
					if(!utn_getNumber("[Ingrese la cantidad de afiches]\n", &bufferSale.qtyPosters,3,INT_MAX,1) && !sale_setQtyPosters(this, bufferSale.qtyPosters))
					{
						printf("¡Cantidad de afiches cargado con exito!\nCantidad de afiches: %d\n\n",bufferSale.qtyPosters);
						output = 0;
					}
					break;
			case 3:
					if(!utn_getNumber("Ingrese la zona donde se pegará el/los afiche/s\n[1] CABA\n[2] ZONA SUR\n[3] ZONA OESTE\n", &bufferSale.posterArea, 3, 3, 1) && !sale_setPosterArea(this, bufferSale.posterArea))
					{
						sale_castZoneToChar(bufferSale.posterArea, bufferPosterArea);
						printf("¡Zona cargada con exito!\nNueva zona: %s\n\n",bufferPosterArea);
						output = 0;
					}
					break;
			case 4:
					output = -2;
					break;
		}
	}
	return output;
}
void sale_castZoneToChar (int zone, char* castZone)
{
	if((zone==1||zone==2||zone==3) && castZone!=NULL)
	{
		switch(zone)
		{
			case 1:
					strcpy(castZone,"CABA");
					break;
			case 2:
					strcpy(castZone,"ZONA SUR");
					break;
			case 3:
					strcpy(castZone,"ZONA OESTE");
					break;
		}
	}
}
int sale_editStatus (Sale* this)
{
	int output = -1;
	int confirm;

	if(!utn_getNumber("¿Desea cambiar el estado de esta venta a 'cobrada'?\n[1] Si\n[2] No\n[3] Volver al menú\n", &confirm, RETRIES, 3, 1) && confirm==1)
	{
		if(!sale_setStatus(this, CHARGED))
		{
			output = 0;
		}
	}
	else
	{
		output = -2;
	}
	return output;
}

int sale_fCriterioReduceCompareIdClient(void* pElement, int idClient)
{
	int output = -1;
	Sale* pBufferSale = (Sale*) pElement;
	int bufferSaleIdClient;

	if(pElement!=NULL && idClient>0 && !sale_getIdClient(pBufferSale, &bufferSaleIdClient))
	{
		if(bufferSaleIdClient==idClient)
		{
			output = 1;
		}
		else
		{
			output = 0;
		}
	}
	return output;
}

int sale_fCriterioReduceAccQtyPosters(void* pElement, int idClient)
{
	int output = -1;
	Sale* pSale = (Sale*) pElement;
	int auxIdClient;
	int auxQtyPosters;
	int auxStatus;

	if(pSale!=NULL && idClient>0)
	{
		if(!sale_getIdClient(pSale, &auxIdClient) && !sale_getQtyPosters(pSale, &auxQtyPosters) && !sale_getStatus(pSale, &auxStatus))
		{
			if(auxIdClient==idClient && auxStatus==CHARGED)
			{
				output = auxQtyPosters;
			}
		}
	}
	return output;
}
/************ SETTERS Y GETTERS *************/

int sale_getIdSale(Sale* this, int* idSale)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*idSale = this->idSale;
		retorno = 0;
	}
	return retorno;
}
int sale_getIdClient(Sale* this, int* idClient)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*idClient = this->idClient;
		retorno = 0;
	}
	return retorno;
}
int sale_getQtyPosters(Sale* this, int* qtyPosters)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*qtyPosters = this->qtyPosters;
		retorno = 0;
	}
	return retorno;
}
int sale_getFileName(Sale* this, char* fileName)
{
	int retorno = -1;
	if(this!=NULL)
	{
		strcpy(fileName,this->fileName);
		retorno = 0;
	}
	return retorno;
}
int sale_getPosterArea(Sale* this, int* posterArea)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*posterArea = this->posterArea;
		retorno = 0;
	}
	return retorno;
}
int sale_getStatus(Sale* this, int* status)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*status = this->status;
		retorno = 0;
	}
	return retorno;
}

int sale_setIdSale(Sale* this, int idSale)
{
	int retorno = -1;
	if(this != NULL && idSale>-1)
	{
		this->idSale = idSale;
		retorno = 0;
	}
	return retorno;
}

int sale_setIdSaleTxt(Sale* this, char* idSale)
{
	int result = -1;
	char bufferId[BUFFER_SIZE];

	if (this != NULL && idSale != NULL && val_isValidNumber(idSale))
	{
		strncpy(bufferId, idSale, BUFFER_SIZE);
		this -> idSale = atoi(bufferId);
		result = 0;
	}
	return result;
}
int sale_setIdClient(Sale* this, int idClient)
{
	int retorno = -1;
	if(this != NULL && idClient>-1)
	{
		this->idClient = idClient;
		retorno = 0;
	}
	return retorno;
}
int sale_setIdClientTxt(Sale* this, char* idClient)
{
	int result = -1;
	char bufferId[BUFFER_SIZE];

	if (this != NULL && idClient != NULL && val_isValidNumber(idClient))
	{
		strncpy(bufferId, idClient, BUFFER_SIZE);
		this -> idClient = atoi(bufferId);
		result = 0;
	}
	return result;
}
int sale_setQtyPosters(Sale* this, int qtyPosters)
{
	int retorno = -1;
	if(this != NULL && qtyPosters>-1)
	{
		this->qtyPosters = qtyPosters;
		retorno = 0;
	}
	return retorno;
}
int sale_setQtyPostersTxt(Sale* this, char* qtyPosters)
{
	int result = -1;
	char bufferQty[BUFFER_SIZE];

	if (this != NULL && qtyPosters != NULL && val_isValidNumber(qtyPosters))
	{
		strncpy(bufferQty, qtyPosters, BUFFER_SIZE);
		this -> qtyPosters = atoi(bufferQty);
		result = 0;
	}
	return result;
}
int sale_setFileName(Sale* this, char* fileName)
{
	int retorno = -1;
	if(this != NULL && fileName!=NULL && val_isValidAlphaNumeric(fileName))
	{
		strncpy(this->fileName,fileName,(int) sizeof(this->fileName));
		retorno = 0;
	}
	return retorno;
}
int sale_setPosterArea(Sale* this, int posterArea)
{
	int retorno = -1;
	if(this != NULL && (posterArea==1 || posterArea==2 || posterArea==3))
	{
		this->posterArea = posterArea;
		retorno = 0;
	}
	return retorno;
}
int sale_setPosterAreaTxt(Sale* this, char* posterArea)
{
	int retorno = -1;
	char bufferArea [BUFFER_SIZE];

	if(this != NULL && posterArea!=NULL && val_isValidNumber(posterArea))
	{
		strncpy(bufferArea,posterArea,(int) sizeof(this->posterArea));
		this->posterArea = atoi(bufferArea);
		retorno = 0;
	}
	return retorno;
}

int sale_setStatus(Sale* this, int status)
{
	int retorno = -1;
	if(this != NULL && (status == CHARGED || status == UNPAID))
	{
		this->status = status;
		retorno = 0;
	}
	return retorno;
}

int sale_setStatusTxt(Sale* this, char* status)
{
	int result = -1;
	char bufferStatus[BUFFER_SIZE];

	if (this != NULL && status != NULL && val_isValidNumber(status))
	{
		strncpy(bufferStatus, status, BUFFER_SIZE);
		this -> status = atoi(bufferStatus);
		result = 0;
	}
	return result;
}


