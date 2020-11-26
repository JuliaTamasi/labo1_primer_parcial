#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Linkedlist.h"
#include "Client.h"
#include "validations.h"



Client* client_new()
{
	return (Client*)malloc(sizeof(Client));
}

void client_delete(Client* this)
{
	free(this);
}
/* \brief add in a existing list of clients the values received as they are
 * \param in id: get id as int
 * \param char* name: get name as text
 * \param int workedHours: get worked hours as int
 * \param float salary: get salary as float
 * \returns memory address of client with loaded data or NULL if error
 */
Client* client_newWithParameters(int id, char* name, char* lastName, char* cuit)
{
	Client* this = client_new();

	if(this != NULL && id>-1 && name != NULL && lastName != NULL && cuit != NULL)
	{
		if( !client_setName(this, name) &&
			!client_setIdClient(this, id) &&
			!client_setLastName(this, lastName) &&
			!client_setCuit(this, cuit))
		{
			return this;
		}
	}
	client_delete(this);
	return NULL;
}

/* \brief add in a existing list of clients the values received as parameters as text
 * \param char* idStr: get id as text
 * \param char* name: get name as text
 * \param char* workedHours: get worked hours as text
 * \param char* salary: get salary as text
 * \returns memory address of client with loaded data or NULL if error
 */
Client* client_newParametros(char* id, char* name,char* lastName, char* cuit)
{
	Client* this = client_new();

	if(this != NULL && id != NULL && name != NULL && lastName != NULL && cuit != NULL)
	{
		if( !client_setIdTxt(this, id) &&
			!client_setName(this, name) &&
			!client_setLastName(this, lastName) &&
			!client_setCuit(this, cuit))
		{
			return this;
		}
	}
	client_delete(this);
	return NULL;
}
/** \brief compares a CUIT with a CUIT of the array to know if it was previously entered
 * \param Client* aClients, Pointer to Clients's array
 * \param int len, Array lenght
 * \param char* cuit, cuit to be compared
 * \return Return (0) if CUIT already exists (-1) if not
 */
/*int client_findByCuit(Linkedlist* this, char* cuit)
{
	int result = -1;
	for(int i=0;i<len;i++)
	{
		if(strcmp(cuit,aClients[i]->cuit)==0)
		{
			result = 0;
			break;
		}
	}
	return result;
}*/
void client_printHeader()
{
	printf("\n************************************** CLIENTES ******************************************\n");
	printf("\n------------------------------------------------------------------------------------------\n");
	printf("    ID    |            NOMBRE            |           APELLIDO           |      CUIT      |");
}

/*\brief prints the data of a certain client
 * \param LinkedList* pArrayListClient, pointer to LinkedList
 * \param int index, position of the linkedlist where the pointer to the searched client is located
 * \return [-1] if error / [0] if ok
 */
int client_printByIndex(LinkedList* pArrayListClient, int index)
{
	int result = -1;
	Client* pClient;
	Client bufferClient;

	if(pArrayListClient!=NULL && index>-1)
	{
		pClient = ll_get(pArrayListClient, index);
		if( !client_getName(pClient, bufferClient.name) &&
			!client_getLastName(pClient, bufferClient.lastName) &&
			!client_getIdClient(pClient, &bufferClient.idClient) &&
			!client_getCuit(pClient, bufferClient.cuit))
		{
			printf( "\n------------------------------------------------------------------------------------------\n"
					"%-10d|%-30s|%-30s|%-16s|\n"
					"------------------------------------------------------------------------------------------\n",bufferClient.idClient, bufferClient.name, bufferClient.lastName,bufferClient.cuit);
			result = 0;
		}
	}
	return result;
}

/** \brief compares a CUIT to know if it was previously entered
 * \param LinkedList* this, Pointer to LinkedList
 * \param char* cuit, cuit to be compared
 * \return Return (0) if CUIT already exists (-1) if not
 */
int client_findByCuit (LinkedList* this, char* cuit)
{
	int output = -1;
	Client* buffer;
	char bufferCuit [CUIT_LEN];

	if(this!=NULL && cuit!=NULL)
	{
		for (int i=0; i<ll_len(this); i++)
		{
			buffer = ll_get(this, i);
			if(buffer!=NULL && !client_getCuit(buffer, bufferCuit))
			{
				if(strcmp(bufferCuit,cuit)==0)
				{
					output = 0;
					break;
				}
				else
				{
					output = 1;
				}
			}
		}
	}
	return output;
}
/** \brief compares an ID to know if it was previously entered
 * \param LinkedList* this, Pointer to LinkedList
 * \param int idClient, ID to be compared
 * \param int* index, pointer to memory space where the data will be saved
 * \return Return (0) if OK and (-1) if ERROR
 */
