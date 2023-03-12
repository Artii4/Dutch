#include "headers.h"
#include <exception>
#include <stdexcept>

Lexer::Lexer(std::string input) {
  this->input = input;

  this->index = -1;
  consume();
}

Lexer::Lexer() = default;

void Lexer::consume() {
  lookahead = ++index < input.length() ? input[index] : EOF;
}

Token Lexer::word() {
  // Collect the characters into a string buffer
  std::string buf;
  while (isalpha(lookahead)) {
    buf += lookahead;
    consume();
  }

  // Checking for keywords
  if (buf == "laat")
    return {LAAT};
  if (buf == "het")
    return {HET};
  if (buf == "zijn")
    return {ZIJN};
  if (buf == "print")
    return {PRINT};
  if (buf == "uit")
    return {UIT};
  if (buf == "en")
    return {EN};

  // If not a keyword, return an ordinary name token
  return {NAME, buf};
}

Token Lexer::number() {
  std::string buf;
  while (isdigit(lookahead) || lookahead == '.') {
    buf += lookahead;
    consume();
  }

  return {NUMBER, buf};
}

Token Lexer::next_token() {
  skip_spaces();

  switch (lookahead) {
  case '+':
    consume();
    return {PLUS};
  case '-':
    consume();
    return {MINUS};
  case '*':
    consume();
    return {TIMES};
  case '/':
    consume();
    return {DIVIDE};
  case '(':
    consume();
    return {LPAREN};
  case ')':
    consume();
    return {RPAREN};
  case ';':
    consume();
    return {SEMICOLON};
  case EOF:
    return {END};
  default:
    if (isalpha(lookahead))
      return word();
    else if (isdigit(lookahead))
      return number();
    else
      throw std::runtime_error("Invalid character");
  }
}

void Lexer::skip_spaces() {
  while (isspace(lookahead))
    consume();
}
