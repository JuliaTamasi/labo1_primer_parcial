/*
 * validations.h
 *
 *  Created on: 4 nov. 2020
 *      Author: juji
 */

#ifndef SRC_VALIDATIONS_H_
#define SRC_VALIDATIONS_H_

int val_isValidNumber(char* number);
int val_isValidString(char* string, int len);
int val_isValidFloat(char* number);
int val_isValidCuitClient(char* cuitClient);
int val_isValidAlphaNumeric(char* pResult);

#endif /* SRC_VALIDATIONS_H_ */
