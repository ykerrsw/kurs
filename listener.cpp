#include "listener.h"


uint64_t listener::sredn(){
    uint64_t sum = 0;
    uint64_t sr = 0;
    uint32_t count = static_cast<uint32_t>(vec.size());
    for (uint64_t value : vec) {
        // типо если переполнение
        if (sum > 9223372036854775807 - value) {
            return 9223372036854775807;
        }
        
        sum += value;
        } 
    sr = sum / count;
    return sr;}
    


int listener::interaction(string database, string logFile){
    
    Errors Err;
    Err.set_File_Log(logFile);

    Data DB;       //! DataReader
    DB.set_FileReader(database);
    auto db = DB.getClient();

    vector<std::string> str1 = db.first;
    vector<std::string> str2 = db.second;

    set_DB_clients(str1, str2);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
       Err.error_recording("критичная", "Fun: interaction. Ошибка при создании сокета.");
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(get_address().c_str());
    serverAddress.sin_port = htons(get_port());

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        close(serverSocket);
        Err.error_recording("критичная", "Fun: interaction. Ошибка при привязке сокета к адресу.");}

    if (listen(serverSocket, 5) == -1) {
        close(serverSocket);
        Err.error_recording("критичная", "Fun: interaction. Ошибка при начале прослушивания порта.");
    }

    std::cout << "\nСервер запущен на адресе " << get_address();
    std::cout << " и порту " << get_port() << std::endl;

     while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket == -1) {
            close(serverSocket);
            Err.error_recording("некритичная", "Fun: interaction. Ошибка при принятии соединения.");
        }

        cout << "ПОДКЛЮЧЕНИЕ - YES" << endl;


        char buf[1024];
        int bytes_read;

        // Получение от клиента логина
        bytes_read = recv(clientSocket, buf, sizeof(buf), 0);
        buf[bytes_read] = '\0';
        User u;                                                 //!!!!!!!!!!
        u.set_ID(string(buf));
        
        string s1;
        // Проверка логина DataReader
        if(!u.СheckLogin(DB_clients.first)){
            
            s1 = "ERR";
            cout << "АУТЕНТИФИКАЦИЯ - NO" << endl;
            cout << "ЗАКРЫТИЕ СОКЕТА" << endl;
            strcpy(buf,s1.c_str());
            send(clientSocket, buf, s1.length(), 0);

            close(clientSocket);
            Err.error_recording("некритичная", "Fun: interaction. Ошибка аутентификации");
            continue;
        }

        // Отправка SALT16 клиенту
        set_salt();
        string s2 = get_salt();
        cout << "SALT16=" << s2 << endl;
        strcpy(buf, s2.c_str());
        send(clientSocket, buf, s2.length(), 0);


        // Получение от клиента HASH
        bytes_read = recv(clientSocket, buf, sizeof(buf), 0);
        buf[bytes_read] = '\0';
        
        u.set_hash(string(buf));

        string s3;
        // Проверка пароля

        if(!u.CheckPassword(DB_clients.second, DB_clients.first, get_salt())){
            s3 = "ERR";
            cout << "АУТЕНТИФИКАЦИЯ - NO" << endl;
            cout << "ЗАКРЫТИЕ СОКЕТА" << endl;
            strcpy(buf,s3.c_str());
            send(clientSocket, buf, s3.length(), 0);

            close(clientSocket);
            Err.error_recording("некритичная", "Fun: interaction. Ошибка аутентификации");
            continue;
        }

        string s4 = "OK";
        cout << "АУТЕНТИФИКАЦИЯ - YES" << endl;
        strcpy(buf,s4.c_str());
        send(clientSocket, buf, s4.length(), 0);


        // Получение веторов

        // Получение количества векторов
        uint32_t col = 0;
        recv(clientSocket, &col, sizeof(col), 0);
        cout << "КОЛИЧЕСТВО ВЕКТОРОВ: " << col << endl;

        for(auto i = 0; i < col; i++){

            // Получение длины вектора
            uint32_t vec_len = 0;
            recv(clientSocket, &vec_len, sizeof(vec_len), 0);
            cout << "ДЛИНА ВЕКТОРА: " << vec_len << endl;

            // Получение вектора
            uint64_t arr[vec_len] = {0};

            recv(clientSocket, &arr, sizeof(arr), 0);

            vector<uint64_t> vec1;
            for (size_t j = 0; j < vec_len; j++) {
            vec1.push_back(arr[j]);
            cout << vec1[j] << " ";
            }
            cout << "\n";

            // Подсчет результатов
            set_vec(vec1);
            auto res = sredn();
            cout << "РЕЗУЛЬТАТ ВЫЧИСЛЕНИЙ: " << res << endl;

            // Отправка результата
            send(clientSocket, &res, sizeof(res), 0);


        }
        // Закрываем соединение с клиентом
        cout << "ЗАКРЫТИЕ СОКЕТА" << endl;
        close(clientSocket);
    }

    // Закрываем серверный сокет User
    close(serverSocket);

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
string listener::get_address(){
    return address;}
//----------------------------------------------------------------------------------------------------------------------------------------------
void listener::set_address(string address1){
    const vector<string> list_add = {"127.0.0.1"};
    int fl = 0;
    for(auto it:list_add){
        if(it == address1){
            fl = 1;
            address = address1;
        }
    }
    if(fl != 1){
        Err.error_recording("критичная", "Fun: set_address. Адрес сервера не соответствует разрешенным.");
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------
int listener::get_port(){
    return port;}

//----------------------------------------------------------------------------------------------------------------------------------------------

void listener::set_port(int port1){
    if (port1 < 1023){
        Err.error_recording("критичная", "Fun: set_port. Порт сервера должен быть больше 1024.");
    } port = port1;}
//----------------------------------------------------------------------------------------------------------------------------------------------
vector<uint64_t> listener::get_vec(){
    return vec;
}
//----------------------------------------------------------------------------------------------------------------------------------------------
void listener::set_vec(vector<uint64_t> v){
    vec = v; }
//----------------------------------------------------------------------------------------------------------------------------------------------
string listener::get_salt(){
    return salt; }
//----------------------------------------------------------------------------------------------------------------------------------------------
void listener::set_salt(){
    // Символы, которые могут встречаться в строке SALT
    const string saltCharacters = "0123456789ABCDEF";
    const int saltLength = 16;

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, saltCharacters.length() - 1);

    std::string Salt;
    Salt.reserve(saltLength);

    for (int i = 0; i < saltLength; ++i) {
        int randomIndex = dis(gen);
        Salt += saltCharacters[randomIndex];
    }

    salt = Salt;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
pair<vector<string>, vector<string>> listener::get_DB_clients(){
    return DB_clients;}

//----------------------------------------------------------------------------------------------------------------------------------------------
void listener::set_DB_clients(vector<string> login, vector<string> password){
    DB_clients = std::make_pair(login,password);}
