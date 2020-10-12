/*
 ============================================================================
 Name        : labo1_primer_parcial.c
 Author      : Julia Tamasi
 Description : Primer Parcial Laboratorio I
 ============================================================================
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#define NAME_LEN 50
#define CUIT_LEN 14
#define CLIENT_LEN 99
#define RETRIES 3

typedef struct
{
	char name [NAME_LEN];
	char lastName [NAME_LEN];
	int isEmpty;
	int idClient;
	char cuit [CUIT_LEN];
}Client;
int cli_initArray(Client* pArray, int len);
int cli_addElement(Client* pArray, int len);
int cli_printArray(Client* pArray, int len);
int cli_modifyClient (Client* pArray, int len);
int cli_findIndexById(Client* pArray, int len, int id);
int cli_removeClient(Client* pArray, int len, int idClient);
#endif /* CLIENT_H_ */
