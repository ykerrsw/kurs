#include <iostream>
#include <system_error>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <cstring>
#include "calc.h"
#include "listener.h"
#include "errors.h"
#include "server.h"

Listener::Listener(int port1, int qlen, std::string ip1):
    sock(socket(AF_INET, SOCK_STREAM, 0)),				// созд сокет 
    self_addr(new sockaddr_in),							// созд сруктура отправителя
    //foreign_addr(new sockaddr_in),						
    queueLen(qlen)                                      //количество в очереди
{	
	ip = ip1;
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
    
	int result = inet_pton(AF_INET, ip.c_str(), &(self_addr->sin_addr));
	if (result != 1) {
  		err1.error_recording("критичная", "Ошибка преобразования IP-адреса: " + std::string(strerror(errno)));}

    // Привязка сокета к адресу
    if (bind(sock, reinterpret_cast<const sockaddr*>(self_addr.get()), sizeof (sockaddr_in)) == -1)
         err1.error_recording("Критическая ошибка", "Ошибка привязки сокета: " + std::string(strerror(errno)) + ", Port: " + std::to_string(port) + ", IP: " + ip);
    socklen_t addrlen = sizeof(self_addr);
    if (getsockname(sock, (struct sockaddr*)&self_addr, &addrlen) == -1) {
              err1.error_recording("Критическая ошибка", "Ошибка при получении адреса сокета: " + std::string(strerror(errno)));
     // Прослушивание порта
     if (listen(sock, 5) == -1) {
     close(sock);
        err1.error_recording("критичная", "ошибка при прослушке порта");
        
}}
  
  
void Listener::Run(){
    errors err2;
    int rc;
    int buflen = 1024; 
    int bytes_read;
    
    while (true){ 
    unique_ptr <char[]> buf(new char[buflen]);
    
    std::cout<<"2/1"<<endl;
    struct sockaddr_in client;
    std::cout<<"2/2"<<endl;
    socklen_t Length = sizeof(client);
    std::cout<<"2/3"<<endl;
     int work_sock = accept(sock, reinterpret_cast<struct sockaddr*>(&client), &Length);
     std::cout<<"2/4"<<endl;
     if (work_sock == -1) {
       int error = errno;
       err2.error_recording("Некритичная", "Ошибка при принятии соединения: " + std::string(strerror(error)));}
 
                        
    rc = recv(work_sock, buf.get(), buflen, 0); 
    std::cout<<"3"<<endl;
    buf[bytes_read] = '\0';
    string received_message(buf.get(), bytes_read);
    if (rc == -1){
        err2.error_recording("некритичная", "ошибка при очистке буфера.");}
        //res.resize(res.find_last_not_of("\n\r") + 1);
     //buf[bytes_read] = '\0';
      std::cout<<"4 пункт"<<endl;
    server s1;
    pair<vector<string>, vector<string>> para;
    para = s1.data_base();
    //login = string(buf);
    
    //проверка логина
    int count1 = 0;
    for (auto i: para.first)
    {if (received_message == i){
       count1++;}
    string err1;
    if (count1 ==0){
      std::cout<<"5 пункт"<<endl;
    cout << "логин неверен" << endl;
    cout << "закрытие сокета" << endl;
    strcpy(buf.get(),err1.c_str());
    send(work_sock, buf.get(), err1.length(), 0);
     close(work_sock);
     err2.error_recording("некритичная", "ошибка аутентификации");
    continue;}}
     
     
    // Отправка SALT16 клиенту
    salt = s1.generate_salt();
    cout << "SALT16=" << salt << endl;
    buf[0] = '\0'; // Очищаем буфер, записывая нуль-терминатор
    strcpy(buf.get(), salt.c_str());         //копирует в массив
    send(work_sock, buf.get(), salt.length(), 0);


    // Получение от клиента HASH
    rc = recv(work_sock, buf.get(), buflen, 0);
    string received_message2(buf.get(), bytes_read);
    buf[0] = '\0'; // Очищаем буфер, записывая нуль-терминатор
    buf[rc] = '\0';
    hash = string(buf.get());
    s1.set_hash(hash);

    // Проверка пароля  
    string err_;
    s1.check_pass(para.second, para.first, salt, login);
    int count2 = 0;
    for (auto i: para.second)
    {if (received_message2 == i){
       count2++; }
    if (count2 ==0){
    err_ = "ERROR";
    cout << "пароль неверен" << endl;
    cout << "закрытие сокета" << endl;
    strcpy(buf.get(),err_.c_str());
    send(work_sock, buf.get(), err_.length(), 0);
    close(work_sock);
    err2.error_recording("некритичная", "ошибка аутентификации");
    continue;}


    string s4 = "OK";
    cout << "аутентификация пройдена" << endl;
    strcpy(buf.get(),s4.c_str());
    send(work_sock, buf.get(), s4.length(), 0);


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
close(work_sock);
}}
        
//-----------------------------------------------------------------------------
/*Listener::~Listener(){
    close(sock);
}
//-----------------------------------------------------------------------------
void Listener::set_port(int prt1){
    errors err3;
    if (prt1 < 1023){
    err3.error_recording("критичная", "порт сервера должен быть больше 1024.");
    port = prt1;
}}
//-----------------------------------------------------------------------------
void Listener::set_ip(std::string ip1){
    ip = ip1;
    }
//-----------------------------------------------------------------------------
void Listener::set_db(std::string db1){
    db = db1;
    }
//-----------------------------------------------------------------------------
void Listener::set_log(std::string log){
    logfile = log;
    }*/
