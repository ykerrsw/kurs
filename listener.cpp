#include <iostream>
#include <system_error>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include "calc.h"
#include "listener.h"
#include "errors.h"
using namespace std;

Listener::Listener(int port1, int qlen = 3):
    sock(socket(AF_INET, SOCK_STREAM, 0)),				// созд сокет 
    self_addr(new sockaddr_in),							// созд сруктура отправителя
    foreign_addr(new sockaddr_in),						// созд структура получателя
    queueLen(qlen)                                      //количество в очереди
{
    errors err1;
    port = port1;
    if (sock == -1)
        err1.error_recording("критичная", "ошибка создания сокета");
    int on = 1;
    int rc1 = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
    if ( rc1 == -1 )
        err1.error_recording("критичная", "ошибка создания сокета");
    
    // заполнение структуры для адреса сервера
    self_addr->sin_family = AF_INET;
    self_addr->sin_port = htons(port);
    self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");

    // Привязка сокета к адресу
    if (bind(sock, reinterpret_cast<const sockaddr*>(self_addr.get()), sizeof (sockaddr_in)) == -1)
        err1.error_recording("критичная", "ошибка привязки сокета к адресу");        
     // Прослушивание порта
     if (listen(sock, 5) == -1) {
     close(sock);
        err1.error_recording("критичная", "ошибка при прослушке порта");
}}
  
  
void Run();{
    errors err2;
    while (true){ 
    
    int rc;
    int buflen = 1024; 
    int bytes_read;
    unique_ptr <char[]> buf(new char[buflen]);
    
    
    struct sockaddr_in client;
    socklen_t Length = sizeof(client);
     int work_sock = accept(sock, (struct sockaddr*)&client, &Length);
     if (clientSocket == -1) {
        close(serverSocket);
        err2.error_recording("некритичная", "ошибка при принятии соединения.");}
        
                        
    rc = recv(work_sock, buf, buflen, 0); 
    buf[bytes_read] = '\0';
    if (rc == -1)
        err2.error_recording("некритичная", "ошибка при очистке буфера.");}
        res.resize(res.find_last_not_of("\n\r") + 1);
     buf[bytes_read] = '\0';
    
    server s1();
    para = s1.data_base(file_name);
    //login = string(buf);
    
    //проверка логина
    int count1 = 0;
    for (auto i: para.first)
    {if (rc == i){
       count1++; }
    string err1;
    if (count1 ==0){
    
    cout << "логин неверен" << endl;
    cout << "закрытие сокета" << endl;
    strcpy(buf,err1.c_str());
    send(work_sock, buf, err1.length(), 0);
     close(work_sock);
     err2.error_recording("некритичная", "ошибка аутентификации");
    continue;}}
     
     
    // Отправка SALT16 клиенту
    salt = s1.generate_salt();
    cout << "SALT16=" << salt << endl;
    buf[0] = '\0'; // Очищаем буфер, записывая нуль-терминатор
    strcpy(buf, salt.c_str());         //копирует в массив
    send(work_sock, buf, salt.length(), 0);


    // Получение от клиента HASH
    rc = recv(work_sock, buf, buflen, 0);
    buf[0] = '\0'; // Очищаем буфер, записывая нуль-терминатор
    buf[rc] = '\0';
    hash = string(buf);
    s1.set_hash(hash);

    // Проверка пароля Err
    string err_;
    s1.check_pass(para.second, para.first, salt, login);
    int count2 = 0;
    for (auto i: para.second)
    {if (rc == i){
       count2++; }
    if (count2 ==0){
    err_ = "ERROR";
    cout << "пароль неверен" << endl;
    cout << "закрытие сокета" << endl;
    strcpy(buf,err_.c_str());
    send(work_sock, buf, err_.length(), 0);
    close(work_sock);
    err2.error_recording("некритичная", "ошибка аутентификации");
    continue;}


    string s4 = "OK";
    cout << "аутентификация пройдена" << endl;
    strcpy(buf,s4.c_str());
    send(work_sock, buf, s4.length(), 0);


    // Получение количества векторов
    uint32_t col = 0;
    recv(work_sock, &col, sizeof(col), 0);
    cout << "количество векторов: " << col << endl;

    for(auto i = 0; i < col; i++){

        // Получение длины вектора
        uint32_t vec_len = 0;
        recv(work_sock, &vec_len, sizeof(vec_len), 0);
        cout << "длина вектора: " << vec_len << endl;

        // Получение вектора
        uint64_t arr[vec_len] = {0};

        recv(work_sock, &arr, sizeof(arr), 0);

        vector<uint64_t> vec1;
        for (size_t j = 0; j < vec_len; j++) {
        vec1.push_back(arr[j]);
        cout << vec1[j] << " ";
        }
        cout << "\n";

        // Подсчет результатов
        calc c(vec1, vec_len);
        auto res = c.calculate();
        cout << "результат вычислений: " << res << endl;

        // Отправка результата
        send(work_sock, &res, sizeof(res), 0);


    }
    // Закрываем соединение с клиентом
    cout << "ЗАКРЫТИЕ СОКЕТА" << endl;
    close(work_sock);
}

// Закрываем серверный сокет
close(serverSocket);

return 0;}}
        
//-----------------------------------------------------------------------------
Listener::~Listener()
{
    close(sock);
}
//-----------------------------------------------------------------------------
Listener::void set_port(int prt1){
    errors err3;
    if (prt1 < 1023){
    err3.error_recording("критичная", "порт сервера должен быть больше 1024.");
    port = prt1;
}}
//-----------------------------------------------------------------------------
Listener::void set_ip(string ip1){
    ip = ip1;
    }
//-----------------------------------------------------------------------------
Listener::void set_db(string db1){
    db = db1;
    }
//-----------------------------------------------------------------------------
Listener::void set_log(string log){
    logfile = log;
    }
