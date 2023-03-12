CXX = g++ # Vul hier jouw compiler in als je een andere hebt.
objects = obj/token.o obj/lexer.o obj/parser.o obj/ast.o obj/interpreter.o

bin/dutch: obj/main.o $(objects)
	$(CXX) -o bin/dutch obj/main.o $(objects)
bin/tests: obj/tests.o $(objects)
	$(CXX) -o bin/tests obj/tests.o $(objects)

$(objects) obj/main.o: src/headers.h
obj/main.o: src/main.cpp
	$(CXX) -g -Wall -std=c++11 -c src/main.cpp -o obj/main.o
obj/token.o: src/token.cpp
	$(CXX) -g -Wall -std=c++11 -c src/token.cpp -o obj/token.o
obj/lexer.o: src/lexer.cpp
	$(CXX) -g -Wall -std=c++11 -c src/lexer.cpp -o obj/lexer.o
obj/tests.o: tests/tests.cpp
	$(CXX) -g -Wall -std=c++11 -c tests/tests.cpp -o obj/tests.o
obj/parser.o: src/parser.cpp
	$(CXX) -g -Wall -std=c++11 -c src/parser.cpp -o obj/parser.o
obj/ast.o: src/ast.cpp
	$(CXX) -g -Wall -std=c++11 -c src/ast.cpp -o obj/ast.o
obj/interpreter.o: src/interpreter.cpp
	$(CXX) -g -Wall -std=c++11 -c src/interpreter.cpp -o obj/interpreter.o


clean:
	rm obj/*
test: bin/tests
	./bin/tests

.PHONY: clean test
