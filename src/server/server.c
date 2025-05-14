#include "server.h"
#include "../list/list.h"

// Функция обработки входящих HTTP-запросов
int process_request(struct mg_connection*   c,
               		   struct mg_http_message* hm) {
    // Код состояния по умолчанию - внутренняя ошибка сервера
    int         status_code = 500;
    // Тип содержимого (Content-Type) будет выбран позже
    const char* ctype = "";
    // Ответ, который будет отправлен клиенту
    char* 	response = NULL;
    // Ошибка по умолчанию - файл не найден
    int 	error_code = ERR_FILE_NOT_FOUND;
    
    // Проверка: если пришел POST-запрос на /login
    if(!mg_strcmp(    hm->uri,    mg_str("/login")) && 
       !mg_strcasecmp(hm->method, mg_str("POST"))) {
    	// Буферы для хранения введённого имени пользователя и пароля
    	char username[100], password[100];
    	// Получение ожидаемого имени из переменной окружения
    	const char* expected_user = getenv("LOGIN_USER");
    	// Получение ожидаемого пароля из переменной окружения
    	const char* expected_pass = getenv("LOGIN_PASS");
        
    	if(!expected_user || !expected_pass)
            // Если переменные окружения не заданы - ошибка
	    error_code = ERR_MISSING_ENV;
        else {
            // Извлечение значений из тела POST-запроса
            mg_http_get_var(&hm->body, "username",
                        	    	username,
                     	     	 sizeof(username));
	    mg_http_get_var(&hm->body, "password",
                            	    	password,
                 	     	 sizeof(password));

	    // Проверка введённых данных
	    if(!strcmp(username, expected_user) &&
               !strcmp(password, expected_pass))
              	// Если всё верно - читаем файл HTML c инструментом форматирования
		response   = read_file(PATH_ELEMENTS_HTML);
            else {
        	// Иначе - HTML с ошибкой
		response   = read_file(PATH_ERROR_HTML);
        	error_code = ERR_INVALID_CREDENTIALS;
            }

            // Если файл успешно прочитан - подготавливаем ответ
            if(response) {
        	status_code = 200;
            	ctype 	    = CONTENT_TYPE_HTML;
            	error_code  = ERR_OK;
            }
    	}
    }
    
    // Если запрашивается файл стилей
    else if(!mg_strcmp(hm->uri, mg_str("/styles.css"))) {
    response = read_file(PATH_CSS_STYLES); // Читаем файл CSS
    if(response) {
        status_code = 200;
        ctype 	    = CONTENT_TYPE_CSS;
        error_code  = ERR_OK;
    }
    }

    // Если запрашивается результат операции вычисления
    else if(!mg_strcmp(hm->uri, mg_str("/list")) &&
	    !mg_strcasecmp(hm->method, mg_str("POST")) &&
	    hm->body.len < MAX_BODY_LEN) {
	char	 elements[MAX_ELEMENTS_SIZE];
	char raw_elements[MAX_BODY_LEN];
	char type_parse[MAX_TYPE_PARSE_LEN];

	mg_http_get_var(&hm->body, "elements",
                            	    raw_elements,
                 	     	    MAX_BODY_LEN);
	mg_http_get_var(&hm->body, "type_list",
				    type_parse,
				    MAX_TYPE_PARSE_LEN);

	if(!parse_string(raw_elements, 
			 elements, 
			 MAX_ELEMENTS_SIZE,
			 type_parse)) {
    	     // Читаем шаблон для результата
    	    if(!load_template_and_replace(PATH_LIST_HTML,
				    	  "{{result}}",
					   elements,
					   &response)) {
            	status_code = 200;
            	ctype       = CONTENT_TYPE_HTML;
            	error_code  = ERR_OK;
    	    }
	}
    }

    // Если запрашивается что-либо другое - возвращаем login.html
    else {
    response = read_file(PATH_LOGIN_HTML);
	// Загружаем страницу логина
    	if(response) {
       	    status_code = 200;
       	    ctype  	= CONTENT_TYPE_HTML;
       	    error_code  = ERR_OK;
    	}
    }

    // Если не было ошибок - отправляем ответ клиенту
    if(error_code == ERR_OK)
    	mg_http_reply(c, status_code, ctype, "%s", response);
    else 
    	mg_http_reply(c, 500, "", "");
    // В случае ошибки - пустой  ответ с кодом 500
    
    free(response);
    return error_code;
}

// Основная функция-обработчик событий сервера
void main_fun(struct mg_connection *c,
              int    ev,
              void*  ev_data) {
    if(ev == MG_EV_HTTP_MSG) {
    	int    result;
    	struct mg_http_message*     hm = (struct mg_http_message*)ev_data;
    	// Преобразуем данные события к нужному типу
    	result = process_request(c, hm); // Передаём запрос в обработчик
    
    	printf("Результат обработки: %d\n", result);
    	// Логирование результата обработки
    }
}

