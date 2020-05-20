/* MIT License
 * Copyright (c) Alexander Mazovets
*/

#include "phonebook.h"

phone get_phone (int locale, int service, int provider, int abonent) {
    locale   = abs (locale);   locale   %= 10000;
    service  = abs (service);  service  %= 1000;
    provider = abs (provider); provider %= 1000;
    abonent  = abs (abonent);  abonent  %= 10000;

    phone tmp = {locale, service, provider, abonent};
    return tmp;
}

int phone_cmp (phone phone1, phone phone2) {
    if ((phone1.locale  == phone2.locale)   &&
        (phone1.service == phone2.service)  &&
        (phone1.provider== phone2.provider) &&
        (phone1.abonent == phone2.abonent)) 
    {
        return 0;
    }
    return 1;
}

int print_phone (phone current) {
    return printf ("%d(%03d)%03d-%04d ", 
            current.locale,
            current.service,
            current.provider,
            current.abonent
            );
}



record *get_record (char *nick, phone number) {
    record *new_record = (record*) malloc (sizeof (record)); 
    if (NULL==new_record) { exit (1); }
    
    new_record->nickname = nick;
    new_record->phonenumber = number;
    new_record->next = new_record;
    return new_record;
}

record *update_record (
        record *old_record,
        book *cur_book,
        char *new_name,
        phone new_number) {
    delete_record (old_record, find_page (old_record->nickname[0], *cur_book));
    return add_record (*get_record (new_name, new_number), cur_book);
}

int record_cmp (record record1, record record2) {
    if ((0==strcmp (record1.nickname, record2.nickname)) &&
        (0==phone_cmp (record1.phonenumber, record2.phonenumber))) 
    {
        return 0;
    }
    return 1;
}

int print_record (record current, int size) {
    printf ("%-*s :: ", size ,current.nickname);
    print_phone (current.phonenumber);
    return 0;
}



book *init_book (void) {
    book *new_book = (book*) malloc (sizeof (book));
    if (NULL==new_book) { exit (1); }

    new_book->character = '\0';
    new_book->node = (record*) malloc (sizeof (record));
    new_book->node = get_record ("\0", get_phone (0, 0, 0, 0));
    new_book->node->next = new_book->node;

    new_book->next = new_book;
    new_book->prev = new_book;
    return new_book;
}

book *find_page (char character, book cur_book) {
    book *pointer = cur_book.next;
    while (pointer->character!='\0' && character!=pointer->character) {
        pointer = pointer->next;
    }
    if (pointer->character!='\0') { return pointer; }
    return NULL;
}

book *add_page (char character, book *cur_book) {
    book *pointer = find_page (character, *cur_book);
    if (pointer) { return pointer; }   
    
    pointer = cur_book->next;
    while (pointer->character!='\0' && character>pointer->character) {
        pointer = pointer->next;
    }
    
    book *new_page = (book*) malloc (sizeof (book));
    if (NULL==new_page) { exit (1); }
    new_page->character = character;
    new_page->node = get_record ("\0", get_phone (0, 0, 0, 0));

    new_page->node->next = new_page->node;

    pointer->prev->next = new_page;
    pointer->prev->next->next = pointer;
    pointer->prev->next->prev = pointer->prev;
    pointer->prev = new_page;

    return new_page;
}

record *find_record (record required, book cur_book) {
    book *cur_page = find_page (required.nickname[0], cur_book);
    if (NULL==cur_page) { return NULL; }

    record *pointer = cur_page->node->next;
    while ( (strcmp (pointer->nickname, "\0")) &&
            (record_cmp (required, *pointer))) {
        pointer = pointer->next;
    }
    if (pointer->nickname!="\0") { return pointer; }
    return NULL;
}   

record *add_record (record current, book *cur_book) {
    record *pointer = find_record (current, *cur_book);
    if (pointer) { return pointer; }

    book *cur_page = add_page (current.nickname[0], cur_book);
    pointer = cur_page->node;
    while ( (pointer->next->nickname[0]!='\0') && 
            (strcmp (current.nickname, pointer->next->nickname)>0)) {
        pointer = pointer->next;
    }

    record *new_record = get_record (current.nickname, current.phonenumber);

    new_record->next = pointer->next;
    pointer->next = new_record;
    
    return pointer->next;
}

record **find_nickname (char *nickname, book cur_book) {
    assert (nickname);
    int length = 1;

    record **list = (record**) malloc (length*sizeof (record*));
    if (NULL==list) { exit (1); }
    list[0] = NULL;

