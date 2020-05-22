/* MIT License
 *
 * Copyright (c) 2020 Alexander Mazovets
 * */

#ifndef MAIN_H_
#define MAIN_H_

#include "phonebook.h"


typedef struct {
    book *cur_book;
    char *path;
} bookpath;


/* Закрытие книги по пути и удаление из каталога. */
int close_path (int cat_cur, bookpath *catalog, int *cat_size)  {
    close_book (catalog[cat_cur].cur_book);
    for (int i = 0; i<*cat_size-1; i++) {
        catalog[cat_cur+i] = catalog[cat_cur+i+1]; }
    *cat_size--;
    catalog = (bookpath*) realloc (catalog, *cat_size*sizeof (bookpath)); if (NULL==catalog) { exit (1); }
    return 0;
}

int path_print_page (char character, book cur_book, int size) {
    book *cur_page = find_page (character, cur_book); if (NULL==cur_page) { return 1; } 
    print_page (*cur_page, size); 
    return 0;
}

int path_add_record (char *new_name, int *number, book *cur_book) {
    phone new_phone = get_phone (number[0], number[1], number[2], number[3]);
    record *new_record = get_record (new_name, new_phone);
    add_record (*new_record, cur_book);
    return 0;
}

int help (void) {
    return printf (
            "\n"
            "Справка:\n"
            "\n"
            "   ?   вывод этого списка\n"
            "\n"
            "  Сохранение и выход\n"
            "   q   закрыть книгу без сохранения\n"
            "   Q   закрыть всё и выйти\n"
            "   w   сохранить книгу\n"
            "   W   сохранить книгу как\n"
            "\n"
            "  Поиск\n"
            "   f   по имени\n"
            "   b   распечатать книгу\n"
            "   p   распечатать страницу\n"
            "\n"
            "  Редактирование\n"
            "   n   новая запись\n"
            "   u   редактировать запись\n"
            "   d   удалить запись\n"
            "\n"
            "  Каталог\n"
            "   c   > o   открыть книгу\n"
            "       > P   книги в рабочем каталоге\n"
            "       > N   добавить книгу в рабочий каталог\n"
            "       > n   перейти к следующей книге в каталоге\n"
            "       > p   перейти к предыдущей книге в каталоге\n"
            );
}


#endif /* MAIN_H_ */
