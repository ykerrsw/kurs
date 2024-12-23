all:
	g++ main.cpp Errors.cpp listener.cpp Data.cpp Interface.cpp sha224.cpp User.cpp -o isp -I/usr/include/cryptopp -L/usr/lib/x86_64-linux-gnu -lcryptopp

unit:
	g++ unit_test.cpp Errors.cpp listener.cpp Data.cpp Interface.cpp sha224.cpp User.cpp -o utest -lcryptopp -lUnitTest++ -L/usr/lib/x86_64-linux-gnu

clean:
	rm -f isp utest

