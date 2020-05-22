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


int main() {
    printf ("Добро пожаловать в phbook util (util-linux phone book v1.0).\n");
    int cat_size = 1; // Размер каталога
    int cat_cur = 0;  // Текущий каталог
    bookpath *catalog = (bookpath*) malloc (cat_size*sizeof (bookpath)); if (NULL==catalog) { exit (1); } 
    catalog[0].path = "data/book.r";
    catalog[0].cur_book = init_book ();
    upload_book (catalog[0].path, 256, catalog[0].cur_book);

    char key;
    char extra_key;
    while ('Q'!=(key = get_key ("\n\nКоманда (? для справки): ", '\0', "\nQ?qwWfbpn"))) {
        switch (key) {
        case '?':
            help ();
            break;
        case 'q':
            key = '\0';
            key = get_key ("\nЗакрыть книгу без сохранения? (y/N): ", 'N', "\nyYnN");
            if ('y'==key || 'Y'==key) {
                if (cat_size==1) { 
                    close_book (catalog[0].cur_book);
                    catalog[0].cur_book = init_book ();
                    //upload_book (catalog[0].path, 256, catalog[0].cur_book); 
                } else { 
                    close_path (cat_cur, catalog, &cat_size); 
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
            print_nickname (get_line ("\nПоиск по имени: ", "", 256), *catalog[cat_cur].cur_book, 15);
            break;
        case 'b':
            print_book (*catalog[cat_cur].cur_book, 15);
            break;
        case 'p':
            path_print_page (get_word ("\nБуква страницы: ", "", 256)[0], *catalog[cat_cur].cur_book, 15);
            break;
        case 'n':
            path_add_record (get_word ("\nНовое имя: ", "", 256), get_number_set ("\nВведите номер: ", "\n0123456789", 4, 0, 0,9999, 0,999, 0,999, 0,9999), catalog[cat_cur].cur_book);
            break;

        default:
            break;
        }
    }
    return 0;
}

