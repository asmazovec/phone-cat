/* MIT License 
 * Copyright (c) Alexander Mazovets
 * */

#ifndef PHONEBOOK_H_
#define PHONEBOOK_H_

#include <stdio.h>
#include <assert.h>
#include <string.h> 


/* Номер телефона. */
typedef struct {        
    int locale;         /// Международный идентификатор (4 - 1 символ).
    int service;        /// Код услуги (3 символа).
    int provider;       /// Код поставщика услуги (3 символа). 
    int abonent;        /// Идентификатор абонента (4 символа).
} phone;

/* Структура записи в книге. */
typedef struct {     
    char* nickname;     /// Псевдоним владельца номера телефона.  
    phone phonenumber;  /// Номер телефона.
    struct record *next;/// Указатель на следующую запись на странице.
} record;

/* Структура телефонной книги */
typedef struct {
    char character;     /// Буква текущей страницы книги.
    record *node;       /// Первая запись на странице, инициализирует страницу.
    struct book *next;  /// указатель на следующую страницу книги.
    struct book *prev;  /// указатель на предыдущую страницу книги.
} book;


/* Конструктор номера телефона. */
phone get_phone (
        int locale,
        int service,
        int provider,
        int abonent);

/* Редактирует существующий номер. 
 * Возвращает указатель на отредактированный номер.
 * */
phone *update_phone (
        phone *cur_phone,
        int new_locale,
        int new_service,
        int new_provider,
        int new_abonent);

/* Сравнивает номера телефона. 
 * Если одинаковые, возвращает 0, иначе 1.
 * */
int phone_cmp (phone phone1, phone phone2);

/* Выводит номер телефона inline */
int print_phone (phone current);



/* Конструктор записи телефонной книги. */
record get_record (
        char  *name,
        phone number);

/* Редактирует существующую запись. 
 * Возвращает указатель на отредактированную запись.
 * */
record *update_record (
        record *current,
        char   *new_name,
        phone  new_number);

/* Сравнивает 2 записи.
 * Если одинаковые, возвращает 0, иначе 1.
 * */
int record_cmp (record record1, record record2);

/* Выводит информацию о записи inline. */
int print_record (record current);



/* Находит запись в телефонной книге. 
 * Возвращает указатель на запись, если такая существует, иначе NULL.
 * */
record *find_record (record required, book cur_book);

/* Заносит запись в телефонную книгу. 
 * Возвращает указатель на эту запись в книге.
 * */
record *add_record (record new_record, book *cur_book);

/* Удаляет запись из телефонной книги. 
 * Если успех, возвращает 0, иначе 1.
 * */
int delete_record (record *current, book);

/* Загружает телефонную книгу из файла. */
book load_book (const char *path);

/* Записывает телефонную книгу на диск. 
 * Если успех, возвращает 0, иначе 1.
 * */
int write_book (book cur_book);


#endif /* PHONEBOOK_H_ */
