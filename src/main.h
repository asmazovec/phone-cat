/* MIT License
 *
 * Copyright (c) 2020 Alexander Mazovets
 * */

#ifndef MAIN_H_
#define MAIN_H_

#include "phonebook.h"
#include "consupport.h"


typedef struct {
    book *cur_book;
    char *path;
} bookpath;

/* Спрашивает информацию о новых полях записи.
 * size - размер печати полученной записи.
 * */
record *path_ask_record (const char *def_name, phone *def_phone, int size) {
    int locale   = 0;       /// Международный идентификатор (4 - 1 символ).
    int service  = 0;       /// Код услуги (3 символа).
    int provider = 0;       /// Код поставщика услуги (3 символа). 
    int abonent  = 0;       /// Идентификатор абонента (4 символа).

    char *new_name;
    int *number;

    if (def_name[0]=='\0') {
        new_name = get_line ("\nНовое имя: ", "?NoName", 256); 
    } else {
        new_name = get_line ("\nНовое имя   (enter - пропустить): ", def_name, 256); 
    }
    if (NULL==def_phone) {
        number = get_sign_set ("Новый номер телефона: ", -1, 14);
    } else {
        number = get_sign_set ("Новый номер (enter - пропустить): ", -1, 14);
    }
    phone new_phone;
    if (NULL==def_phone || number[0]!=-1) {
        int i = 13;
        while (i+1>0) {
            if (number[i]!=-1) { break; }
            i--;
        }

        int dec = 1; int cur = i; i -= 4;
        while (cur>i && cur+1>0) {
            abonent += number[cur]*dec;
            dec*=10;
            cur--;
        }

        dec = 1; cur = i; i -= 3;
        while (cur>i && cur+1>0) {
            provider += number[cur]*dec;
            dec*=10;
            cur--;
        }

        dec = 1; cur = i; i -= 3;
        while (cur>i && cur+1>0) {
            service += number[cur]*dec;
            dec*=10;
            cur--;
        }

        dec = 1; cur = i; i -= 4;
        while (cur>i && cur+1>0) {
            locale += number[cur]*dec;
            dec*=10;
            cur--;
        }
        new_phone = get_phone (locale, service, provider, abonent);
    } else {
        new_phone = *def_phone;
    }

    record *new_record = get_record (new_name, new_phone); 

    printf ("\n");
    print_record (*new_record, size);
    printf ("\n"); 
    return new_record;
}

/* Закрытие книги по пути и удаление из каталога. */
int close_path (bookpath *catalog, int cat_size, int cat_cur)  {
    close_book (catalog[cat_cur].cur_book);
    for (int i = 0; i<cat_size-1; i++) {
        catalog[cat_cur+i] = catalog[cat_cur+i+1]; }
    return 0;
}

int path_print_page (char character, book cur_book, int size) {
    book *cur_page = find_page (character, cur_book); if (NULL==cur_page) { return 1; } 
    print_page (*cur_page, size); 
    return 0;
}

int path_update_record (book *cur_book) {
    char *line = get_line ("\nПоиск записи по части имени (enter - отмена): ", "", 256);
    if (line[0]=='\0') { printf ("\nОтмена редактирования\n"); return 1; }
    record *new_record;

    record **f_records = find_nickname (line, *cur_book);
    int i = 0;
    int cur = 0;
    while (f_records[i]) {
        printf ("%3d :: ", i+1);
        print_record (*f_records[i], 15);
        printf ("\n", i);
        i++;
    }
    free (line);
    if (i==0) {
        printf ("\nВы ошиблись при вводе или записи с таким именем не существует\n");
    } else if (i==1) {
        new_record = path_ask_record (f_records[0]->nickname, &f_records[0]->phonenumber, 15); 
        update_record (f_records[0], cur_book, new_record->nickname, new_record->phonenumber);
    } else {
        cur = *get_number_set ("\nНомер записи из списка (enter - отмена): ", "\n0123456789", 1, 0, 0, i+1);
        if (cur<1 || cur>i) { printf ("\nОтмена редактирования\n"); return 1; }
        
        new_record = path_ask_record (f_records[cur-1]->nickname, &f_records[cur-1]->phonenumber, 15); 
        update_record (f_records[cur-1], cur_book, new_record->nickname, new_record->phonenumber);
    }
    return 0;
}

