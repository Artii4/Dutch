#include "headers.h"
#include <cassert>

Token::Token(Token_type type) {
  this->type = type;
  this->value = type_to_string(type);
}

Token::Token(Token_type type, std::string value) {
  this->type = type;
  this->value = value;
}

Token::Token() = default;

std::string Token::type_to_string(Token_type type) {
  switch (type) {
  case PLUS:
    return "PLUS";
  case MINUS:
    return "MINUS";
  case TIMES:
    return "TIMES";
  case DIVIDE:
    return "DIVIDE";
  case NUMBER:
    return "NUMBER";
  case NAME:
    return "NAME";
  case SEMICOLON:
    return "SEMICOLON";
  case LPAREN:
    return "LPAREN";
  case RPAREN:
    return "RPAREN";
  case LAAT:
    return "LAAT";
  case HET:
    return "HET";
  case ZIJN:
    return "ZIJN";
  case PRINT:
    return "PRINT";
  case UIT:
    return "UIT";
  case EN:
    return "EN";
  case END:
    return "END";
  default:
    assert(false);
  }
}

std::string Token::to_string() {
  std::string result;

  result += "<type: ";
  result += type_to_string(type);
  result += "; value: ";
  result += value;
  result += ">";

  return result;
}

Token_type Token::get_type() { return type; }
std::string Token::get_value() { return value; }
