/*
 * controller.h
 *
 *  Created on: 23 nov. 2020
 *      Author: juji
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_loadClientFromText(char* path , LinkedList* pArrayListClient);
int controller_loadSaleFromText(char* path , LinkedList* pArrayListSale);
int controller_listClient(LinkedList* pArrayListClient);
int controller_listSale(LinkedList* pArrayListSale);
int controller_addClient(LinkedList* pArrayListClients);
int controller_addSale(LinkedList* pArrayListSale, LinkedList* pArrayListClients);
int controller_modifySale(LinkedList* pArrayListSales, LinkedList* pArrayListClients, int option);
int controller_saveSalesAsText(char* path, LinkedList* pArrayListSale);
int controller_saveClientAsText(char* path, LinkedList* clientList);

#endif /* CONTROLLER_H_ */
