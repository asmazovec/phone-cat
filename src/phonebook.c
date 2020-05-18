/* MIT License
 * Copyright (c) Alexander Mazovets
*/

#include "phonebook.h"

phone get_phone (
        int locale,
        int service,
        int provider,
        int abonent) {
    locale   = abs (locale);   locale   %= 10000;
    service  = abs (service);  service  %= 1000;
    provider = abs (provider); provider %= 1000;
    abonent  = abs (abonent);  abonent  %= 10000;

    phone tmp = {locale, service, provider, abonent};
    return tmp;
}

phone *update_phone (
        phone *cur_phone,
        int new_locale,
        int new_service,
        int new_provider,
        int new_abonent) {
    assert (cur_phone);
    *cur_phone = get_phone (new_locale, new_service, new_provider, new_abonent);
    return cur_phone;
}

int phone_cmp (phone phone1, phone phone2) {
    if (    (phone1.locale==phone2.locale) &&
            (phone1.service==phone2.service) &&
            (phone1.provider==phone2.provider) &&
            (phone1.abonent==phone2.abonent)) {
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



record get_record (
        char   *name,
        phone number) {
    assert (name);

    record tmp = {name, number};
    return tmp;
}

record *update_record (
        record *current,
        char   *new_name,
        phone  new_number) {
    assert (current);
    assert (new_name);
    
    *current = get_record (new_name, new_number);
    return current;
}

int record_cmp (record record1, record record2) {
    if (    (0==strcmp (record1.nickname, record2.nickname)) &&
            (0==phone_cmp (record1.phonenumber, record2.phonenumber))) {
        return 0;
    }
    return 1;
}

int print_record (record current, int size) {
    printf ("%-*s :: ", size ,current.nickname);
    print_phone (current.phonenumber);
    return 0;
}



book *init_book (book *new_book) {
    assert (new_book);
    new_book->character = '\0';
    new_book->node = (record*) malloc (sizeof (record));
    *new_book->node = get_record ("\0", get_phone (0, 0, 0, 0));
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
    new_page->node = (record*) malloc (sizeof (record));
    if (NULL==new_page->node) { exit (1); }
    update_record (new_page->node, "\0", get_phone (0, 0, 0, 0));
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
    while ( (strcmp (pointer->next->nickname, "\0")) &&
            (strcmp (current.nickname, pointer->next->nickname)>0)) {
        pointer = pointer->next;
    }

    record *new_record = (record*) malloc (sizeof (record));
    if (NULL==new_record) { exit (0); }
    update_record (new_record, current.nickname, current.phonenumber);

    new_record->next = pointer->next;
    pointer->next = new_record;
    
    return new_record;
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
            (strcmp (pointer->nickname, nickname))) {
        pointer = pointer->next;
    }
    
    while ( (strcmp (pointer->nickname, "\0")) &&
            (0==strcmp (pointer->nickname, nickname))) {
        list = (record**) realloc (list, ++length*sizeof (record*));
        if (NULL==list) { exit (1); }

        list[length-2] = pointer;
        list[length-1] = NULL;

        pointer = pointer->next;
    }
    return list;
}

int print_nickname (char* nickname, book cur_book) {
    record **list = find_nickname (nickname, cur_book);
    int i = 0;
    while (list[i]) { /* while (*list++) */
        print_phone (list[i++]->phonenumber);
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
/*
int delete_record (record current, book &cur_book) {
    
}
*/
 












