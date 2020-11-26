/*
 * Sales.h
 *
 *  Created on: 23 nov. 2020
 *      Author: juji
 */

#ifndef SALE_H_
#define SALE_H_
#define NAME_LEN 100
#define BUFFER_SIZE 1024
#define CHARGED 1
#define UNPAID 0
#define CABA 1
#define ZONA_SUR 2
#define ZONA_OESTE 3

typedef struct
{
	int idSale;
	int idClient;
	int qtyPosters;
	char fileName[NAME_LEN];
	int posterArea;
	int status;
}Sale;

Sale* sale_new();
Sale* sale_newParametros(char* idSale, char* idClient, char* qtyPosters, char* fileName, char* posterArea, char* status);
Sale* sale_newWithParameters(int idSale, int idClient, int qtyPosters, char* fileName, int posterArea, int status);
void sale_delete(Sale* this);
int sale_setIdSale(Sale* this, int idSale);
int sale_setIdSaleTxt(Sale* this, char* idSale);
int sale_getIdSale(Sale* this, int* idSale);
int sale_setIdClient(Sale* this, int idClient);
int sale_setIdClientTxt(Sale* this, char* idClient);
int sale_getIdClient(Sale* this, int* idClient);
int sale_setQtyPosters(Sale* this, int qtyPosters);
int sale_setQtyPostersTxt(Sale* this, char* qtyPosters);
int sale_getQtyPosters(Sale* this, int* qtyPosters);
int sale_setFileName(Sale* this, char* fileName);
int sale_getFileName(Sale* this, char* fileName);
int sale_setPosterArea(Sale* this, int posterArea);
int sale_setPosterAreaTxt(Sale* this, char* posterArea);
int sale_getPosterArea(Sale* this, int* posterArea);
int sale_setStatus(Sale* this, int status);
int sale_setStatusTxt(Sale* this, char* status);
int sale_getStatus(Sale* this, int* status);
void sale_printHeader();
int sale_printByIndex(LinkedList* pArrayListSale, int index);
int sale_searchMaxId(LinkedList *pArraySales);
int sale_fCriterioFilterUnpaid(void* pElement);
int sale_fCriterioFilterCharged(void* pElement);
int sale_findIndexById (LinkedList* this, int idSale, int* index);
int sale_editFields(Sale* this);
int sale_editStatus (Sale* this);
void sale_castZoneToChar (int zone, char* castZone);
int sale_fCriterioReduceCompareIdClient(void* pElement, int idClient);
int sale_fCriterioReduceAccQtyPosters(void* pElement, int idClient);

#endif /* SALE_H_ */
