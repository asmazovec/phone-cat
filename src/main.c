/* MIT License
 *
 * Copyright (c) 2020 Alexander Mazovets
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */ 


#include "consupport.h"
#include "phonebook.h"
//#include <stdlib.h>


typedef struct {
    book *cur_book;
    char *path;
} bookpath;


int _delete_record (bookpath *bookshelf, int cur_path) {
    int f = 0;
    int select = 0;
    record **removable_list = find_nickname ( 
            get_line ("\nВведите имя, которое хотите удалить: ", "\0", NULL, 256),
            *bookshelf[cur_path].cur_book);
    book *page;

    printf ("\n");
    f = 0;
    while (removable_list[f]) {
        printf ("   %i :: ", f);
        print_record (*removable_list[f++], 15);
        printf ("\n");
    }

    if (f==0) {
        printf ("Записи с таким именем не существует\n");
    } else if (f==1) {
        page = find_page (removable_list[0]->nickname[0], 
                *bookshelf[cur_path].cur_book);
        delete_record (removable_list[0], page);
    } else {
        select = get_number ("Выберите номер записи (по умолчанию 0): ", 0, f-1, 0, NULL, 256);
        page = find_page (removable_list[select]->nickname[0], 
                *bookshelf[cur_path].cur_book);
        delete_record (removable_list[select], page);
    }
    return 0;
}


int main() {
    printf ("Добро пожаловать в phbook util (util-linux phone book v1.0).\n\n");

    int number_path = 1;
    int cur_path = 0;
    bookpath *bookshelf = (bookpath*) malloc (sizeof (bookpath));
    bookshelf[cur_path].path = get_word ("Открыть книгу (по умолчанию data/book.r): ",
            "data/book.r", NULL, 256);
    bookshelf[cur_path].cur_book = init_book ();
    upload_book (bookshelf[cur_path].path, 256, bookshelf[cur_path].cur_book);

    char key;
    while ('q'!=(key = get_key ("\n\nКоманда (? для справки): ", '\0', "?fqwWlpdunb"))) {
        switch (key) {
        case '?':
            printf ("\nСправка:\n"
                    "\n"
                    "   ?   вывод этого списка\n"
                    "   f   открытые книги\n"
                    "\n"
                    "  Выход и работа с файлами\n"
                    "   q   выход без сохранения изменений\n"
                    "   w   сохранение книги в файл \n"
                    "   W   сохранение книги в файл по новому пути\n"
                    "\n"
                    "  Печать записей\n"
                    "   p   варианты просмотра записей\n"
                    "      > b   печать всей книги\n"
                    "      > p   печать одной страницы\n"
                    "      > f   печать по имени\n"
                    "\n"
                    "  Редактирование книги\n"
                    "   d   удалить запись\n"
                    "   u   редактировать запись\n"
                    "   n   создать новую запись\n"
                    "   b   загрузить новую книгу для редактирования\n"
                    );
            break;
        
        case 'f':
            for (int i = 0; i<number_path; i++) {
                printf (" %c %i :: %s\n", (i==cur_path)? '>': ' ', i, bookshelf[i].path);
            }
            break;

        case 'w':
            write_book (*bookshelf[cur_path].cur_book, bookshelf[cur_path].path);
            break;
        
        case 'W':
            write_book (
                    *bookshelf[cur_path].cur_book, 
                    get_word ("\nВыберите путь сохранения (по умолчанию текущий путь): ",bookshelf[cur_path].path, NULL, 256));
            break;

        case 'p':
            key = get_key ("\nВыберите вариант просмотра (по умолчанию f - по имени): ", 'f', "bpf");
            switch (key) {
            case 'b':
                printf ("\n > %i :: %s записи:\n", cur_path, bookshelf[cur_path].path);
                print_book (*bookshelf[cur_path].cur_book, 15);
                break;

            case 'p':
                find_page (
                        get_word ("\nВведите букву страницы: ", "\0", NULL, 1)[0],
                        *bookshelf[cur_path].cur_book);
                printf ("\n > %i :: %s записи:\n", cur_path, bookshelf[cur_path].path);
                break;

            case 'f':
                printf ("\n > %i :: %s записи:\n", cur_path, bookshelf[cur_path].path);
                print_nickname (
                        get_line ("Введите имя, которое ищете: ", "\0", NULL, 256),
                        *bookshelf[cur_path].cur_book, 15);
                break;

            default: 
                printf ("\nОтмена печати\n");
                break;
            }
            break;

        case 'd':
            _delete_record (bookshelf, cur_path);
            break;

        case 'n':
            add_record (
                    *get_record (
                        get_line ("\nВведите имя: ", "\0", NULL, 256),
                        get_phone (
                            get_number ("\nВведите 1-4: ", 0, 9999, 0, NULL, 5),
                            get_number ("\nВведите 3: ", 0, 999, 0, NULL, 4),
                            get_number ("\nВведите 3: ", 0, 999, 0, NULL, 4),
                            get_number ("\nВведите 4: ", 0, 9999, 0, NULL, 5))),
                    bookshelf[cur_path].cur_book);
            break;

        default: 
            break;
        }
    }



    /*
    printf ("%s\n", get_line      ("Введи строку: ", NULL, NULL, 256)); 
    printf ("%s\n", get_line_caps ("ВВЕДИ СТРОКУ: ", "DEFAULT", NULL, 256)); 
    printf ("%s\n", get_word      ("Введи слово : ", "DEFAULT", NULL, 256)); 
    printf ("%s\n", get_word_caps ("ВВЕДИ СЛОВО : ", "DEFAULT", NULL, 256)); 
    printf ("%c\n", get_key       ("Введи символ: ", 'q', "qwerty")); 
    */
    /*
    book *b_test1 = init_book();
    
    phone ph_test = get_phone (8, 800, 555, 3535);
    record rec_test = *get_record ("Hello", ph_test);

    add_record (rec_test, b_test1); 
    add_record (*get_record ("Hello1", get_phone (1,1,1,1)), b_test1);
    add_record (*get_record ("Hello1", get_phone (1,1,1,1)), b_test1);
    print_book (*b_test1, 15);
    
    
    
    update_record (find_nickname ("H", *b_test1)[0], b_test1, "Hah", get_phone (1,1,1,1));
    print_book (*b_test1, 15);



    delete_record (find_nickname ("Hell", *b_test1)[0], find_page ('H', *b_test1));
    print_book (*b_test1, 15);

    //delete_record (find_nickname ("Hell", *b_test1)[0], find_page ('H', *b_test1));
    //print_book (*b_test1, 15);
    */
    return 0;
}
