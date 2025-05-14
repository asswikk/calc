#include "server.h"

static int s_received_signal = 0;

static void signal_handler(int sig) {
    s_received_signal = sig;
}

int main(void) {
    const char* server_address = "http://localhost:10001";
    // Адрес, по которому будет запущен сервер
    
    struct mg_mgr mgr; // Контекст менеджера соединений
    mg_mgr_init(&mgr); // Инициализация менеджера
    mg_http_listen(&mgr, server_address, main_fun, NULL);
    // Запуск сервера на указанном адресе и обработчиком событий
    
    signal(SIGINT, signal_handler); // Ctrl+C
    signal(SIGTERM, signal_handler); // kill команда

    printf("Сервер запущен на %s\n", server_address);
    printf("Нажмите Ctrl+C для остановки..\n");// Вывод сообщения в консоль
    
    while(!s_received_signal) {
	mg_mgr_poll(&mgr, 1000);
    } // Основной цикл обработки событий с интервалом 1000 мс
    
    mg_mgr_free(&mgr);
    // Очистка ресурсов перед завершением
    printf("\nСервер остановлен!\n");

    return 0;
}
