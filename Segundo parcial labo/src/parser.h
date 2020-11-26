/*
 * parser.h
 *
 *  Created on: 23 nov. 2020
 *      Author: juji
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_clientFromText(FILE* pFile , LinkedList* pArrayListClient);
int parser_saleFromText(FILE* pFile , LinkedList* pArrayListSale);

#endif /* PARSER_H_ */
