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


int main() {
    book b_test;
    init_book (&b_test);

    add_record (get_record ("Hello", get_phone (8, 912, 001, 0001)), &b_test); 
    add_record (get_record ("Hello", get_phone (8, 912, 002, 0002)), &b_test); 

    add_record (get_record ("Alice", get_phone (8, 942, 242, 7854)), &b_test); 
    add_record (get_record ("Alice", get_phone (8, 912, 002, 2554)), &b_test); 
    add_record (get_record ("Amigo", get_phone (8, 912, 002, 2554)), &b_test); 
 
    add_record (get_record ("Michael", get_phone (8, 912, 002, 5323)), &b_test); 
    add_record (get_record ("Alexander", get_phone (8, 912, 002, 9855)), &b_test); 
    add_record (get_record ("kipr-avtomoyka", get_phone (8, 912, 002, 0505)), &b_test); 

    add_record (get_record ("kipr-avtomoyka", get_phone (8, 912, 002, 0505)), &b_test); 

    print_book (b_test, 15);

    print_nickname ("Alice", b_test);
    /* протестировать find_nickname и print_nickname */
    return 0;
}