int path_delete_record (book *cur_book) {
    char *line = get_line ("\nПоиск записи по части имени (enter - отмена): ", "", 256);
    if (line[0]=='\0') { printf ("\nОтмена удаления\n"); return 1; }
    record *new_record;

    record **f_records = find_nickname (line, *cur_book);
    int i = 0;
    int cur = 0;
    while (f_records[i]) {
        printf ("%3d :: ", i+1);
        print_record (*f_records[i], 15);
        printf ("\n", i);
        i++;
    }
    free (line);
    
    book *cur_page;
    char key;
    if (i==0) {
        printf ("\nВы ошиблись при вводе или записи с таким именем не существует\n");
    } else if (i==1) {
        key = get_key ("\nУдалить запись? (y/N): ", 'N', "\nyY");
        if ('y'==key || 'Y'==key) {
            cur_page = find_page (f_records[0]->nickname[0], *cur_book);
            delete_record (f_records[0], cur_page); 
        } else {
            printf ("\nОтмена удаления\n");
        }
    } else {
        cur = *get_number_set ("\nНомер записи из списка (пустой ввод - отмена): ", "\n0123456789", 1, 0, 0, i+1);
        if (cur<1 || cur>i) { printf ("\nОтмена редактирования\n"); return 1; }
        
        key = get_key ("\nУдалить запись? (y/N): ", 'N', "\nyY");
        if ('y'==key || 'Y'==key) {
            cur_page = find_page (f_records[cur-1]->nickname[0], *cur_book);
            delete_record (f_records[cur-1], cur_page); 
        } else {
            printf ("\nОтмена удаления\n");
        }
    }
    return 0;
}

int help (void) {
#if defined (__gnu_linux__)
    return printf (
            "\n"
            "Справка:\n"
            "\n"
            "\x1b[1;32m  Страница проекта: https://github.com/asmazovec/prog.sem2.8 \x1b[0m\n"
            "\n"
            "   ?   вывод этого списка\n"
            "\n"
            "\x1b[1m  Сохранение и выход \x1b[0m \n"
            "   o   открыть новую книгу (добавит книгу в каталог)\n"
            "   q   закрыть книгу без сохранения\n"
            "   Q   закрыть все книги в каталоге и выйти\n"
            "   w   сохранить книгу\n"
            "   W   сохранить книгу как\n"
            "\n"
            "\x1b[1m  Поиск \x1b[0m \n"
            "   f   поиск по части имени\n"
            "   b   просмотр всех записей в книге\n"
            "   p   просмотр всех записей на странице\n"
            "\n"
            "\x1b[1m  Редактирование \x1b[0m \n"
            "   n   новая запись\n"
            "   u   редактировать запись\n"
            "   d   удалить запись\n"
            "\n"
            "\x1b[1m  Каталог открытых книг \x1b[0m \n"
            "   c   просмотр каталога открытых книг\n"
            "   ]   переход к следующей книге из каталога\n"
            "   [   переход к предыдущей книге из каталога\n"
            );
#elif defined (__WIN32__) || defined (__WIN64__)
    return printf (
            "\n"
            "Справка:\n"
            "\n"
            "  Страница проекта: https://github.com/asmazovec/prog.sem2.8\n"
            "\n"
            "   ?   вывод этого списка\n"
            "\n"
            "  Сохранение и выход\n"
            "   o   открыть новую книгу (добавит книгу в каталог)\n"
            "   q   закрыть книгу без сохранения\n"
            "   Q   закрыть все книги в каталоге и выйти\n"
            "   w   сохранить книгу\n"
            "   W   сохранить книгу как\n"
            "\n"
            "  Поиск\n"
            "   f   поиск по имени части\n"
            "   b   просмотр всех записей в книге\n"
            "   p   просмотр всех записей на странице\n"
            "\n"
            "  Редактирование\n"
            "   n   новая запись\n"
            "   u   редактировать запись\n"
            "   d   удалить запись\n"
            "\n"
            "  Каталог открытых книг\n"
            "   c   просмотр каталога открытых книг\n"
            "   ]   переход к следующей книге из каталога\n"
            "   [   переход к предыдущей книге из каталога\n"
            );
    

#else
    return 0;

#endif
}


#endif /* MAIN_H_ */
