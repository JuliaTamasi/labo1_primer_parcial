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
int ad_addElement(Advertisement* arrayAds, int len, Client* AClients, int lenClients);
int ad_initArray(Advertisement* arrayAds, int len);
int ad_printByClientId(Advertisement* arrayAds,int len,int idClient);
int ad_removeAd(Advertisement* arrayAds, int len, int idClient);
int ad_findIndexById(Advertisement* arrayAds, int len, int id);
int ad_status(Advertisement *arrayAds, int len, Client *aClients, int lenClients, int chosenOption);
int ad_arrayIsEmpty (Advertisement* arrayAds, int len);
int ad_addHardcode(Advertisement* pArrayAds, int lenAds);
#endif /* ADVERTISEMENT_H_ */
