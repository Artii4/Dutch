#pragma once
#include <string>
#include <vector>

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

enum class AST_type {
  PLUS,
  MINUS,
  TIMES,
  DIVIDE,

  NUMBER,
  NAME,
	HET,

  ASSIGNMENT,
  PRINT,

  // This is the parent node of all nodes in a program
  PROGRAM
};

class AST {
  std::vector<AST> children;
  std::string value;
  AST_type type;

public:
	AST();
  AST(AST_type);
	AST(AST_type, std::string value);

	void add_child(AST);

	AST at(int);
	AST_type get_type();
	std::string get_value();
};

// This class converts tokens into an abstract syntax tree
class Parser {
public:
  Parser(Lexer);
  Parser(std::string);
  Parser();

  AST parse();

private:
	// Helper functions
	void consume();
	Token expect(Token_type);

	// GRAMMAR RULES

	// A program is a collection of one or more statements
	AST program();
	// A statement is an assignment or print-command
	AST statement();

	// Two possible kinds of statements
	AST assignment();
	AST print(); 

	// Expression is mul, mul - expression, or mul + expression
	AST expression();

	// Mul is value * mul, value / mul, or simply value
	AST mul();

	// Name, 'het', or number
	AST value();


  Token lookahead;
  Lexer input;
};

class Interpreter {
public:
  Interpreter();

  // Interpret the abstract syntax tree and return the output buffer
  std::string interpret(AST);

private:
  std::string output;
};
