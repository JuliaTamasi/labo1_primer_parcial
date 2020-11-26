/*
 * Client.h
 *
 *  Created on: 23 nov. 2020
 *      Author: juji
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#define NAME_CLIENT_LEN 100
#define CUIT_LEN 14
#define BUFFER_SIZE 1024

typedef struct
{
	char name [NAME_CLIENT_LEN];
	char lastName [NAME_CLIENT_LEN];
	char cuit [CUIT_LEN];
	int idClient;
}Client;

Client* client_new();
Client* client_newParametros(char* id, char* name,char* lastName, char* cuit);
Client* client_newWithParameters(int id, char* name, char* lastName, char* cuit);
void client_printHeader();
int client_printByIndex(LinkedList* pArrayListClient, int index);
void client_delete(Client* this);
int client_fCriterioFindMaxId (void* pElement);
int client_findByCuit (LinkedList* this, char* cuit);
int client_findIndexById (LinkedList* this, int idClient, int* index);
int client_searchMaxId(LinkedList *pArrayClients);


int client_setName(Client* this, char* name);
int client_getName(Client* this, char* name);
int client_setLastName(Client* this, char* lastName);
int client_getLastName(Client* this, char* lastName);
int client_setCuit(Client* this, char* cuit);
int client_getCuit(Client* this, char* cuit);
int client_setIdClient(Client* this, int idClient);
int client_setIdTxt(Client* this, char* idClient);
int client_getIdClient(Client* this, int* idClient);


#endif /* CLIENT_H_ */
