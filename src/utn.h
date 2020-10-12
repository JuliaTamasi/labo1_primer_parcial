#ifndef UTN_H_
#define UTN_H_

int utn_getNumberFloat(char *message, float *number, int attempts, int max, int min);
int utn_getMenu(int *number, int retries, int max, int min);
int utn_getName(char message[], char errorMessage[], char* pResult,int attemps, int limit);
void utn_ordenarArray(int array[], int len);
int utn_imprimirArray(int array[], int limite);
int utn_getNumber(char *message, int *number, int attempts, int max, int min);
int utn_getAddress(char* msg, char* msgError, char *pResult, int attemps, int len);
int utn_getCuit(char* msg, char* msgError, char *pResult, int len, int attemps);
#endif /* UTN_H_ */
