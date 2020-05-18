/* MIT License 
 * Copyright (c) Alexander Mazovets
 * */

#ifndef PHONEBOOK_H_
#define PHONEBOOK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <assert.h>


/* Номер телефона. */
typedef struct {        
    int locale;         /// Международный идентификатор (4 - 1 символ).
    int service;        /// Код услуги (3 символа).
    int provider;       /// Код поставщика услуги (3 символа). 
    int abonent;        /// Идентификатор абонента (4 символа).
} phone;

/* Структура записи в книге. */
typedef struct record {     
    char* nickname;     /// Псевдоним владельца номера телефона.  
    phone phonenumber;  /// Номер телефона.
    struct record *next;/// Указатель на следующую запись на странице.
} record;

/* Структура телефонной книги */
typedef struct book {
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
int print_record (record current, int size);



/* Инициализирует новую книгу. */
book *init_book (book *new_book);

/* Находит страницу, соответствующую первой букве искомой записи в
 * телефонной книге. 
 * Возвращает указатель на страницу, если такая существует, иначе NULL.
 * */
book *find_page (char character, book cur_book);

/* Добавляет страницу буквы фамилии к книге в лексикографическом порядке. 
 * Возвращает указатель на страницу. 
 * */
book *add_page (char character, book *cur_book);

/* Печатает страницу из телефонной книги, на псевдоним отводится size
 * символов.
 * */
int print_page (book cur_page, int size);

/* Распечатывает всю телефонную книгу, на псевдоним отводится size
 * символов. 
 * */
int print_book (book cur_book, int size);

/* Находит запись, соответствующую искомой записи в телефонной книге.
 * Возвращает указатель на запись, если такая существует, иначе NULL.
 * */
record *find_record (record required, book cur_book);

/* Находит все записи по псевдониму в телефонной книге. Последний
 * элемент - указатель NULL.
 * */
record **find_nickname (char *nickname, book cur_book);

/* Печатает все номера телефона по искомому имени. */
int print_nickname (char *nickname, book cur_book);

/* Заносит запись в телефонную книгу. 
 * Возвращает указатель на эту запись в книге.
 * */
record *add_record (record current, book *cur_book);

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
