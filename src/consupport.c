/* MIT License
 * Copyright (c) Alexander Mazovets
*/

#include "consupport.h"


char *get_line (const char *prompt, char *current, int size) {
    assert (size);
    current = (char*) malloc ((size+1)*sizeof (char));
    current[0] = '\0';
    
    printf ("%s", prompt);

    char c;
    do {
        c = getchar ();
        current[strlen (current)] = c;
    } while (c!='\n' && strlen (current)<size);
    current[strlen (current)] = '\0';

    return current;
}


char *get_line_caps (const char *prompt , char *current, int size) {
    assert (size);
    current = (char*) malloc ((size+1)*sizeof (char));
    current[0] = '\0';
    
    printf ("%s", prompt);

    char c;
    do {
        c = getchar ();
        current[strlen (current)] = toupper (c);
    } while (c!='\n' && strlen (current)<size);
    current[strlen (current)] = '\0';

    return current;
}


char *get_word (const char *prompt, char *current, int size) {
    assert (size);
    current = (char*) malloc ((size+1)*sizeof (char));
    current[0] = '\0';

    printf ("%s", prompt);

    char c;
    do {
        c = getchar ();
        current[strlen (current)] = c;
        if (c==' ') {
            while (getchar ()!='\n');
        }
    } while (c!='\n' && c!=' ' && strlen (current)<size);
    current[strlen (current)] = '\0';

    return current;
}


char *get_word_caps (const char *prompt, char *current, int size) {
    assert (size);
    current = (char*)malloc ((size+1)*sizeof (char));
    current[0] = '\0';

    printf ("%s", prompt);

    char c;
    do {
        c = getchar ();
        current[strlen (current)] = toupper (c);
        if (c==' ') {
            while (getchar ()!='\n');
        }
    } while (c!='\n' && c!=' ' && strlen (current)<size);
    current[strlen (current)] = '\0';
    
    return current;
}


char get_key (const char *prompt, const char *purposes) {
    printf ("%s", prompt);

    char c;
    scanf ("%c", &c);
    while (getchar ()!='\n');

    do {
        if (*purposes==c) 
            return c; 
    } while (*purposes++);

    return '\0';
}


int get_number (const char *prompt, int *current) {
    printf ("%s", prompt);
    int tmp;
    scanf ("%d", &tmp);
    while (getchar ()!='\n');

    if (current) { *current = tmp; }

    return tmp;
}
