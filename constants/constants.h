#ifndef CONSTANTS_H
#define CONSTANTS_H

// Базовые пути
#define DIR_TEMPLATES "./templates/"
#define DIR_CSS "./css/"
 
// Пути к HTML-шаблонам
#define PATH_LOGIN_HTML DIR_TEMPLATES "login.html"
#define PATH_ELEMENTS_HTML DIR_TEMPLATES "elements.html"
#define PATH_ERROR_HTML DIR_TEMPLATES "error.html"
#define PATH_LIST_HTML DIR_TEMPLATES "list.html"

// Путь к CSS
#define PATH_CSS_STYLES DIR_CSS "styles.css"
 
// Content-Type заголовки
#define CONTENT_TYPE_HTML "Content-Type: text/html; charset=utf-8\r\n"
#define CONTENT_TYPE_CSS "Content-Type: text/css; charset=utf-8\r\n"

// Максимальное количество слов для преобразования в список
#define MAX_WORDS 2
#define MAX_ELEMENTS_SIZE 1001
#define MAX_BODY_LEN (MAX_ELEMENTS_SIZE + 20)
#define MAX_TYPE_PARSE_LEN 2

// Коды ошибок
enum {
    // Ошибки нет, все прошло успешно
    ERR_OK 		    = 0,
    // Не установлены переменные окружения LOGIN_USER или LOGIN_PASS
    ERR_MISSING_ENV 	    = 1,
    // Неверное имя пользователя или пароль
    ERR_INVALID_CREDENTIALS = 2,
    // Не удалось открыть нужный файл
    ERR_FILE_NOT_FOUND 	    = 3,
    // Не удалось выделить память
    ERR_ALLOCATION 	    = 4,
    // Не удалось найти подстроку в строке
    ERR_SEARCH 		    = 5,
    ERR_DIVISION_BY_ZERO     = 6,
    ERR_INVALID_TYPE         = 7
};

#endif

