#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_LEN 50
#define ARRAY_SIZE 4096

static int utn_myGets(char *array, int lenght);
static int utn_verifyNumArray(char array[]);
static int utn_verifyCharArray(char *pArray);
static int utn_verifyFloat(char array[]);
static int isAlphaNumeric(char* pResult);

//ESTATICAS
/*
 * \brief static function to use instead of scanf(); to pick up user data
 * \param char* array, pointer to array
 * \param int lenght, limit of array
 */
static int utn_myGets(char *array, int lenght) {
	int retorno = -1;
	if (array != NULL && lenght > 0 && fgets(array, lenght, stdin) == array) {
		fflush(stdin);
		if (array[strlen(array) - 1] == '\n' &&array[0]!='\n') {
			array[strlen(array) - 1] = '\0';
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Verifies if given array of number is a valid integer number
 * \param char* pArray, string to be asses
 * \return [1] if ok / [0] if error
 */
static int utn_verifyNumArray(char array[]) {
	int retorno = 1;
	int i = 0;
	if (array != NULL) {
		if (array[0] == '-') {
			i = 1;
		}
		for (; array[i] != '\0'; i++) {
			if ((array[i] > '9' || array[i] < '0')) {
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief Verifies if given array of number is a valid float number
 * \param char* pArray, string to be asses
 * \return [1] if ok / [0] if error
 */
static int utn_verifyFloat(char array[])
{
	int retorno = 1;
	int i = 0;
	int commaCounter = 0;
	if (array != NULL && strlen(array)>0)
	{
		if (array[0] == '-')
		{
			i = 1;
		}
		for (; array[i]!='\0'; i++)
		{
			if(array[i]=='.')
			{
				commaCounter++;
			}
			if(commaCounter>1 || ((array[i] > '9' || array[i] < '0') && array[i]!='.'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*
 * \brief Verifies if given string as a pointer is a valid string
 * \param char* pArray, string to be asses
 * \return [1] if ok / [0] if error
 */
static int utn_verifyCharArray(char *pArray)
{
	int retorno = 0;
	int i;
	if (pArray != NULL)
	{
		for (i = 0; pArray[i] != '\0'; i++)
		{
			if ((pArray[i] < 'a' || pArray[i] > 'z') && (pArray[i] < 'A' || pArray[i] > 'Z') && (pArray[i] != 32))
			{
				retorno = -1;
				break;
			}
		}
	}
	return retorno;
}
static int isAlphaNumeric(char* pResult)
{
	int retorno = 1;
	int i;
	if(pResult != NULL){
		for(i=0;pResult[i] != '\0';i++)
		{
			if((pResult[i] != ' ') && (pResult[i] < 'a' || pResult[i] > 'z') && (pResult[i] < 'A' || pResult[i] > 'Z') && (pResult[i] < '0' || pResult[i] > '9'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
//PUBLICAS
/* \ brief getName para pedirle al usuario que ingrese un caracter
 * \ param char *message es un puntero al espacio de memoria donde está el mensaje que verá el usuario
 * \ param char *userInput es el puntero al espacio de memoria donde se guarda el caracter que ingresa el usuario
 * \ param char *errorMessage es el puntero al espacio de memoria donde está el mensaje de error que se mostrará si el usario ingresa una opción incorrecta
 * \ param int attempts es la variable que decrementa en 1 cada vez que el usario comete un error al ingresar un caracter no válido
 * \ return (-1) Error / (0) Ok
 */
int utn_getName(char message[], char errorMessage[], char* pResult, int attemps, int limit)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	if (message != NULL && errorMessage != NULL && pResult != NULL && attemps >= 0)
	{
		do
		{
			printf("\n%s", message);
			if (utn_myGets(bufferString, ARRAY_SIZE) == 0 && utn_verifyCharArray(bufferString) == 0 && strnlen(bufferString, ARRAY_SIZE) < limit)
			{
				retorno = 0;
				strncpy(pResult, bufferString, limit);
				break;
			}
			else
			{

				printf("%s", errorMessage);
				attemps--;
			}
		}while (attemps >= 0);
	}
	return retorno;
}
void utn_ordenarArray(int array[], int len)
{
	int indice;
	int flagEstadoDesordenado = 1;
	int aux;
	while(flagEstadoDesordenado==1)
	{
		flagEstadoDesordenado=0;
		for(indice=0 ; indice<(len-1) ; indice++)
		{
			if(array[indice] > array[indice+1])
			{
				// intercambiar (swap)
				aux = array[indice];
				array[indice] = array[indice+1];
				array[indice+1] = aux;
				flagEstadoDesordenado=1;
			}
		}
	}
}
int utn_imprimirArray(int array[], int limite)
{
	int retorno = -1;
	int i;
	if(array!= NULL && limite > 0)
	{
		for (i=0; i<limite; i++)
		{
			printf("\nLa posicion es %d y el valor es: %d\n\n", i, array[i]);
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Requests a number from the user that represents a menu option
 * \param number*, pointer to the memory space where the data obtained will be saved
 * \param retries, opportunities to enter incorrect data
 * \param int min, Minimum allowed value
 * \param int max, Maximum allowed value
 * \return (-1) to indicate error/ (0) it's OK.
 */

int utn_getMenu(int *number, int retries, int max, int min)
{
	int retorno = -1;
	char textNumber[ARRAY_SIZE];
	if (number != NULL && min<=max && retries>=0)
	{
		do
		{
			printf( "Bienvenido. Elija una opcion:\n" //MENU INICIO
					"1- ALTA\n"
					"2- MODIFICACION\n"
					"3- BAJA\n"
					"4- REPORTE\n"
					"5- SALIR");
			if (utn_myGets(textNumber, ARRAY_SIZE) == 0 && utn_verifyNumArray(textNumber) == 1)
			{
				*number = atoi(textNumber);
				retorno = 0;
				break;
			}
			else
			{
				retries--;
				if (retries != 0)
				{
					printf("\nError, te quedan %d intentos \n", retries);
				}
			}
		} while (retries > 0);
	}
	return retorno;
}
/* \brief asks user for an integer number
 * \param char* message, message shown to user
 * \param int* number, pointer to memory space where value obtained will be saved
 * \param int attempts, number of attempts for the user to choose a correct number from the menu
 * \param int max, maximum value allowed
 * \param int min, minimum value allowed
 * \return [-1] if error / [0] if ok
 */
int utn_getNumber(char *message, int *number, int attempts, int max, int min)
{
	int retorno = -1;
	char bufferTextNumber[ARRAY_SIZE];
	int bufferNumber;
	if (message != NULL && number != NULL)
	{
		do {
			printf("%s\n", message);
			if( utn_myGets(bufferTextNumber, ARRAY_SIZE) == 0 &&
				utn_verifyNumArray(bufferTextNumber) == 1 && max >= min)
			{
				bufferNumber = atoi(bufferTextNumber);
				if(bufferNumber<=max && bufferNumber>=min)
				{
					*number = bufferNumber;
					retorno = 0;
					break;
				}
				else
				{
					attempts--;
					if (attempts != 0)
					{
						printf("\nError, te quedan %d intentos \n", attempts);
					}
				}
			}
			else
			{
				attempts--;
				if (attempts != 0)
				{
					printf("\nError. Te quedan %d intentos\n", attempts);
				}
			}
		} while (attempts > 0);
	}
	return retorno;
}
/* \brief asks user for a float number
 * \param char* message, message shown to user
 * \param float* number, pointer to memory space where value obtained will be saved
 * \param int attempts, number of attempts for the user to choose a correct number from the menu
 * \param int max, maximum value allowed
 * \param int min, minimum value allowed
 * \return [-1] if error / [0] if ok
 * */
int utn_getNumberFloat(char *message, float *number, int attempts, int max, int min)
{
	int retorno = -1;
	char bufferTextNumber[ARRAY_SIZE];
	float bufferFloat;
	if (message != NULL && number != NULL)
	{
		do
		{
			printf("%s\n", message);
			if (utn_myGets(bufferTextNumber, ARRAY_SIZE) == 0
					&& utn_verifyFloat(bufferTextNumber) == 1 && max >= min)
			{
				bufferFloat = atof(bufferTextNumber);
				if(bufferFloat<=max && bufferFloat>=min)
				{
					*number = bufferFloat;
					retorno = 0;
					break;
				}
				else
				{
					attempts--;
					if (attempts != 0)
					{
						printf("\nError, te quedan %d intentos \n", attempts);
					}
				}
			}
			else
			{
				attempts--;
				if (attempts != 0)
				{
					printf("\nError, te quedan %d intentos \n", attempts);
				}
			}
		}while (attempts > 0);
	}
	return retorno;
}
int utn_getAddress(char* msg, char* msgError, char *pResult, int attemps, int len)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0 && len>0)
	{
		do
		{
			printf("%s", msg);
			if(utn_myGets(bufferString, ARRAY_SIZE) == 0 && isAlphaNumeric(bufferString) == 1 && strnlen(bufferString, sizeof(bufferString)) < len)
			{
				retorno = 0;
				strncpy(pResult, bufferString, len);
				break;
			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}

		}while(attemps >= 0);
	}
	return retorno;
}
static int isCuit(char* pResult)
{
	int retorno = 1;
	int i;
	int dashCounter;
	if(pResult != NULL){
		for(i=0;pResult[i] != '\0';i++)
		{
			if(pResult[i] == '-')
			{
				dashCounter++;
			}
			if(dashCounter>2 || (pResult[i] != '-' && (pResult[i] > '9' || pResult[i] < '0')))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int utn_getCuit(char* msg, char* msgError, int *pResult, int attemps)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0)
	{
		do
		{
			printf("%s", msg);
			if(utn_myGets(bufferString, ARRAY_SIZE) == 0 && isCuit(bufferString) == 1)
			{
				bufferInt = atoi(bufferString);
				*pResult = bufferInt;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}

		}while(attemps >= 0);
	}
	return retorno;
}
