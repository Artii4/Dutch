#include "headers.h"
#include <iostream>
#include <string>

int main() {
  Interpreter interpreter;

  while (true) {
    std::cout << ">>> ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "q") {
      std::cout << "bye!" << std::endl;
      break;
    }

    AST tree = Parser(input).parse();
    std::string output = interpreter.interpret(tree);

    if (output == "")
      continue;

    std::cout << output;
  }

  return 0;
}