int client_findIndexById (LinkedList* this, int idClient, int* index)
{
	int output = -1;
	Client* buffer;
	int bufferId;
	int i;

	if(this!=NULL && idClient>0)
	{
		for(i=0;i<ll_len(this);i++)
		{
			buffer = ll_get(this, i);
			if(buffer!=NULL && !client_getIdClient(buffer, &bufferId) && idClient==bufferId)
			{
				*index = i;
				output = 0;
				break;
			}
		}
	}
	return output;
}
/** \brief Busca el ID maximo en la lista de clientes
 * \param LinkedList *pArrayClients, Pointer to LinkedList
 * \return Return the maxID + 1 if OK and (-1) if ERROR
 */
int client_searchMaxId(LinkedList *pArrayClients)
{
	int result = -1;
	Client* bufferClient;
	int length = ll_len(pArrayClients);
	int id;
	int maxId;
	if (pArrayClients != NULL) {

		for (int i = 0 ; i < length ; i++)
		{
			bufferClient = ll_get(pArrayClients, i);
			client_getIdClient(bufferClient,&id);

			if (i == 0 || id > maxId)
			{
				maxId = id;
			}
		}
		result = maxId + 1;
	}
	return result;
}
/*int client_fCriterioPrint(void* pElement)
{
	int output = -1;
	Client* aux = (Client*) pElement;
	Client bufferClient;

	if( aux!=NULL && !client_getIdClient(aux, &bufferClient.idClient) &&
		!client_getName(aux, bufferClient.name) && !client_getLastName(aux, bufferClient.lastName) &&
		!client_getCuit(aux, bufferClient.cuit))
	{
		printf("Entre al if de la criterio");
		printf( "\n------------------------------------------------------------------------------------------\n"
				"%-10d|%-30s|%-30s|%-16s|\n"
				"------------------------------------------------------------------------------------------\n",bufferClient.idClient, bufferClient.name, bufferClient.lastName,bufferClient.cuit);
		output = 0;
	}
	return output;
}
*/
/******************* SETTERS & GETTERS ********************/

int client_getName(Client* this, char* name)
{
	int retorno = -1;
	if(this!=NULL)
	{
		strcpy(name,this->name);
		retorno = 0;
	}
	return retorno;
}
int client_getLastName(Client* this, char* lastName)
{
	int retorno = -1;
	if(this!=NULL)
	{
		strcpy(lastName,this->lastName);
		retorno = 0;
	}
	return retorno;
}
int client_getCuit(Client* this, char* cuit)
{
	int retorno = -1;
	if(this!=NULL)
	{
		strcpy(cuit,this->cuit);
		retorno = 0;
	}
	return retorno;
}
int client_getIdClient(Client* this, int* idClient)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*idClient = this->idClient;
		retorno = 0;
	}
	return retorno;
}
int client_setName(Client* this, char* name)
{
	int retorno = -1;
	if(this != NULL && val_isValidString(name, NAME_CLIENT_LEN))
	{
		strncpy(this->name,name,(int) sizeof(this->name));
		retorno = 0;
	}
	return retorno;
}
int client_setLastName(Client* this, char* lastName)
{
	int retorno = -1;
	if(this != NULL && val_isValidString(lastName, NAME_CLIENT_LEN))
	{
		strncpy(this->lastName,lastName,(int) sizeof(this->lastName));
		retorno = 0;
	}
	return retorno;
}
int client_setCuit(Client* this, char* cuit)
{
	int retorno = -1;
	if(this != NULL && val_isValidCuitClient(cuit))
	{
		strncpy(this->cuit,cuit,(int) sizeof(this->cuit));
		retorno = 0;
	}
	return retorno;
}
int client_setIdClient(Client* this, int idClient)
{
	int retorno = -1;
	if(this != NULL && idClient>-1)
	{
		this->idClient = idClient;
		retorno = 0;
	}
	return retorno;
}
/* \brief set id of client as text
 * \param Client* this: pointer to client
 * \param int* id: id by reference as text to be set to that client
 * \return [-1] if error / [0] if ok
 */
int client_setIdTxt(Client* this, char* idClient)
{
	int result = -1;
	char bufferId [BUFFER_SIZE];

	if(this != NULL && idClient != NULL && val_isValidNumber(idClient))
	{
		strncpy(bufferId, idClient, BUFFER_SIZE);
		this -> idClient = atoi(bufferId);
		result = 0;
	}
	return result;
}
