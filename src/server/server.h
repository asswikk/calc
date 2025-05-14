#ifndef SERVER_H
#define SERVER_H

#include "../../mongoose/mongoose.h"
// Подключение библиотеки Mongoose для реализации встроенного HTTP-сервера
#include "../input/input.h"
// Подключение собственной функции read_file() для чтения файлов
#include "../../constants/constants.h"
// Подключение заголовка с определениями путей к HTML/CSS и Content-Type
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int process_request(struct mg_connection*   c,
               		   struct mg_http_message* hm);

// Основная функция-обработчик событий сервера
void main_fun(struct mg_connection *c,
             	     int    ev,
             	     void*  ev_data);

#endif
