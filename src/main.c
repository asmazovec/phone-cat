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
    /*
    printf ("%i\n\n", get_number ("Что за число? ", NULL));
    printf ("%c\n\n", get_key ("Что за символ? ", "qwerty"));
    printf ("%s\n\n", get_word_caps ("ААА! БОЛЬШОЕ СЛОВО! ", NULL, 256));
    printf ("%s\n\n", get_line_caps ("ААА! БОЛЬШАЯ СТРОКА! ", NULL, 256));
    */
    //print_phone (get_phone (12342, 2, -73128, -13));
    
    phone ph_test1 = get_phone(2, 2, -73128, -13);
    phone ph_test2 = get_phone(8, 962, 221, 3874);

    print_phone (ph_test1);
    printf (" phone_cmp %d\n\n", phone_cmp (ph_test1, ph_test2));

    update_phone (&ph_test1, 8, 962, 221, 3874);
    
    print_phone (ph_test1);
    printf (" phone_cmp %d\n\n", phone_cmp (ph_test1, ph_test2));
    
    update_phone (&ph_test1, 8, 321, 323, 5321);


    record rec_test1 = get_record ("Hello", ph_test1);
    record rec_test2 = get_record ("Bye", ph_test2);

    print_record (rec_test1);
    printf (" record_cmp %d\n\n", record_cmp (rec_test1, rec_test2)); // 0

    update_record (&rec_test2, "Hello", ph_test1); 

    print_record (rec_test2); 
    printf (" record_cmp %d\n\n", record_cmp (rec_test1, rec_test2)); // 1


    book b_test = {'\0', NULL, NULL, NULL};



    
    
    return 0;
}
