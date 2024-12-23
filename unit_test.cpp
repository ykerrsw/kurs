#include <UnitTest++/UnitTest++.h>
#include "listener.h"


using namespace std;

	TEST(ydachno_log){
		User test;
		test.set_ID("user");
		auto resultat = test.СheckLogin({"user", "ivanov", "user0"});
		UNITTEST_CHECK_EQUAL(resultat, 1);}
 
	TEST(neydachno_log){
		User test;
		test.set_ID("user");
		auto resultat = test.СheckLogin({"ivanov", "user0"});
		UNITTEST_CHECK_EQUAL(resultat, 0);}
		
	TEST(ydachno_pass){
		User test;
		test.set_ID("user");
		test.set_hash("36108A357B8A7715B1CCD1A0552CF22D3426C45CF68D6F5DC1DF8E33");
		auto resultat = test.CheckPassword({"P@ssW0rd", "123456", "qwe123"}, {"user", "ivanov", "user0"}, "1AF4D801F8BBA41A");
		UNITTEST_CHECK_EQUAL(resultat, 1);}

	TEST(neydachno_pass){
		User test;
		test.set_ID("user");
		test.set_hash("B77654515B81DCF72FCF0387A1EF6C51");
		auto resultat = test.CheckPassword({"P@ssW0rd", "123456", "qwe123"}, {"user", "ivanov", "user0"}, "1AF4D801F8BBA41A");
		UNITTEST_CHECK_EQUAL(resultat, 0);}
		
		
//-------------------------------------------------------------------------------------------------------------------------------------		
		

    TEST(log){
    	Errors err;
        CHECK_THROW(err.set_File_Log("!/#@/log.conf"), invalid_argument);}

	
//-------------------------------------------------------------------------------------------------------------------------------------
    TEST(data_base_error1){
    	Data db;
        db.set_FileReader("!@//DB_client.conf");
        CHECK_THROW(db.getClient(), invalid_argument);}

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

/*
      auto client = db.getClient(); //Проверяем что метод отработал
      UNITTEST_CHECK(client == 0); //Проверяем что код возврата = 0;*/


}
//-------------------------------------------------------------------------------------------------------------------------------------

    TEST(ip_error){
    listener l;
        CHECK_THROW(l.set_address("101.101.101.101"), invalid_argument);}
        

    TEST(port_error){
    	listener l;
        CHECK_THROW(l.set_address("104"), invalid_argument);}
        
    
    TEST(sr_arf){
    	listener l;
		l.set_vec({5, 6, 7, 8});
        auto resultat = l.sredn();
        UNITTEST_CHECK_EQUAL(resultat, 6);}
        
        
    TEST(perepolnenie){
    	listener l;
        l.set_vec({9223372036854775807, 1});
        auto resultat = l.sredn();
        UNITTEST_CHECK_EQUAL(resultat, 9223372036854775807);}


int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}
