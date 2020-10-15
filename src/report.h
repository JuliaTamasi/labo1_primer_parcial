/*
 ============================================================================
 Name        : labo1_primer_parcial.c
 Author      : Julia Tamasi
 Description : Primer Parcial Laboratorio I
 ============================================================================
 */

#ifndef REPORT_H_
#define REPORT_H_
#include <stdio.h>
#include <stdlib.h>
#include "Advertisement.h"
#include "Client.h"

int rep_printClientsAndActiveAds (Client* aClients, int len, Advertisement* pArray, int lenAds);
int rep_reports (Client* aClients, int lenClients, Advertisement* arrayAds, int lenAds);
typedef struct
{
	int id;
	int qtyAds;
	int isEmpty;
}AuxiliarClient;
#endif /* REPORT_H_ */
