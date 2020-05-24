/* MIT License
 * Copyright (c) Alexander Mazovets
*/

#include "consupport.h"


/* Возвращает специальный символ, читая его из стандартного потока
 * ввода.
 * Если символ не является специальным, возвращает '\0'.
 * */
char get_specific (const char *purpose) {
    char key = getchar ();
    while (*purpose) {
        if (key==*purpose++) { return key; }
    }
    return '\0';
}

/* Приглашение к считыванию строки из стандартного потока ввода. 
 * prompt - приглашение ко вводу,
 * def - ввод по умолчанию,
 * length - длина считываемой строки.
 * */
char *get_line (const char *prompt, const char *def, int length) {
    printf ("%s", prompt); // приглашение.
    char *line = (char*) malloc (length*sizeof (char)); if (NULL==line) { exit (1); } 

    int cur_pose = 0; // текущая позиция, по которой ведется запись в строку.
    do {
        if (cur_pose>=length) { while (getchar ()!='\n'); break; } // достигнут предел для записи.
        line[cur_pose] = getchar (); 
    } while (line[cur_pose++]!='\n'); // основное условие завершения строки.
    if (cur_pose==1) { strcpy (line, def); return line; } // пустой ввод вернет default.
    line[cur_pose-1] = '\0';  
    return line;
}

/* Приглашение к считыванию строки заглавными буквами из стандартного потока ввода. 
 * prompt - приглашение ко вводу,
 * def - ввод по умолчанию,
 * length - длина считываемой строки.
 * */
char *get_line_capital (const char *prompt, const char *def, int length) {
    printf ("%s", prompt); // приглашение.
    char *line = (char*) malloc (length*sizeof (char)); if (NULL==line) { exit (1); } 

    int cur_pose = 0; // текущая позиция, по которой ведется запись в строку.
    do {
        if (cur_pose>=length) { while (getchar ()!='\n'); break; } // достигнут предел для записи.
        line[cur_pose] = toupper (getchar ()); 
    } while (line[cur_pose++]!='\n'); // основное условие завершения строки.
    if (cur_pose==1) { strcpy (line, def); return line; } // пустой ввод вернет default.
    line[cur_pose-1] = '\0';  
    return line;
}

/* Приглашение к считыванию слова до первого пробела из стандартного потока ввода. 
 * prompt - приглашение ко вводу,
 * def - значение по умолчанию,
 * length - длина считываемой строки.
 * */
char *get_word (const char *prompt, const char *def, int length) {
    printf ("%s", prompt); // приглашение.
    char *line = (char*) malloc (length*sizeof (char)); if (NULL==line) { exit (1); } 

    int cur_pose = 0; // текущая позиция, по которой ведется запись в строку.
    do {
        if (cur_pose>=length)      { while (getchar ()!='\n'); break; } // достигнут предел для записи.
        if (line[cur_pose-1]==' ') { while (getchar ()!='\n'); break; } // достигнут конец слова.
        line[cur_pose] = getchar (); 
    } while (line[cur_pose++]!='\n'); // основное условие завершения строки.
    if (cur_pose==1) { strcpy (line, def); return line; } // пустой ввод вернет default.
    line[cur_pose-1] = '\0';  
    return line;
}

/* Приглашение к считыванию слова до первого пробела из стандартного потока ввода. 
 * prompt - приглашение ко вводу,
 * def - значение по умолчанию,
 * length - длина считываемой строки.
 * */
char *get_word_capital (const char *prompt, const char *def, int length) {
    printf ("%s", prompt); // приглашение.
    char *line = (char*) malloc (length*sizeof (char)); if (NULL==line) { exit (1); } 

    int cur_pose = 0; // текущая позиция, по которой ведется запись в строку.
    do {
        if (cur_pose>=length)      { while (getchar ()!='\n'); break; } // достигнут предел для записи.
        if (line[cur_pose-1]==' ') { while (getchar ()!='\n'); break; } // достигнут конец слова.
        line[cur_pose] =  toupper (getchar ()); 
    } while (line[cur_pose++]!='\n'); // основное условие завершения строки.
    if (cur_pose==1) { strcpy (line, def); return line; } // пустой ввод вернет default.
    line[cur_pose-1] = '\0';  
    return line;
}


