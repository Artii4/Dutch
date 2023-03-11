#pragma once
#include <string>

enum Token_type {
  // Operators
  PLUS,
  MINUS,
  TIMES,
  DIVIDE,

  // Identifiers
  NUMBER,
  NAME,

  SEMICOLON,
  LPAREN,
  RPAREN,

  // Keywords
  LAAT,
  HET,
  ZIJN,
  PRINT,
  UIT,
  EN,

  END
};

class Token {
public:
  Token(Token_type);
  Token(Token_type, std::string value);
  Token();

  Token_type get_type();
  std::string get_value();

  std::string to_string();
  static std::string type_to_string(Token_type type);

private:
  Token_type type;
  std::string value;
};

// Convert raw input into tokens
class Lexer {
public:
  Lexer(std::string);
  Lexer();

  Token next_token();

private:
	void consume();
	void skip_spaces();

	Token word();
	Token number();

  char lookahead;
  int index;
  std::string input;
};
