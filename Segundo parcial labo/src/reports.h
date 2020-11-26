/*
 * reports.h
 *
 *  Created on: 26 nov. 2020
 *      Author: juji
 */

#ifndef REPORTS_H_
#define REPORTS_H_

int rep_generateSalesReport (LinkedList* pArrayListSales, LinkedList* pArrayListClients, int op);
int rep_generateStats (LinkedList* pArrayListSales, LinkedList* pArrayListClients);
int rep_generateStatsClients (LinkedList* pArrayListSales, LinkedList* pArrayListClients, int op);
int rep_saleWithMorePosters(LinkedList* pArrayListSales, LinkedList* pArrayListClients);


#endif /* REPORTS_H_ */
