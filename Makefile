all:
	g++ main.cpp server.cpp errors.cpp listener.cpp calc.cpp interface.cpp -o isp -I/usr/include/cryptopp -L/usr/lib/x86_64-linux-gnu -lcryptopp

unit:
	g++ main.cpp server.cpp errors.cpp listener.cpp calc.cpp interface.cpp -o utest -lcryptopp -lUnitTest++ -L/usr/lib/x86_64-linux-gnu

clean:
	rm -f isp utest

