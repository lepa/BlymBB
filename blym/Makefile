all:
	g++ -o libblym.so -lcurl -Wl,-soname,libblym.so -shared blym.cpp -fPIC -ansi -pedantic 
install:
	cp libblym.so /usr/lib/
test:
	g++ -o test -lblym test.cpp
