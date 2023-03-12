#include "headers.h"
#include <iostream>

Interpreter::Interpreter() { last_variable_name = ""; }

// Reset the output for the user, walk the entire tree, and return
// the new output.
std::string Interpreter::interpret(AST tree) {
  output = "";
  walk(tree);

  return output;
}

void Interpreter::walk(AST tree) {
  if (tree.get_type() != AST_type::PROGRAM)
    throw std::runtime_error("Expected PROGRAM in walk()");

  for (const auto &statement : tree.get_children()) {
    switch (statement.get_type()) {
    case AST_type::ASSIGNMENT:
      assignment(statement);
      break;
    case AST_type::PRINT:
      print(statement);
      break;
    default:
      throw std::runtime_error("Invalid AST in walk()");
    }
  }
}

void Interpreter::assignment(AST tree) {
  last_variable_name = tree.at(0).get_value();
  variables[last_variable_name] = calculate(tree.at(1));
}

void Interpreter::print(AST tree) {
  output += std::to_string(calculate(tree.at(0)));
  output += "\n";
}

double Interpreter::calculate(AST tree) {
  switch (tree.get_type()) {
    // Leaves
  case AST_type::NUMBER:
    return std::stod(tree.get_value());
  case AST_type::NAME:
    return variables[tree.get_value()];
  case AST_type::HET:
    return variables[last_variable_name];

    // Binary nodes
  case AST_type::PLUS:
    return calculate(tree.at(0)) + calculate(tree.at(1));
  case AST_type::MINUS:
    return calculate(tree.at(0)) - calculate(tree.at(1));
  case AST_type::TIMES:
    return calculate(tree.at(0)) * calculate(tree.at(1));
  case AST_type::DIVIDE:
    return calculate(tree.at(0)) / calculate(tree.at(1));

    // Any other type of node is invalid
  default:
    throw std::runtime_error("Invalid AST node: " + tree.to_string());
  }
}
