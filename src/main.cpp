#include <iostream>
#include <string>
#include "headers.h"

int main() {
	Lexer l("laat pi 3 zijn;");

	while (true) {
		Token t = l.next_token();
		std::cout << t.to_string() << std::endl;

		if (t.get_type() == END) break;
	}
}
