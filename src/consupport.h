/* MIT License
 * Copyright (c) Alexander Mazovets
*/ 


#ifndef CONSUPPORT_H_
#define CONSUPPORT_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>


char *get_line (const char *prompt, char *current, int size);
char *get_word (const char *prompt, char *current, int size);
char *get_word_caps (const char *prompt, char *current, int size);
char *get_line_caps (const char *prompt, char *current, int size);
char get_key (const char *prompt, const char *purposes);
int get_number (const char *prompt, int *current);


#endif /* CONSUPPORT_H_ */
