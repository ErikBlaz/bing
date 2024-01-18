all: main

main:
	mkdir -p build/bin
	cp -r lib build
	cp -r include build
	cp -r sounds build
	g++ -o build/bin/bing src/main.cpp -I./include -L./lib -lIrrKlang

clean:
	rm -rf build