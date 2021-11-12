l6:main.cpp pluginManager.cpp
	g++ -o l6 pluginManager.cpp main.cpp -std=c++11 -Wall -Werror -ldl
cat:
	g++ plugins/cat/cat.cpp -fPIC -shared -o plugins/cat.so -Wall -Werror -std=c++11 -I ./
simple:
	g++ plugins/simple/simple.cpp -fPIC -shared -o plugins/simple.so -Wall -Werror -std=c++11 -I ./
clean:
	rm -f l6 *.o plugins/*.so