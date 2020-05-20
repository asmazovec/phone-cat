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


char *get_line (const char *prompt, char *def, char *current, int size);
char *get_line_caps (const char *prompt, char *def, char *current, int size);
char *get_word (const char *prompt, char *def, char *current, int size);
char *get_word_caps (const char *prompt, char *def, char *current, int size);
char get_key (const char *prompt, char def, const char *purposes);
int get_number (const char *prompt, int min, int max, int def, int *current, int size);


#endif /* CONSUPPORT_H_ */
