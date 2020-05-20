/* MIT License
 * Copyright (c) Alexander Mazovets
*/

#include "consupport.h"


char *get_line (const char *prompt, char *def, char *current, int size) {
    current = (char*) malloc ((size+1)*sizeof (char));
    current[0] = '\0';
    
    printf ("%s", prompt);

    char c;
    do {
        c = getchar ();
        current[strlen (current)] = c;
    } while (c!='\n' && strlen (current)<size);

    if (current[0]=='\n' && def) { return def; }
    current[strlen (current)-1] = '\0';

    return current;
}


char *get_line_caps (const char *prompt, char *def, char *current, int size) {
    current = (char*) malloc ((size+1)*sizeof (char));
    current[0] = '\0';
    
    printf ("%s", prompt);

    char c;
    do {
        c = getchar ();
        current[strlen (current)] = toupper (c);
    } while (c!='\n' && strlen (current)<size);

    if (current[0]=='\n' && def) { return def; }
    current[strlen (current)-1] = '\0';

    return current;
}


char *get_word (const char *prompt, char *def, char *current, int size) {
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

    if (current[0]=='\n' && def) { return def; }
    current[strlen (current)-1] = '\0';

    return current;
}


char *get_word_caps (const char *prompt, char *def, char *current, int size) {
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

    if (current[0]=='\n' && def) { return def; }
    current[strlen (current)-1] = '\0';
    
    return current;
}


char get_key (const char *prompt, char def, const char *purposes) {
    printf ("%s", prompt);

    char c = getchar ();
    if (c=='\n') {
        return def; 
    } 
    while (getchar ()!='\n');

    do {
        if (*purposes==c) { return c; } 
    } while (*purposes++);

    return '\0';
}


int get_number (const char *prompt, int min, int max, int def, int *current, int size) {
    char *line = (char*) malloc ((size+1)*sizeof (char));
    line[0] = '\0';

    printf ("%s", prompt);

    char c;
    do {
        c = getchar ();
        line[strlen (line)] = c;
        if (c==' ') {
            while (getchar ()!='\n');
        }
    } while (c!='\n' && c!=' ' && strlen (line)<size);

    if (line[0]=='\n') { return def; }
    line[strlen (line)] = '\0';
    
    int out = atoi (line);
    if (out > max) {
        return max;
    } else if (out < min) {
        return min;
    }

    return out;
}
