all:
	g++ main.cpp server.cpp errors.cpp listener.cpp calc.cpp interface.cpp ./md5/md5.cpp -o isp -L/usr/lib/x86_64-linux-gnu -lcrypto

unit:
	g++ main.cpp server.cpp errors.cpp listener.cpp calc.cpp interface.cpp ./md5/md5.cpp -o utest -lcrypto -lUnitTest++ -L/usr/lib/x86_64-linux-gnu
clean:
	rm -f isp