    book *cur_page = find_page (nickname[0], cur_book);
    if (NULL==cur_page) { return list; }

    record *pointer = cur_page->node->next;
    while ( (strcmp (pointer->nickname, "\0")) &&
            (NULL==strstr (pointer->nickname, nickname))) {
        pointer = pointer->next;
    }
    
    while ( (strcmp (pointer->nickname, "\0")) &&
            (strstr (pointer->nickname, nickname))) {
        list = (record**) realloc (list, ++length*sizeof (record*));
        if (NULL==list) { exit (1); }

        list[length-2] = pointer;
        list[length-1] = NULL;

        pointer = pointer->next;
    }
    return list;
}

int print_nickname (char* nickname, book cur_book, int size) {
    record **list = find_nickname (nickname, cur_book);
    int i = 0;
    while (list[i]) {
        printf ("%4d :: ", i);
        print_record (*list[i++], size);
        printf ("\n");
    } 
    return 0;
}

int print_page (book cur_page, int size) {
    printf ("Page %c  ", cur_page.character);

    record *pointer = cur_page.node->next;
    while ( strcmp (pointer->nickname, "\0")) {
        print_record (*pointer, size);
        printf ("\n        ");
        pointer = pointer->next;
    }
    printf ("\n"); 
    return 0;
}

int print_book (book cur_book, int size) {
    book *pointer = cur_book.next;
    while (pointer->character!='\0') {
        print_page (*pointer, size);
        pointer = pointer->next;
    }
    return 0;
}

int delete_record (record *removable, book *page) {
    record *pointer = page->node;

    while (pointer->next!=removable) {
        if (pointer->next->nickname[0]=='\0') { return 1; }
        pointer = pointer->next;
    }

    if (page->node->next->next->nickname[0]=='\0') {
        page->prev->next = page->next;
        page->next->prev = page->prev;

        free (page->node);
        free (page);
    } else {
        record *rec_next = pointer->next->next;
        free (pointer->next);
        pointer->next = rec_next;
    }

    return 0;
}
 
int write_book (book cur_book, const char* path) {
    FILE* load = fopen (path, "w");
    if (NULL==load) { 
        fclose (load); 
        printf ("%s ошибка при открытии файла\n", path); 
        return 1;
    }
    
    book *book_pointer = cur_book.next;
    record *record_pointer = book_pointer->node->next;

    while (book_pointer->character!='\0') {
        while (strcmp (record_pointer->nickname, "\0")) {
            fprintf (load, "%04d-%03d-%03d-%04d %s\n",
                     record_pointer->phonenumber.locale,
                     record_pointer->phonenumber.service,
                     record_pointer->phonenumber.provider,
                     record_pointer->phonenumber.abonent,
                     record_pointer->nickname);
            record_pointer = record_pointer->next;
        }
        book_pointer = book_pointer->next;
        record_pointer = book_pointer->node->next;
    }

    fclose (load);
    return 0;
}

int upload_book (const char *path, int size, book *cur_book) {
    assert (cur_book);
    FILE* load = fopen (path, "a+");
    if (NULL==load) { 
        fclose (load);
        printf ("%s ошибка при открытии файла\n", path);
        return 1; }

    int locale;
    int service;
    int provider;
    int abonent;

    char line_record[size];
    char *nickname = (char*) malloc (size*sizeof (char));
    if (NULL==nickname) { fclose (load); exit (1); }

    char *token;
    while (fgets (line_record, size, load)) {
        token = strtok (line_record, "-"); locale = atoi (token);
        token = strtok (NULL, "-"); service = atoi (token);
        token = strtok (NULL, "-"); provider = atoi (token);
        token = strtok (NULL, " "); abonent = atoi (token);
        token = strtok (NULL, "\n");
        strcpy (nickname, token);
        add_record (*get_record (nickname, get_phone (locale, service, provider, abonent)), cur_book);    
    }

    fclose (load);
    return 0;
}

book *close_book (book *cur_book) {
    book *cur_page = cur_book->next;
    record *pointer = cur_page->node;

    while (cur_page->character!='\0') {
        while (cur_page->node->next->nickname[0]!='\0') {
            while (pointer->next->next->nickname[0]!='\0') {
                pointer = pointer->next;
            }
            free (pointer->next);
            pointer->next = cur_page->node;
            pointer = cur_page->node;
        }
        free (cur_page->node);
        cur_page = cur_page->next;
        free (cur_page->prev);
    }
    cur_page->next = cur_page;
    cur_page->prev = cur_page;
    return cur_page;
}
