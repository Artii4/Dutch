#include "headers.h"

AST::AST() = default;

AST::AST(AST_type type) {
	this->type = type;
}

AST::AST(AST_type, std::string value) {
	this->type = type;
	this->value = value;
}

void AST::add_child(AST child) {
	children.push_back(child);
}

AST_type AST::get_type() {
	return type;
}

std::string AST::get_value() {
	return value;
}

AST AST::at(int index) {
	return children[index];
}
