all:
	g++ -o libblym.so -lcurl -Wl,-soname,libblym.so -shared blym.cpp -fPIC -ansi -pedantic -L../String/ -lString
install:
	cp libblym.so /usr/lib/
test:
	g++ -o test -lblym test.cpp
