#ifndef UTN_H_
#define UTN_H_
#define RETRIES 3

int utn_getNumberFloat(char *message, float *number, int attempts, int max, int min);
int utn_getMenu(int *number, int retries, int max, int min);
int utn_getName(char message[], char errorMessage[], char* pResult,int attemps, int limit);
int utn_getNumber(char *message, int *number, int attempts, int max, int min);
int utn_getCuit(char* msg, char* msgError, char *pResult, int len, int attemps);
int utn_getStringAlphanumeric(char* msg, char* msgError, char *pResult, int attemps, int len);
#endif /* UTN_H_ */
