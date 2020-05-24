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
 * */ 

#include "consupport.h"
#include "main.h"

#if defined (__WIN32__) || defined (__WIN64__)
#include <Windows.h>
#endif

char *version = "v1.0 release";


int main() {
    char *def_path;

    char *tmp_line;
    int *tmp_number;
    
    int cat_size = 1; // Размер каталога
    int cat_cur = 0;  // Номер текущего каталога

    bookpath *catalog = (bookpath*) malloc (cat_size*sizeof (bookpath)); if (NULL==catalog) { exit (1); } 

#if defined (__gnu_linux__)
    def_path = "data/book.def";
    printf ("Добро пожаловать в \x1b[1;32mphone cat =^_^= util\x1b[0m (UTIL-Linux Phone Book %s).", version);

    #define PROMPT printf ("\n\nОткрытая книга \x1b[1m%s\x1b[0m\n", catalog[cat_cur].path);

#elif defined (__WIN32__) || defined (__WIN64__)
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    def_path = "data\\book.def.r";
    printf ("Добро пожаловать в phone cat =^_^= util (UTIL-Windows Phone %s).", version);

    printf ("\n\nПредупреждение! \nКодировка UTF-8 некорректно работает со вводом русских символов.\n");
    #define PROMPT printf ("\n\nОткрытая книга %s\n", catalog[cat_cur].path);

#else 
    printf ("Неизвестная операционная система.\n");
    exit (2);

#endif

    catalog[0].cur_book = init_book ();
    catalog[0].path = def_path;
    upload_book (catalog[0].path, 256, catalog[0].cur_book);

    char key = '\0';
    char extra_key;
    while ('Q'!=key) {
        PROMPT;
        key = get_key ("Команда (? для справки): ", '\0', "\n?hHoqQwWflbpnudc][");
        switch (key) {
        case '?':
            help ();
            break;
        case 'h':
            help ();
            break;
        case 'H':
            help ();
            break;
        case 'o':
            cat_size++;
            catalog = (bookpath*) realloc (catalog ,cat_size*sizeof (bookpath));
            cat_cur = cat_size-1;
            catalog[cat_cur].cur_book = init_book ();
            tmp_line = get_word ("\nРасположение книги : ", def_path, 256);
            catalog[cat_cur].path = tmp_line;
            upload_book (catalog[cat_cur].path, 256, catalog[cat_cur].cur_book); 
            break;
        case 'q':
            key = get_key ("\nЗакрыть книгу без сохранения? (y/N): ", 'N', "\nyY");
            if ('y'==key || 'Y'==key) {
                if (cat_size==1) { 
                    close_book (catalog[0].cur_book);
                    catalog[0].cur_book = init_book ();
                    catalog[0].path = def_path;
                    upload_book (catalog[0].path, 256, catalog[0].cur_book); 
                } else { 
                    close_path (catalog, cat_size, cat_cur); 
                    cat_cur--;
                    cat_size--;
                    cat_cur = abs (cat_cur %= cat_size);
                    catalog = (bookpath*) realloc (catalog, cat_size*sizeof (bookpath)); if (NULL==catalog) { exit (1); }
                }
            } else { 
                printf ("\nОтмена закрытия\n"); 
            }
            break;
        case 'w':
            write_book (*catalog[cat_cur].cur_book, catalog[cat_cur].path);
            break;
        case 'W':
            write_book (*catalog[cat_cur].cur_book, get_word ("\nКаталог для записи (текущий по умолчанию): ", catalog[cat_cur].path, 256));
            break;
        case 'f':
            print_nickname (get_line ("\nПоиск по части имени: ", "", 256), *catalog[cat_cur].cur_book, 15);
            break;
        case 'b':
            print_book (*catalog[cat_cur].cur_book, 15);
            break;
        case 'p':
            path_print_page (get_word ("\nБуква страницы: ", "", 256)[0], *catalog[cat_cur].cur_book, 15);
            break;
        case 'n':
            add_record (*path_ask_record ("", NULL, 15), catalog[cat_cur].cur_book);
            break;
        case 'u':
            path_update_record (catalog[cat_cur].cur_book);
            break;
        case 'd':
            path_delete_record (catalog[cat_cur].cur_book);
            break;
        case 'c':
            for (int i = 0; i<cat_size; i++) {
                printf (" %c %d :: %s\n", (cat_cur==i)? '>': ' ', i+1, catalog[i].path);
            }
            break;
        case ']':
            cat_cur++; 
            cat_cur = abs (cat_cur %= cat_size);
            break;
        case '[':
            cat_cur--;
            cat_cur = abs (cat_cur %= cat_size);
            break;
        default:
            break;
        }
    }
    printf ("\n");
    return 0;
}


