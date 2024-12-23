#include <UnitTest++/UnitTest++.h>
#include "listener.h"


using namespace std;
/**
 * @brief Тест проверяет успешный вход пользователя в систему.
 *
 * Создается объект User, устанавливается его ID, и вызывается метод СheckLogin
 * с правильными учетными данными. Проверяется, что метод возвращает 1,
 * что означает успешный вход.
 */
	TEST(ydachno_log){
		User test;
		test.set_ID("user");
		auto resultat = test.СheckLogin({"user", "ivanov", "user0"});
		UNITTEST_CHECK_EQUAL(resultat, 1);}
/**
 * @brief Тест проверяет неудачный вход пользователя в систему.
 *
 * Создается объект User, устанавливается его ID, и вызывается метод СheckLogin
 * с неправильными учетными данными. Проверяется, что метод возвращает 0,
 * что означает неудачный вход.
 */ 
	TEST(neydachno_log){
		User test;
		test.set_ID("user");
		auto resultat = test.СheckLogin({"ivanov", "user0"});
		UNITTEST_CHECK_EQUAL(resultat, 0);}
/**
 * @brief Тест проверяет успешную проверку пароля пользователя.
 *
 * Создается объект User, устанавливается его ID и хеш пароля, и вызывается метод CheckPassword
 * с правильными учетными данными и солью. Проверяется, что метод возвращает 1,
 * что означает успешную проверку пароля.
 */		
	TEST(ydachno_pass){
		User test;
		test.set_ID("user");
		test.set_hash("36108A357B8A7715B1CCD1A0552CF22D3426C45CF68D6F5DC1DF8E33");
		auto resultat = test.CheckPassword({"P@ssW0rd", "123456", "qwe123"}, {"user", "ivanov", "user0"}, "1AF4D801F8BBA41A");
		UNITTEST_CHECK_EQUAL(resultat, 1);}
/**
 * @brief Тест проверяет неудачную проверку пароля пользователя.
 *
 * Создается объект User, устанавливается его ID и хеш пароля, и вызывается метод CheckPassword
 * с неправильными учетными данными или солью. Проверяется, что метод возвращает 0,
 * что означает неудачную проверку пароля.
 */
	TEST(neydachno_pass){
		User test;
		test.set_ID("user");
		test.set_hash("B77654515B81DCF72FCF0387A1EF6C51");
		auto resultat = test.CheckPassword({"P@ssW0rd", "123456", "qwe123"}, {"user", "ivanov", "user0"}, "1AF4D801F8BBA41A");
		UNITTEST_CHECK_EQUAL(resultat, 0);}
		
		
//-------------------------------------------------------------------------------------------------------------------------------------		
		
/**
 * @brief Тест проверяет, что при попытке установить невалидный путь к файлу журнала ошибок
 * выбрасывается исключение invalid_argument.
 *
 * Создается объект Errors, и вызывается метод set_File_Log с невалидным путем.
 * Проверяется, что выбрасывается исключение invalid_argument.
 */
    TEST(log){
    	Errors err;
        CHECK_THROW(err.set_File_Log("!/#@/log.conf"), invalid_argument);}

	
//-------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Тест проверяет, что при попытке установить невалидный путь к базе данных клиентов
 * выбрасывается исключение invalid_argument.
 *
 * Создается объект Data, и вызывается метод set_FileReader с невалидным путем.
 * Проверяется, что при вызове метода getClient выбрасывается исключение invalid_argument.
 */
    TEST(data_base_error1){
    	Data db;
        db.set_FileReader("!@//DB_client.conf");
        CHECK_THROW(db.getClient(), invalid_argument);}
/**
 * @brief Тест проверяет успешное открытие файла базы данных клиентов.
 *
 * Создается объект Data, устанавливается имя файла базы данных.
 * Проверяется, что метод getClient не выбрасывает исключение invalid_argument.
 */
    TEST(data_base_open) {
    Data db;
    db.set_FileReader("DB.conf"); 
    bool exceptionThrown = false; 
    try {
        db.getClient();
    } 
    catch (const std::invalid_argument& e) {
        exceptionThrown = true;}
        
    UNITTEST_CHECK(!exceptionThrown); 



}
//-------------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Тест проверяет, что при попытке установить невалидный IP-адрес
 * выбрасывается исключение invalid_argument.
 *
 * Создается объект listener, и вызывается метод set_address с невалидным IP-адресом.
 * Проверяется, что выбрасывается исключение invalid_argument.
 */
    TEST(ip_error){
    listener l;
        CHECK_THROW(l.set_address("101.101.101.101"), invalid_argument);}
        
/**
 * @brief Тест проверяет, что при попытке установить невалидный номер порта
 * выбрасывается исключение invalid_argument.
 *
 * Создается объект listener, и вызывается метод set_address с невалидным номером порта.
 * Проверяется, что выбрасывается исключение invalid_argument.
 */
    TEST(port_error){
    	listener l;
        CHECK_THROW(l.set_address("104"), invalid_argument);}
        
/**
 * @brief Тест проверяет правильность расчета среднего арифметического значения вектора чисел.
 *
 * Создается объект listener, устанавливается вектор чисел и вызывается метод sredn().
 * Проверяется, что метод возвращает правильное среднее арифметическое значение.
 */    
    TEST(sr_arf){
    	listener l;
		l.set_vec({5, 6, 7, 8});
        auto resultat = l.sredn();
        UNITTEST_CHECK_EQUAL(resultat, 6);}
        
/**
 * @brief Тест проверяет работу метода sredn() при переполнении (не является идеальным тестом).
 *
 * Создается объект listener, устанавливается вектор чисел, содержащий очень большое значение
 * и единицу.  Этот тест может быть улучшен, так как он проверяет лишь ожидаемое поведение
 * при переполнении, но не гарантирует его корректности.
 */      
    TEST(perepolnenie){
    	listener l;
        l.set_vec({9223372036854775807, 1});
        auto resultat = l.sredn();
        UNITTEST_CHECK_EQUAL(resultat, 9223372036854775807);}

/**
 * @brief Главная функция для запуска всех юнит-тестов.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 *
 * @return int Возвращает результат выполнения тестов (0 при успехе).
 */
int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}
