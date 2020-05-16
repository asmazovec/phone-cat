/* MIT License
 * Copyright (c) Alexander Mazovets
*/

#include "phonebook.h"

phone get_phone (
        int locale,
        int service,
        int provider,
        int abonent) {
    locale   *= (locale<0)?   -1: 1; locale   %= 10000;
    service  *= (service<0)?  -1: 1; service  %= 1000;
    provider *= (provider<0)? -1: 1; provider %= 1000;
    abonent  *= (abonent<0)?  -1: 1; abonent  %= 10000;

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
    return printf ("%d(%03d)%03d-%04d", 
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
    if (    (strcmp (record1.nickname, record2.nickname)) &&
            (phone_cmp (record1.phonenumber, record2.phonenumber))) {
        return 0;
    }
    return 1;
}

int print_record (record current) {
    printf ("%s :: ", current.nickname);
    print_phone (current.phonenumber);
    return 0;
}



// Нахожу лист нужной буквы в телефонной книге.
book *find_book (record required, const book *cur_book) {
    // Внутренний указатель на страницу.
    book *pointer = cur_book;
    while (cur_book->node!=NULL && required.nickname[0]!=cur_book->character) {
        cur_book = *cur_book->next;
    }
    return cur_book;
}

record *find_record (record required, book cur_book) {
    
    // Внутренний указатель внутри листа книги.
    record *pointer = cur_book.node;
    // Если лист искомой буквы существует, перебираю записи.
    if (pointer && required.nickname[0]==cur_book.character) {
        // Пока искомая запись не равна текущей и пока не дошли до конца списка.
        while (pointer && 1==record_cmp (required, *pointer)) {
            pointer = *pointer.next;
        }
        if (pointer) {
            return pointer;
        }
    }
    
    return NULL;
}

record *add_record (record new_record, book *cur_book) {
    if (NULL==cur_book->node) {
        new_record.next = NULL;
        *cur_book->node = new_record;
        return cur_book.node;
    }

    record *exists = find_record (new_record, *cur_book);
    if (exists) {
        return exists;
    }

    while () {
        
    }

    return ;
}
