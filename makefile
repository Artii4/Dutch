objects = obj/token.o obj/lexer.o

bin/dutch: obj/main.o $(objects)
	g++ -o bin/dutch obj/main.o $(objects)
bin/tests: obj/tests.o $(objects)
	g++ -o bin/tests obj/tests.o $(objects)

$(objects) obj/main.o: src/headers.h
obj/main.o: src/main.cpp
	g++ -std=c++11 -c src/main.cpp -o obj/main.o
obj/token.o: src/token.cpp
	g++ -std=c++11 -c src/token.cpp -o obj/token.o
obj/lexer.o: src/lexer.cpp
	g++ -std=c++11 -c src/lexer.cpp -o obj/lexer.o
obj/tests.o: tests/tests.cpp
	g++ -std=c++11 -c tests/tests.cpp -o obj/tests.o


clean:
	rm obj/*
test: bin/tests
	./bin/tests

.PHONY: clean
