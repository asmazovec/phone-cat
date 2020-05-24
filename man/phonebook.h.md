# phonebook.h

Заголовочный файл реализует структуру телефонной книги.

- [structure phone](#phone)
- [structure record](#record)
- [structure book](#book)

## phone
- [get_phone ()](#get_phone)
- [phone_cmp ()](#phone_cmp)
- [print_phone ()](#print_phone)

## record
- [get_record ()](#get_record)
- [update_record ()](#update_record)
- [record_cmp ()](#record_cmp)
- [print_record ()](#print_record)

## book
- [init_book ()](#init_book)
- [find_page ()](#find_page)
- [add_page ()](#add_page)
- [print_page ()](#print_page)
- [print_book ()](#print_book)
- [find_record ()](#find_record)
- [find_nickname ()](#find_nickname)
- [print_nickname ()](#print_nickname)
- [add_record ()](#add_record)
- [delete_record ()](#delete_record)
- [close_book ()](#close_book)
- [upload_book ()](#upload_book)
- [write_book ()](#write_book)

---
<a name="phone"></a>
```C
typedef struct {        
    int locale;         /// Международный идентификатор (4 - 1 символ).
    int service;        /// Код услуги (3 символа).
    int provider;       /// Код поставщика услуги (3 символа). 
    int abonent;        /// Идентификатор абонента (4 символа).
} phone;
```

Номер телефона. 


---
<a name="record"></a>
```C
typedef struct record {     
    char* nickname;     /// Псевдоним владельца номера телефона.  
    phone phonenumber;  /// Номер телефона.
    struct record *next;/// Указатель на следующую запись на странице.
} record;
```

Структура записи в книге.

---
<a name="book"></a>
```C
typedef struct book {
    char character;     /// Буква текущей страницы книги.
    record *node;       /// Первая запись на странице, инициализирует страницу.
    struct book *next;  /// указатель на следующую страницу книги.
    struct book *prev;  /// указатель на предыдущую страницу книги.
} book;
```

Структура телефонной книги.

---
<a name="get_phone"></a>
```C
phone get_phone (
        int locale,
        int service,
        int provider,
        int abonent);
```

Конструктор номера телефона.

---
<a name="phone_cmp"></a>
```C
int phone_cmp (phone phone1, phone phone2);
```

Сравнивает номера телефона. Если одинаковые, возвращает 0, иначе 1.

---
<a name="print_phone"></a>
```C
int print_phone (phone current);
```

Выводит номер телефона inline.

---
<a name="get_record"></a>
```C
record *get_record (
        char  *name,
        phone number); 
```

Конструктор записи телефонной книги.

---
<a name="update_record"></a>
```C
record *update_record (
        record *new_record,
        book *cur_book,
        char   *new_name,
        phone  new_number);
```

Редактирует существующую запись. Возвращает указатель на отредактированную запись.

---
<a name="record_cmp"></a>
```C
int record_cmp (record record1, record record2);
```

Сравнивает 2 записи. Если одинаковые, возвращает 0, иначе 1.

---
<a name="print_record"></a>
```C
int print_record (record current, int size);
```

Выводит информацию о записи inline.

---
<a name="init_book"></a>
```C
book *init_book (void);
```

Инициализирует новую книгу.

---
<a name="find_page"></a>
```C
book *find_page (char character, book cur_book);
```

Находит страницу, соответствующую первой букве искомой записи в телефонной книге. 
Возвращает указатель на страницу, если такая существует, иначе NULL.

---
<a name="add_page"></a>
```C
book *add_page (char character, book *cur_book);
```

Добавляет страницу буквы фамилии к книге в лексикографическом порядке. 
Возвращает указатель на страницу. 

---
<a name="print_page"></a>
```C
int print_page (book cur_page, int size);
```

Печатает страницу из телефонной книги, на псевдоним отводится size символов.

---
<a name="print_book"></a>
```C
int print_book (book cur_book, int size);
```

Распечатывает всю телефонную книгу, на псевдоним отводится size символов. 

---
<a name="find_record"></a>
```C
record *find_record (record required, book cur_book);
```

Находит запись, соответствующую искомой записи в телефонной книге.
Возвращает указатель на запись, если такая существует, иначе NULL.

---
<a name="find_nickname"></a>
```C
record **find_nickname (char *nickname, book cur_book);
```

Находит все записи по псевдониму в телефонной книге. Последний
элемент - указатель NULL.

---
<a name="print_nickname"></a>
```C
int print_nickname (char *nickname, book cur_book, int size);
```

Печатает все номера телефона по искомому имени.

---
<a name="add_record"></a>
```C
record *add_record (record current, book *cur_book);
```

Заносит запись в телефонную книгу. 
Возвращает указатель на эту запись в книге.

---
<a name="delete_record"></a>
```C
int delete_record (record *removable, book *page);
```

Удаляет запись из телефонной книги. 
Если успех, возвращает 0, иначе 1.

---
<a name="close_book"></a>
```C
int close_book (book *cur_book);
```

Закрывает книгу, освобождая память.

---
<a name="upload_book"></a>
```C
int upload_book (const char *path, int size, book *new_book);
```

Загружает телефонную книгу из файла.

---
<a name="write_book"></a>
```C
int write_book (book cur_book, const char* path);
```

Записывает телефонную книгу на диск. 
Если успех, возвращает 0, иначе 1.

---
