#include "headers.h"
#include <exception>
#include <stdexcept>

AST::AST() = default;

AST::AST(AST_type type) {
	this->type = type;
	this->value = type_to_string(type);
}

AST::AST(AST_type type, std::string value) {
  this->type = type;
  this->value = value;
}

void AST::add_child(AST child) { children.push_back(child); }

AST_type AST::get_type() const { return type; }
std::string AST::get_value() const { return value; }
std::vector<AST> AST::get_children() const { return children; }

AST AST::at(int index) const { return children[index]; }

bool AST::operator==(const AST &t) const {
  return children == t.get_children() && value == t.get_value() &&
         type == t.get_type();
}

std::string AST::type_to_string(AST_type t) {
  switch (t) {
  case AST_type::PLUS:
    return "PLUS";
  case AST_type::MINUS:
    return "MINUS";
  case AST_type::TIMES:
    return "TIMES";
  case AST_type::DIVIDE:
    return "DIVIDE";
  case AST_type::NUMBER:
    return "NUMBER";
  case AST_type::NAME:
    return "NAME";
  case AST_type::HET:
    return "HET";
  case AST_type::ASSIGNMENT:
    return "ASSIGNMENT";
  case AST_type::PRINT:
    return "PRINT";
  case AST_type::PROGRAM:
    return "PROGRAM";
	default:
		throw std::runtime_error("Invalid AST type in switch: " + std::to_string((int)t));
  }
}

std::string AST::single_to_string() const {
  return "<type: " + type_to_string(type) + "; value: " + value + ">";
}

std::string AST::to_string() const {
	std::string buf = "(";
	buf += single_to_string();

	if (!children.empty())
		for (auto child : children)
			buf += child.to_string();

	buf += ")";

	return buf;
}