/* Специальный ввод символа. 
 * prompt - приглашение,
 * def - значение по умолчанию,
 * purpose - целевые символы.
 * */
char get_key (const char *prompt, char def, const char *purpose) {
    printf ("%s", prompt); // приглашение.
    char key = get_specific (purpose);
    if (key=='\n') { return  def; }
    while (getchar ()!='\n');
    return key;
}

/* Выделяет из строки нужное число цифр.
 * prompt - приглашение,
 * def - заполнит недобранные цифры,
 * count - ожидаемое число цифр.
 * */
int *get_sign_set (const char *prompt, int def, int count) {
    printf ("%s", prompt); // приглашение
    int *set = (int*) malloc (count*sizeof (int)); if (NULL==set) { exit (1); }

    char cur_char = '\0';

    int cur_sign = 0;
    int num_sign = 0;
    while (num_sign<count) {
        set[num_sign] = def;
        num_sign++;
    }
    
    num_sign = 0;
    do {
        if (num_sign>=count) { while (getchar ()!='\n'); break; } // достигнут предел для записи.
        cur_char = get_specific ("\n0123456789");
        if (cur_char!='\0') {
            if (cur_char=='0') { set[num_sign] = 0; }
            if (cur_char=='1') { set[num_sign] = 1; }
            if (cur_char=='2') { set[num_sign] = 2; }
            if (cur_char=='3') { set[num_sign] = 3; }
            if (cur_char=='4') { set[num_sign] = 4; }
            if (cur_char=='5') { set[num_sign] = 5; }
            if (cur_char=='6') { set[num_sign] = 6; }
            if (cur_char=='7') { set[num_sign] = 7; }
            if (cur_char=='8') { set[num_sign] = 8; }
            if (cur_char=='9') { set[num_sign] = 9; }
            num_sign++;
        }
    } while (cur_char!='\n'); // основное условие завершения строки.
    return set;
}

/* Ввод последовательности чисел.
 * prompt - приглашение,
 * def - значение по умолчанию,
 * count - количество читаемых чисел,
 * ... - на каждое новое число min1, max1, min2, max2, ...
 * */
int *get_number_set (const char *prompt, const char *purpose, int count, int def, ...) {
    printf ("%s", prompt); // приглашение.
    int *set = (int*) malloc (count*sizeof (int)); if (NULL==set) { exit (1); }

    va_list args;
    va_start (args, def);

    int cur_min; // минимум для текущего.
    int cur_max; // максимум для текущего.

    char *number_line; 
    int length;
    char cur_char;
    int cur_cell = 0;

    while (cur_cell<count) {
        cur_min = va_arg (args, int);
        cur_max = va_arg (args, int);
        length = 1;
        set[cur_cell] = def;
        number_line = (char*) malloc (length*sizeof (char)); if (NULL==number_line) { exit (1); }
        while ('\0'==(cur_char = get_specific (purpose)));
        number_line[length-1] = cur_char;
        while (cur_char!='\n' && cur_char!='\0') {
            number_line[length-1] = cur_char;
            cur_char = get_specific (purpose);
            length++;
            number_line = (char*) realloc (number_line, length*sizeof (char)); 
            if (NULL==number_line) { exit (1); }
            number_line[length-1] = '\0';
        }
        if ('\0'!=number_line[0])  { set[cur_cell] = atoi (number_line); }
        if (set[cur_cell]>cur_max) { set[cur_cell] = cur_max; }
        if (set[cur_cell]<cur_min) { set[cur_cell] = cur_min; }
        
        if ('\n'==number_line[0]) { 
            while (cur_cell<count) { set[cur_cell++] = def; } 
            free (number_line); 
            return set;
        }
        cur_cell++;
        if ('\n'==cur_char) { 
            while (cur_cell<count) { set[cur_cell++] = def; }
            free (number_line);
            return set;
        }
        free (number_line);
    }
    if ('\0'==number_line[0]) { while (getchar ()!='\n'); }
    va_end (args);
    return set;
}

