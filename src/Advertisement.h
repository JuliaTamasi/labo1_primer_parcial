/*
 ============================================================================
 Name        : labo1_primer_parcial.c
 Author      : Julia Tamasi
 Description : Primer Parcial Laboratorio I
 ============================================================================
 */

#ifndef ADVERTISEMENT_H_
#define ADVERTISEMENT_H_
#define AD_LEN 63
#define QTY_AD 999
#define ACTIVE 1
#define PAUSED 0
#include "Client.h"
typedef struct
{
	int idAd;
	int isEmpty;
	int status;
	char adText [AD_LEN];
	int area;
	int idClient;
}Advertisement;
int ad_addElement(Advertisement* pArray, int len, Client* AClients, int lenClients);
int ad_initArray(Advertisement* pArray, int len);
int ad_printByClientId(Advertisement* pArray,int len,int idClient);
int ad_removeAd(Advertisement* pArray, int len, int idClient);
int ad_findIndexById(Advertisement* pArray, int len, int id);
int ad_status(Advertisement *pArray, int len, Client *aClients, int lenClients, int chosenOption);
int ad_arrayIsEmpty (Advertisement* pArray, int len);
#endif /* ADVERTISEMENT_H_ */
